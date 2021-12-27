/*
 * subscriber.c
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */


#include <stdio.h>
#include <stdlib.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>

TASK_ID gSubscriberTaskID;

PVOID mbeSubscriberTask()
{
	// I2 retval;
	mprintf("init...\n");
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
