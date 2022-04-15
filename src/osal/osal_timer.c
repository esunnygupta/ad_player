/**
 * @file osal_timer.c
 * @author Sunny Gupta
 * @brief
 * @version 0.1
 * @date 2022-02-28
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include <osal_type.h>
#include <osal_timer.h>
#include <logs.h>

TIMER mbeOSALtimerCreate(PVOID mbeTimerThread)
{
    I2 status;
    TIMER timerId;
    struct sigevent sevp;

    sevp.sigev_notify = SIGEV_THREAD;
    sevp.sigev_value.sival_ptr = &timerId;
    sevp.sigev_notify_function = mbeTimerThread;
    sevp.sigev_notify_attributes = NULL;

    status = timer_create(CLOCK_REALTIME, &sevp, &timerId);
    if (status == 0)
    {
        return timerId;
    }

    return NULL;
}

I2 mbeOSALarmTimer(TIMER timerId, UI4 seconds)
{
    I2 status;
    struct itimerspec ts;

    ts.it_value.tv_sec = seconds / 100;
    ts.it_value.tv_nsec = seconds % 100;
    ts.it_interval.tv_sec = 0;
    ts.it_interval.tv_nsec = 0;

    status = timer_settime(timerId, 0, &ts, NULL);

    return status;
}

I2 mbeOSALtimerDelete(TIMER timerId)
{
    I2 status;

    status = timer_delete(timerId);
    if (status != 0)
    {
        eprintf("Timer [%p] deletion failed.\n", timerId);
    }

    return status;
}