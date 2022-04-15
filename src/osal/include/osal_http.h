/**
 * @file osal_http.h
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-04-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef SRC_OSAL_INCLUDE_OSAL_HTTP_H_
#define SRC_OSAL_INCLUDE_OSAL_HTTP_H_

typedef struct MBEOSAL_httpCreateStruct {
    I1 *memory;
    size_t size;
} MBEOSAL_HTTP_CREATE_STRUCT;

I4 mbeOSALHttpCreate(I1 *url, MBEOSAL_HTTP_CREATE_STRUCT *chunk);

#endif /* SRC_OSAL_INCLUDE_OSAL_HTTP_H_ */