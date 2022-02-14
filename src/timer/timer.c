/*
 * timer.c
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */


#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>
#include <osal_thread.h>
#include <osal_msgq.h>
#include <hw_info.h>
#include <timer.h>

TASK_ID gTimerTaskID;

PVOID mbeTimerTask()
{
	I2 retval;
	mprintf("init...\n");
	mprintf("exit...\n");

	return NULL;
}

VOID mbeTimerTaskCreate()
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
	stTaskCreate->task_name = mbeTimerTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask not created\n");
	}
	gTimerTaskID = stTaskCreate->task_id;
	//mprintf("exit...\n");
}

VOID mbeTimerTaskDelete()
{
	I2 ret;

	//mprintf("init...\n");
	ret = mbeOSALtaskJoin(gTimerTaskID);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gTimerTaskID);
	//mprintf("exit...\n");
}
