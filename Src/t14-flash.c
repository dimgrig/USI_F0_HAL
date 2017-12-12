/*
 * t14-flash.c
 *
 *  Created on: 23 но€б. 2017 г.
 *      Author: Dima
 */

#include "t14-flash.h"
#include "t14-usb.h"


void FLASH_INIT(){
 /* Initialize test status */
  MemoryProgramStatus = PASSED;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  /* Unlock the Options Bytes *************************************************/
  HAL_FLASH_OB_Unlock();

  /* Get pages write protection status ****************************************/
  HAL_FLASHEx_OBGetConfig(&OptionsBytesStruct);

#ifdef WRITE_PROTECTION_DISABLE
  /* Check if desired pages are already write protected ***********************/
  if((OptionsBytesStruct.WRPPage & FLASH_PAGE_TO_BE_PROTECTED) != FLASH_PAGE_TO_BE_PROTECTED)
  {
    /* Restore write protected pages */
    OptionsBytesStruct.OptionType   = OPTIONBYTE_WRP;
    OptionsBytesStruct.WRPState     = OB_WRPSTATE_DISABLE;
    OptionsBytesStruct.WRPPage = FLASH_PAGE_TO_BE_PROTECTED;
    if(HAL_FLASHEx_OBProgram(&OptionsBytesStruct) != HAL_OK)
    {
      /* Error occurred while options bytes programming. **********************/
      while (1)
      {
    	  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
    	  HAL_Delay(300);
      }
    }

    /* Generate System Reset to load the new option byte values ***************/
    HAL_FLASH_OB_Launch();
  }
#elif defined WRITE_PROTECTION_ENABLE
  /* Check if desired pages are not yet write protected ***********************/
  if(((~OptionsBytesStruct.WRPPage) & FLASH_PAGE_TO_BE_PROTECTED )!= FLASH_PAGE_TO_BE_PROTECTED)
  {
    /* Enable the pages write protection **************************************/
    OptionsBytesStruct.OptionType = OPTIONBYTE_WRP;
    OptionsBytesStruct.WRPState   = OB_WRPSTATE_ENABLE;
    OptionsBytesStruct.WRPPage    = FLASH_PAGE_TO_BE_PROTECTED;
    if(HAL_FLASHEx_OBProgram(&OptionsBytesStruct) != HAL_OK)
    {
      /* Error occurred while options bytes programming. **********************/
      while (1)
      {
        BSP_LED_On(LED3);
      }
    }

    /* Generate System Reset to load the new option byte values ***************/
    HAL_FLASH_OB_Launch();
  }
#endif /* WRITE_PROTECTION_DISABLE */

  /* Lock the Options Bytes *************************************************/
  HAL_FLASH_OB_Lock();
}

void FLASH_CALIBRATION_ERASE(){
	HAL_FLASH_Unlock();

	/* Fill EraseInit structure************************************************/
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = FLASH_USER_START_ADDR + FLASH_PAGE_SIZE * 0;
	//EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR)/FLASH_PAGE_SIZE;
	EraseInitStruct.NbPages     = 1;

	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	HAL_FLASH_Lock();
}

void FLASH_MATERIAL_ERASE(){
	HAL_FLASH_Unlock();

	/* Fill EraseInit structure************************************************/
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = FLASH_USER_START_ADDR + FLASH_PAGE_SIZE * 1;
	EraseInitStruct.NbPages     = 1;

	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	HAL_FLASH_Lock();
}

void FLASH_WRITE(uint32_t WriteAddress, uint32_t WriteData)
{
	HAL_FLASH_Unlock();

	/* The selected pages are not write protected *******************************/
	if ((OptionsBytesStruct.WRPPage & FLASH_PAGE_TO_BE_PROTECTED) != 0x00)
	{
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddress, WriteData) == HAL_OK)
		{
			;
		}
		else
		{
			/* Error occurred while writing data in Flash memory.
			 User can add here some code to deal with this error */
			while (1)
			{
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
				HAL_Delay(300);
			}
		}
	}
	else
	{
		;
	}

	/* Lock the Flash to disable the flash control register access (recommended
	to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();
}

void FLASH_WRITE_VALUE(uint32_t ValueAddress, uint32_t value)
{
	FLASH_WRITE(ValueAddress, value);
}

uint32_t FLASH_READ_VALUE(uint32_t ValueAddress)
{
	HAL_FLASH_Unlock();
	uint32_t result = (*(__IO uint32_t *) ValueAddress);
	HAL_FLASH_Lock();
	return result;
}

void FLASH_WRITE_CALIBRATION(){

  float WrittenValue = 0;
  uint32_t WrittenValue_int32 = 0;

  char data_[sizeof(float)] = {0x00, 0x00, 0x00, 0x00};

  FLASH_CALIBRATION_ERASE();

  WrittenValue = F1K;
  memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
  WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
  FLASH_WRITE_VALUE(FK_Address, WrittenValue_int32);
  //WrittenValue = 12540.3464;
  WrittenValue = F1B;
  memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
  WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
  FLASH_WRITE_VALUE(FB_Address, WrittenValue_int32);

  WrittenValue = A1K;
  memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
  WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
  FLASH_WRITE_VALUE(AK_Address, WrittenValue_int32);
  WrittenValue = A1B;
  memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
  WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
  FLASH_WRITE_VALUE(AB_Address, WrittenValue_int32);

  WrittenValue = F1F;
  memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
  WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
  FLASH_WRITE_VALUE(FF_Address, WrittenValue_int32);

  WrittenValue = Ktor;
  memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
  WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
  FLASH_WRITE_VALUE(Ktor_Address, WrittenValue_int32);

  WrittenValue = Mtor;
  memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
  WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
  FLASH_WRITE_VALUE(Mtor_Address, WrittenValue_int32);

  FLASH_WRITE_VALUE(FLASH_CALIBRATION_INIT_Address, 1);

  FLASH_READ_CALIBRATION();
}

void FLASH_READ_CALIBRATION(){
	uint32_t F1K_int32 = FLASH_READ_VALUE(FK_Address);
	uint32_t F1B_int32 = FLASH_READ_VALUE(FB_Address);
	uint32_t A1K_int32 = FLASH_READ_VALUE(AK_Address);
	uint32_t A1B_int32 = FLASH_READ_VALUE(AB_Address);
	uint32_t F1F_int32 = FLASH_READ_VALUE(FF_Address);
	uint32_t Ktor_int32 = FLASH_READ_VALUE(Ktor_Address);
	uint32_t Mtor_int32 = FLASH_READ_VALUE(Mtor_Address);

	char data_[sizeof(float)] = {0x00, 0x00, 0x00, 0x00};

	data_[0] = (F1K_int32>>0) & 0xFF;
	data_[1] = (F1K_int32>>8) & 0xFF;
	data_[2] = (F1K_int32>>16) & 0xFF;
	data_[3] = (F1K_int32>>24) & 0xFF;
	memcpy(&F1K, data_, sizeof(F1K));

	data_[0] = (F1B_int32>>0) & 0xFF;
	data_[1] = (F1B_int32>>8) & 0xFF;
	data_[2] = (F1B_int32>>16) & 0xFF;
	data_[3] = (F1B_int32>>24) & 0xFF;
	memcpy(&F1B, data_, sizeof(F1B));

	data_[0] = (A1K_int32>>0) & 0xFF;
	data_[1] = (A1K_int32>>8) & 0xFF;
	data_[2] = (A1K_int32>>16) & 0xFF;
	data_[3] = (A1K_int32>>24) & 0xFF;
	memcpy(&A1K, data_, sizeof(A1K));

	data_[0] = (A1B_int32>>0) & 0xFF;
	data_[1] = (A1B_int32>>8) & 0xFF;
	data_[2] = (A1B_int32>>16) & 0xFF;
	data_[3] = (A1B_int32>>24) & 0xFF;
	memcpy(&A1B, data_, sizeof(A1B));

	data_[0] = (F1F_int32>>0) & 0xFF;
	data_[1] = (F1F_int32>>8) & 0xFF;
	data_[2] = (F1F_int32>>16) & 0xFF;
	data_[3] = (F1F_int32>>24) & 0xFF;
	memcpy(&F1F, data_, sizeof(F1F));

	data_[0] = (Ktor_int32>>0) & 0xFF;
	data_[1] = (Ktor_int32>>8) & 0xFF;
	data_[2] = (Ktor_int32>>16) & 0xFF;
	data_[3] = (Ktor_int32>>24) & 0xFF;
	memcpy(&Ktor, data_, sizeof(Ktor));

	data_[0] = (Mtor_int32>>0) & 0xFF;
	data_[1] = (Mtor_int32>>8) & 0xFF;
	data_[2] = (Mtor_int32>>16) & 0xFF;
	data_[3] = (Mtor_int32>>24) & 0xFF;
	memcpy(&Mtor, data_, sizeof(Mtor));
}

void FLASH_WRITE_MATERIAL(){
	float WrittenValue = 0;
	uint32_t WrittenValue_int32 = 0;

	char data_[sizeof(float)] = {0x00, 0x00, 0x00, 0x00};

	FLASH_MATERIAL_ERASE();
	FLASH_WRITE_VALUE(FLASH_MATERIAL_INIT_Address, MATERIAL_CHOOSEN);

	for (int i=0, address = FLASH_MATERIAL_INIT_Address + 0x00000050; i < MATERIAL_SIZE ; i++) {
		WrittenValue = MATERIAL_STK[i];
		memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
		WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
		FLASH_WRITE_VALUE(address, WrittenValue_int32);
		address += 0x00000050;

		WrittenValue = MATERIAL_SBK[i];
		memcpy(data_, &WrittenValue, sizeof(WrittenValue));    // send data
		WrittenValue_int32 = (((data_[3]<<24)&0xff000000) | ((data_[2]<<16)&0xff0000) | ((data_[1]<<8)&0xff00) | ((data_[0]<<0)&0xff));
		FLASH_WRITE_VALUE(address, WrittenValue_int32);
		address += 0x00000050;
	}

	FLASH_READ_MATERIAL();
}

void FLASH_READ_MATERIAL(){
	char data_[sizeof(float)] = {0x00, 0x00, 0x00, 0x00};

	MATERIAL_CHOOSEN = FLASH_READ_VALUE(FLASH_MATERIAL_INIT_Address);

	for (int i=0, address = FLASH_MATERIAL_INIT_Address + 0x00000050; i < MATERIAL_SIZE ; i++) {
		uint32_t STK_int32 = FLASH_READ_VALUE(address);
		data_[0] = (STK_int32>>0) & 0xFF;
		data_[1] = (STK_int32>>8) & 0xFF;
		data_[2] = (STK_int32>>16) & 0xFF;
		data_[3] = (STK_int32>>24) & 0xFF;
		memcpy(&MATERIAL_STK[i], data_, sizeof(MATERIAL_STK[i]));
		address += 0x00000050;

		uint32_t SBK_int32 = FLASH_READ_VALUE(address);
		data_[0] = (SBK_int32>>0) & 0xFF;
		data_[1] = (SBK_int32>>8) & 0xFF;
		data_[2] = (SBK_int32>>16) & 0xFF;
		data_[3] = (SBK_int32>>24) & 0xFF;
		memcpy(&MATERIAL_SBK[i], data_, sizeof(MATERIAL_SBK[i]));
		address += 0x00000050;
	}

	STK = MATERIAL_STK[(int)MATERIAL_CHOOSEN - 210];
	SBK = MATERIAL_SBK[(int)MATERIAL_CHOOSEN - 210];
}
