/*
 * userdef.h
 *
 *  Created on: 23 но€б. 2017 г.
 *      Author: Dima
 */
#include "stm32f0xx.h"

#ifndef INC_USERDEF_H_
#define INC_USERDEF_H_

#define A1K 0.00002861
//0.000057220
#define A1B 0

#define F1K_init 0.10f //0.0857f
#define F1B_init 100 //-4.457f

float F1K;
float F1B;

uint8_t hextoascii(uint8_t hex);
uint8_t asciitohex(uint8_t ascii);
void float_to_char_array(float value, uint8_t *arr, uint8_t* length, uint32_t digits);

#endif /* INC_USERDEF_H_ */
