#include <stdio.h>
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"

void SSI_CLK_HIGH();
void SSI_CLK_LOW();
uint8_t SSI_DATA_PORT();
uint32_t ReadSSI(void);
