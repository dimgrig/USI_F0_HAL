/*
 * userdef.h
 *
 *  Created on: 23 но€б. 2017 г.
 *      Author: Dima
 */
#include "stm32f0xx.h"
#include <stdlib.h>

#ifndef INC_USERDEF_H_
#define INC_USERDEF_H_

//#define A1K 0.00002861
//0.000057220
//#define A1B 0

#define F1K_init 0.10f //0.0857f
#define F1B_init 100 //-4.457f
#define A1K_init 0.00002861f //0.0857f
#define A1B_init 0.0f
#define F1F_init 1.0f

float F1K;
float F1B;
float A1K;
float A1B;
float F1F;

uint8_t hextoascii(uint8_t hex);
uint8_t asciitohex(uint8_t ascii);
void float_to_char_array(float value, uint8_t *arr, uint8_t* length, uint8_t digits);
void char_array_to_float(float *value, uint8_t *arr, uint8_t length);

#endif /* INC_USERDEF_H_ */
