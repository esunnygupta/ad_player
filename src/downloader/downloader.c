/*
 * downloader.c
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_list.h>
#include <osal_timer.h>
#include <osal_thread.h>
#include <osal_msgq.h>
#include <hw_info.h>
#include <downloader.h>
#include <campaign.h>

TASK_ID gDownloaderTaskID;
MUTEX mutexDownloader = PTHREAD_MUTEX_INITIALIZER;
COND condDownloader = PTHREAD_COND_INITIALIZER;

VOID mbeDownloaderTimerThread(union sigval arg)
{
	pthread_mutex_lock(&mutexDownloader);
	pthread_cond_signal(&condDownloader);
	pthread_mutex_unlock(&mutexDownloader);

    mprintf("\n");
	mbeGetCampaigns();
}

PVOID mbeDownloaderTask()
{
	TIMER timerId;

	timerId = mbeOSALtimerCreate(mbeDownloaderTimerThread);
	mbeOSALarmTimer(timerId, 200);
	pthread_mutex_lock(&mutexDownloader);
	pthread_cond_wait(&condDownloader, &mutexDownloader);
	pthread_mutex_unlock(&mutexDownloader);
	mbeOSALtimerDelete(timerId);

	return NULL;
}

VOID mbeDownloaderTaskCreate()
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
	stTaskCreate->task_name = mbeDownloaderTask;
	ret = mbeOSALtaskCreate(stTaskCreate);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask not created\n");
	}
	gDownloaderTaskID = stTaskCreate->task_id;
	//mprintf("exit...\n");
}

VOID mbeDownloaderTaskDelete()
{
	I2 ret;

	//mprintf("init...\n");
	ret = mbeOSALtaskJoin(gDownloaderTaskID);
	if(ret < 0)
	{
		eprintf("MBEAPP_mainTask join failed\n");
	}
	mbeOSALdeleteTask(gDownloaderTaskID);
	//mprintf("exit...\n");
}
