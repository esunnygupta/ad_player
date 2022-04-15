/**
 * @file campaign.c
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-02-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#include <curl/curl.h>
#include <cjson/cJSON.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_http.h>
#include <hw_info.h>
#include <campaign.h>

VOID mbeGetCampaigns()
{
	PI1 out;
	cJSON *json = NULL;
	MBEOSAL_HTTP_CREATE_STRUCT response;
	I1 url[] = "http://3.109.20.0/api/campaign";

	mprintf("init...\n");
	
	mbeOSALHttpCreate(url, &response);

	json = cJSON_Parse((const char *)response.memory);
	out = cJSON_Print(json);
	cJSON_Delete(json);
	mprintf("json:\n%s\n", out);

	free(response.memory);
	
	mprintf("exit...\n");
	return;
}