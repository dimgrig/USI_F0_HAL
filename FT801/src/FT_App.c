/*
 * FT_app.c
 *
 *  Created on: 21 окт. 2017 г.
 *      Author: Dima
 */

#include "FT_App.h"


unsigned int incCMDOffset(unsigned int currentOffset, unsigned char commandSize);
extern FT_PROGMEM ft_prog_uchar8_t SAMApp_Metric_L1[];
extern FT_PROGMEM ft_prog_uchar8_t SAMApp_L1[];
ft_uint32_t SAMApp_Metric_L1_SIZE = 148;
ft_uint32_t SAMApp_L1_SIZE = 6489;
ft_uint32_t FONT_POS = 1000;
ft_uint32_t R_FONT = 12;
ft_uint32_t Ft_CmdBuffer_Index;
ft_uint32_t Ft_DlBuffer_Index;


//#ifdef BUFFER_OPTIMIZATION
//ft_uint8_t  Ft_DlBuffer[FT_DL_SIZE];
//ft_uint8_t  Ft_CmdBuffer[FT_CMD_FIFO_SIZE];
//#endif
//
//ft_void_t Ft_App_WrCoCmd_Buffer(Ft_Gpu_Hal_Context_t *phost,ft_uint32_t cmd)
//{
//#ifdef  BUFFER_OPTIMIZATION
//   /* Copy the command instruction into buffer */
//   ft_uint32_t *pBuffcmd;
//   pBuffcmd =(ft_uint32_t*)&Ft_CmdBuffer[Ft_CmdBuffer_Index];
//   *pBuffcmd = cmd;
//#endif
//   Ft_Gpu_Hal_WrCmd32(phost,cmd);
//
//#ifdef ARDUINO_PLATFORM
//   Ft_Gpu_Hal_WrCmd32(phost,cmd);
//#endif
//
//   /* Increment the command index */
//   Ft_CmdBuffer_Index += FT_CMD_SIZE;
//}
//
//ft_void_t Ft_App_WrDlCmd_Buffer(Ft_Gpu_Hal_Context_t *phost,ft_uint32_t cmd)
//{
//#ifdef BUFFER_OPTIMIZATION
//   /* Copy the command instruction into buffer */
//   ft_uint32_t *pBuffcmd;
//   pBuffcmd =(ft_uint32_t*)&Ft_DlBuffer[Ft_DlBuffer_Index];
//   *pBuffcmd = cmd;
//#endif
//   Ft_Gpu_Hal_Wr32(phost,(RAM_DL+Ft_DlBuffer_Index),cmd);
//#ifdef ARDUINO_PLATFORM
//   Ft_Gpu_Hal_Wr32(phost,(RAM_DL+Ft_DlBuffer_Index),cmd);
//#endif
//   /* Increment the command index */
//   Ft_DlBuffer_Index += FT_CMD_SIZE;
//}
//
//ft_void_t Ft_App_WrCoStr_Buffer(Ft_Gpu_Hal_Context_t *phost,const ft_char8_t *s)
//{
//#ifdef  BUFFER_OPTIMIZATION
//  ft_uint16_t length = 0;
//  length = strlen(s) + 1;//last for the null termination
//
//  strcpy(&Ft_CmdBuffer[Ft_CmdBuffer_Index],s);
//
//  /* increment the length and align it by 4 bytes */
//  Ft_CmdBuffer_Index += ((length + 3) & ~3);
//#endif
//}
//
//ft_void_t Ft_App_Flush_DL_Buffer(Ft_Gpu_Hal_Context_t *phost)
//{
//#ifdef  BUFFER_OPTIMIZATION
//   if (Ft_DlBuffer_Index > 0)
//     Ft_Gpu_Hal_WrMem(phost,RAM_DL,Ft_DlBuffer,Ft_DlBuffer_Index);
//#endif
//   Ft_DlBuffer_Index = 0;
//
//}
//
//ft_void_t Ft_App_Flush_Co_Buffer(Ft_Gpu_Hal_Context_t *phost)
//{
//#ifdef  BUFFER_OPTIMIZATION
//   if (Ft_CmdBuffer_Index > 0)
//     Ft_Gpu_Hal_WrCmdBuf(phost,Ft_CmdBuffer,Ft_CmdBuffer_Index);
//#endif
//   Ft_CmdBuffer_Index = 0;
//}

//ft_void_t SAMAPP_BootupConfig(Ft_Gpu_Hal_Context_t *phost)
//{
//	/* Do a power cycle for safer side */
//	Ft_Gpu_Hal_Powercycle(phost,FT_TRUE);
//
//	/* Access address 0 to wake up the FT800 */
//	Ft_Gpu_HostCommand(phost,FT_GPU_ACTIVE_M);
//	Ft_Gpu_Hal_Sleep(20);
//
//	/* Set the clk to external clock */
//	Ft_Gpu_HostCommand(phost,FT_GPU_EXTERNAL_OSC);
//	Ft_Gpu_Hal_Sleep(20);
//
//
//	/* Switch PLL output to 48MHz */
//	Ft_Gpu_HostCommand(phost,FT_GPU_PLL_48M);
//	Ft_Gpu_Hal_Sleep(20);
//
//	/* Do a core reset for safer side */
//	Ft_Gpu_HostCommand(phost,FT_GPU_CORE_RESET);
//
//
//	{
//		ft_uint8_t chipid;
//		//Read Register ID to check if FT800 is ready.
//		Ft_Gpu_Hal_Sleep(100);
//		chipid = Ft_Gpu_Hal_Rd8(phost, REG_ID);
//		Ft_Gpu_Hal_Sleep(100);
//		while(chipid != 0x7C)
//		chipid = Ft_Gpu_Hal_Rd8(phost, REG_ID);
//
//	}
//	 /* Global variables for display resolution to support various display panels */
//	  /* Default is WQVGA - 480x272 */
//	  ft_int16_t FT_DispWidth = 320;
//	  ft_int16_t FT_DispHeight = 240;
//	  ft_int16_t FT_DispHCycle =  360;
//	  ft_int16_t FT_DispHOffset = 43;
//	  ft_int16_t FT_DispHSync0 = 0;
//	  ft_int16_t FT_DispHSync1 = 63;
//	  ft_int16_t FT_DispVCycle = 278;
//	  ft_int16_t FT_DispVOffset = 12;
//	  ft_int16_t FT_DispVSync0 = 0;
//	  ft_int16_t FT_DispVSync1 = 15;
//	  ft_uint8_t FT_DispPCLK = 8;
//	  ft_char8_t FT_DispSwizzle = 0;
//	  ft_char8_t FT_DispPCLKPol = 1;
//
//	    FT_DispWidth = 320;
//		FT_DispHeight = 240;
//		FT_DispHCycle =  408;
//		FT_DispHOffset = 70;
//		FT_DispHSync0 = 0;
//		FT_DispHSync1 = 10;
//		FT_DispVCycle = 263;
//		FT_DispVOffset = 13;
//		FT_DispVSync0 = 0;
//		FT_DispVSync1 = 2;
//		FT_DispPCLK = 8;
//		FT_DispSwizzle = 2;
//		FT_DispPCLKPol = 0;
//
//
//	//	FT_DispWidth = 320;
//	//	FT_DispHeight = 240;
//	//	FT_DispHCycle =  400;
//	//	FT_DispHOffset = 70;
//	//	FT_DispHSync0 = 0;
//	//	FT_DispHSync1 = 10;
//	//	FT_DispVCycle = 250;
//	//	FT_DispVOffset = 5;
//	//	FT_DispVSync0 = 0;
//	//	FT_DispVSync1 = 2;
//	//	FT_DispPCLK = 8;
//	//	FT_DispSwizzle = 2;
//	//	FT_DispPCLKPol = 0;
//
//
//	  Ft_Gpu_Hal_Wr16(phost, REG_HCYCLE, FT_DispHCycle);
//	  Ft_Gpu_Hal_Wr16(phost, REG_HOFFSET, FT_DispHOffset);
//	  Ft_Gpu_Hal_Wr16(phost, REG_HSYNC0, FT_DispHSync0);
//	  Ft_Gpu_Hal_Wr16(phost, REG_HSYNC1, FT_DispHSync1);
//	  Ft_Gpu_Hal_Wr16(phost, REG_VCYCLE, FT_DispVCycle);
//	  Ft_Gpu_Hal_Wr16(phost, REG_VOFFSET, FT_DispVOffset);
//	  Ft_Gpu_Hal_Wr16(phost, REG_VSYNC0, FT_DispVSync0);
//	  Ft_Gpu_Hal_Wr16(phost, REG_VSYNC1, FT_DispVSync1);
//	  Ft_Gpu_Hal_Wr8(phost, REG_SWIZZLE, FT_DispSwizzle);
//	  Ft_Gpu_Hal_Wr8(phost, REG_PCLK_POL, FT_DispPCLKPol);
//	  Ft_Gpu_Hal_Sleep(100);
//	  Ft_Gpu_Hal_Wr8(phost, REG_PCLK,FT_DispPCLK);//after this display is visible on the LCD
//	  Ft_Gpu_Hal_Wr16(phost, REG_HSIZE, FT_DispWidth);
//	  Ft_Gpu_Hal_Wr16(phost, REG_VSIZE, FT_DispHeight);
//
//	  Ft_Gpu_Hal_Wr8(phost, REG_GPIO_DIR,0x83 | Ft_Gpu_Hal_Rd8(phost,REG_GPIO_DIR));
//	  Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0x083 | Ft_Gpu_Hal_Rd8(phost,REG_GPIO));
//
//
//	/* Touch configuration - configure the resistance value to 1200 - this value is specific to customer requirement and derived by experiment */
//	  Ft_Gpu_Hal_Wr16(phost, REG_TOUCH_RZTHRESH,1200);
//	  Ft_Gpu_Hal_Wr8(phost, REG_GPIO_DIR,0xff);
//	  Ft_Gpu_Hal_Wr8(phost, REG_GPIO,0x0ff);
//
////	  Ft_Gpu_Hal_Wr16(phost, REG_TOUCH_RZTHRESH,1200);
////	delay_ms(10);
////	Ft_Gpu_Hal_Wr32(phost, REG_PWM_DUTY,255);
//
//
//	 /* Boot up for FT800 followed by graphics primitive sample cases */
//	  /* Initial boot up DL - make the back ground green color */
//	  const ft_uint8_t FT_DLCODE_BOOTUP[12] =
//	  {
//	      0,255,0,2,//GPU instruction CLEAR_COLOR_RGB
//	      7,0,0,38, //GPU instruction CLEAR
//	      0,0,0,0,  //GPU instruction DISPLAY
//	  };
//
//	  /*It is optional to clear the screen here*/
////	      Ft_Gpu_Hal_WrMem(phost, RAM_DL,(ft_uint8_t *)FT_DLCODE_BOOTUP,sizeof(FT_DLCODE_BOOTUP));
////	      Ft_Gpu_Hal_Wr8(phost, REG_DLSWAP,DLSWAP_FRAME);
//
//
////	      Ft_Gpu_Hal_Wr8(phost, REG_PCLK,FT_DispPCLK);//after this display is visible on the LCD
//
//	  SAMAPP_API_Calibrate(phost, 0); // работает
//
//	  Ft_Gpu_Hal_Sleep(50);//Show the booting up screen.
//
//}

//ft_void_t SAMAPP_API_Calibrate(Ft_Gpu_Hal_Context_t *phost, ft_uint8_t mode)
//{
//	ft_uint32_t REG_TOUCH_CALIBRATE_A;
//	ft_uint32_t REG_TOUCH_CALIBRATE_B;
//	ft_uint32_t REG_TOUCH_CALIBRATE_C;
//	ft_uint32_t REG_TOUCH_CALIBRATE_D;
//	ft_uint32_t REG_TOUCH_CALIBRATE_E;
//	ft_uint32_t REG_TOUCH_CALIBRATE_F;
//	if (mode == 0) {
//		REG_TOUCH_CALIBRATE_A = 0x00005a81;
//		REG_TOUCH_CALIBRATE_B = 0x00000066;
//		REG_TOUCH_CALIBRATE_C = 0xfff89d6b;
//		REG_TOUCH_CALIBRATE_D = 0xfffffcb6;
//		REG_TOUCH_CALIBRATE_E = 0x00006c3f;
//		REG_TOUCH_CALIBRATE_F = 0x20003fd0;
//
//		Ft_Gpu_Hal_Wr32(phost, REG_TOUCH_TRANSFORM_A, REG_TOUCH_CALIBRATE_A);
//		Ft_Gpu_Hal_Wr32(phost, REG_TOUCH_TRANSFORM_B, REG_TOUCH_CALIBRATE_B);
//		Ft_Gpu_Hal_Wr32(phost, REG_TOUCH_TRANSFORM_C, REG_TOUCH_CALIBRATE_C);
//		Ft_Gpu_Hal_Wr32(phost, REG_TOUCH_TRANSFORM_D, REG_TOUCH_CALIBRATE_D);
//		Ft_Gpu_Hal_Wr32(phost, REG_TOUCH_TRANSFORM_E, REG_TOUCH_CALIBRATE_E);
//		Ft_Gpu_Hal_Wr32(phost, REG_TOUCH_TRANSFORM_F, REG_TOUCH_CALIBRATE_F);
//	} else {
//		Ft_Gpu_CoCmd_Dlstart(phost);
//		//Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
//		Ft_Gpu_CoCmd_Calibrate(phost,0);
//		Ft_App_Flush_Co_Buffer(phost);
//		Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//
//		REG_TOUCH_CALIBRATE_A = Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TRANSFORM_A);
//		REG_TOUCH_CALIBRATE_B = Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TRANSFORM_B);
//		REG_TOUCH_CALIBRATE_C = Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TRANSFORM_C);
//		REG_TOUCH_CALIBRATE_D = Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TRANSFORM_D);
//		REG_TOUCH_CALIBRATE_E = Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TRANSFORM_E);
//		REG_TOUCH_CALIBRATE_F = Ft_Gpu_Hal_Rd32(phost, REG_TOUCH_TRANSFORM_F);
//	}
//
//    Ft_Gpu_Hal_Sleep(50);
//}
//
//
//ft_uint16_t SAMAPP_API_Screen_BackGround(Ft_Gpu_Hal_Context_t *phost, ft_char8_t *str)
//{
//	  Ft_Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000, SAMApp_Metric_L1, SAMApp_Metric_L1_SIZE); //загружаем метрику шрифта
//	  Ft_Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000 + SAMApp_Metric_L1_SIZE, SAMApp_L1, SAMApp_L1_SIZE); //загружаем шрифт
//
//	  Ft_Gpu_CoCmd_Dlstart(phost); // команда начала дисплей-листа
//
//	  //Ft_Gpu_CoCmd_Dlstart(phost);
//	  	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
//	  	Ft_App_WrCoCmd_Buffer(phost,CLEAR(0xff,0xff,0xff));
//
//
//	  //Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff)); //установка цвета фона
//	  Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1)); //установка цвета фона
//	  Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(255,0,0)); // установка цвета текста
//	  Ft_App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(12)); //назначение нашему шрифту указателя
//
//	  Ft_App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(1085));
//	  Ft_App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(L1,3,21));
//	  Ft_App_WrCoCmd_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER,BORDER,18,21));
//	  Ft_Gpu_CoCmd_SetFont(phost, 12, RAM_G + 1000);
//
//
//
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xff,0x00));
//	Ft_Gpu_CoCmd_Text(phost, 10, 10, 12, 0, "\x21\x24\x14\x06\x0c\x28\x43\x5b\x5d");
//	//Ft_Gpu_CoCmd_Text(phost, 10, 10, 16, 0, str);
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
//	Ft_Gpu_CoCmd_Text(phost, 10, 30, 12, 0, "\x58\x59\x5a");
//	//Ft_Gpu_CoCmd_Text(phost, 10, 30, 16, 0, 777);
//
//	Ft_App_WrCoCmd_Buffer(phost,BEGIN(LINES));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0, 30, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(300, 30, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0, 50, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(300, 50, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(160, 0, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(160, 120, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,END());
//
//
//
//
//	//Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
//	//Ft_Gpu_CoCmd_Swap(phost);
//
//	Ft_App_Flush_Co_Buffer(phost);
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//	//while(0!=Ft_Gpu_Hal_Rd16(phost,REG_CMD_READ));
//
//	ft_uint16_t dloffset = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL); // размер коируемого дисплей-листа
//	//dloffset -= 4;
//	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY); // указание FT800 скопировать области памяти
//	Ft_Gpu_Hal_WrCmd32(phost,100000L); // адрес, куда будем копировать в области графической памяти RAM_G
//	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL); // адрес, откуда копируем
//	Ft_Gpu_Hal_WrCmd32(phost,dloffset); // количество байт
//
//
//
//		/* Download the commands into fifo */
//		//Ft_App_Flush_Co_Buffer(phost);
//
//		/* Wait till coprocessor completes the operation */
//		//Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//
//	Ft_Gpu_Hal_Sleep(50);
//	return dloffset;
//
//}

//ft_void_t SAMAPP_API_Screen_Content(Ft_Gpu_Hal_Context_t *phost,
//		Screen_TypeDef SCREEN, State_TypeDef STATE,
//		ft_uint16_t tag,
//		ft_uint16_t dloffset,
//		double F, double A, double A0, double H, double F1, double A1,
//		double E, double HB, double ST, double SB,
//		ft_uint16_t nmb)
//{
//	ft_uint32_t storedMaterial;
//
//	uint8_t value_c_length = 10;
//	char value_c[value_c_length];
//
//	Ft_Gpu_CoCmd_Dlstart(phost); // начало нового дисплей-листа
//	Ft_Gpu_CoCmd_Append(phost,100000L, dloffset); // добавление к текущему набору команд, команд скопированных MEMCPY
//
//	switch (SCREEN){
//		case MAIN:
//			//Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
//			//Ft_App_WrCoCmd_Buffer(phost,CLEAR(0xff,0xff,0xff));
//
//
//			//Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0x00,0xff));
//			//Ft_Gpu_CoCmd_Text(phost, 10, 50, 16, 0, "CONTENT");
//			Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xd8,0x00));
//			//Ft_Gpu_CoCmd_Number(phost, 10, 60, 16, 0, nmb);
//			//Ft_Gpu_CoCmd_Number(phost, 10, 70, 16, 0, STATE);
//
//			//Ft_Gpu_CoCmd_Text(phost, 117, 7,  12, 0, "\x65\x67\x60"); //Fk=
//			//Ft_Gpu_CoCmd_Text(phost, 227, 7, 12, 0, "\x63\x67\x60"); //Ak=
//
//
//			//float b = 12.234;
//			sprintf(value_c, "%d.%d", (int)F, (int)( ( F - floor(F) ) * pow(10, 1) ));
//			Ft_Gpu_CoCmd_Text(phost, 155, 7, 22, 0, value_c);
//			sprintf(value_c, "%d.%d", (int)A, (int)( ( A - floor(A) ) * pow(10, 3) ));
//			Ft_Gpu_CoCmd_Text(phost, 265, 7, 22, 0, value_c);
//
//
//			switch (STATE)
//		  {
//			case IDLE:
//			  //placeValuesReset();
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(2));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==2)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 110, 190, 100, 40, 12, 0, "\x21\x2a\x26\x18");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//			break;
//			case TOUCH:
//			  //placeValuesReset();
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(2));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==2)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 110, 190, 100, 40, 12, 0, "\x17\x02\x26\x02\x1e\x14\x0c");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//			break;
//			case MEASURE:
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(2));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==2)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 110, 190, 100, 40, 12, 0, "\x13\x12\x1c\x0c\x24\x0c\x1e\x14\x0c");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//				sprintf(value_c, "%d.%d", (int)A0, (int)( ( A0 - floor(A0) ) * pow(10, 3) ));
//				Ft_Gpu_CoCmd_Text(phost, 155, 42, 22, 0, value_c);
//			break;
//			case REMOVAL:
//
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(2));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==2)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 110, 190, 100, 40, 12, 0, "\x25\x1e\x42\x28\x14\x0c");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//				  sprintf(value_c, "%d.%d", (int)A0, (int)( ( A0 - floor(A0) ) * pow(10, 3) ));
//				  Ft_Gpu_CoCmd_Text(phost, 155, 42, 22, 0, value_c);
//				  sprintf(value_c, "%d.%d", (int)F1, (int)( ( F1 - floor(F1) ) * pow(10, 1) ));
//				Ft_Gpu_CoCmd_Text(phost, 155, 77, 22, 0, value_c);
//				sprintf(value_c, "%d.%d", (int)A1, (int)( ( A1 - floor(A1) ) * pow(10, 3) ));
//				Ft_Gpu_CoCmd_Text(phost, 265, 77, 22, 0, value_c);
//			break;
//			case RESULTS:
//
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(2));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==2)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 110, 190, 100, 40, 12, 0, "\x21\x2a\x26\x18");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//				sprintf(value_c, "%d.%d", (int)A0, (int)( ( A0 - floor(A0) ) * pow(10, 3) ));
//				Ft_Gpu_CoCmd_Text(phost, 155, 42, 22, 0, value_c);
//				sprintf(value_c, "%d.%d", (int)F1, (int)( ( F1 - floor(F1) ) * pow(10, 1) ));
//				Ft_Gpu_CoCmd_Text(phost, 155, 77, 22, 0, value_c);
//				sprintf(value_c, "%d.%d", (int)A1, (int)( ( A1 - floor(A1) ) * pow(10, 3) ));
//				Ft_Gpu_CoCmd_Text(phost, 265, 77, 22, 0, value_c);
//				sprintf(value_c, "%d.%d", (int)H, (int)( ( H - floor(H) ) * pow(10, 3) ));
//				Ft_Gpu_CoCmd_Text(phost, 265, 42, 22, 0, value_c);
//
//				sprintf(value_c, "%d.%d", (int)E, (int)( ( E - floor(E) ) * pow(10, 0) ));
//				Ft_Gpu_CoCmd_Text(phost, 155, 112, 22, 0, value_c);
//				sprintf(value_c, "%d.%d", (int)ST, (int)( ( ST - floor(ST) ) * pow(10, 2) ));
//				Ft_Gpu_CoCmd_Text(phost, 265, 112, 22, 0, value_c);
//				sprintf(value_c, "%d.%d", (int)HB, (int)( ( HB - floor(HB) ) * pow(10, 2) ));
//				Ft_Gpu_CoCmd_Text(phost, 155, 147, 22, 0, value_c);
//				sprintf(value_c, "%d.%d", (int)SB, (int)( ( SB - floor(SB) ) * pow(10, 2) ));
//				Ft_Gpu_CoCmd_Text(phost, 265, 147, 22, 0, value_c);
//
//			break;
//		  }
//
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_App_WrCoCmd_Buffer(phost,TAG(1));          // assign the tag value
//			Ft_Gpu_CoCmd_FgColor(phost,(tag==1)?button_color_hover:button_color);
//			Ft_Gpu_CoCmd_Button(phost, 5, 190, 100, 40, 12, 0, "\x1d\x02\x26\x28\x24\x20\x16\x18\x14");
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//
//
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_App_WrCoCmd_Buffer(phost,TAG(3));          // assign the tag value
//			Ft_Gpu_CoCmd_FgColor(phost,(tag==3)?button_color_hover:button_color);
//			Ft_Gpu_CoCmd_Button(phost, 215, 190, 100, 40, 12, 0, "\x25\x04\x24\x20\x26");
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//		break;
//		case SETTINGS:
//			//tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
//
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_App_WrCoCmd_Buffer(phost,TAG(1));          // assign the tag value
//			Ft_Gpu_CoCmd_FgColor(phost,(tag==1)?button_color_hover:button_color);
//			Ft_Gpu_CoCmd_Button(phost, 5, 190, 100, 40, 12, 0, "\x1d\x02\x26\x28\x24\x20\x16\x18\x14"); // Настройки
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_App_WrCoCmd_Buffer(phost,TAG(4));          // assign the tag value
//			Ft_Gpu_CoCmd_FgColor(phost,(tag==4)?button_color_hover:button_color);
//			Ft_Gpu_CoCmd_Button(phost, 110, 10, 100, 40, 12, 0, "\x1b\x02\x28\x0c\x24\x14\x02\x1a"); // Материал
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_App_WrCoCmd_Buffer(phost,TAG(5));          // assign the tag value
//			Ft_Gpu_CoCmd_FgColor(phost,(tag==5)?button_color_hover:button_color);
//			Ft_Gpu_CoCmd_Button(phost, 110, 60, 100, 40, 12, 0, "\x17\x02\x1a\x14\x04\x24\x20\x06\x18\x02"); //Калибровка
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//		break;
//		case MATERIAL:
//
//			//**storedMaterial = FLASH_Read_DataWord(0);
//
//			Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xd8,0x00));
//
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_App_WrCoCmd_Buffer(phost,TAG(1));          // assign the tag value
//			Ft_Gpu_CoCmd_FgColor(phost,(tag==1)?button_color_hover:button_color);
//			Ft_Gpu_CoCmd_Button(phost, 5, 190, 100, 40, 12, 0, "\x5f");
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//
//			if (tag >= 201 & tag <=203) {
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(201));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==201)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 10, 10, 100, 30, 12, 0, "\x54");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(202));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==202)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 10, 50, 100, 30, 12, 0, "\x55");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(203));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(tag==203)?button_color_hover:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 10, 90, 100, 30, 12, 0, "\x56");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//			} else {
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(201));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(storedMaterial==201)?button_color_selected:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 10, 10, 100, 30, 12, 0, "\x54");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(202));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(storedMaterial==202)?button_color_selected:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 10, 50, 100, 30, 12, 0, "\x55");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//				Ft_App_WrCoCmd_Buffer(phost,TAG(203));          // assign the tag value
//				Ft_Gpu_CoCmd_FgColor(phost,(storedMaterial==203)?button_color_selected:button_color);
//				Ft_Gpu_CoCmd_Button(phost, 10, 90, 100, 30, 12, 0, "\x56");
//				Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//			}
//		break;
//		case CALIBRATION:
//			Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xd8,0x00));
//
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_App_WrCoCmd_Buffer(phost,TAG(1));          // assign the tag value
//			Ft_Gpu_CoCmd_FgColor(phost,(tag==1)?button_color_hover:button_color);
//			Ft_Gpu_CoCmd_Button(phost, 5, 190, 100, 40, 12, 0, "\x5f");
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//
//
//
//			Keyboard(phost, tag);
////			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
////			Ft_Gpu_CoCmd_Keys(phost, 5, 200, 315, 20, 2, (OPT_CENTER | tag), "0123456789.<");
////			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//		break;
//	}
//
//	Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
//	Ft_Gpu_CoCmd_Swap(phost);
//
//	/* Download the commands into fifo */
//	Ft_App_Flush_Co_Buffer(phost);
//
//	/* Wait till coprocessor completes the operation */
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//
//    Ft_Gpu_Hal_Sleep(5);
//}


//ft_uint16_t API_Screen_BasicScreen(Ft_Gpu_Hal_Context_t *phost, Screen_TypeDef SCREEN)
//{
//	Ft_Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000, SAMApp_Metric_L1, SAMApp_Metric_L1_SIZE); //загружаем метрику шрифта
//	Ft_Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000 + SAMApp_Metric_L1_SIZE, SAMApp_L1, SAMApp_L1_SIZE); //загружаем шрифт
//
//	Ft_Gpu_CoCmd_Dlstart(phost); // команда начала дисплей-листа
//
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR(0xff,0xff,0xff));
//
//	//Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff)); //установка цвета фона
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1)); //установка цвета фона
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(255,0,0)); // установка цвета текста
//	Ft_App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(12)); //назначение нашему шрифту указателя
//
//	Ft_App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(1085));
//	Ft_App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(L1,3,21));
//	Ft_App_WrCoCmd_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER,BORDER,18,21));
//	Ft_Gpu_CoCmd_SetFont(phost, 12, RAM_G + 1000);
//
//	switch (SCREEN){
//		case MAIN:
//			API_Screen_MainScreen(phost);
//		break;
//		case SETTINGS:
//			;//API_Screen_SettingsScreen(phost, SCREEN);
//		break;
//		case MATERIAL:
//			;//API_Screen_MaterialScreen(phost, SCREEN);
//		break;
//		case CALIBRATION:
//			;//API_Screen_LogsScreen(phost);
//		break;
//	}
//
//	Ft_App_Flush_Co_Buffer(phost);
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//	//while(0!=Ft_Gpu_Hal_Rd16(phost,REG_CMD_READ));
//
//	ft_uint16_t dloffset = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL); // размер коируемого дисплей-листа
//	//dloffset -= 4;
//	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY); // указание FT800 скопировать области памяти
//	Ft_Gpu_Hal_WrCmd32(phost,100000L); // адрес, куда будем копировать в области графической памяти RAM_G
//	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL); // адрес, откуда копируем
//	Ft_Gpu_Hal_WrCmd32(phost,dloffset); // количество байт
//
//	Ft_Gpu_Hal_Sleep(50);
//	return dloffset;
//
//}
//
//void API_Screen_MainScreen(Ft_Gpu_Hal_Context_t *phost)
//{
//	Ft_App_WrCoCmd_Buffer(phost, white);
//	Ft_Gpu_CoCmd_Text(phost, 2, 7, 12, 0, "\x21\x20\x18\x02\x12\x02\x1e\x14\x42"); //Показания
//	Ft_Gpu_CoCmd_Text(phost, 117, 7,  12, 0, "\x65\x67\x60"); //Fk=
//	Ft_Gpu_CoCmd_Text(phost, 227, 7, 12, 0, "\x63\x67\x60"); //Ak=
//
//	Ft_Gpu_CoCmd_Text(phost, 2, 59, 12, 0, "\x13\x12\x1c\x0c\x24\x0c\x1e\x14\x42"); //Измерения
//	Ft_Gpu_CoCmd_Text(phost, 117, 42, 12, 0, "\x63\x53\x60"); //A0=
//	Ft_Gpu_CoCmd_Text(phost, 227, 42, 12, 0, "\x66\x67\x60"); //hk=
//	Ft_Gpu_CoCmd_Text(phost, 117, 77, 12, 0, "\x65\x67\x60"); //Fk=
//	Ft_Gpu_CoCmd_Text(phost, 227, 77, 12, 0, "\x63\x67\x60"); //Ak=
//
//	Ft_Gpu_CoCmd_Text(phost, 2, 129, 12, 0, "\x05\x3a\x32\x14\x26\x1a\x0c\x1e\x14\x42"); //Вычисления
//	Ft_Gpu_CoCmd_Text(phost, 117, 112, 12, 0, "\x0b\x43\x60"); //E =
//	Ft_Gpu_CoCmd_Text(phost, 227, 112, 12, 0, "\x64\x27\x60"); //ST=
//	Ft_Gpu_CoCmd_Text(phost, 117, 147, 12, 0, "\x1d\x05\x60"); //HB=
//	Ft_Gpu_CoCmd_Text(phost, 227, 147, 12, 0, "\x64\x05\x60"); //SB=
//
//
//	Ft_App_WrCoCmd_Buffer(phost,gray);
//	Ft_App_WrCoCmd_Buffer(phost,BEGIN(LINES));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0, 35, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(FT_Width, 35, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(110, 70, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(FT_Width, 70, 0, 0));
//
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0, 105, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(FT_Width, 105, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(110, 140, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(FT_Width, 140, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0, 175, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(FT_Width, 175, 0, 0));
//
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(110, 0, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(110, 175, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(220, 0, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(220, 175, 0, 0));
//
//	Ft_App_WrCoCmd_Buffer(phost,END());
//
//}




//ft_void_t Keyboard(Ft_Gpu_Hal_Context_t *phost, ft_uint16_t tag)
//{
////	ft_uint8_t TextFont = 12;
////	ft_uint8_t ButtonW = 40;
////	ft_uint8_t ButtonH = 40;
////	ft_uint8_t yBtnDst = 5;
////	ft_uint8_t CurrChar = '|';
////	ft_uint8_t CurrTag = 0;
////	ft_uint8_t PrevTag = 0;
////	//ft_uint8_t Pendown = 1;
////	ft_uint8_t CurrTextIdx = 0;
//	ft_uint16_t FT_DispWidth = 320;
////	ft_uint8_t yOffset = 0;
//
//	/* Check the user input and then add the characters into array */
//	CurrTag = tag;
////	Pendown = ((Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_DIRECT_XY)>>31) & 0x01);
//	CurrChar = CurrTag;
//
//	if(CurrTag==249)
//	{
//		CurrTag=0;
//	}
//	if(0 == CurrTag)
//	{
//		CurrChar = '\x52';
//	}
//
//	/* check whether pendown has happened */
//	if( /*( 1 == Pendown) &&*/ (0 != PrevTag))
//	{
//		CurrTextIdx++;
////		/* clear all the charaters after 24 are pressed */
////		if(CurrTextIdx > 24)
////		{
////			CurrTextIdx = 0;
////		}
//	}
//
////	Ft_Gpu_CoCmd_Dlstart(phost);
////	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
////	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
////	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
//
//	/* Draw text entered by user */
//	/* make sure the array is a string */
//	DispText[CurrTextIdx] = CurrChar;
////	DispText[CurrTextIdx + 1] = '\0';
//	Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
//	Ft_Gpu_CoCmd_Text(phost,FT_DispWidth/2, 40, 12, OPT_CENTER, DispText);//text info
//	Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
////	yOffset = 80 + 10;
//	/* Construct a simple keyboard - note that the tags associated with the keys are the character values given in the arguments */
//	Ft_Gpu_CoCmd_FgColor(phost,0x404080);
//	Ft_Gpu_CoCmd_GradColor(phost,0x00ff00);
//
//// Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont,(OPT_CENTER | CurrTag), "qwertyuiop");
//// Ft_Gpu_CoCmd_GradColor(phost,0x00ffff);
//// yOffset += ButtonH + yBtnDst;
//// Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont,(OPT_CENTER | CurrTag), "asdfghjkl");
//// Ft_Gpu_CoCmd_GradColor(phost,0xffff00);
//// yOffset += ButtonH + yBtnDst;
//// Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont,(OPT_CENTER | CurrTag), "zxcvbnm");//hilight button z
//// yOffset += ButtonH + yBtnDst;
//// Ft_App_WrCoCmd_Buffer(phost,TAG(' '));
////
//// if(' ' == CurrTag)
//// {
////	 Ft_Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER | OPT_FLAT, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
//// }
//// else
//// {
////	 Ft_Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
//// }
//
//
////	yOffset = 80 + 10;
//	Ft_Gpu_CoCmd_Keys(phost, 40, 80, 6*40, 40, 12, (0 | CurrTag), "\x53\x54\x55\x56\x57\x58");
//	Ft_Gpu_CoCmd_Keys(phost, 40, 140, 6*40, 40, 12, (0 | CurrTag), "\x59\x5a\x5b\x5c\x50\x51");
////	yOffset += ButtonH + yBtnDst;
////	Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "456");
////	yOffset += ButtonH + yBtnDst;
////	Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "123");
////	yOffset += ButtonH + yBtnDst;
////	Ft_App_WrCoCmd_Buffer(phost,COLOR_A(255));
////	Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "0.");//hilight button 0
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
//
////	StringArray[0] = '\0';
////	strcat(StringArray,"Next demo in ");
////	Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
////	strcat(StringArray,"s");
////	Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX,StringArray);
////	if(tftConfig == RTP35 || tftConfig == RTP43 || tftConfig == CTP35 || tftConfig== CTP43)
////	{
////		Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
////		Ft_App_WrCoCmd_Buffer(phost,TAG(249));
////		Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
////		CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
////	}
//
//	PrevTag = CurrTag;
//}



//ft_void_t SAMAPP_API_Test_Screen_Content(Ft_Gpu_Hal_Context_t *phost,
//		Screen_TypeDef SCREEN, State_TypeDef STATE,
//		ft_uint16_t tag,
//		ft_uint16_t dloffset)
//{
//	//Ft_Gpu_CoCmd_Dlstart(phost); // начало нового дисплей-листа
//	//Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
//	//Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
//
//	Ft_Gpu_CoCmd_Append(phost,100000L, dloffset); // добавление к текущему набору команд, команд скопированных MEMCPY
//
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0x00,0xff));
//	Ft_Gpu_CoCmd_Text(phost, 10, 50, 16, 0, "CONTENT");
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xd8,0x00));
//	Ft_Gpu_CoCmd_Number(phost, 10, 70, 16, 0, STATE);
//
//	Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
//	Ft_Gpu_CoCmd_Swap(phost);
//
//	/* Download the commands into fifo */
//	Ft_App_Flush_Co_Buffer(phost);
//
//	/* Wait till coprocessor completes the operation */
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//
//    Ft_Gpu_Hal_Sleep(5);
//}


ft_void_t __SAMAPP_BootupConfig(Ft_Gpu_Hal_Context_t *phost)
{
	/* Do a power cycle for safer side */
	HAL_GPIO_WritePin(GPIOB, FT800_PD_N, GPIO_PIN_SET); 	// Initial state of PD_N - high
	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Initial state of SPI CS - high
	HAL_Delay(20);																				// Wait 20ms
	HAL_GPIO_WritePin(GPIOB, FT800_PD_N, GPIO_PIN_RESET); // Reset FT800
	HAL_Delay(20);																				// Wait 20ms
	HAL_GPIO_WritePin(GPIOB, FT800_PD_N, GPIO_PIN_SET); 	// FT800 is awake
	HAL_Delay(20);

	  ft800cmdWrite(FT800_ACTIVE);													// Start FT800
	  HAL_Delay(20);																					// Give some time to process
	  ft800cmdWrite(FT800_CLKEXT);													// Set FT800 for external clock
	  HAL_Delay(20);																					// Give some time to process
	  ft800cmdWrite(FT800_CLK48M);													// Set FT800 for 48MHz PLL
	  HAL_Delay(20);
	  ft800cmdWrite(FT_GPU_CORE_RESET);
	  HAL_Delay(20);

	/* Do a core reset for safer side */
	//Ft_Gpu_HostCommand(phost,FT_GPU_CORE_RESET);


	{
		ft_uint8_t chipid;
		//Read Register ID to check if FT800 is ready.
		HAL_Delay(20);
		chipid = ft800memRead8(REG_ID);
		HAL_Delay(20);
		while(chipid != 0x7C)
		chipid = ft800memRead8(REG_ID);

	}
	 /* Global variables for display resolution to support various display panels */
	  /* Default is WQVGA - 480x272 */
	  ft_int16_t FT_DispWidth = 320;
	  ft_int16_t FT_DispHeight = 240;
	  ft_int16_t FT_DispHCycle =  360;
	  ft_int16_t FT_DispHOffset = 43;
	  ft_int16_t FT_DispHSync0 = 0;
	  ft_int16_t FT_DispHSync1 = 63;
	  ft_int16_t FT_DispVCycle = 278;
	  ft_int16_t FT_DispVOffset = 12;
	  ft_int16_t FT_DispVSync0 = 0;
	  ft_int16_t FT_DispVSync1 = 15;
	  ft_uint8_t FT_DispPCLK = 8;
	  ft_char8_t FT_DispSwizzle = 0;
	  ft_char8_t FT_DispPCLKPol = 1;

	    FT_DispWidth = 320;
		FT_DispHeight = 240;
		FT_DispHCycle =  408;
		FT_DispHOffset = 70;
		FT_DispHSync0 = 0;
		FT_DispHSync1 = 10;
		FT_DispVCycle = 263;
		FT_DispVOffset = 13;
		FT_DispVSync0 = 0;
		FT_DispVSync1 = 2;
		FT_DispPCLK = 8;
		FT_DispSwizzle = 2;
		FT_DispPCLKPol = 0;


		ft800memWrite16( REG_HCYCLE, FT_DispHCycle);
		ft800memWrite16( REG_HOFFSET, FT_DispHOffset);
		ft800memWrite16( REG_HSYNC0, FT_DispHSync0);
		ft800memWrite16( REG_HSYNC1, FT_DispHSync1);
		ft800memWrite16( REG_VCYCLE, FT_DispVCycle);
		ft800memWrite16( REG_VOFFSET, FT_DispVOffset);
		ft800memWrite16( REG_VSYNC0, FT_DispVSync0);
		ft800memWrite16( REG_VSYNC1, FT_DispVSync1);
		ft800memWrite16( REG_SWIZZLE, FT_DispSwizzle);
		ft800memWrite16( REG_PCLK_POL, FT_DispPCLKPol);

	  ft800memWrite8( REG_PCLK,FT_DispPCLK);//after this display is visible on the LCD
	  ft800memWrite16( REG_HSIZE, FT_DispWidth);
	  ft800memWrite16( REG_VSIZE, FT_DispHeight);

	  //ft800memWrite8( REG_GPIO_DIR,0x83 | ft800memRead8(REG_GPIO_DIR));
	  //ft800memWrite8( REG_GPIO,0x083 | ft800memRead8(REG_GPIO));

	/* Touch configuration - configure the resistance value to 1200 - this value is specific to customer requirement and derived by experiment */
	  ft800memWrite16(REG_TOUCH_RZTHRESH,1200);
	  ft800memWrite8(REG_GPIO_DIR,0xff);
	  ft800memWrite8(REG_GPIO,0x0ff);

//	  ft800memWrite8(REG_TOUCH_MODE, 3);															// Enable touch
//	  	ft800memWrite8(REG_TOUCH_ADC_MODE, 1);
//	  	ft800memWrite16(REG_TOUCH_CHARGE, 5000);
//	  	ft800memWrite8(REG_TOUCH_SETTLE, 3);
//	  	ft800memWrite8(REG_TOUCH_OVERSAMPLE, 7);
//	  	ft800memWrite16(REG_TOUCH_RZTHRESH, 1500);

//	  Ft_Gpu_Hal_Wr16(phost, REG_TOUCH_RZTHRESH,1200);
//	delay_ms(10);
//	Ft_Gpu_Hal_Wr32(phost, REG_PWM_DUTY,255);


	 /* Boot up for FT800 followed by graphics primitive sample cases */
	  /* Initial boot up DL - make the back ground green color */
//	  const ft_uint8_t FT_DLCODE_BOOTUP[12] =
//	  {
//	      0,255,0,2,//GPU instruction CLEAR_COLOR_RGB
//	      7,0,0,38, //GPU instruction CLEAR
//	      0,0,0,0,  //GPU instruction DISPLAY
//	  };

	  /*It is optional to clear the screen here*/
//	      Ft_Gpu_Hal_WrMem(phost, RAM_DL,(ft_uint8_t *)FT_DLCODE_BOOTUP,sizeof(FT_DLCODE_BOOTUP));
//	      Ft_Gpu_Hal_Wr8(phost, REG_DLSWAP,DLSWAP_FRAME);


	  //    Ft_Gpu_Hal_Wr8(phost, REG_PCLK,FT_DispPCLK);//after this display is visible on the LCD

	  __SAMAPP_API_Calibrate(0); // работает

	  //Ft_Gpu_Hal_Sleep(50);//Show the booting up screen.

//		// start of Display List
//		ft_uint32_t ramDisplayList = RAM_DL;
//
//		// Clear Color RGB   00000010 RRRRRRRR GGGGGGGG BBBBBBBB  (R/G/B = Colour values) default zero / black
//		ft800memWrite32(ramDisplayList, DL_CLEAR_RGB);
//
//		ramDisplayList += 4;// point to next location
//		// Clear 00100110 -------- -------- -----CST  (C/S/T define which parameters to clear)
//		ft800memWrite32(ramDisplayList, (DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));
//
//		ramDisplayList += 4;
//		// DISPLAY command 00000000 00000000 00000000 00000000 (end of display list)
//		ft800memWrite32(ramDisplayList, DL_DISPLAY);
//		// 00000000 00000000 00000000 000000SS  (SS bits define when render occurs)
//		ft800memWrite32(REG_DLSWAP, DLSWAP_FRAME);
//		// Nothing is being displayed yet... the pixel clock is still 0x00
//
//		unsigned char ft800Gpio;
//		// Read the FT800 GPIO register for a read/modify/write operation
//		ft800Gpio = ft800memRead8(REG_GPIO);
//		// set bit 7 of FT800 GPIO register (DISP) - others are inputs
//		ft800Gpio = ft800Gpio | 0x80;
//		// Enable the DISP signal to the LCD panel
//		ft800memWrite8(REG_GPIO, ft800Gpio);
//		// Now start clocking data to the LCD panel
//		ft800memWrite8(REG_PCLK, FT_DispPCLK);
//		for(int duty = 0; duty <= 128; duty++)
//		{
//			// Turn on backlight - ramp up slowly to full brighness
//			ft800memWrite8(REG_PWM_DUTY, duty);
//			HAL_Delay(10);
//		}


}



ft_void_t __SAMAPP_API_Calibrate(ft_uint8_t mode)
{
	ft_uint32_t REG_TOUCH_CALIBRATE_A;
	ft_uint32_t REG_TOUCH_CALIBRATE_B;
	ft_uint32_t REG_TOUCH_CALIBRATE_C;
	ft_uint32_t REG_TOUCH_CALIBRATE_D;
	ft_uint32_t REG_TOUCH_CALIBRATE_E;
	ft_uint32_t REG_TOUCH_CALIBRATE_F;
	if (mode == 0) {
		REG_TOUCH_CALIBRATE_A = 0x00005a81;
		REG_TOUCH_CALIBRATE_B = 0x00000066;
		REG_TOUCH_CALIBRATE_C = 0xfff89d6b;
		REG_TOUCH_CALIBRATE_D = 0xfffffcb6;
		REG_TOUCH_CALIBRATE_E = 0x00006c3f;
		REG_TOUCH_CALIBRATE_F = 0x20003fd0;

		ft800memWrite32( REG_TOUCH_TRANSFORM_A, REG_TOUCH_CALIBRATE_A);
		ft800memWrite32( REG_TOUCH_TRANSFORM_B, REG_TOUCH_CALIBRATE_B);
		ft800memWrite32( REG_TOUCH_TRANSFORM_C, REG_TOUCH_CALIBRATE_C);
		ft800memWrite32( REG_TOUCH_TRANSFORM_D, REG_TOUCH_CALIBRATE_D);
		ft800memWrite32( REG_TOUCH_TRANSFORM_E, REG_TOUCH_CALIBRATE_E);
		ft800memWrite32( REG_TOUCH_TRANSFORM_F, REG_TOUCH_CALIBRATE_F);
	} else {
//		Ft_Gpu_CoCmd_Dlstart(phost);
//		//Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
//		Ft_Gpu_CoCmd_Calibrate(phost,0);
//		Ft_App_Flush_Co_Buffer(phost);
//		Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

		cmd_dlstart();
		cmd(CMD_CALIBRATE);
		cmd(0);
		cmd(DISPLAY());//cmd(DL_DISPLAY);
		//cmd_swap();//cmd(CMD_SWAP);

		unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
		unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer

		ft800memWrite16(REG_CMD_WRITE, cli);
		do
		{
			cmdBufferRd = ft800memRead16(REG_CMD_READ);															// Read the graphics processor read pointer
			cmdBufferWr = ft800memRead16(REG_CMD_WRITE); 														// Read the graphics processor write pointer
		} while (cmdBufferWr != cmdBufferRd);

		REG_TOUCH_CALIBRATE_A = ft800memRead32(REG_TOUCH_TRANSFORM_A);
		REG_TOUCH_CALIBRATE_B = ft800memRead32(REG_TOUCH_TRANSFORM_B);
		REG_TOUCH_CALIBRATE_C = ft800memRead32(REG_TOUCH_TRANSFORM_C);
		REG_TOUCH_CALIBRATE_D = ft800memRead32(REG_TOUCH_TRANSFORM_D);
		REG_TOUCH_CALIBRATE_E = ft800memRead32(REG_TOUCH_TRANSFORM_E);
		REG_TOUCH_CALIBRATE_F = ft800memRead32(REG_TOUCH_TRANSFORM_F);

		ft800memWrite32( REG_TOUCH_TRANSFORM_A, REG_TOUCH_CALIBRATE_A);
		ft800memWrite32( REG_TOUCH_TRANSFORM_B, REG_TOUCH_CALIBRATE_B);
		ft800memWrite32( REG_TOUCH_TRANSFORM_C, REG_TOUCH_CALIBRATE_C);
		ft800memWrite32( REG_TOUCH_TRANSFORM_D, REG_TOUCH_CALIBRATE_D);
		ft800memWrite32( REG_TOUCH_TRANSFORM_E, REG_TOUCH_CALIBRATE_E);
		ft800memWrite32( REG_TOUCH_TRANSFORM_F, REG_TOUCH_CALIBRATE_F);
	}

	HAL_Delay(5);
}






ft_void_t __SAMAPP_API_Screen_Content(Ft_Gpu_Hal_Context_t *phost,
		Screen_TypeDef SCREEN, State_TypeDef STATE,
		ft_uint16_t tag,
		ft_uint16_t dloffset,
		double F, double A, double A0, double H, double F1, double A1,
		double E, double HB, double ST, double SB,
		ft_uint16_t nmb)
{
	unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdOffset = 0x0000;

	//ft800memWrite32(REG_CMD_WRITE, 0);
	//ft800memWrite32(REG_CMD_READ, 0);
	//cli = dloffset;
	//ft800memWrite32(REG_CMD_WRITE, cli);
	//ft800memWrite32(REG_CMD_READ, cli);

	ft_uint32_t storedMaterial;

	uint8_t value_c_length = 10;
	char value_c[value_c_length];

	do
	{
		cmdBufferRd = ft800memRead32(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead32(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);
	//cli = cmdBufferWr;
	cli = cli__;
//	ft800memWrite16(REG_CMD_WRITE, cli__);
//	ft800memWrite16(REG_CMD_READ, cli__);

//	cli = 0;
//
	ft800memWrite32(REG_CMD_READ, 0);
	ft800memWrite32(REG_CMD_WRITE, 0);


	cmd_dlstart();
	cmd_append(10000L, dloffset);





//	cmd(CLEAR_COLOR_RGB(0,0,0));
//	cmd(CLEAR(0xff,0xff,0xff));
//	cmd(COLOR_RGB(255,0,0)); // установка цвета текста
//
//
//	cmd(BITMAP_HANDLE(12)); //назначение нашему шрифту указателя
//	cmd(BITMAP_SOURCE(1085));
//	cmd(BITMAP_LAYOUT(L1,3,21));
//	cmd(BITMAP_SIZE(NEAREST,BORDER,BORDER,18,21));
//	cmd(CMD_SETFONT);
//	cmd(12);
//	cmd(RAM_G + FONT_POS);
//
//	switch (SCREEN){
//		case MAIN:
//			__API_Screen_MainScreen(phost);
//		break;
//		case SETTINGS:
//			;//API_Screen_SettingsScreen(phost, SCREEN);
//		break;
//		case MATERIAL:
//			;//API_Screen_MaterialScreen(phost, SCREEN);
//		break;
//		case CALIBRATION:
//			;//API_Screen_LogsScreen(phost);
//		break;
//	}










	cmd(COLOR_RGB(0xff, 0xd8, 0));// установка цвета текста
	cmd_number(10, 60, 16, 0, nmb);
	//cmd_text( 10, 10, 12, 0, "\x21\x24\x14\x06\x0c\x28\x43\x5b\x5d");
	//cmd_text( 10, 30, 12, 0, "\x58\x59\x5a");

	//Ft_Gpu_CoCmd_Dlstart(phost); // начало нового дисплей-листа
	//Ft_Gpu_CoCmd_Append(phost,100000L, dloffset); // добавление к текущему набору команд, команд скопированных MEMCPY

	switch (SCREEN){
		case MAIN:
			//Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
			//Ft_App_WrCoCmd_Buffer(phost,CLEAR(0xff,0xff,0xff));


			//Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0x00,0xff));
			//Ft_Gpu_CoCmd_Text(phost, 10, 50, 16, 0, "CONTENT");
			cmd(COLOR_RGB(0xff, 0xd8, 0)); //Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xd8,0x00));
			//Ft_Gpu_CoCmd_Number(phost, 10, 60, 16, 0, nmb);
			//Ft_Gpu_CoCmd_Number(phost, 10, 70, 16, 0, STATE);

			//Ft_Gpu_CoCmd_Text(phost, 117, 7,  12, 0, "\x65\x67\x60"); //Fk=
			//Ft_Gpu_CoCmd_Text(phost, 227, 7, 12, 0, "\x63\x67\x60"); //Ak=


			//float b = 12.234;
			sprintf(value_c, "%d.%d", (int)F, (int)( ( F - floor(F) ) * pow(10, 1) ));
			cmd_text(155, 7, 22, 0, value_c); //Ft_Gpu_CoCmd_Text(phost, 155, 7, 22, 0, value_c);
			sprintf(value_c, "%d.%d", (int)A, (int)( ( A - floor(A) ) * pow(10, 3) ));
			cmd_text(265, 7, 22, 0, value_c); //Ft_Gpu_CoCmd_Text(phost, 265, 7, 22, 0, value_c);


			switch (STATE)
		  {
			case IDLE:
			  //placeValuesReset();
				cmd(TAG_MASK(1));
				cmd(TAG(2));
				//cmd_track(110, 190, 100, 40, 2);          // assign the tag value
				cmd_fgcolor((tag==2)?button_color_hover:button_color);
				cmd_button(110, 190, 100, 40, R_FONT, 0, "\x21\x2a\x26\x18");
				cmd(TAG_MASK(0));
			break;
			case TOUCH:
			  //placeValuesReset();
				cmd(TAG_MASK(1));
				cmd(TAG(2));          // assign the tag value
				cmd_fgcolor((tag==2)?button_color_hover:button_color);
				cmd_button(110, 190, 100, 40, R_FONT, 0, "\x17\x02\x26\x02\x1e\x14\x0c");
				cmd(TAG_MASK(0));
			break;
			case MEASURE:
				cmd(TAG_MASK(1));
				cmd(TAG(2));          // assign the tag value
				cmd_fgcolor((tag==2)?button_color_hover:button_color);
				cmd_button(110, 190, 100, 40, R_FONT, 0, "\x13\x12\x1c\x0c\x24\x0c\x1e\x14\x0c");
				cmd(TAG_MASK(0));

				sprintf(value_c, "%d.%d", (int)A0, (int)( ( A0 - floor(A0) ) * pow(10, 3) ));
				cmd_text(155, 42, 22, 0, value_c);
			break;
			case REMOVAL:

				cmd(TAG_MASK(1));
				cmd(TAG(2));          // assign the tag value
				cmd_fgcolor((tag==2)?button_color_hover:button_color);
				cmd_button(110, 190, 100, 40, R_FONT, 0, "\x25\x1e\x42\x28\x14\x0c");
				cmd(TAG_MASK(0));

				sprintf(value_c, "%d.%d", (int)A0, (int)( ( A0 - floor(A0) ) * pow(10, 3) ));
				cmd_text(155, 42, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)F1, (int)( ( F1 - floor(F1) ) * pow(10, 1) ));
				cmd_text(155, 77, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)A1, (int)( ( A1 - floor(A1) ) * pow(10, 3) ));
				cmd_text(265, 77, 22, 0, value_c);
			break;
			case RESULTS:

				cmd(TAG_MASK(1));
				cmd(TAG(2));          // assign the tag value
				cmd_fgcolor((tag==2)?button_color_hover:button_color);
				cmd_button(110, 190, 100, 40, R_FONT, 0, "\x21\x2a\x26\x18");
				cmd(TAG_MASK(0));

				sprintf(value_c, "%d.%d", (int)A0, (int)( ( A0 - floor(A0) ) * pow(10, 3) ));
				cmd_text(155, 42, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)F1, (int)( ( F1 - floor(F1) ) * pow(10, 1) ));
				cmd_text(155, 77, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)A1, (int)( ( A1 - floor(A1) ) * pow(10, 3) ));
				cmd_text(265, 77, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)H, (int)( ( H - floor(H) ) * pow(10, 3) ));
				cmd_text(265, 42, 22, 0, value_c);

				sprintf(value_c, "%d.%d", (int)E, (int)( ( E - floor(E) ) * pow(10, 0) ));
				cmd_text(155, 112, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)ST, (int)( ( ST - floor(ST) ) * pow(10, 2) ));
				cmd_text(265, 112, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)HB, (int)( ( HB - floor(HB) ) * pow(10, 2) ));
				cmd_text(155, 147, 22, 0, value_c);
				sprintf(value_c, "%d.%d", (int)SB, (int)( ( SB - floor(SB) ) * pow(10, 2) ));
				cmd_text(265, 147, 22, 0, value_c);

			break;
		  }


			cmd(TAG_MASK(1));
			cmd(TAG(1));          // assign the tag value
			cmd_fgcolor((tag==1)?button_color_hover:button_color);
			cmd_button(5, 190, 100, 40, R_FONT, 0, "\x1d\x02\x26\x28\x24\x20\x16\x18\x14");
			cmd(TAG_MASK(0));


			cmd(TAG_MASK(1));
			cmd(TAG(3));          // assign the tag value
			cmd_fgcolor((tag==3)?button_color_hover:button_color);
			cmd_button(215, 190, 100, 40, R_FONT, 0, "\x25\x04\x24\x20\x26");
			cmd(TAG_MASK(0));

		break;
		case SETTINGS:
			//tag = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);

			cmd(TAG_MASK(1));
			cmd(TAG(1));          // assign the tag value
			cmd_fgcolor((tag==1)?button_color_hover:button_color);
			cmd_button(5, 190, 100, 40, R_FONT, 0, "\x1d\x02\x26\x28\x24\x20\x16\x18\x14"); // Настройки
			cmd(TAG_MASK(0));

			cmd(TAG_MASK(1));
			cmd(TAG(4));          // assign the tag value
			cmd_fgcolor((tag==4)?button_color_hover:button_color);
			cmd_button( 110, 10, 100, 40, R_FONT, 0, "\x1b\x02\x28\x0c\x24\x14\x02\x1a"); // Материал
			cmd(TAG_MASK(0));

			cmd(TAG_MASK(1));
			cmd(TAG(5));          // assign the tag value
			cmd_fgcolor((tag==5)?button_color_hover:button_color);
			cmd_button( 110, 60, 100, 40, R_FONT, 0, "\x17\x02\x1a\x14\x04\x24\x20\x06\x18\x02"); //Калибровка
			cmd(TAG_MASK(0));

		break;
		case MATERIAL:

			//**storedMaterial = FLASH_Read_DataWord(0);

			cmd(COLOR_RGB(0xff,0xd8,0x00));

			cmd(TAG_MASK(1));
			cmd(TAG(1));          // assign the tag value
			cmd_fgcolor((tag==1)?button_color_hover:button_color);
			cmd_button(5, 190, 100, 40, R_FONT, 0, "\x5f");
			cmd(TAG_MASK(0));


			if (tag >= 201 & tag <=203) {
				cmd(TAG_MASK(1));
				cmd(TAG(201));          // assign the tag value
				cmd_fgcolor((tag==201)?button_color_hover:button_color);
				cmd_button(10, 10, 100, 30, R_FONT, 0, "\x54");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(202));          // assign the tag value
				cmd_fgcolor((tag==202)?button_color_hover:button_color);
				cmd_button(10, 50, 100, 30, R_FONT, 0, "\x55");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(203));          // assign the tag value
				cmd_fgcolor((tag==203)?button_color_hover:button_color);
				cmd_button(10, 90, 100, 30, R_FONT, 0, "\x56");
				cmd(TAG_MASK(0));
			} else {
				cmd(TAG_MASK(1));
				cmd(TAG(201));          // assign the tag value
				cmd_fgcolor((storedMaterial==201)?button_color_selected:button_color);
				cmd_button(10, 10, 100, 30, R_FONT, 0, "\x54");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(202));          // assign the tag value
				cmd_fgcolor((storedMaterial==202)?button_color_selected:button_color);
				cmd_button(10, 50, 100, 30, R_FONT, 0, "\x55");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(203));          // assign the tag value
				cmd_fgcolor((storedMaterial==203)?button_color_selected:button_color);
				cmd_button(10, 90, 100, 30, R_FONT, 0, "\x56");
				cmd(TAG_MASK(0));
			}
		break;
		case CALIBRATION:
			cmd(COLOR_RGB(0xff,0xd8,0x00));

			cmd(TAG_MASK(1));
			cmd(TAG(1));          // assign the tag value
			cmd_fgcolor((tag==1)?button_color_hover:button_color);
			cmd_button(5, 190, 100, 40, R_FONT, 0, "\x5f");
			cmd(TAG_MASK(0));



			//***Keyboard(phost, tag);



//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(1));
//			Ft_Gpu_CoCmd_Keys(phost, 5, 200, 315, 20, 2, (OPT_CENTER | tag), "0123456789.<");
//			Ft_App_WrCoCmd_Buffer(phost,TAG_MASK(0));
		break;
	}

	cmd_number(10, 90, 16, 0, cli__);
	cmd_number(10, 110, 16, 0, cli);
	cmd_number(10, 130, 16, 0, tag);

	cmd(DL_END);
	cmd(DISPLAY());//cmd(DL_DISPLAY);
	cmd_swap();//cmd(CMD_SWAP);

	cli_temp = cli;
	while (cli_dub > cli) {
		cmd(0);
	}
	cli_dub = cli_temp;

	ft800memWrite32(REG_CMD_WRITE, cli );
	do
	{
		cmdBufferRd = ft800memRead32(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead32(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);

//	Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
//	Ft_Gpu_CoCmd_Swap(phost);
//
//	/* Download the commands into fifo */
//	Ft_App_Flush_Co_Buffer(phost);
//
//	/* Wait till coprocessor completes the operation */
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	HAL_Delay(50);
}


ft_uint16_t __API_Screen_BasicScreen(Ft_Gpu_Hal_Context_t *phost, Screen_TypeDef SCREEN)
{
	unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdOffset = 0x0000;												// Used to navigate command rung buffer



	do
	{
		cmdBufferRd = ft800memRead16(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead16(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);
	cli_dub = cmdBufferWr;
	cli = 0;

	ft800memWrite16(REG_CMD_WRITE, 0);
	ft800memWrite16(REG_CMD_READ, 0);

//	cmd_dlstart();
//
//	cmd(CMD_MEMSET);
//	cmd(0);
//	cmd(0);
//	cmd(10*1024);
//
//	ft800memWrite16(REG_CMD_WRITE, cli);
//	do
//	{
//		cmdBufferRd = ft800memRead16(REG_CMD_READ);															// Read the graphics processor read pointer
//		cmdBufferWr = ft800memRead16(REG_CMD_WRITE); 														// Read the graphics processor write pointer
//	} while (cmdBufferWr != cmdBufferRd);


	for (int i = 0; i < SAMApp_Metric_L1_SIZE; i++){
		ft800memWrite8(RAM_G + FONT_POS + i, SAMApp_Metric_L1[i]);
	}
	for (int i = 0; i < SAMApp_L1_SIZE; i++){
		ft800memWrite8(RAM_G + FONT_POS + i + SAMApp_Metric_L1_SIZE, SAMApp_L1[i]);
	}


	cmd_dlstart();


	//cmd(DL_CLEAR_RGB | 0x000000UL);
	//cmd(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);
	//cmd(CLEAR(255, 255, 255));// установка цвета текста
	cmd(CLEAR_COLOR_RGB(0,0,0));
	cmd(CLEAR(0xff,0xff,0xff));
	cmd(COLOR_RGB(255,0,0)); // установка цвета текста


	cmd(BITMAP_HANDLE(12)); //назначение нашему шрифту указателя
	cmd(BITMAP_SOURCE(1085));
	cmd(BITMAP_LAYOUT(L1,3,21));
	cmd(BITMAP_SIZE(NEAREST,BORDER,BORDER,18,21));
	cmd(CMD_SETFONT);
	cmd(12);
	cmd(RAM_G + FONT_POS);

	//Ft_Gpu_CoCmd_Dlstart(phost); // команда начала дисплей-листа

//	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR(0xff,0xff,0xff));
//
//	//Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff)); //установка цвета фона
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1)); //установка цвета фона
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(255,0,0)); // установка цвета текста
//	Ft_App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(12)); //назначение нашему шрифту указателя
//
//	Ft_App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(1085));
//	Ft_App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(L1,3,21));
//	Ft_App_WrCoCmd_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER,BORDER,18,21));
//	Ft_Gpu_CoCmd_SetFont(phost, 12, RAM_G + 1000);

	switch (SCREEN){
		case MAIN:
			__API_Screen_MainScreen(phost);
		break;
		case SETTINGS:
			;//API_Screen_SettingsScreen(phost, SCREEN);
		break;
		case MATERIAL:
			;//API_Screen_MaterialScreen(phost, SCREEN);
		break;
		case CALIBRATION:
			;//API_Screen_LogsScreen(phost);
		break;
	}

	ft_uint16_t dloffset = 0;

	ft800memWrite16(REG_CMD_WRITE, cli);
	do
	{
		cmdBufferRd = ft800memRead16(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead16(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);

	dloffset = ft800memRead16(REG_CMD_DL); // размер коируемого дисплей-листа     cli;//

	cmd_memcpy(10000L, RAM_DL, dloffset);
	//cmd(CMD_MEMCPY); // указание FT800 скопировать области памяти
	//cmd(100000L); // адрес, куда будем копировать в области графической памяти RAM_G
	//cmd(RAM_DL); // адрес, откуда копируем
	//cmd(dloffset); // количество байт

	//cmd(DL_END);
	//cmd(DL_DISPLAY);
	//cmd(CMD_SWAP);

	//ft800memWrite16(REG_CMD_WRITE, cli);
		/* Download the commands into fifo */
		//Ft_App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		//Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	HAL_Delay(5);

	cli__ = cli;
	cli_temp = cli;
	while (cli_dub > cli) {
		cmd(0);
	}
	//cli_dub = cli_temp;
	cli_dub = 0;


	return dloffset;

//	Ft_App_Flush_Co_Buffer(phost);
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//	//while(0!=Ft_Gpu_Hal_Rd16(phost,REG_CMD_READ));
//
//	ft_uint16_t dloffset = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL); // размер коируемого дисплей-листа
//	//dloffset -= 4;
//	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY); // указание FT800 скопировать области памяти
//	Ft_Gpu_Hal_WrCmd32(phost,100000L); // адрес, куда будем копировать в области графической памяти RAM_G
//	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL); // адрес, откуда копируем
//	Ft_Gpu_Hal_WrCmd32(phost,dloffset); // количество байт
//
//	Ft_Gpu_Hal_Sleep(50);
//	return dloffset;

}

void __API_Screen_MainScreen(Ft_Gpu_Hal_Context_t *phost)
{
	cmd(white);
	cmd_text(2, 7, R_FONT, 0, "\x21\x20\x18\x02\x12\x02\x1e\x14\x42"); //Показания
	cmd_text(117, 7,  R_FONT, 0, "\x65\x67\x60"); //Fk=
	cmd_text(227, 7, R_FONT, 0, "\x63\x67\x60"); //Ak=

	cmd_text(2, 59, R_FONT, 0, "\x13\x12\x1c\x0c\x24\x0c\x1e\x14\x42"); //Измерения
	cmd_text(117, 42, R_FONT, 0, "\x63\x53\x60"); //A0=
	cmd_text(227, 42, R_FONT, 0, "\x66\x67\x60"); //hk=
	cmd_text(117, 77, R_FONT, 0, "\x65\x67\x60"); //Fk=
	cmd_text(227, 77, R_FONT, 0, "\x63\x67\x60"); //Ak=

	cmd_text(2, 129, R_FONT, 0, "\x05\x3a\x32\x14\x26\x1a\x0c\x1e\x14\x42"); //Вычисления
	cmd_text(117, 112, R_FONT, 0, "\x0b\x43\x60"); //E =
	cmd_text(227, 112, R_FONT, 0, "\x64\x27\x60"); //ST=
	cmd_text(117, 147, R_FONT, 0, "\x1d\x05\x60"); //HB=
	cmd_text(227, 147, R_FONT, 0, "\x64\x05\x60"); //SB=


	cmd(gray);
	cmd(BEGIN(LINES));
	cmd(VERTEX2II(0, 35, 0, 0));
	cmd(VERTEX2II(FT_Width, 35, 0, 0));
	cmd(VERTEX2II(110, 70, 0, 0));
	cmd(VERTEX2II(FT_Width, 70, 0, 0));

	cmd(VERTEX2II(0, 105, 0, 0));
	cmd(VERTEX2II(FT_Width, 105, 0, 0));
	cmd(VERTEX2II(110, 140, 0, 0));
	cmd(VERTEX2II(FT_Width, 140, 0, 0));
	cmd(VERTEX2II(0, 175, 0, 0));
	cmd(VERTEX2II(FT_Width, 175, 0, 0));

	cmd(VERTEX2II(110, 0, 0, 0));
	cmd(VERTEX2II(110, 175, 0, 0));
	cmd(VERTEX2II(220, 0, 0, 0));
	cmd(VERTEX2II(220, 175, 0, 0));

	cmd(END());

}

ft_void_t SAMAPP_API_Screen(Ft_Gpu_Hal_Context_t *phost, ft_char8_t *str)
{
	unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdOffset = 0x0000;												// Used to navigate command rung buffer
	unsigned int point_size = 0x0100;												// Define a default dot size
	unsigned long point_x = (96 * 16);											// Define a default point x-location (1/16 anti-aliased)
	unsigned long point_y = (136 * 16);											// Define a default point y-location (1/16 anti-aliased)
	unsigned long color;


	do
	{
		cmdBufferRd = ft800memRead16(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead16(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);
	cli = cmdBufferWr;
	//cli = 0;

	ft800memWrite32(REG_CMD_WRITE, 0);
	ft800memWrite32(REG_CMD_READ, 0);

	cmd_dlstart();

	cmd(DL_CLEAR_RGB | 0x000000UL);
	cmd(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);

	cmd_fgcolor(0xff00ff);
	cmd_text( 150, 100, 16, "Test");

//	Ft_Gpu_CoCmd_Dlstart(phost);
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR(0xff,0x00,0x0f));

//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xaa,0xa0,0x0a));
//	Ft_Gpu_CoCmd_Text(phost, 150, 100, 16, OPT_CENTER, str);

//	Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
//	Ft_Gpu_CoCmd_Swap(phost);
//
//	/* Download the commands into fifo */
//	Ft_App_Flush_Co_Buffer(phost);
//
//	/* Wait till coprocessor completes the operation */
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	cmd(DL_END);
	cmd(DL_DISPLAY);
	cmd(CMD_SWAP);

	ft800memWrite16(REG_CMD_WRITE, cli);

	HAL_Delay(10);

//	do{
//	cmdBufferRd = ft800memRead16(REG_CMD_READ);	// Read the graphics processor read pointer
//				cmdBufferWr = ft800memRead16(REG_CMD_WRITE);// Read the graphics processor write pointer
//			}while (cmdBufferWr != cmdBufferRd);// Wait until the two registers match
//
//			cmdOffset = cmdBufferWr;// The new starting point the first location after the last command
//
//	ft800memWrite32(RAM_CMD + cmdOffset, (DL_DISPLAY)); // Instruct the graphics processor to show the list
//	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer
//
//	ft800memWrite32(RAM_CMD + cmdOffset, (CMD_SWAP)); // Make this list active
//	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer
//
//	ft800memWrite16(REG_CMD_WRITE, (cmdOffset));// Update the ring buffer pointer so the graphics processor starts executin

	Ft_Gpu_Hal_Sleep(50);
}


void API_Screen_Test()
{
	unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdOffset = 0x0000;												// Used to navigate command rung buffer
	unsigned int point_size = 0x0100;												// Define a default dot size
	unsigned long point_x = (96 * 16);											// Define a default point x-location (1/16 anti-aliased)
	unsigned long point_y = (136 * 16);											// Define a default point y-location (1/16 anti-aliased)
	unsigned long color;

	do
	{
		cmdBufferRd = ft800memRead16(REG_CMD_READ);	// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead16(REG_CMD_WRITE);// Read the graphics processor write pointer
	}while (cmdBufferWr != cmdBufferRd);// Wait until the two registers match

	cmdOffset = cmdBufferWr;// The new starting point the first location after the last command

	color = 0xFF0000;

	ft800memWrite32(RAM_CMD + cmdOffset, (CMD_DLSTART)); // Start the display list
	cmdOffset = incCMDOffset(cmdOffset, 4); // Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (DL_CLEAR_RGB | 0x000000));// Set the default clear color to black
	cmdOffset = incCMDOffset(cmdOffset, 4);// Update the command pointer


	ft800memWrite32(RAM_CMD + cmdOffset, (DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG));// Clear the screen - this and the previous prevent artifacts between lists
	// Attributes are the color, stencil and tag buffers
	cmdOffset = incCMDOffset(cmdOffset, 4);// Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (DL_COLOR_RGB | color));// Set the color of the following item(s) - toggle red/white from above
	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (DL_POINT_SIZE | point_size));// Select the size of the dot to draw
	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (DL_BEGIN | FTPOINTS));// Indicate to draw a point (dot)
	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (DL_VERTEX2F | (point_x << 15) | point_y));// Set the point center location
	cmdOffset = incCMDOffset(cmdOffset, 4);// Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (DL_END));	// End the point
	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (DL_DISPLAY)); // Instruct the graphics processor to show the list
	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer

	ft800memWrite32(RAM_CMD + cmdOffset, (CMD_SWAP)); // Make this list active
	cmdOffset = incCMDOffset(cmdOffset, 4);	// Update the command pointer

	ft800memWrite16(REG_CMD_WRITE, (cmdOffset));// Update the ring buffer pointer so the graphics processor starts executing

	HAL_Delay(50);
}






ft_uint16_t __SAMAPP_API_Screen_BackGround(Ft_Gpu_Hal_Context_t *phost, ft_char8_t *str)
{
	unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdOffset = 0x0000;												// Used to navigate command rung buffer

	//Ft_Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000, SAMApp_Metric_L1, SAMApp_Metric_L1_SIZE); //загружаем метрику шрифта
	//Ft_Gpu_Hal_WrMemFromFlash(phost, RAM_G + 1000 + SAMApp_Metric_L1_SIZE, SAMApp_L1, SAMApp_L1_SIZE); //загружаем шрифт

	for (int i = 0; i < SAMApp_Metric_L1_SIZE; i++){
		ft800memWrite8(RAM_G + 1000 + i, SAMApp_Metric_L1[i]);
	}
	for (int i = 0; i < SAMApp_L1_SIZE; i++){
		ft800memWrite8(RAM_G + 1000 + i + SAMApp_Metric_L1_SIZE, SAMApp_L1[i]);
	}

	do
	{
		cmdBufferRd = ft800memRead16(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead16(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);
	cli = cmdBufferWr;
	cli = 0;

	ft800memWrite32(REG_CMD_WRITE, 0);
	ft800memWrite32(REG_CMD_READ, 0);

	cmd_dlstart();

	cmd(DL_CLEAR_RGB | 0x010101UL);
	cmd(DL_CLEAR | CLR_COL | CLR_STN | CLR_TAG);

	cmd(COLOR_RGB(255, 0, 0));// установка цвета текста


	cmd(BITMAP_HANDLE(12)); //назначение нашему шрифту указателя
	cmd(BITMAP_SOURCE(1085));
	cmd(BITMAP_LAYOUT(L1,3,21));
	cmd(BITMAP_SIZE(NEAREST,BORDER,BORDER,18,21));
	cmd(CMD_SETFONT);
	cmd(12);
	cmd(RAM_G + 1000);
	//Ft_Gpu_CoCmd_SetFont(phost, 12, RAM_G + 1000);



	//cmd_text( 10, 10, 12, 0, "\x21\x24\x14\x06\x0c\x28\x43\x5b\x5d");

	//cmd_text( 10, 30, 12, 0, "\x58\x59\x5a");

	cmd(BEGIN(RECTS));
//	cmd(VERTEX2II(1, 203, 0, 0));
//	cmd(COLOR_RGB(22, 23, 26));
//	cmd(VERTEX2II(496, 291, 0, 0));
	cmd(VERTEX2II(0, 30, 0, 0));
	cmd(VERTEX2II(300, 30, 0, 0));
	cmd(VERTEX2II(0, 50, 0, 0));
	cmd(VERTEX2II(300, 50, 0, 0));
	cmd(VERTEX2II(160, 0, 0, 0));
	cmd(VERTEX2II(160, 120, 0, 0));
	cmd(END());

	//  Ft_Gpu_CoCmd_Dlstart(phost); // команда начала дисплей-листа

	  //Ft_Gpu_CoCmd_Dlstart(phost);
	//  Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0,0,0));
	//  Ft_App_WrCoCmd_Buffer(phost,CLEAR(0xff,0xff,0xff));


	  //Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(0xff,0xff,0xff)); //установка цвета фона
	//  Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1)); //установка цвета фона
	//  Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(255,0,0)); // установка цвета текста


//	  Ft_App_WrCoCmd_Buffer(phost,BITMAP_HANDLE(12)); //назначение нашему шрифту указателя
//	  Ft_App_WrCoCmd_Buffer(phost,BITMAP_SOURCE(1085));
//	  Ft_App_WrCoCmd_Buffer(phost, BITMAP_LAYOUT(L1,3,21));
//	  Ft_App_WrCoCmd_Buffer(phost, BITMAP_SIZE(NEAREST, BORDER,BORDER,18,21));
//	  Ft_Gpu_CoCmd_SetFont(phost, 12, RAM_G + 1000);



//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0x00,0xff,0x00));
//	Ft_Gpu_CoCmd_Text(phost, 10, 10, 12, 0, "\x21\x24\x14\x06\x0c\x28\x43\x5b\x5d");
//	//Ft_Gpu_CoCmd_Text(phost, 10, 10, 16, 0, str);
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0x00,0x00));
//	Ft_Gpu_CoCmd_Text(phost, 10, 30, 12, 0, "\x58\x59\x5a");
//	//Ft_Gpu_CoCmd_Text(phost, 10, 30, 16, 0, 777);

//	Ft_App_WrCoCmd_Buffer(phost,BEGIN(LINES));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0, 30, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(300, 30, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(0, 50, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(300, 50, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(160, 0, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,VERTEX2II(160, 120, 0, 0));
//	Ft_App_WrCoCmd_Buffer(phost,END());




	//Ft_App_WrCoCmd_Buffer(phost,DISPLAY());
	//Ft_Gpu_CoCmd_Swap(phost);

//	Ft_App_Flush_Co_Buffer(phost);
//	Ft_Gpu_Hal_WaitCmdfifo_empty(phost);
//	//while(0!=Ft_Gpu_Hal_Rd16(phost,REG_CMD_READ));
//
//	ft_uint16_t dloffset = 0;
//	ft_uint16_t dloffset = Ft_Gpu_Hal_Rd16(phost,REG_CMD_DL); // размер коируемого дисплей-листа
//	//dloffset -= 4;
//	Ft_Gpu_Hal_WrCmd32(phost,CMD_MEMCPY); // указание FT800 скопировать области памяти
//	Ft_Gpu_Hal_WrCmd32(phost,100000L); // адрес, куда будем копировать в области графической памяти RAM_G
//	Ft_Gpu_Hal_WrCmd32(phost,RAM_DL); // адрес, откуда копируем
//	Ft_Gpu_Hal_WrCmd32(phost,dloffset); // количество байт

	ft_uint16_t dloffset = cli;// ft800memRead16(REG_CMD_DL); // размер коируемого дисплей-листа

	cmd(CMD_MEMCPY); // указание FT800 скопировать области памяти
	cmd(100000L); // адрес, куда будем копировать в области графической памяти RAM_G
	cmd(RAM_DL); // адрес, откуда копируем
	cmd(dloffset); // количество байт

	//cmd(DL_END);
	//cmd(DL_DISPLAY);
	//cmd(CMD_SWAP);

	//ft800memWrite16(REG_CMD_WRITE, cli);
		/* Download the commands into fifo */
		//Ft_App_Flush_Co_Buffer(phost);

		/* Wait till coprocessor completes the operation */
		//Ft_Gpu_Hal_WaitCmdfifo_empty(phost);

	Ft_Gpu_Hal_Sleep(50);

	cli__ = cli;
	return dloffset;

}

