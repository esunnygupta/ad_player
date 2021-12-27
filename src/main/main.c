/*
 * main.c
 *
 *  Created on: 23-Mar-2018
 *      Author: root
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#include <mosquitto.h>

#include <logs.h>
#include <version.h>
#include <osal_type.h>
#include <osal_list.h>
#include <app.h>

TASK_ID gAppMainTaskID;
//SEM gSemaphore;

VOID cleanup()
{
	I2 retval;
	
	retval = mosquitto_lib_cleanup();
	if (retval < 0)
	{
		mprintf("mosquitto library cleanup failed...\n");
	}
}

PVOID mbeAppMainTask()
{
	I2 retval;
	mprintf("init...\n");
	
	// TODO: System and network check. Raise error if any issue.

	retval = mosquitto_lib_init();
	if (retval != MOSQ_ERR_SUCCESS)
	{
		mprintf("mosquitto library initialization failed...\n");
		return NULL;
	}
	mprintf("exit...\n");

	return NULL;
}

VOID appExit()
{
	I2 retval;

	retval = mbeOSALtaskJoin(gAppMainTaskID);
	if(retval < 0)
	{
		mprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gAppMainTaskID);
}

VOID appInit()
{
	I2 ret;
	MBEOSAL_TASK_CREATE_STRUCT *stTaskCreate;

	//sem_init(&gSemaphore, 0, 1);
	stTaskCreate = (MBEOSAL_TASK_CREATE_STRUCT *)malloc(sizeof(MBEOSAL_TASK_CREATE_STRUCT));
	if(NULL == stTaskCreate)
	{
		mprintf("malloc() failed...\n");
		return;
	}
	stTaskCreate->task_name = mbeAppMainTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		mprintf("MBEAPP_mainTask not created\n");
	}
	gAppMainTaskID = stTaskCreate->task_id;
}

int main(int argc, char *argv[])
{
	mprintf("%s-v%s init...\n", PROJECT, VERSION);
	appInit();
	app();
	appExit();
	cleanup();
	mprintf("%s-v%s exit...\n", PROJECT, VERSION);

	return 0;
}
