/*
 * userdef.c
 *
 *  Created on: 23 ����. 2017 �.
 *      Author: Dima
 */

#include "userdef.h"

void float_to_char_array(float value, uint8_t *arr, uint8_t* length, uint32_t digits)
{
	uint8_t value_c_length = 10;
	uint8_t value_c[value_c_length];
	uint32_t value_dec = (uint32_t)value;
	uint32_t value_fr = (uint32_t) (( value - (uint32_t)(value) ) * digits );
	//uint8_t length = 0;
	uint8_t l = 0;
	//uint8_t arr[32];

	if (value_dec == 0){

		*(arr+*length) = hextoascii(0); //
		(*length)++;
	} else {
		l=0;
		while(value_dec != 0)
		{
			value_c[l] = hextoascii(value_dec%10);//
			value_dec /= 10;// n = n/10
			l++;
		}

		for (int i = 0; i < l; i++){
			*(arr+*length) = value_c[l-i-1];
			(*length)++;
		}
	}

	*(arr+*length) = 0x2E;
	(*length)++;

	if (value_fr == 0){
		*(arr+*length) = hextoascii(0);//
		(*length)++;
	} else {
		l=0;
		while(value_fr != 0)
		{
			value_c[l] = hextoascii(value_fr%10);//
			value_fr /= 10;// n = n/10
			l++;
		}

		for (int i = 0; i < l; i++){
			*(arr+*length) = value_c[l-i-1];
			(*length)++;
		}
	}

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
