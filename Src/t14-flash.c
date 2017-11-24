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

void FLASH_ERASE(){
	HAL_FLASH_Unlock();

	/* Fill EraseInit structure************************************************/
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
	EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR)/FLASH_PAGE_SIZE;

	HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
	HAL_FLASH_Lock();
}

void FLASH_WRITE(uint32_t WriteAddress, uint32_t WriteData)
{
	HAL_FLASH_Unlock();

	/* The selected pages are not write protected *******************************/
	if ((OptionsBytesStruct.WRPPage & FLASH_PAGE_TO_BE_PROTECTED) != 0x00)
	{

//		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
//		{
//		/*
//			Error occurred while page erase.
//			User can add here some code to deal with this error.
//			PageError will contain the faulty page and then to know the code error on this page,
//			user can call function 'HAL_FLASH_GetError()'
//			*/
//			while (1)
//			{
//				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
//				HAL_Delay(300);
//			}
//		}

		/* FLASH Word program of DATA_32 at addresses defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */

//		for (int i = 0; i < length; i++)
//		{

//			*(__IO uint32_t*)WriteAddress = Data;
//			WriteAddress = WriteAddress + 4;
//			WriteData++;


			if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddress, WriteData) == HAL_OK)
			{
//				WriteAddress = WriteAddress + 4;
//				WriteData++;
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

//		}

	}
	else
	{
//		/* The desired pages are write protected */
//		/* Check that it is not allowed to write in this page */
//		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddress, WriteData++) != HAL_OK)
//		{
//			/* Error returned during programmation. */
//			/* Check that WRPERR flag is well set */
//			if (HAL_FLASH_GetError() == HAL_FLASH_ERROR_WRP)
//			{
//				MemoryProgramStatus = FAILED;
//			}
//			else
//			{
//				/* Another error occurred.
//				 User can add here some code to deal with this error */
//				while (1)
//				{
//					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
//					HAL_Delay(300);
//				}
//			}
//		}
//		else
//		{
//			/* Write operation is successful. Should not occur
//			User can add here some code to deal with this error */
//			while (1)
//			{
//				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
//				HAL_Delay(300);
//			}
//		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();
}

void FLASH_READ(uint32_t ReadAddress, uint32_t* ReadData)
{
	HAL_FLASH_Unlock();

	ReadData = ((__IO uint32_t*) ReadAddress);

	//ReadData = ((__IO uint32_t*) ReadAddress);
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



//void FLASH_WRITE_VALUE(uint32_t ValueAddress, float value)
//{
//	uint8_t length = 0;
//	uint8_t l = 0;
//	uint32_t arr[32];
//
//	uint32_t value_c_length = 10;
//	uint32_t value_c[value_c_length];
//
//	uint32_t value_dec = (uint32_t)value;
//	uint32_t value_fr = (uint32_t) (( value - (uint32_t)(value) ) * 1000 );
////	//uint32_t value_tmp =
////	float value_fr_f = 0;
////	uint32_t value_fr = 0;
////	int j = 1;
////	uint32_t multiplier = 1;
////	do {
////		value_fr_f = (( value - (uint32_t)(value) ) * multiplier );
////		value_fr = (uint32_t)value_fr_f;
////		multiplier *= 10;
////	} while (value_fr_f != value_fr);
//
//
//	if (value_dec == 0){
//		arr[length] = hextoascii(0); //
//		length++;
//	} else {
//		l=0;
//		while(value_dec != 0)
//		{
//			value_c[l] = hextoascii(value_dec%10);//
//			value_dec /= 10;// n = n/10
//			l++;
//		}
//
//		for (int i = 0; i < l; i++){
//			arr[length] = value_c[l-i-1];
//			length++;
//		}
//	}
//
//	arr[length] = 0x2E;
//	length++;
//
//	if (value_fr == 0){
//		arr[length] = (0);// hextoascii
//		length++;
//	} else {
//		l=0;
//		while(value_fr != 0)
//		{
//			value_c[l] = hextoascii(value_fr%10);//
//			value_fr /= 10;// n = n/10
//			l++;
//		}
//
//		for (int i = 0; i < l; i++){
//			arr[length] = value_c[l-i-1];
//			length++;
//		}
//	}
//
//	arr[length] = 0x0A;
//	length++;
//	uint32_t *parr = arr;
//
//	FLASH_WRITE(ValueAddress, parr, length);
//}
//
//float FLASH_READ_VALUE(uint32_t ValueAddress)
//{
//	uint8_t length = 0;
//	uint8_t l1, l2 = 0;
//	uint32_t arr[32];
//	uint8_t arr_dec[32];
//	uint8_t arr_fr[32];
//
//	uint8_t point = 0;
//	uint32_t value_dec = 0;
//	uint32_t value_fr = 0;
//
//	float result = 0.0f;
//
//	uint8_t i = 0;
//
//	HAL_FLASH_Unlock();
//	do{
//		//FLASH_READ(ValueAddress, ReadData);
//		arr[length] = (*(__IO uint32_t*) ValueAddress);
//		//ReadData = ((__IO uint32_t*) ReadAddress);
//		ValueAddress = ValueAddress + 4;
//		//arr[j] = *ReadData;
//		length++;
//	} while ((arr[length] != 0x0A) && (length < 50));
//	HAL_FLASH_Lock();
//
//	if (length < 50)
//	{
//		for (i = 0; i < length; i++)
//		{
//			if (point == 0){
//				if (arr[i] == 0x2E){
//					point = i+1;
//				} else {
//					arr_dec[i] = (arr[i]); //asciitohex
//					l1++;
//				}
//			} else {
//				arr_fr[i - point] = (arr[i]); //asciitohex
//				l2++;
//			}
//		}
//
//
//		uint8_t arr1[l1];
//		uint8_t arr2[l2];
//		for (i = 0; i < l1; i++) {
//			arr1[i] = arr_dec[i];
//		}
//		for (i = 0; i < l2; i++) {
//			arr2[i] = arr_fr[i];
//		}
//
//		sscanf(arr_dec, "%d", &value_dec);
//		sscanf(arr_fr, "%d", &value_fr);
//
//		float divider = 1.0;
//		for (int i = 0; i < l2; i++) {
//			divider *= 10.0;
//		}
//
//		result = ((float)value_dec + (float)(value_fr / divider));
//	}
//
//	return result;
//
//}
