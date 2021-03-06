/*
 * osal_thread.c
 *
 *  Created on: 29-Mar-2018
 *      Author: sunny
 */

#include <stdio.h>
#include <pthread.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>
#include <osal_thread.h>

UI8 gTaskId = 0;
MBEOSAL_TASK_LIST_STRUCT *stTaskList = NULL;

I2 mbeOSALtaskCreate(MBEOSAL_TASK_CREATE_STRUCT *stTaskCreate)
{
	I2 ret;

	//mprintf("init...\n");
	stTaskCreate->task_id = gTaskId;
	ret = pthread_create(&(stTaskCreate->task_id), NULL, stTaskCreate->task_name, NULL);
	if(ret < 0)
	{
		eprintf("Failed[%d]\n",ret);
		return MBEOSAL_TYPE_FAILURE;
	}
	else
	{
		mprintf("TaskID [%lu]\n", stTaskCreate->task_id);
		gTaskId++;
		mbeOSALaddTask(&stTaskList, stTaskCreate);
	}
	//mprintf("exit...\n");

	return MBEOSAL_TYPE_SUCCESS;
}

I2 mbeOSALtaskJoin(TASK_ID ui4task_id)
{
	I2 ret;

	//mprintf("init...\n");
	ret = pthread_join(ui4task_id, NULL);
	if(ret < 0)
	{
		eprintf("Failed[%d]\n",ret);
		return MBEOSAL_TYPE_FAILURE;
	}
	else
	{
		gTaskId--;
	}
	//mprintf("exit...\n");

	return MBEOSAL_TYPE_SUCCESS;
}
