/*
 * t14-flash.h
 *
 *  Created on: 23 но€б. 2017 г.
 *      Author: Dima
 */

#ifndef INC_T14_FLASH_H_
#define INC_T14_FLASH_H_

#include "stm32f0xx_hal.h"


/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/

/* Uncomment this line to Enable Write Protection */
//#define WRITE_PROTECTION_ENABLE

/* Uncomment this line to Disable Write Protection */
#define WRITE_PROTECTION_DISABLE
#define ADDR_FLASH_PAGE_32  0x08010000 /* Start @ of user Flash area */
#define ADDR_FLASH_PAGE_33  0x08010800 /* End @ of user Flash area */
#define FLASH_USER_START_ADDR       ADDR_FLASH_PAGE_32   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR         ADDR_FLASH_PAGE_33   /* End @ of user Flash area */
#define FLASH_PAGE_TO_BE_PROTECTED (OB_WRP_PAGES24TO25 | OB_WRP_PAGES26TO27)

#define DATA_32                     ((uint32_t)0x12345678)

//uint32_t Address = 0;
uint32_t PageError;
__IO TestStatus MemoryProgramStatus;
/*Variable used for Erase procedure*/
static FLASH_EraseInitTypeDef EraseInitStruct;
/*Variable used to handle the Options Bytes*/
static FLASH_OBProgramInitTypeDef OptionsBytesStruct;

#endif /* INC_T14_FLASH_H_ */
