/**
 * @file player.c
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-01-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>
#include <osal_thread.h>
#include <osal_msgq.h>
#include <mpv_client.h>
#include <player.h>

TASK_ID gPlayerTaskID;
extern I4 gMessageQdescriptor;

PVOID mbePlayerTask()
{
	PI1 message;
	volatile bool extFlag = true;

	message = (PI1) malloc(sizeof(I1) * MESSAGE_Q_MAX_MESSAGE_SIZE);
	if (message == NULL)
	{
		eprintf("Memory allocation failed.\n");
		return NULL;
	}
	do
	{
		memset(message, 0, MESSAGE_Q_MAX_MESSAGE_SIZE);
		mbeReceiveMessageFromMsgQ(gMessageQdescriptor, message);
		if (strcmp(message, "exit") == 0)
		{
			extFlag = false;
		}
		else 
		{
			mpv_main(message, NULL, NULL);
		}
	} while(extFlag);

	free(message);
	message = NULL;

    return NULL;
}

VOID mbePlayerTaskCreate()
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
	stTaskCreate->task_name = mbePlayerTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask not created\n");
	}
	gPlayerTaskID = stTaskCreate->task_id;
	//mprintf("exit...\n");
}

VOID mbePlayerTaskDelete()
{
	I2 ret;

	//mprintf("init...\n");
	ret = mbeOSALtaskJoin(gPlayerTaskID);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gPlayerTaskID);
	//mprintf("exit...\n");
}