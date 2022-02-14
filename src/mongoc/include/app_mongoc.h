/*
 * app_mongoc.h
 *
 *  Created on: 01-Oct-2018
 *      Author: sunny
 */

#ifndef SRC_MONGOC_INCLUDE_MONGOC_H_
#define SRC_MONGOC_INCLUDE_MONGOC_H_

#define MONGO_URL                   "mongodb://localhost:27017"
#define MONGO_DATABASE              "ad_local"
#define MONGO_SCHEDULE_COLLECTION   "schedules"

VOID mbeMongoCTaskCreate();
VOID mbeMongoCTaskDelete();

VOID mbeMongoCInit();

#endif /* SRC_MONGOC_INCLUDE_MONGOC_H_ */
