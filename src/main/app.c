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

	// Authenticate Client
	mbeGetToken();

	// Set Media - Temporary Basis
	mbeSetMedia();

	// Create Tasks
	// mbeProtocolTaskCreate();
	mbeSubscriberTaskCreate();

	// Delete Tasks
	// mbeProtocolTaskDelete();
	mbeSubscriberTaskDelete();

	return 0;
}
