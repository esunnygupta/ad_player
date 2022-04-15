/**
 * @file osal_http.c
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include <curl/curl.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_http.h>
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    MBEOSAL_HTTP_CREATE_STRUCT *mem = (MBEOSAL_HTTP_CREATE_STRUCT *)userp;
 
    I1 *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(!ptr) {
        /* out of memory! */
        eprintf("not enough memory (realloc returned NULL)\n");
        return 0;
    }
 
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
 
    return realsize;
}
 
I4 mbeOSALHttpCreate(I1 *url, MBEOSAL_HTTP_CREATE_STRUCT *chunk)
{
    CURL *curl_handle;
    CURLcode res;
 
    chunk->memory = (I1 *)malloc(sizeof(I1));  /* will be grown as needed by the realloc above */
    chunk->size = 0;    /* no data at this point */
 
    curl_global_init(CURL_GLOBAL_ALL);
 
    /* init the curl session */
    curl_handle = curl_easy_init();
 
    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
 
    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)chunk);
 
    /* some servers do not like requests that are made without a user-agent
        field, so we provide one */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
    /* get it! */
    res = curl_easy_perform(curl_handle);
 
    /* check for errors */
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    }
    else 
    {
        /*
         * Now, our chunk.memory points to a memory block that is chunk.size
         * bytes big and contains the remote file.
         *
         * Do something nice with it!
         */
 
        mprintf("%lu bytes retrieved\n", (unsigned long)chunk->size);
    }
 
    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
 
    /* we are done with libcurl, so clean it up */
    curl_global_cleanup();
 
    return 0;
}
