/*
 * mongoc.c
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */


#include <stdio.h>
#include <stdlib.h>

#include <mongoc/mongoc.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>
#include <osal_thread.h>
#include <osal_msgq.h>
#include <hw_info.h>
#include <app_mongoc.h>

TASK_ID gMongoCTaskID;
mongoc_client_t *gMongoClient;

VOID mbeMongoCInit()
{
	// I2 retval;
	mongoc_uri_t *uri;
	mongoc_client_t *client;
	bson_error_t error;

	mprintf("init...\n");

	// Mongo C library initialization
	mongoc_init();

	uri = mongoc_uri_new_with_error(MONGO_URL, &error);
	if (!uri)
	{
		eprintf("Failed to parse URI, Error: %s\n", error.message);
		return;
	}

	client = mongoc_client_new_from_uri(uri);
	if (!client)
	{
		eprintf("Failed to connect to Mongo DB.\n");
		return;
	}
	gMongoClient = client;
	mprintf("exit...\n");

	return;
}

PVOID mbeMongoCTask()
{
	// I2 retval;
	mongoc_uri_t *uri;
	mongoc_client_t *client;
	bson_error_t error;

	mprintf("init...\n");
	uri = mongoc_uri_new_with_error(MONGO_URL, &error);
	if (!uri)
	{
		eprintf("Failed to parse URI, Error: %s\n", error.message);
		return NULL;
	}

	client = mongoc_client_new_from_uri(uri);
	if (!client)
	{
		eprintf("Failed to connect to Mongo DB.\n");
		return NULL;
	}
	mprintf("exit...\n");

	return NULL;
}

VOID mbeMongoCTaskCreate()
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
	stTaskCreate->task_name = mbeMongoCTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask not created\n");
	}
	gMongoCTaskID = stTaskCreate->task_id;
	//mprintf("exit...\n");
}

VOID mbeMongoCTaskDelete()
{
	I2 ret;

	//mprintf("init...\n");
	ret = mbeOSALtaskJoin(gMongoCTaskID);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gMongoCTaskID);
	//mprintf("exit...\n");
}
