/*
 * subscriber.c
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */


#include <stdio.h>
#include <stdlib.h>

#include <mosquitto.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>
#include <hw_info.h>
#include <subscriber.h>

TASK_ID gSubscriberTaskID;

VOID mbeSubscriberConnectCallback(struct mosquitto *mosq_client, PVOID obj, I4 rc)
{
	mprintf("Connect [%d]\n", rc);
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
	mprintf("Message: %s\n", (char *)mosq_message->payload);
}

PVOID mbeSubscriberTask()
{
	I2 retval;
	struct mosquitto *mosq_client;
	mprintf("init...\n");
	mosq_client = mosquitto_new(SERIAL_NO, true, NULL);
	if (mosq_client == NULL)
	{
		mprintf("Failed to create mosquitto client...\n");
		// Todo: Send event to exit app.
		return NULL;
	}
	mosquitto_connect_callback_set(mosq_client, mbeSubscriberConnectCallback);
	mosquitto_disconnect_callback_set(mosq_client, mbeSubscriberDisconnectCallback);
	mosquitto_subscribe_callback_set(mosq_client, mbeSubscriberSubscribeCallback);
	mosquitto_message_callback_set(mosq_client, mbeSubscriberMessageCallback);
	mosquitto_connect(mosq_client, MQTT_SERVER_IP, MQTT_SERVER_PORT, MQTT_CONNECTION_TIMEOUT);
	mosquitto_subscribe(mosq_client, NULL, MQTT_TOPIC, 0);
	retval = mosquitto_loop_forever(mosq_client, MQTT_CONNECTION_TIMEOUT, 1);
	if (retval != MOSQ_ERR_SUCCESS)
	{
		mprintf("Failed to block the subscriber forever...\n");
	}
	mosquitto_disconnect(mosq_client);
	mosquitto_destroy(mosq_client);
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
		mprintf("malloc() failed...\n");
		return;
	}
	stTaskCreate->task_name = mbeSubscriberTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		mprintf("MBEAPP_mainTask not created\n");
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
		mprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gSubscriberTaskID);
	//mprintf("exit...\n");
}
