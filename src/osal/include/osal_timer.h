/**
 * @file osal_timer.h
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-02-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SRC_OSAL_INCLUDE_OSAL_TIMER_H_
#define SRC_OSAL_INCLUDE_OSAL_TIMER_H_

TIMER mbeOSALtimerCreate();
I2 mbeOSALarmTimer(TIMER timerId, UI4 seconds);
I2 mbeOSALtimerDelete(TIMER timerId);

#endif /* SRC_OSAL_INCLUDE_OSAL_TIMER_H_ */