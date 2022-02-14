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
	UI8 http_result;
	PI1 out;
	HTTP_SESSION_HANDLE http_session;
	cJSON *root = NULL;

	root = cJSON_CreateObject();
	cJSON_AddItemToObject(root, "serial_id", cJSON_CreateString(SERIAL_NO));
	cJSON_AddTrueToObject(root, "is_active");

	out = cJSON_Print(root);
	cJSON_Delete(root);
	mprintf("%s\n", out);

	mprintf("init...\n");
	http_session = HTTPClientOpenRequest(0);
	http_result = HTTPClientSendRequest(http_session, "http://3.109.20.0/device", NULL, 0, 0, 0, 80);
	mprintf("HTTP Status Code: %ld\n", http_result);
	http_result = HTTPClientCloseRequest(&http_session);
	if (http_result != HTTP_CLIENT_SUCCESS)
	{
		eprintf("Failed to close http request.\n");
	}
	mprintf("exit...\n");
	return;
}
