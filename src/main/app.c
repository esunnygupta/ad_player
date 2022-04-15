/*
 * app.c
 *
 *  Created on: 30-Sep-2018
 *      Author: sunny
 */

#include <stdio.h>
#include <string.h>

#include <logs.h>
#include <osal_type.h>
#include <app.h>
#include <hw_info.h>
#include <client.h>
#include <subscriber.h>
#include <player.h>
#include <app_mongoc.h>
#include <auth.h>
#include <downloader.h>

MBEMAIN_FILE_INFO_STRUCT stFileInfo;

VOID mbeSetMedia()
{
	// strcpy(stFileInfo.filename, filename);
	// mprintf("filename: %s\n", stFileInfo.filename);
	return;
}

I2 app()
{
	// Initialize Client
	mbeMongoCInit();

	// Authenticate Client
	// mbeGetAuthToken();

	// Set Media - Temporary Basis
	// mbeSetMedia();

	// Create Tasks
	// mbeProtocolTaskCreate();
	mbeSubscriberTaskCreate();
	mbePlayerTaskCreate();
	mbeDownloaderTaskCreate();

	// Delete Tasks
	// mbeProtocolTaskDelete();
	mbeSubscriberTaskDelete();
	mbePlayerTaskDelete();
	mbeDownloaderTaskDelete();

	return 0;
}
