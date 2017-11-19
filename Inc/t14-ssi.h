#include <stdio.h>
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"

#define A1K 0.00002861
//0.000057220
#define A1B 0

#define F1K 0.10f //0.0857f
#define F1B 0 //-4.457f

void SSI_CLK_HIGH();
void SSI_CLK_LOW();
uint8_t SSI_DATA_PORT();
uint32_t ReadSSI(void);
