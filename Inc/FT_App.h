/*
 * FT_App.h
 *
 *  Created on: 21 окт. 2017 г.
 *      Author: Dima
 */
#include <stdio.h>
#include "FT_Platform.h"

#include "GUI.h"
//#include "t14-flash.h"
#include "FT80x.h"
#include "arial.TTF_18_L1.rawh"

#ifndef FT_APP_H_
#define FT_APP_H_

ft_uint32_t white = COLOR_RGB(0xbb,0xbb,0xbb);
ft_uint32_t gray = COLOR_RGB(0x77,0x77,0x77);
ft_uint32_t button_color = COLOR_RGB(0x00,0x26,0x77);
ft_uint32_t button_color_hover = COLOR_RGB(0x00,0x55,0xff);
ft_uint32_t button_color_selected = COLOR_RGB(0x00,0xff,0x55);

ft_uint16_t FT_Width = 320;
ft_uint16_t FT_Height = 240;

//ft_uint8_t DispText[20];
//ft_uint8_t CurrChar = '|';
//ft_uint8_t CurrTag = 0;
//ft_uint8_t PrevTag = 0;
////ft_uint8_t Pendown = 1;
//ft_uint8_t CurrTextIdx = 0;


ft_void_t FT_APP_BootupConfig();
ft_void_t FT_APP_Calibrate(ft_uint8_t mode);
ft_void_t FT_APP_Screen_Content(Screen_TypeDef SCREEN, State_TypeDef STATE,
		ft_uint16_t tag,
		ft_uint16_t dloffset,
		double F, double A, double A0, double H, double F1, double A1,
		double E, double HB, double ST, double SB,
		ft_uint16_t nmb);
ft_uint16_t FT_APP_Screen_BasicScreen(Screen_TypeDef SCREEN);
void FT_APP_Screen_MainScreen();
ft_void_t FT_APP_Screen(ft_char8_t *str);
void FT_APP_Screen_Test();

#endif /* FT_APP_H_ */
