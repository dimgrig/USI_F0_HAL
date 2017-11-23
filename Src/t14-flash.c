/*
 * t14-flash.c
 *
 *  Created on: 23 но€б. 2017 г.
 *      Author: Dima
 */

#include "t14-flash.h"

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



void FLASH_WRITE(uint32_t WriteAddress, uint32_t WriteData)
{
	HAL_FLASH_Unlock();

	/* The selected pages are not write protected *******************************/
	if ((OptionsBytesStruct.WRPPage & FLASH_PAGE_TO_BE_PROTECTED) != 0x00)
	{
		/* Fill EraseInit structure************************************************/
		EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
		EraseInitStruct.PageAddress = FLASH_USER_START_ADDR;
		EraseInitStruct.NbPages     = (FLASH_USER_END_ADDR - FLASH_USER_START_ADDR)/FLASH_PAGE_SIZE;

		if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
		{
		/*
			Error occurred while page erase.
			User can add here some code to deal with this error.
			PageError will contain the faulty page and then to know the code error on this page,
			user can call function 'HAL_FLASH_GetError()'
			*/
			while (1)
			{
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
				HAL_Delay(300);
			}
		}

		/* FLASH Word program of DATA_32 at addresses defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */

		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddress, WriteData) == HAL_OK)
		{
			;//Address = Address + 4;
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
		/* The desired pages are write protected */
		/* Check that it is not allowed to write in this page */
		if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, WriteAddress, WriteData) != HAL_OK)
		{
			/* Error returned during programmation. */
			/* Check that WRPERR flag is well set */
			if (HAL_FLASH_GetError() == HAL_FLASH_ERROR_WRP)
			{
				MemoryProgramStatus = FAILED;
			}
			else
			{
				/* Another error occurred.
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
			/* Write operation is successful. Should not occur
			User can add here some code to deal with this error */
			while (1)
			{
				HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);
				HAL_Delay(300);
			}
		}
	}

	/* Lock the Flash to disable the flash control register access (recommended
	to protect the FLASH memory against possible unwanted operation) *********/
	HAL_FLASH_Lock();
}

void FLASH_READ(uint32_t ReadAddress, uint32_t *ReadData)
{
	HAL_FLASH_Unlock();

	*ReadData = (*(__IO uint32_t*) ReadAddress);

	HAL_FLASH_Lock();
}

