/**
 * @file osal_msgq.h
 * @author Sunny Gupta
 * @brief 
 * @version 0.1
 * @date 2022-01-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef SRC_OSAL_INCLUDE_OSAL_MSGQ_H_
#define SRC_OSAL_INCLUDE_OSAL_MSGQ_H_

#define MESSAGE_Q_MAX_MESSAGES      10
#define MESSAGE_Q_MAX_MESSAGE_SIZE  256

I4 mbeCreateMessageQ(const char *name, I4 flags, MODE mode);
I4 mbeDeleteMessageQ(const char *name, I4 mqdes);
I4 mbeSendMessageToMsgQ(I4 mqdes, const char *message, I4 msg_len);
I4 mbeReceiveMessageFromMsgQ(I4 mqdes, PI1 message);

#endif /* SRC_OSAL_INCLUDE_OSAL_MSGQ_H_ */