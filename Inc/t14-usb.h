/*
 * t14-usb.h
 *
 *  Created on: 30 ���. 2017 �.
 *      Author: Dima
 */

#ifndef T14_USB_H_
#define T14_USB_H_

#include <stdio.h>
#include "stm32f0xx.h"
#include "stm32f0xx_hal.h"
#include "usb_device.h"

//void USB_Send_DataPair(State_TypeDef STATE, double F, double A);
void USB_Send_Packet(uint8_t *packet, uint16_t length);
//void USB_Send_State(State_TypeDef STATE);
uint8_t hextoascii(uint8_t hex);

#endif /* T14_USB_H_ */
