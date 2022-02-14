/*
 * subscriber.c
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */


#include <stdio.h>
#include <stdlib.h>

#include <mosquitto.h>
#include <mongoc/mongoc.h>
#include <bson/bson.h>
#include <cjson/cJSON.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>
#include <osal_thread.h>
#include <osal_msgq.h>
#include <hw_info.h>
#include <subscriber.h>
#include <mpv_client.h>
#include <app_mongoc.h>

TASK_ID gSubscriberTaskID;
struct mosquitto *mosq_client;
extern I4 gMessageQdescriptor;
extern mongoc_client_t *gMongoClient;

VOID mbeSubscriberConnectCallback(struct mosquitto *mosq_client, PVOID obj, I4 rc)
{
	mprintf("Connect [%d]\n", rc);
	mosquitto_subscribe(mosq_client, NULL, MQTT_TOPIC, 0);
}

VOID mbeSubscriberDisconnectCallback(struct mosquitto *mosq_client, PVOID obj, I4 rc)
{
	mprintf("Disconnect [%d]\n", rc);
}

VOID mbeSubscriberSubscribeCallback(struct mosquitto *mosq_client, PVOID obj, I4 rc, I4 count, const int *grant)
{
	mprintf("Subscribe [%d] [%d]\n", rc, count);
}

VOID mbeSubscriberMessageCallback(struct mosquitto *mosq_client, PVOID obj, const struct mosquitto_message *mosq_message)
{
	mongoc_collection_t *collection;
	bson_error_t error;
	bson_oid_t oid;
	bson_t *doc;
	cJSON *json_data;
	cJSON *link_data;

	mprintf("Message: %s\n", (char *)mosq_message->payload);
	collection = mongoc_client_get_collection(gMongoClient, MONGO_DATABASE, MONGO_SCHEDULE_COLLECTION);
	doc = bson_new_from_json(mosq_message->payload, -1, &error);
	bson_oid_init(&oid, NULL);
	BSON_APPEND_OID(doc, "_id", &oid);
	if (!mongoc_collection_insert_one(collection, doc, NULL, NULL, &error))
	{
		eprintf("Failed to insert to database.\n");
	}
	bson_destroy(doc);
	mongoc_collection_destroy(collection);
	json_data = cJSON_Parse(mosq_message->payload);
	if (json_data == NULL)
	{
		const char *error = cJSON_GetErrorPtr();
		if (error != NULL)
		{
			eprintf("Error before: %s\n", error);
		}
	}
	link_data = cJSON_GetObjectItem(json_data, "link");
	if (link_data != NULL)
	{
		mprintf("Video Link: %s\n", link_data->valuestring);
		mbeSendMessageToMsgQ(gMessageQdescriptor, (const char *)link_data->valuestring, mosq_message->payloadlen);
	}
	cJSON_Delete(json_data);
}

PVOID mbeSubscriberTask()
{
	I2 retval;
	mprintf("init...\n");
	mosq_client = mosquitto_new(SERIAL_NO, true, NULL);
	if (mosq_client == NULL)
	{
		eprintf("Failed to create mosquitto client...\n");
		// Todo: Send event to exit app.
		return NULL;
	}
	mosquitto_connect_callback_set(mosq_client, mbeSubscriberConnectCallback);
	mosquitto_disconnect_callback_set(mosq_client, mbeSubscriberDisconnectCallback);
	mosquitto_subscribe_callback_set(mosq_client, mbeSubscriberSubscribeCallback);
	mosquitto_message_callback_set(mosq_client, mbeSubscriberMessageCallback);
	mosquitto_connect(mosq_client, MQTT_SERVER_IP, MQTT_SERVER_PORT, MQTT_CONNECTION_TIMEOUT);
	retval = mosquitto_loop_forever(mosq_client, -1, 1);
	if (retval != MOSQ_ERR_SUCCESS)
	{
		eprintf("Failed to block the subscriber forever...\n");
	}
	mprintf("exit...\n");

	return NULL;
}

VOID mbeSubscriberTaskCreate()
{
	I2 ret;
	MBEOSAL_TASK_CREATE_STRUCT *stTaskCreate;

	//mprintf("init...\n");
	stTaskCreate = (MBEOSAL_TASK_CREATE_STRUCT *)malloc(sizeof(MBEOSAL_TASK_CREATE_STRUCT));
	if(NULL == stTaskCreate)
	{
		eprintf("malloc() failed...\n");
		return;
	}
	stTaskCreate->task_name = mbeSubscriberTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask not created\n");
	}
	gSubscriberTaskID = stTaskCreate->task_id;
	//mprintf("exit...\n");
}

VOID mbeSubscriberTaskDelete()
{
	I2 ret;

	//mprintf("init...\n");
	ret = mbeOSALtaskJoin(gSubscriberTaskID);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gSubscriberTaskID);
	//mprintf("exit...\n");
}
