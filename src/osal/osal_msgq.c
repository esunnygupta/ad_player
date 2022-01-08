/**
 * @file osal_msgq.c
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-01-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_msgq.h>

I4 mbeCreateMessageQ(const char *name, I4 flags, MODE mode)
{
    mqd_t mqfd;
    struct mq_attr attributes;

    attributes.mq_maxmsg = MESSAGE_Q_MAX_MESSAGES;
    attributes.mq_msgsize = MESSAGE_Q_MAX_MESSAGE_SIZE;

    mqfd = mq_open(name, flags, mode, &attributes);
    if (mqfd < 0)
    {
        eprintf("message queue creation failed. Error [%d]\n", mqfd);
        return MBEOSAL_TYPE_FAILURE;
    }

    return mqfd;
}

I4 mbeDeleteMessageQ(const char *name, I4 mqdes)
{
    I4 ret;

    ret = mq_close(mqdes);
    if (ret < 0)
    {
        eprintf("Invalid message q descriptor.\n");
        return MBEOSAL_TYPE_FAILURE;
    }

    ret = mq_unlink(name);
    if (ret < 0)
    {
        eprintf("No message q found with name: %s\n", name);
        return MBEOSAL_TYPE_FAILURE;
    }

    return MBEOSAL_TYPE_SUCCESS;
}

I4 mbeSendMessageToMsgQ(I4 mqdes, const char *message, I4 msg_len)
{
    I4 ret;
    struct mq_attr attributes;

    ret = mq_getattr(mqdes, &attributes);
    if (ret < 0)
    {
        eprintf("Failed to fetch Message Q attributes.\n");
        return MBEOSAL_TYPE_FAILURE;
    }

    if (attributes.mq_curmsgs > MESSAGE_Q_MAX_MESSAGES)
    {
        eprintf("Message Q Full. Could not post more messages.\n");
        return MBEOSAL_TYPE_FAILURE;
    }

    if (message == NULL)
    {
        eprintf("Could not post empty message to message q.\n");
        return MBEOSAL_TYPE_FAILURE;
    }

    if (msg_len > attributes.mq_msgsize)
    {
        eprintf("Message length of message exceeds by %ld\n", (msg_len - attributes.mq_msgsize));
        return MBEOSAL_TYPE_FAILURE;
    }

    ret = mq_send(mqdes, message, msg_len, 0);
    if (ret < 0)
    {
        eprintf("Could not post message to message q.\n");
        return MBEOSAL_TYPE_FAILURE;
    }

    return MBEOSAL_TYPE_SUCCESS;
}

I4 mbeReceiveMessageFromMsgQ(I4 mqdes, PI1 message, I4 msg_len)
{
    I4 ret;
    I4 no_of_bytes;
    struct mq_attr attributes;

    ret = mq_getattr(mqdes, &attributes);
    if (ret < 0)
    {
        eprintf("Failed to fetch Message Q attributes.\n");
        return MBEOSAL_TYPE_FAILURE;
    }

    if (msg_len > attributes.mq_msgsize)
    {
        eprintf("Message length of message exceeds by %ld\n", (msg_len - attributes.mq_msgsize));
        return MBEOSAL_TYPE_FAILURE;
    }

    no_of_bytes = mq_receive(mqdes, message, msg_len, 0);
    if (no_of_bytes < 0)
    {
        eprintf("Message could not be received from message q.\n");
        return MBEOSAL_TYPE_FAILURE;
    }
    else
    {
        mprintf("Message received of %d bytes.\n", no_of_bytes);
    }

    return MBEOSAL_TYPE_SUCCESS;
}