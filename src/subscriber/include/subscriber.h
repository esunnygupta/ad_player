/*
 * subscriber.h
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */

#ifndef SRC_SUBSCRIBER_INCLUDE_SUBSCRIBER_H_
#define SRC_SUBSCRIBER_INCLUDE_SUBSCRIBER_H_

// #define MQTT_SERVER_IP                  "127.0.0.1"
#define MQTT_SERVER_IP                  "3.109.20.0"
#define MQTT_SERVER_PORT                1883
#define MQTT_CONNECTION_TIMEOUT         10

#define MQTT_TOPIC                      "/playlist"

VOID mbeSubscriberTaskCreate();
VOID mbeSubscriberTaskDelete();

#endif /* SRC_SUBSCRIBER_INCLUDE_SUBSCRIBER_H_ */
