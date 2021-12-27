/*
 * hw_info.h
 *
 *  Created on: 31-Oct-2018
 *      Author: sunny
 */

#ifndef SRC_MAIN_INCLUDE_HW_INFO_H_
#define SRC_MAIN_INCLUDE_HW_INFO_H_

#define SERIAL_NO	"1501MBE8S2301"
#define CHIP_ID		"728928"

typedef struct MBEMAIN_hwInfoStruct
{
	UI1 serialNo[16];
	UI1 chipId[12];
}MBEMAIN_HW_INFO_STRUCT;

#endif /* SRC_MAIN_INCLUDE_HW_INFO_H_ */
