/*
 * main.c
 *
 *  Created on: 23-Mar-2018
 *      Author: Sunny Gupta
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <mosquitto.h>

#include <logs.h>
#include <version.h>
#include <osal_type.h>
#include <osal_list.h>
#include <osal_thread.h>
#include <osal_signal.h>
#include <osal_msgq.h>
#include <app.h>

TASK_ID gAppMainTaskID;
I4 gMessageQdescriptor;

VOID cleanup()
{
	I2 retval;
	
	retval = mosquitto_lib_cleanup();
	if (retval < 0)
	{
		eprintf("mosquitto library cleanup failed...\n");
	}
}

PVOID mbeAppMainTask()
{
	I2 retval;
	I4 mqdes;
	const char message_q_name[8] = "/main_q";

	mprintf("init...\n");
	
	// TODO: System and network check. Raise error if any issue.

	// Mosquitto library initialization
	retval = mosquitto_lib_init();
	if (retval != MOSQ_ERR_SUCCESS)
	{
		eprintf("mosquitto library initialization failed...\n");
	}

	// Register Signal Handler for SIGINT
	mbeRegisterSignalHandler(SIGINT, mbeSigIntHandler);

	// Create a Message Q for sending events.
	mqdes = mbeCreateMessageQ(message_q_name, O_CREAT | O_RDWR, 0660);
	gMessageQdescriptor = mqdes;

	mprintf("exit...\n");

	return NULL;
}

VOID appExit()
{
	I2 retval;

	retval = mbeOSALtaskJoin(gAppMainTaskID);
	if(retval < 0)
	{
		eprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gAppMainTaskID);
}

VOID appInit()
{
	I2 ret;
	MBEOSAL_TASK_CREATE_STRUCT *stTaskCreate;

	stTaskCreate = (MBEOSAL_TASK_CREATE_STRUCT *)malloc(sizeof(MBEOSAL_TASK_CREATE_STRUCT));
	if(NULL == stTaskCreate)
	{
		eprintf("malloc() failed...\n");
		return;
	}
	stTaskCreate->task_name = mbeAppMainTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask not created\n");
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
