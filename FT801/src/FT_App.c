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

//extern FT_PROGMEM ft_prog_uchar8_t SAMApp_L1[];


ft_uint32_t FONT_POS = 1000;
ft_uint32_t R_FONT = 12;
ft_uint32_t E_FONT = 18;
ft_uint32_t Ft_CmdBuffer_Index;
ft_uint32_t Ft_DlBuffer_Index;



ft_void_t FT_APP_BootupConfig()
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

	FT_APP_Calibrate(0);

	ft_uint32_t SAMApp_Metric_L1_SIZE = 148;
	ft_uint32_t SAMApp_L1_SIZE = 6489;
	for (ft_uint32_t i = 0; i < SAMApp_Metric_L1_SIZE; i++){
		ft800memWrite8(RAM_G + FONT_POS + i, SAMApp_Metric_L1[i]);
	}
	for (ft_uint32_t i = 0; i < SAMApp_L1_SIZE; i++){
		ft800memWrite8(RAM_G + FONT_POS + i + SAMApp_Metric_L1_SIZE, SAMApp_L1[i]);
	}

}

ft_void_t FT_APP_Calibrate(ft_uint8_t mode)
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

ft_void_t FT_APP_Screen_Content(Screen_TypeDef SCREEN, State_TypeDef STATE,
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

	ft800memWrite32(REG_CMD_READ, 0);
	ft800memWrite32(REG_CMD_WRITE, 0);

	cmd_dlstart();
	cmd_append(10000L, dloffset);

	cmd(COLOR_RGB(0xff, 0xd8, 0));// установка цвета текста
	#ifdef ADMIN_INFO
		cmd_number(10, 60, 16, 0, nmb);
	#endif

	switch (SCREEN){
		case MAIN:

			sprintf(value_c, "%d.%d", (int)F, (int)( ( F - floor(F) ) * pow(10, 1) ));
			cmd_text(155, 7, 22, 0, value_c);
			sprintf(value_c, "%d.%d", (int)A, (int)( ( A - floor(A) ) * pow(10, 3) ));
			cmd_text(265, 7, 22, 0, value_c);

			switch (STATE)
		    {
			case IDLE:
				cmd(TAG_MASK(1));
				cmd(TAG(2));
				cmd_fgcolor((tag==2)?button_color_hover:button_color);
				cmd_button(110, 190, 100, 40, R_FONT, 0, "\x21\x2a\x26\x18");
				cmd(TAG_MASK(0));
			break;
			case TOUCH:
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

			cmd(TAG_MASK(1));
			cmd(TAG(6));          // assign the tag value
			cmd_fgcolor((tag==6)?button_color_hover:button_color);
			cmd_button( 110, 110, 100, 40, R_FONT, 0, "\x33\x02\x08"); //Шаг
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


			if (tag >= 211 & tag <=213) {
				cmd(TAG_MASK(1));
				cmd(TAG(211));          // assign the tag value
				cmd_fgcolor((tag==211)?button_color_hover:button_color);
				cmd_button(10, 10, 100, 30, R_FONT, 0, "\x54");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(212));          // assign the tag value
				cmd_fgcolor((tag==212)?button_color_hover:button_color);
				cmd_button(10, 50, 100, 30, R_FONT, 0, "\x55");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(213));          // assign the tag value
				cmd_fgcolor((tag==213)?button_color_hover:button_color);
				cmd_button(10, 90, 100, 30, R_FONT, 0, "\x56");
				cmd(TAG_MASK(0));
			} else {
				cmd(TAG_MASK(1));
				cmd(TAG(211));          // assign the tag value
				cmd_fgcolor((storedMaterial==211)?button_color_selected:button_color);
				cmd_button(10, 10, 100, 30, R_FONT, 0, "\x54");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(212));          // assign the tag value
				cmd_fgcolor((storedMaterial==212)?button_color_selected:button_color);
				cmd_button(10, 50, 100, 30, R_FONT, 0, "\x55");
				cmd(TAG_MASK(0));

				cmd(TAG_MASK(1));
				cmd(TAG(213));          // assign the tag value
				cmd_fgcolor((storedMaterial==213)?button_color_selected:button_color);
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

			uint8_t length=0;
			uint8_t arr[32];
			cmd(TAG_MASK(1));
			cmd(TAG(201));          // assign the tag value
			cmd_fgcolor((tag==201)?button_color_hover:button_color);
			float_to_char_array(F1K, &arr[0], &length, 3);
			cmd_button(10, 10, 100, 30, E_FONT, 0, arr);
			cmd(TAG_MASK(0));

			length=0;
			cmd(TAG_MASK(1));
			cmd(TAG(202));          // assign the tag value
			cmd_fgcolor((tag==202)?button_color_hover:button_color);
			float_to_char_array(F1B, &arr[0], &length, 3);
			cmd_button(10, 50, 100, 30, E_FONT, 0, arr);
			cmd(TAG_MASK(0));

			length=0;
			cmd(TAG_MASK(1));
			cmd(TAG(203));          // assign the tag value
			cmd_fgcolor((tag==203)?button_color_hover:button_color);
			float_to_char_array(A1K, &arr[0], &length, 7);
			cmd_button(110, 10, 100, 30, E_FONT, 0, arr);
			cmd(TAG_MASK(0));

			length=0;
			cmd(TAG_MASK(1));
			cmd(TAG(204));          // assign the tag value
			cmd_fgcolor((tag==204)?button_color_hover:button_color);
			float_to_char_array(A1B, &arr[0], &length, 3);
			cmd_button(110, 50, 100, 30, E_FONT, 0, arr);
			cmd(TAG_MASK(0));

			cmd(TAG_MASK(1));
			cmd(TAG(205));          // assign the tag value
			cmd_fgcolor((F1F==1)?button_color_hover:button_color);
			//float_to_char_array(F1F, &arr[0], &length, 0);
			//cmd_button(10, 100, 100, 30, E_FONT, 0, arr);
			cmd_button(10, 100, 100, 30, E_FONT, 0, "Filter");
			cmd(TAG_MASK(0));

			//***Keyboard(phost, tag);
		break;

		case STEPPER:
			cmd(COLOR_RGB(0xff,0xd8,0x00));

			cmd(TAG_MASK(1));
			cmd(TAG(1));          // assign the tag value
			cmd_fgcolor((tag==1)?button_color_hover:button_color);
			cmd_button(5, 190, 100, 40, R_FONT, 0, "\x5f");
			cmd(TAG_MASK(0));

			cmd(TAG_MASK(1));
			cmd(TAG(21));
			cmd_fgcolor((tag==21)?button_color_hover:button_color);
			cmd_button(10, 10, 100, 30, R_FONT, 0, "\x5f");
			cmd(TAG_MASK(0));

			length=0;
			cmd(TAG_MASK(1));
			cmd(TAG(22));
			cmd_fgcolor((tag==22)?button_color_hover:button_color);
			cmd_button(110, 10, 100, 30, R_FONT, 0, "\x61");
			cmd(TAG_MASK(0));

			//***Keyboard(phost, tag);
		break;
	}

	#ifdef ADMIN_INFO
		cmd_number(10, 90, 16, 0, cli__);
		cmd_number(10, 110, 16, 0, cli);
		cmd_number(10, 130, 16, 0, tag);
	#endif

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

	HAL_Delay(5);
}


ft_uint16_t FT_APP_Screen_BasicScreen(Screen_TypeDef SCREEN)
{
	ft_uint32_t cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	ft_uint32_t cmdBufferWr = 0x0000;											// Used to navigate command ring buffer

	do
	{
		cmdBufferRd = ft800memRead32(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead32(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);
	cli_dub = cmdBufferWr;
	cli = 0;

	ft800memWrite32(REG_CMD_WRITE, 0);
	ft800memWrite32(REG_CMD_READ, 0);

	cmd_dlstart();

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

	switch (SCREEN){
		case MAIN:
			FT_APP_Screen_MainScreen();
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
		case STEPPER:
			;//API_Screen_LogsScreen(phost);
		break;
	}

	ft_uint16_t dloffset = 0;

	ft800memWrite16(REG_CMD_WRITE, cli);
//	uint16_t TimeOut = 0;
	do
	{
		cmdBufferRd = ft800memRead32(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead32(REG_CMD_WRITE); 														// Read the graphics processor write pointer
//		TimeOut++;
//		if(TimeOut > 0x0FFF){
//			break;
//		}
	} while (cmdBufferWr != cmdBufferRd);
//	if(TimeOut > 0x0FFF){
//
//		ft800memWrite32(REG_CMD_WRITE, cli);
////		ft800memWrite32(REG_CMD_READ, cli);
//
//		cmdBufferRd = ft800memRead32(REG_CMD_READ);															// Read the graphics processor read pointer
//
//	}

	dloffset = ft800memRead16(REG_CMD_DL); // размер коируемого дисплей-листа

	cmd_memcpy(10000L, RAM_DL, dloffset);

	cli__ = cli;
	cli_temp = cli;
	while (cli_dub > cli) {
		cmd(0);
	}
	cli_dub = 0;

	return dloffset;
}

void FT_APP_Screen_MainScreen()
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

ft_void_t FT_APP_Screen(ft_char8_t *str)
{
	unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer

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

	cmd(DL_END);
	cmd(DL_DISPLAY);
	cmd(CMD_SWAP);

	ft800memWrite16(REG_CMD_WRITE, cli);

	HAL_Delay(10);
}


void FT_APP_Screen_Test()
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




ft_void_t Keyboard(ft_uint16_t tag, uint8_t *arr, uint8_t* length)
{
//	ft_uint8_t TextFont = 12;
//	ft_uint8_t ButtonW = 40;
//	ft_uint8_t ButtonH = 40;
//	ft_uint8_t yBtnDst = 5;
//	ft_uint8_t CurrChar = '|';
//	ft_uint8_t CurrTag = 0;
//	ft_uint8_t PrevTag = 0;
//	//ft_uint8_t Pendown = 1;
//	ft_uint8_t CurrTextIdx = 0;
	ft_uint16_t FT_DispWidth = 320;
//	ft_uint8_t yOffset = 0;


	unsigned int cmdBufferRd = 0x0000;											// Used to navigate command ring buffer
	unsigned int cmdBufferWr = 0x0000;											// Used to navigate command ring buffer

	do
	{
		cmdBufferRd = ft800memRead16(REG_CMD_READ);															// Read the graphics processor read pointer
		cmdBufferWr = ft800memRead16(REG_CMD_WRITE); 														// Read the graphics processor write pointer
	} while (cmdBufferWr != cmdBufferRd);
	cli_dub = cmdBufferWr;
	cli = 0;

	ft800memWrite16(REG_CMD_WRITE, 0);
	ft800memWrite16(REG_CMD_READ, 0);

	cmd_dlstart();

	cmd(CLEAR_COLOR_RGB(0,0,0));
	cmd(CLEAR(0xff,0xff,0xff));
	cmd(COLOR_RGB(0xff,0xd8,0x00));

	cmd(TAG_MASK(1));
	cmd(TAG(1));          // assign the tag value
	cmd_fgcolor((tag==1)?button_color_hover:button_color);
	cmd_button(5, 190, 100, 40, R_FONT, 0, "\x5f");
	cmd(TAG_MASK(0));

	cmd(TAG_MASK(1));
	cmd(TAG(3));          // assign the tag value
	cmd_fgcolor((tag==3)?button_color_hover:button_color);
	cmd_button(215, 190, 100, 40, R_FONT, 0, "\x05\x06\x20\x0a"); //Ввод
	cmd(TAG_MASK(0));


	/* Check the user input and then add the characters into array */
	CurrTag = tag;
//	Pendown = ((Ft_Gpu_Hal_Rd32(phost,REG_TOUCH_DIRECT_XY)>>31) & 0x01);


	if(CurrTag > 200)
	{
		CurrTag=0;
	}
	if(CurrTag == 0)
	{
		CurrChar = '\x52';
	} else {
		CurrChar = CurrTag;
	}

	/* check whether pendown has happened */
	if( /*( 1 == Pendown) &&*/ (0 != PrevTag))
	{
//		CurrTextIdx++;
		(*length)++;

//		/* clear all the charaters after 24 are pressed */
//		if(CurrTextIdx > 24)
//		{
//			CurrTextIdx = 0;
//		}
	}

//	Ft_Gpu_CoCmd_Dlstart(phost);
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR_COLOR_RGB(64,64,64));
//	Ft_App_WrCoCmd_Buffer(phost,CLEAR(1,1,1));
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));

	/* Draw text entered by user */
	/* make sure the array is a string */
//	DispText[CurrTextIdx] = CurrChar;
	*(arr+*length) = CurrChar;
	ft_uint8_t arr__[*length+1];
	for(int i = 0; i < *length+1; i++) {
		arr__[i] = *(arr + i);
	}
	arr__[*length+1] = "\x52";
//	DispText[CurrTextIdx + 1] = '\0';
	cmd_text_(FT_DispWidth/2, 40, R_FONT, OPT_CENTER, arr, *length+1);//text info
//	yOffset = 80 + 10;
	/* Construct a simple keyboard - note that the tags associated with the keys are the character values given in the arguments */
	//cmd_fgcolor(0x404080);
	//cmd_gradcolor(0x00ff00);

// Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont,(OPT_CENTER | CurrTag), "qwertyuiop");
// Ft_Gpu_CoCmd_GradColor(phost,0x00ffff);
// yOffset += ButtonH + yBtnDst;
// Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont,(OPT_CENTER | CurrTag), "asdfghjkl");
// Ft_Gpu_CoCmd_GradColor(phost,0xffff00);
// yOffset += ButtonH + yBtnDst;
// Ft_Gpu_CoCmd_Keys(phost, yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont,(OPT_CENTER | CurrTag), "zxcvbnm");//hilight button z
// yOffset += ButtonH + yBtnDst;
// Ft_App_WrCoCmd_Buffer(phost,TAG(' '));
//
// if(' ' == CurrTag)
// {
//	 Ft_Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER | OPT_FLAT, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
// }
// else
// {
//	 Ft_Gpu_CoCmd_Button(phost,yBtnDst, yOffset, 10*ButtonW, ButtonH, TextFont, OPT_CENTER, " ");//mandatory to give '\0' at the end to make sure coprocessor understands the string end
// }


//	yOffset = 80 + 10;
	cmd(TAG_MASK(1));
	cmd_keys(40, 80, 6*40, 40, 12, (0 | CurrTag), "\x53\x54\x55\x56\x57\x58");
	cmd_keys(40, 140, 6*40, 40, 12, (0 | CurrTag), "\x59\x5a\x5b\x5c\x50\x51");
	cmd(TAG_MASK(0));
//	yOffset += ButtonH + yBtnDst;
//	Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "456");
//	yOffset += ButtonH + yBtnDst;
//	Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "123");
//	yOffset += ButtonH + yBtnDst;
//	Ft_App_WrCoCmd_Buffer(phost,COLOR_A(255));
//	Ft_Gpu_CoCmd_Keys(phost, 11*ButtonW, yOffset, 3*ButtonW, ButtonH, TextFont, (0 | CurrTag), "0.");//hilight button 0
	cmd(COLOR_RGB(0xff,0x00,0x00));

//	StringArray[0] = '\0';
//	strcat(StringArray,"Next demo in ");
//	Ft_Gpu_Hal_Dec2Ascii(StringArray,(ThisDemoEnd/100)+1);
//	strcat(StringArray,"s");
//	Ft_Gpu_CoCmd_Text(phost,FT_DispWidth, (FT_DispHeight-12), 20, OPT_RIGHTX,StringArray);
//	if(tftConfig == RTP35 || tftConfig == RTP43 || tftConfig == CTP35 || tftConfig== CTP43)
//	{
//		Ft_App_WrCoCmd_Buffer(phost,COLOR_RGB(0xff,0xff,0xff));
//		Ft_App_WrCoCmd_Buffer(phost,TAG(249));
//		Ft_Gpu_CoCmd_Button(phost,FT_DispWidth-65,FT_DispHeight-42,60,30,20,0, "SKIP->");
//		CurrTag2 = Ft_Gpu_Hal_Rd8(phost,REG_TOUCH_TAG);
//	}

	PrevTag = CurrTag;

	cmd(DL_END);
	cmd(DISPLAY());//cmd(DL_DISPLAY);
	cmd_swap();//cmd(CMD_SWAP);

//	cli__ = cli;
//	cli_temp = cli;
//	while (cli_dub > cli) {
//		cmd(0);
//	}
//	cli_dub = 0;

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

	HAL_Delay(5);
}
