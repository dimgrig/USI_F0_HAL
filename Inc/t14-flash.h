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
//#define FLASH_PAGE_SIZE 0x00000800
#define ADDR_FLASH_PAGE_56  0x0801C000 /* Start @ of user Flash area */
#define ADDR_FLASH_PAGE_58  0x0801D800 /* End @ of user Flash area */
#define FLASH_USER_START_ADDR       ADDR_FLASH_PAGE_56   /* Start @ of user Flash area */
#define FLASH_USER_END_ADDR         ADDR_FLASH_PAGE_58   /* End @ of user Flash area */
#define FLASH_PAGE_TO_BE_PROTECTED (OB_WRP_PAGES24TO25 | OB_WRP_PAGES26TO27 | OB_WRP_PAGES56TO57 | OB_WRP_PAGES58TO59 )

#define DATA_32                     ((uint32_t)0x12345678)

#define FLASH_CALIBRATION_INIT_Address FLASH_USER_START_ADDR + 0x00000000
#define FK_Address FLASH_USER_START_ADDR + 0x00000100
#define FB_Address FLASH_USER_START_ADDR + 0x00000150
#define AK_Address FLASH_USER_START_ADDR + 0x00000200
#define AB_Address FLASH_USER_START_ADDR + 0x00000250
#define FF_Address FLASH_USER_START_ADDR + 0x00000300
#define Ktor_Address FLASH_USER_START_ADDR + 0x00000350
#define Mtor_Address FLASH_USER_START_ADDR + 0x00000400


#define FLASH_MATERIAL_INIT_Address FLASH_USER_START_ADDR + FLASH_PAGE_SIZE

//uint32_t Address = 0;
uint32_t PageError;
__IO TestStatus MemoryProgramStatus;
/*Variable used for Erase procedure*/
static FLASH_EraseInitTypeDef EraseInitStruct;
/*Variable used to handle the Options Bytes*/
static FLASH_OBProgramInitTypeDef OptionsBytesStruct;

void FLASH_INIT();
void FLASH_CALIBRATION_ERASE();
void FLASH_MATERIAL_ERASE();
void FLASH_READ(uint32_t ReadAddress, uint32_t* ReadData);
void FLASH_WRITE_VALUE(uint32_t ValueAddress, uint32_t value);
uint32_t FLASH_READ_VALUE(uint32_t ValueAddress);
void FLASH_WRITE_CALIBRATION();
void FLASH_READ_CALIBRATION();
void FLASH_WRITE_MATERIAL();
void FLASH_READ_MATERIAL();

#endif /* INC_T14_FLASH_H_ */
