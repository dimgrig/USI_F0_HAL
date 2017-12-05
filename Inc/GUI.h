#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"

typedef enum
{
	ERROR_ = 0x30, /*!<  */
	IDLE = 0x31, /*!<  */
	TOUCH   = 0x32, /*!< */
	MEASURE  = 0x33, /*!<  */
	REMOVAL  = 0x34,  /*!<  */
	RESULTS  = 0x35,  /*!<  */
	RESET_  = 0x36  /*!<  */
}State_TypeDef;

typedef enum
{
	MAIN = 0x00, /*!<  */
	SETTINGS   = 0x01, /*!< */
	MATERIAL  = 0x02, /*!<  */
	CALIBRATION  = 0x03,  /*!<  */
	STEPPER  = 0x04  /*!<  */
}Screen_TypeDef;

