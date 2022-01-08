/**
 * @file osal_signal.h
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-01-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SRC_OSAL_INCLUDE_OSAL_SIGNAL_H_
#define SRC_OSAL_INCLUDE_OSAL_SIGNAL_H_

VOID mbeRegisterSignalHandler(I4 signum, SIGHANDLER handler);
VOID mbeSigIntHandler(I4 signum);

#endif /* SRC_OSAL_INCLUDE_OSAL_SIGNAL_H_ */