/*
 * t14-usb.c
 *
 *  Created on: 30 окт. 2017 г.
 *      Author: Dima
 */

#include "t14-usb.h"


void USB_Send_Packet(uint8_t *packet, uint16_t length)
{
	USB_Send_Data(0x02);

	uint8_t CRC_ = 0;
	uint8_t TempChar = 0;
	// uint8_t test_pack[3] = {0x31, 0x32, 0x37};
	for (int i = 0; i < length; i++){
		TempChar = *packet++;
		CRC_ += TempChar;
		USB_Send_Data(TempChar);
	}
	USB_Send_Data(hextoascii((CRC_ >> 4)&0x0F) );
	USB_Send_Data(hextoascii((CRC_ >> 0)&0x0F) );

	USB_Send_Data(0x03);
	USB_Send_Data(0x0A);
}

void USB_Send_DataPair(State_TypeDef STATE, double F, double A){
	uint8_t length = 0;
	uint8_t l = 0;
	uint8_t arr[50];
	arr[length] = 0x02;
	length++;
	arr[length] = (uint8_t)STATE;
	length++;

	uint8_t value_c_length = 32;
	char value_c[value_c_length];



//	uint32_t F_dec = (uint32_t)F;
//	uint32_t F_fr = (uint32_t)( ( F - (uint32_t)(F) ) * 10 );
//
//	if (F_dec == 0){
//		arr[length] = hextoascii(0);
//		length++;
//	} else {
//		l=0;
//		while(F_dec != 0)
//		{
//			value_c[l] = hextoascii(F_dec%10);
//			F_dec /= 10;// n = n/10
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
//	if (F_fr == 0){
//		arr[length] = hextoascii(0);
//		length++;
//	} else {
//		l=0;
//		while(l < 1)
//		{
//			value_c[l] = hextoascii(F_fr%10);
//			F_fr /= 10;// n = n/10
//			l++;
//		}
//
//		for (int i = 0; i < l; i++){
//			arr[length] = value_c[l-i-1];
//			length++;
//		}
//	}
//
//	arr[length] = 0x3B;
//	length++;
//
//	uint32_t A_dec = (uint32_t)A;
//	//uint32_t A_fr = (uint32_t)( ((double)(A - (float)((uint32_t)A))) * 1000.0f );
//	uint32_t A_fr = (uint32_t)( ((A - (long)A)) * 1000 );
//
//	if (A_dec == 0){
//		arr[length] = hextoascii(0);
//		length++;
//	} else {
//		l=0;
//		while(A_dec != 0)
//		{
//			value_c[l] = hextoascii(A_dec%10);
//			A_dec /= 10;// n = n/10
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
//	if (A_fr == 0){
//		arr[length] = hextoascii(0);
//		length++;
//	} else {
//		l=0;
//		while(l < 3)
//		{
//			value_c[l] = hextoascii(A_fr%10);
//			A_fr /= 10;// n = n/10
//			l++;
//		}
//
//		for (int i = 0; i < l; i++){
//			arr[length] = value_c[l-i-1];
//			length++;
//		}
//	}


	sprintf(value_c, "%.1f", F);
	l = strlen(value_c);
	for (int i = 0; i < l; i++){
		arr[length] = value_c[i];
		length++;
	}
	arr[length] = 0x3B;
	length++;

	sprintf(value_c, "%.3f", A);
	l = strlen(value_c);
	for (int i = 0; i < l; i++){
		arr[length] = value_c[i];
		length++;
	}

	uint8_t CRC_ = 0;
	// uint8_t test_pack[3] = {0x31, 0x32, 0x37};
	for (int i = 1; i < length; i++){
		CRC_ += arr[i];
	}

	arr[length] = (hextoascii((CRC_ >> 4)&0x0F) );
	length++;
	arr[length] = (hextoascii((CRC_ >> 0)&0x0F) );
	length++;

	arr[length] = (0x03);
	length++;
	arr[length] = (0x0A);
	length++;

	CDC_Transmit_FS(arr, length);
	//USB_Send_Packet(arr, length);
}



void USB_Send_Data(uint8_t data){
	CDC_Transmit_FS(data, 1);
}
