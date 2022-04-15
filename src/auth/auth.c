/*
 * auth.c
 *
 *  Created on: 31-Oct-2018
 *      Author: sunny
 */

#include <stdio.h>

#include <HTTPClient.h>
#include <cjson/cJSON.h>

#include <logs.h>
#include <osal_type.h>
#include <hw_info.h>
#include <auth.h>

VOID mbeGetAuthToken()
{
	PI1 out;
	cJSON *root = NULL;

	mprintf("init...\n");

	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "serial_id", cJSON_CreateString(SERIAL_NO));
	cJSON_AddTrueToObject(root, "is_active");

	out = cJSON_Print(root);
	cJSON_Delete(root);
	mprintf("%s\n", out);

	mprintf("exit...\n");
	return;
}
