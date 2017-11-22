/*
 * t14-usb.c
 *
 *  Created on: 30 ���. 2017 �.
 *      Author: Dima
 */

#include "t14-usb.h"
#include "GUI.h"


void USB_Send_Packet(uint8_t *packet, uint16_t length)
{
	USB_Send_Data(0x02);
	//USB_Send_Data(0x11);
	//USB_Send_Data(0x15);
	uint8_t CRC_ = 0;
	uint8_t TempChar = 0;
	// uint8_t test_pack[3] = {0x31, 0x32, 0x37};
	for (int i = 0; i < length; i++){
		TempChar = *packet++;
		//TempChar = test_pack[i];
		CRC_ += TempChar;
		USB_Send_Data(TempChar);

	}
	USB_Send_Data(hextoascii((CRC_ >> 4)&0x0F) );
	USB_Send_Data(hextoascii((CRC_ >> 0)&0x0F) );

	USB_Send_Data(0x03);
	USB_Send_Data(0x0A);
}

void USB_Send_State(State_TypeDef STATE){
	uint8_t arr[1] = {(uint8_t)STATE};
	USB_Send_Packet(arr, 1);
}

void USB_Send_DataPair(State_TypeDef STATE, double F, double A){
	uint8_t length = 0;
	uint8_t l = 0;
	uint8_t arr[50];
	arr[length] = 0x02;
	length++;
	arr[length] = (uint8_t)STATE;
	length++;

	uint8_t value_c_length = 10;
	char value_c[value_c_length];

	uint32_t F_dec = (uint32_t)F;
	uint32_t F_fr = (uint32_t)( ( F - (uint32_t)(F) ) * 10 );

	if (F_dec == 0){
		arr[length] = hextoascii(0);
		length++;
	} else {
		l=0;
		while(F_dec != 0)
		{
			value_c[l] = hextoascii(F_dec%10);
			F_dec /= 10;// n = n/10
			l++;
		}

		for (int i = 0; i < l; i++){
			arr[length] = value_c[l-i-1];
			length++;
		}
	}
	//sprintf(value_c, "%d", F_dec);

//	for (int i = 0; i < l; i++){
//		arr[i+length] = value_c[i];
//		length++;
//	}

	arr[length] = 0x2E;
	length++;

//	l=0;
//	while(F_fr != 0)
//	{
//		F_fr /= 10;// n = n/10
//		++l;
//	}
//	sprintf(value_c, "%d", F_fr);
//	for (int i = 0; i < l; i++){
//		arr[i+length] = value_c[i];
//		length++;
//	}

	if (F_fr == 0){
		arr[length] = hextoascii(0);
		length++;
	} else {
		l=0;
		while(F_fr != 0)
		{
			value_c[l] = hextoascii(F_fr%10);
			F_fr /= 10;// n = n/10
			l++;
		}

		for (int i = 0; i < l; i++){
			arr[length] = value_c[l-i-1];
			length++;
		}
	}

	arr[length] = 0x3B;
	length++;



	uint32_t A_dec = (uint32_t)A;
	uint32_t A_fr = (uint32_t)( ( A - (uint32_t)(A) ) * 1000 );

	if (A_dec == 0){
		arr[length] = hextoascii(0);
		length++;
	} else {
		l=0;
		while(A_dec != 0)
		{
			value_c[l] = hextoascii(A_dec%10);
			A_dec /= 10;// n = n/10
			l++;
		}

		for (int i = 0; i < l; i++){
			arr[length] = value_c[l-i-1];
			length++;
		}
	}

	arr[length] = 0x2E;
	length++;

	if (A_fr == 0){
		arr[length] = hextoascii(0);
		length++;
	} else {
		l=0;
		while(A_fr != 0)
		{
			value_c[l] = hextoascii(A_fr%10);
			A_fr /= 10;// n = n/10
			l++;
		}

		for (int i = 0; i < l; i++){
			arr[length] = value_c[l-i-1];
			length++;
		}
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

uint8_t hextoascii(uint8_t hex)
{ uint8_t ascii;
  if (hex>15)
  {hex=(hex-(hex/10)*10);}
  switch (hex)
         {
         case 0: ascii = 0x30; break;
         case 1: ascii = 0x31; break;
			case 2: ascii = 0x32; break;
			case 3: ascii = 0x33; break;
      	case 4: ascii = 0x34; break;
			case 5: ascii = 0x35; break;
			case 6: ascii = 0x36; break;
         case 7: ascii = 0x37; break;
			case 8: ascii = 0x38; break;
			case 9: ascii = 0x39; break;
         case 10: ascii = 0x41;break;
			case 11: ascii = 0x42;break;
			case 12: ascii = 0x43;break;
			case 13: ascii = 0x44;break;
         case 14: ascii = 0x45;break;
			case 15: ascii = 0x46;break;
         default: ascii = 0x30;
         }
  return (ascii);
}

uint8_t asciitohex(uint8_t ascii)
{ uint8_t hex;
  switch (ascii)
         {
         case 0x30: hex = 0;  break;
         case 0x31: hex = 1;  break;
			case 0x32: hex = 2;  break;
			case 0x33: hex = 3;  break;
      	case 0x34: hex = 4;  break;
			case 0x35: hex = 5;  break;
			case 0x36: hex = 6;  break;
         case 0x37: hex = 7;  break;
			case 0x38: hex = 8;  break;
			case 0x39: hex = 9;  break;
         case 0x41: hex = 10; break;
			case 0x42: hex = 11; break;
			case 0x43: hex = 12; break;
			case 0x44: hex = 13; break;
         case 0x45: hex = 14; break;
			case 0x46: hex = 15; break;
         }
  return (hex);
}


void USB_Send_Data(uint8_t data){
	//USBD_CtlSendData(data, 1);
	CDC_Transmit_FS(data, 1);
}

/* if any data received from PC */
//    if (USB_Data_Received_Flag != 0)
//    {
//
//        /* Send data back to PC */
//        /* Data is in "USB_Rx_Buffer", Data length - USB_Data_Received_Count */
//        i = 0;
//
//        while (USB_Data_Received_Count != 0)
//        {
//            USB_Send_Data(USB_Rx_Buffer[i]+0x03);
//            USB_SetLeds(USB_Rx_Buffer[i]);
//            i++;
//            USB_Data_Received_Count--;
//        }
//    USB_Data_Received_Flag = 0;
//    }  /* if */

//	uint8_t testDataToSend[8];
//	for (uint8_t i = 0; i < 8; i++)
//	{
//		testDataToSend[i] = i;
//	}
	//CDC_Transmit_FS(testDataToSend, 8);
