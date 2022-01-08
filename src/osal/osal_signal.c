/**
 * @file osal_signal.c
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-01-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <mosquitto.h>

#include <logs.h>
#include <osal_type.h>
#include <osal_signal.h>
#include <osal_msgq.h>

extern I4 gMessageQdescriptor;
extern struct mosquitto *mosq_client;

VOID mbeSigIntHandler(I4 signum)
{
    I4 retval;
    const char message_q_name[8] = "/main_q";

    mprintf("Signal Captured\n");

    retval = mbeDeleteMessageQ(message_q_name, gMessageQdescriptor);
    if (retval < 0)
    {
        eprintf("Program exiting with error.\n");
        eprintf("Please delete message q manually.\n");
    }
    mosquitto_disconnect(mosq_client);
	mosquitto_destroy(mosq_client);
}

VOID mbeRegisterSignalHandler(I4 signum, SIGHANDLER handler)
{
    if (signal(signum, handler) == SIG_ERR)
    {
        eprintf("Signal Handler registration failed for %d signal.\n", signum);
    }
}