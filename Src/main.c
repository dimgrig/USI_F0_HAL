/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "stm32f0xx_hal.h"
#include "usb_device.h"
#include "userdef.h"

#include "t14-ssi.h"
#include "t14-usb.h"
#include "t14-math.h"

#include "FT_Platform.h"
#include "SampleApp.h"
#include "FT80x.h"

#include "t14-flash.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM2_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */


//#ifdef FILTERING
#define SPS 5000
#define Trc 0.001f
#define K (SPS*Trc)
static uint32_t Dacc = 0;
static uint32_t Dout = 0;
//#endif

uint16_t init_finished = 0;

Screen_TypeDef SCREEN = MAIN;
ft_uint16_t dloffset;
State_TypeDef STATE = IDLE;

double F = 0; //�������
double A = 0;
double E, HB, ST, SB = 0;

double F1 = 0; //���������
double A0 = 0; //�������
double A1 = 0; //���������
double H = 0; //������


#define DMA_BUFFER_SIZE 1024
uint16_t DMA_BUFFER[DMA_BUFFER_SIZE];

/* USER CODE END 0 */

void __attribute__ ((weak)) _init(void)  {}

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USB_DEVICE_Init();
  MX_ADC_Init();
  MX_SPI1_Init();
  MX_TIM2_Init();

  /* USER CODE BEGIN 2 */

//  float* ReaddenValue;
  FLASH_INIT();

  uint32_t FLASH_CALIBRATION_INIT_Data = (uint32_t)FLASH_READ_VALUE(FLASH_CALIBRATION_INIT_Address);
  uint32_t FLASH_MATERIAL_INIT_Data = (uint32_t)FLASH_READ_VALUE(FLASH_MATERIAL_INIT_Address);

  if ((FLASH_CALIBRATION_INIT_Data == 0xFFFFFFFF) || (0 == 1)) { //1==1 if manual
	  F1K = F1K_init;
	  F1B = F1B_init;
	  A1K = A1K_init;
	  A1B = A1B_init;
	  F1F = F1F_init;
	  Ktor = Ktor_init;
	  Mtor = Mtor_init;
	  STK = STK_init;
	  SBK = SBK_init;
	  FLASH_WRITE_CALIBRATION();
  } else {
	  FLASH_READ_CALIBRATION();
  }


  if ((FLASH_MATERIAL_INIT_Data == 0xFFFFFFFF) || (0 == 1)) { //1==1 if manual
	  MATERIAL_CHOOSEN = MATERIAL_init;
	  for (int i=0; i < MATERIAL_SIZE ; i++) {
		  MATERIAL_STK[i] = STK_init;
		  MATERIAL_SBK[i] = SBK_init;
	  }
	  FLASH_WRITE_MATERIAL();
  } else {
	  FLASH_READ_MATERIAL();
  }

  FT_APP_BootupConfig();
  dloffset = FT_APP_Screen_BasicScreen(SCREEN);

  uint16_t flag = 1;
  init_finished = 1;

  HAL_TIM_Base_Start_IT(&htim2);
  HAL_ADC_Start_DMA(&hadc,(uint32_t *)&DMA_BUFFER[0],DMA_BUFFER_SIZE);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
	  //HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_10);

	  uint8_t tag = ft800memRead8(REG_TOUCH_TAG);
	  uint8_t tag__ = 0;

	  if (tag != 0){

		  FT_APP_Screen_Content(SCREEN, STATE, tag, dloffset, F, A, A0, H, F1, A1, E, HB, ST, SB, init_finished);

		  switch (tag){
			case 1:
				switch (SCREEN){
					case MAIN:
						SCREEN = SETTINGS;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
					break;
					case SETTINGS:
						SCREEN = MAIN;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
					break;
					case MATERIAL:
						SCREEN = SETTINGS;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
					break;
					case CALIBRATION:
						SCREEN = SETTINGS;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
					break;
					case STEPPER:
						SCREEN = SETTINGS;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
					break;
				}
			break;
			case 2:
				switch (STATE)
				{
					case IDLE:
					  STATE = TOUCH;
					break;
					case TOUCH:
					  A0 = A;
					  STATE = MEASURE;
					break;
					case MEASURE:
					  F1 = F;//���������
					  A1 = A;
					  STATE = REMOVAL;
					break;
					case REMOVAL:
					  H = A;

					  T14math(&E, &ST, &SB, &HB, F1, A0, A1, H);
					  STATE = RESULTS;
					break;
					case RESULTS:
						//clear
					  STATE = TOUCH;
					break;
				}

				FT_APP_Screen_Content(SCREEN, STATE, tag, dloffset, F, A, A0, H, F1, A1, E, HB, ST, SB, init_finished);
				flag = 1;
			break;
			case 3:
				STATE = IDLE;
				FT_APP_Screen_Content(SCREEN, STATE, tag, dloffset, F, A, A0, H, F1, A1, E, HB, ST, SB, init_finished);
				flag = 0;
			break;
			case 4:
				switch (SCREEN){
					case MAIN:
					break;
					case SETTINGS:
						SCREEN = MATERIAL;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
						MATERIAL_PAGE = 0;
					break;
					case MATERIAL:
					break;
					case CALIBRATION:
					break;
					case STEPPER:
					break;
				}
			break;
			case 5:
				switch (SCREEN){
					case MAIN:
					break;
					case SETTINGS:
						SCREEN = CALIBRATION;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
					break;
					case MATERIAL:
					break;
					case CALIBRATION:
					break;
					case STEPPER:
					break;
				}
			break;
			case 6:
				switch (SCREEN){
					case MAIN:
					break;
					case SETTINGS:
						SCREEN = STEPPER;
						dloffset = FT_APP_Screen_BasicScreen(SCREEN);
					break;
					case MATERIAL:
					break;
					case CALIBRATION:
					break;
					case STEPPER:
					break;
				}
			break;
			case 21:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); //DIR
				while (tag != 0){
					tag = ft800memRead8(REG_TOUCH_TAG);
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13); //STEP
					HAL_Delay(100);
				}
			break;
			case 22:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); //DIR
				while (tag != 0){
					tag = ft800memRead8(REG_TOUCH_TAG);
					HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13); //STEP
					HAL_Delay(100);
				}
			break;
			case 98:
				MATERIAL_PAGE -= 1;
			break;
			case 99:
				MATERIAL_PAGE += 1;
			break;
			case 205:
				if (F1F == 1) {
					F1F = 0;
				} else {
					F1F = 1;
				}
				FLASH_WRITE_CALIBRATION();
			break;
			case 201:	case 202:	case 203:	case 204:	case 206:	case 207:
			//case 205:
			case 101:	case 102:	case 103:	case 104:	case 105:
			case 106:	case 107:	case 108:	case 109:	case 110:
			case 111:	case 112:	case 113:	case 114:	case 115:
			case 116:	case 117:	case 118:	case 119:	case 120:
			case 121:	case 122:	case 123:	case 124:	case 125:
			case 126:	case 127:	case 128:	case 129:	case 130:
				tag__ = tag;
				uint8_t length = 0;
				uint8_t arr[32];
				while (1){
					tag = ft800memRead8(REG_TOUCH_TAG);
					if  ((tag == 1) || (tag == 3)) {
						break;
					}
					Keyboard(tag, &arr[0], &length);
					while (tag != 0){
						tag = ft800memRead8(REG_TOUCH_TAG);
				    }
				}
				if (tag == 1) {
					;//cancel
				} else if (tag == 3) { //save new values
					if ((tag__ == 201) || (tag__ == 202) ||	(tag__ == 203) ||
						(tag__ == 204) || (tag__ == 206) || (tag__ == 207)){

						float user_entered = 0;
						char_array_to_float(&user_entered, &arr[0], length);

						switch (tag__){
							case 201:
								F1K = user_entered;
								FLASH_WRITE_CALIBRATION();
							break;
							case 202:
								F1B = user_entered;
								FLASH_WRITE_CALIBRATION();
							break;
							case 203:
								A1K = user_entered;
								FLASH_WRITE_CALIBRATION();
							break;
							case 204:
								A1B = user_entered;
								FLASH_WRITE_CALIBRATION();
							break;
							case 206:
								Ktor = user_entered;
								FLASH_WRITE_CALIBRATION();
							break;
							case 207:
								Mtor = user_entered;
								FLASH_WRITE_CALIBRATION();
							break;
						}
					}
					if ((tag__ == 101) || (tag__ == 102) ||	(tag__ == 103) || (tag__ == 104) || (tag__ == 105) ||
						(tag__ == 106) || (tag__ == 107) ||	(tag__ == 108) || (tag__ == 109) || (tag__ == 110) ||
						(tag__ == 111) || (tag__ == 112) ||	(tag__ == 113) || (tag__ == 114) || (tag__ == 115) ||
						(tag__ == 116) || (tag__ == 117) ||	(tag__ == 118) || (tag__ == 119) || (tag__ == 120) ||
						(tag__ == 121) || (tag__ == 122) ||	(tag__ == 123) || (tag__ == 124) || (tag__ == 125) ||
						(tag__ == 126) || (tag__ == 127) ||	(tag__ == 128) || (tag__ == 129) || (tag__ == 130) ){

						float user_entered = 0;
						char_array_to_float(&user_entered, &arr[0], length);

						uint8_t nmb = tag__ - 100 - 1;
						if (nmb%2 == 1) {
							MATERIAL_SBK[nmb/2] = user_entered;
						} else {
							MATERIAL_STK[nmb/2] = user_entered;
						}

						FLASH_WRITE_MATERIAL();
					}
				}
			break;
			case 210:	case 211:	case 212:	case 213:	case 214:
			case 215:	case 216:	case 217:	case 218:	case 219:
			case 220:	case 221:	case 222:	case 223:	case 224:
			case 225:	case 226:	case 227:	case 228:	case 229:
				MATERIAL_CHOOSEN = tag;
				FLASH_WRITE_MATERIAL();
			break;
		  }

		  while (tag != 0){
			  tag = ft800memRead8(REG_TOUCH_TAG);
		  }

	  } else {
		  FT_APP_Screen_Content(SCREEN, STATE, tag, dloffset, F, A, A0, H, F1, A1, E, HB, ST, SB, init_finished);
	  }

	  USB_Send_DataPair(STATE, F, A);

	  if (flag != 0)
	  	  init_finished++;

	}
}


void TIM2_IRQHandler(void)
{
	/* USER CODE BEGIN TIM2_IRQn 0 */

	/* USER CODE END TIM3_IRQn 0 */
	HAL_TIM_IRQHandler(&htim2);
	/* USER CODE BEGIN TIM3_IRQn 1 */

	//HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
	// Clear update interrupt bit

	uint32_t mean = 0;
	for (int i = 0 ; i < DMA_BUFFER_SIZE; i++){
		mean += DMA_BUFFER[i];
	}
	F = mean / DMA_BUFFER_SIZE;

	//#ifdef FILTERING
	if (F1F == 1) {
		Dacc = Dacc + F - Dout;
		Dout = Dacc/(uint16_t)K;
		F = Dout;
	}
	//#endif

	F = F1K * F + F1B;
	A = A1K*ReadSSI() + A1B;


//	{
//		F = 30.0;
//		if (STATE == TOUCH) {
//			A = 10.0f;
//		} else if (STATE == REMOVAL) {
//			A = 10.01f;
//		} else {
//			A = 10.05f;
//		}
//	}
	/* USER CODE END TIM3_IRQn 1 */
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_HSI48
                              |RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_HSI48;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  HAL_RCC_MCOConfig(RCC_MCO, RCC_MCO1SOURCE_SYSCLK, RCC_MCODIV_1);

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC init function */
static void MX_ADC_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = ENABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel to be converted. 
    */
  sConfig.Channel = ADC_CHANNEL_8;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* SPI1 init function */
static void MX_SPI1_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  //hspi1.Init.CRCPolynomial = 7;
  //hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  //hspi1.Init.NSSPMode = SPI_NSS_PULSE_DISABLE;

  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* TIM2 init function */
static void MX_TIM2_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 31999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 499;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12 
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15|GPIO_PIN_6 
                          |GPIO_PIN_8, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB1 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB6 PB8 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_6|GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 PB12 PB13 
                           PB14 PB15 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13 
                          |GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
