/*
 * FT80x.c
 *
 *  Created on: 22 ����. 2017 �.
 *      Author: Dima
 */


#include "FT80x.h"
#include "FT_Gpu.h"




/* USER CODE BEGIN 4 */
/******************************************************************************
 * Function:        void ft800cmdWrite(ftCommand)
 * PreCondition:    None
 * Input:           ftCommand
 * Output:          None
 * Side Effects:    None
 * Overview:        Sends FT800 command
 * Note:            None
 *****************************************************************************/
void ft800cmdWrite(unsigned char ftCommand)
{
	unsigned char cZero = 0x00;														// Filler value for command
	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low
	HAL_SPI_Transmit(&hspi1, &ftCommand, 1, TIMEOUTSPI);						// Send command
	HAL_SPI_Transmit(&hspi1, &cZero, 1, TIMEOUTSPI);								// Send first filler byte
	HAL_SPI_Transmit(&hspi1, &cZero, 1, TIMEOUTSPI);								// Send second filler byte
	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high
}

/******************************************************************************
 * Function:        void ft800memWritexx(ftAddress, ftDataxx, ftLength)
 * PreCondition:    None
 * Input:           ftAddress = FT800 memory space address
 *                  ftDataxx = a byte, int or long to send
 * Output:          None
 * Side Effects:    None
 * Overview:        Writes FT800 internal address space
 * Note:            "xx" is one of 8, 16 or 32
 *****************************************************************************/
void ft800memWrite8(unsigned long ftAddress, unsigned char ftData8)
{
	unsigned char cTempAddr[3];														// FT800 Memory Address

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_WRITE;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

    for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, TIMEOUTSPI); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(ftData8); j++)
	{
		HAL_SPI_Transmit(&hspi1, &ftData8, 1, TIMEOUTSPI);						// Send data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high
}

void ft800memWrite16(unsigned long ftAddress, unsigned int ftData16)
{
	unsigned char cTempAddr[3];														// FT800 Memory Address
	unsigned char cTempData[2];														// 16-bit data to write

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_WRITE;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	cTempData[1] = (char) (ftData16 >> 8);								// Compose data to be sent - high byte
	cTempData[0] = (char) (ftData16);											// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

    for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, TIMEOUTSPI); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significant byte
	{
		HAL_SPI_Transmit(&hspi1, &cTempData[j], 1, TIMEOUTSPI);			// Send data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high
}

void ft800memWrite32(unsigned long ftAddress, unsigned long ftData32)
{
	unsigned char cTempAddr[3];														// FT800 Memory Address
	unsigned char cTempData[4];														// 32-bit data to write

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_WRITE;	// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	cTempData[3] = (char) (ftData32 >> 24);								// Compose data to be sent - high byte
	cTempData[2] = (char) (ftData32 >> 16);								//
	cTempData[1] = (char) (ftData32 >> 8);								//
	cTempData[0] = (char) (ftData32);											// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, TIMEOUTSPI); 			// Send Memory Write plus high address byte
	}

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significant byte
	{
		HAL_SPI_Transmit(&hspi1, &cTempData[j], 1, TIMEOUTSPI);			// Send SPI byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high
}
/******************************************************************************
 * Function:        unsigned char ft800memReadxx(ftAddress, ftLength)
 * PreCondition:    None
 * Input:           ftAddress = FT800 memory space address
 * Output:          ftDataxx (byte, int or long)
 * Side Effects:    None
 * Overview:        Reads FT800 internal address space
 * Note:            "xx" is one of 8, 16 or 32
 *****************************************************************************/
ft_uint8_t ft800memRead8(ft_uint32_t ftAddress)
{
	ft_uint8_t ftData8 = ZERO;													// Place-holder for 8-bits being read
	ft_uint8_t cTempAddr[3];														// FT800 Memory Address
	ft_uint8_t cZeroFill = ZERO;												// Dummy byte

	cTempAddr[2] = (ft_uint8_t) (ftAddress >> 16) | MEM_READ;		// Compose the command and address to send
	cTempAddr[1] = (ft_uint8_t) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (ft_uint8_t) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

    for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, TIMEOUTSPI); 			// Send Memory Write plus high address byte
	}

    HAL_SPI_Transmit(&hspi1, &cZeroFill, 1, TIMEOUTSPI);						// Send dummy byte

	for (int j = 0; j < sizeof(ftData8); j++)							// Start with least significant byte
	{
		HAL_SPI_Receive(&hspi1, &ftData8, 1, TIMEOUTSPI);						// Receive data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high

  return (ft_uint8_t)ftData8;																				// Return 8-bits
}

ft_uint16_t ft800memRead16(ft_uint32_t ftAddress)
{
	ft_uint16_t ftData16;																// 16-bits to return
	ft_uint8_t cTempAddr[3];														// FT800 Memory Address
	ft_uint8_t cTempData[2];														// Place-holder for 16-bits being read
	ft_uint8_t cZeroFill;

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_READ;		// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

    for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, TIMEOUTSPI); 			// Send Memory Write plus high address byte
	}

    HAL_SPI_Transmit(&hspi1, &cZeroFill, 1, TIMEOUTSPI);						// Send dummy byte

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significant byte
	{
		HAL_SPI_Receive(&hspi1, &cTempData[j], 1, TIMEOUTSPI);				// Receive data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high

	ftData16 = (cTempData[1]<< 8) | 											// Compose value to return - high byte
					   (cTempData[0]); 														// low byte

  return ftData16;																			// Return 16-bits
}

ft_uint32_t ft800memRead32(ft_uint32_t ftAddress)
{
	ft_uint32_t ftData32;																// 32-bits to return
	ft_uint8_t cTempAddr[3];														// FT800 Memory Address
	ft_uint8_t cTempData[4];														// Place holder for 32-bits being read
	ft_uint8_t cZeroFill;															// Dummy byte

	cTempAddr[2] = (char) (ftAddress >> 16) | MEM_READ;		// Compose the command and address to send
	cTempAddr[1] = (char) (ftAddress >> 8);								// middle byte
	cTempAddr[0] = (char) (ftAddress);										// low byte

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_RESET);	// Set chip select low

  for (int i = 2; i >= 0; i--)
	{
		HAL_SPI_Transmit(&hspi1, &cTempAddr[i], 1, TIMEOUTSPI); 			// Send Memory Write plus high address byte
	}

  HAL_SPI_Transmit(&hspi1, &cZeroFill, 1, TIMEOUTSPI);						// Send dummy byte

	for (int j = 0; j < sizeof(cTempData); j++)						// Start with least significatn byte
	{
		HAL_SPI_Receive(&hspi1, &cTempData[j], 1, TIMEOUTSPI);				// Receive data byte
	}

	HAL_GPIO_WritePin(GPIOB, FT800_CS_N, GPIO_PIN_SET);		// Set chip select high

	ftData32 = (cTempData[3]<< 24) | 											// Compose value to return - high byte
						 (cTempData[2]<< 16) |
						 (cTempData[1]<< 8) |
						 (cTempData[0]); 														// Low byte

  return ftData32;																			// Return 32-bits
}



unsigned int incCMDOffset(unsigned int currentOffset, unsigned char commandSize)
{
    unsigned int newOffset;															// Used to hold new offset
    newOffset = currentOffset + commandSize;						// Calculate new offset
    if(newOffset > 4095)																// If new offset past boundary...
    {
        newOffset = (newOffset - 4096);									// ... roll over pointer
    }
    return newOffset;																		// Return new offset
}


void write_string(char *s) {																// write string

	uint16_t length, n;
	length = strlen(s) + 1;

	for(n = 0; n < length; n++) {

		ft800memWrite8(RAM_CMD + cli + n, s[n]);
	}

	ft800memWrite8(RAM_CMD + cli + n, 0);
	cli += ((length + 3) & ~3);
}

void cmd(uint32_t cmd) {																	// write 32bit command to co-processor engine FIFO RAM_CMD

	ft800memWrite32(RAM_CMD + cli, cmd);
	cli += 4;
}

void cmd_dlstart(void) {																	// start a new display list

	ft800memWrite32(RAM_CMD + cli, CMD_DLSTART);
	cli += 4;
}

void cmd_swap(void) {																		// swap the current display list

	ft800memWrite32(RAM_CMD + cli, CMD_SWAP);
	cli += 4;
}

void cmd_coldstart(void) {																	// set co-processor engine state to default values

	ft800memWrite32(RAM_CMD + cli, CMD_COLDSTART);
	cli += 4;
}

void cmd_interrupt(uint32_t ms) {															// trigger interrupt INT_CMDFLAG

	ft800memWrite32(RAM_CMD + cli, CMD_INTERRUPT);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ms);
	cli += 4;
}

void cmd_append(uint32_t ptr, uint32_t num) {												// append memory to display list

	ft800memWrite32(RAM_CMD + cli, CMD_APPEND);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, num);
	cli += 4;
}

void cmd_regread(uint32_t ptr, uint32_t result) {											// read a register value

	ft800memWrite32(RAM_CMD + cli, CMD_REGREAD);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, result);
	cli += 4;
}

void cmd_memwrite(uint32_t ptr, uint32_t num) {												// write bytes into memory

	ft800memWrite32(RAM_CMD + cli, CMD_MEMWRITE);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, num);
	cli += 4;
}

void cmd_inflate(uint32_t ptr) {															// decompress data into memory

	ft800memWrite32(RAM_CMD + cli, CMD_INFLATE);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
}

void cmd_loadimage(const uint8_t* img, uint32_t ptr, uint32_t length, uint32_t opt) {		//load a JPEG image

	uint32_t i;

	ft800memWrite32(RAM_CMD + cli, CMD_LOADIMAGE);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, opt);
	cli += 4;

	for (i = 0; i < length; i++)
	{
		ft800memWrite8(RAM_CMD + cli, *(img + i));
		cli++;
	}
}

void cmd_memcrc(uint32_t ptr, uint32_t num, uint32_t result) {								//compute a CRC-32 for memory

	ft800memWrite32(RAM_CMD + cli, CMD_MEMCRC);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, num);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, result);
	cli += 4;

}

void cmd_memzero(uint32_t ptr, uint32_t num) {												//write zero to a block of memory

	ft800memWrite32(RAM_CMD + cli, CMD_MEMZERO);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, num);
	cli += 4;
}

void cmd_memset(uint32_t ptr, uint32_t value, uint32_t num) {								//fill memory with a byte value

	ft800memWrite32(RAM_CMD + cli, CMD_MEMSET);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, value);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, num);
	cli += 4;
}

void cmd_memcpy(uint32_t dest, uint32_t src, uint32_t num) {								//copy a block of memory

	ft800memWrite32(RAM_CMD + cli, CMD_MEMCPY);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, dest);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, src);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, num);
	cli += 4;
}

void cmd_button(int16_t x, int16_t y, int16_t w, int16_t h, int16_t font, int16_t opt, const char*s) {				//draw a button

	ft800memWrite32(RAM_CMD + cli, CMD_BUTTON);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((h << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((opt << 16) | font));
	cli += 4;
	write_string(s);
}

void cmd_clock(int16_t x, int16_t y, int16_t r, uint16_t opt, uint16_t h, uint16_t m, uint16_t s, uint16_t ms) {	//draw an analog clock

	ft800memWrite32(RAM_CMD + cli, CMD_CLOCK);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, (y << 16) | x);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((opt << 16) | r));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((m << 16) | h));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((ms << 16) | s));
	cli += 4;
}

void cmd_fgcolor(uint32_t color) {															// set the foreground color

	ft800memWrite32(RAM_CMD + cli, CMD_FGCOLOR);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, color);
	cli += 4;
}

void cmd_bgcolor(uint32_t color) {															// set the backgroupd color

	ft800memWrite32(RAM_CMD + cli, CMD_BGCOLOR);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, color);
	cli += 4;
}

void cmd_gradcolor(uint32_t color) {														// set the 3D button highlight color

	ft800memWrite32(RAM_CMD + cli, CMD_GRADCOLOR);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, color);
	cli += 4;
}

//void cmd_gauge(int16_t x, int16_t y, int16_t r, uint16_t opt, uint16_t major, uint16_t minor, uint16_t val, uint16_t range) {	// draw a gauge
//
//	ft800memWrite32(RAM_CMD + cli, CMD_GAUGE);
//	cli += 4;
//	ft800memWrite32(RAM_CMD + cli, (y << 16) | x);
//	cli += 4;
//	ft800memWrite32(RAM_CMD + cli, ((opt << 16) | r));
//	cli += 4;
//	ft800memWrite32(RAM_CMD + cli, ((minor << 16) | major));
//	cli += 4;
//	ft800memWrite32(RAM_CMD + cli, ((range << 16) | val));
//	cli += 4;
//
//}

void cmd_gradient(int16_t x0, int16_t y0, uint32_t rgb0, int16_t x1, int16_t y1, uint32_t rgb1) {		// draw a smooth color gradient

	ft800memWrite32(RAM_CMD + cli, CMD_GRADIENT);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y0 << 16) | x0));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, rgb0);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y1 << 16) | x1));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, rgb1);
	cli += 4;
}

void cmd_keys(int16_t x, int16_t y, int16_t w, int16_t h, int16_t font, uint16_t opt, const char* s) {		// draw a row of keys

	ft800memWrite32(RAM_CMD + cli, CMD_KEYS);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((h << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((opt << 16) | font));
	cli += 4;
	write_string(s);
}

void cmd_progress(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t opt, uint16_t val, uint16_t range) {		// draw a progress bar

	ft800memWrite32(RAM_CMD + cli, CMD_PROGRESS);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((h << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((val << 16) | opt));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, range);
	cli += 4;
}

void cmd_scrollbar(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t opt, uint16_t val, uint16_t size, uint16_t range) {	// draw a scroll bar

	ft800memWrite32(RAM_CMD + cli, CMD_SCROLLBAR);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((h << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((val << 16) | opt));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((range << 16) | size));;
	cli += 4;
}

void cmd_slider(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t opt, uint16_t val, uint16_t range) {					// draw a slider

	ft800memWrite32(RAM_CMD + cli, CMD_SLIDER);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((h << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((val << 16) | opt));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, range);
	cli += 4;
}

void cmd_dial(int16_t x, int16_t y, int16_t r, uint16_t opt, uint16_t val) {												// draw a rotary dial control

	ft800memWrite32(RAM_CMD + cli, CMD_DIAL);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((opt << 16) | r));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, val);
	cli += 4;
}

void cmd_toggle(int16_t x, int16_t y, int16_t w, int16_t font, uint16_t opt, uint16_t state, const char* s) {				// draw a toggle switch

	ft800memWrite32(RAM_CMD + cli, CMD_TOGGLE);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((font << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((state << 16) | opt));
	cli += 4;
	write_string(s);
}

void cmd_text(int16_t x, int16_t y, int16_t font, uint16_t opt, const char* s) {											// draw text

	ft800memWrite32(RAM_CMD + cli, CMD_TEXT);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((opt << 16) | font));
	cli += 4;
	write_string(s);
}

void cmd_number(int16_t x, int16_t y, int16_t font, uint16_t opt, int32_t n) {												// draw a decimal number

	ft800memWrite32(RAM_CMD + cli, CMD_NUMBER);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((opt << 16) | font));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, n);
	cli += 4;
}

void cmd_loadidentity(void) {																								// set the current matrix to the identity matrix

	ft800memWrite32(RAM_CMD + cli, CMD_LOADIDENTITY);
	cli += 4;
}

void cmd_setmatrix(void) {																									// write the current matrix to the display list

	ft800memWrite32(RAM_CMD + cli, CMD_SETMATRIX);
	cli += 4;
}

void cmd_getmatrix(int32_t a, int32_t b, int32_t c, int32_t d, int32_t e, int32_t f) {										// retrieves the current matrix coefficients

	ft800memWrite32(RAM_CMD + cli, CMD_GETMATRIX);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, a);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, b);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, c);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, d);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, e);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, f);
	cli += 4;
}

void cmd_getptr(uint32_t result) {																							// get the end memory address of inflated data

	ft800memWrite32(RAM_CMD + cli, CMD_GETPTR);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, result);
	cli += 4;
}

void cmd_getprops(uint32_t ptr, uint32_t width, uint32_t height) {															// get the image properties decompressed by CMD_LOADIMAGE

	ft800memWrite32(RAM_CMD + cli, CMD_GETPROPS);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, width);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, height);
	cli += 4;
}

void cmd_scale(int32_t sx, int32_t sy) {																					// apply a scale to the current matrix

	ft800memWrite32(RAM_CMD + cli, CMD_SCALE);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, sx);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, sy);
	cli += 4;
}

void cmd_rotate(int32_t a) {																								// apply a rotation to the current matrix

	ft800memWrite32(RAM_CMD + cli, CMD_ROTATE);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, a);
	cli += 4;
}

void cmd_translate(int32_t tx, int32_t ty) {																				// apply a translation to the current matrix

	ft800memWrite32(RAM_CMD + cli, CMD_TRANSLATE);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, tx);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ty);
	cli += 4;
}

void cmd_calibrate(void) {																						// execute the screen calibration routine

	ft800memWrite32(RAM_CMD + cli, CMD_CALIBRATE);
	cli += 4;
}

void cmd_spinner(int16_t x, int16_t y, uint16_t style, uint16_t scale) {										// start an animated spinner

	ft800memWrite32(RAM_CMD + cli, CMD_SPINNER);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((scale << 16) | style));
	cli += 4;
}

void cmd_screensaver(void) {																					// start an animated screensaver

	ft800memWrite32(RAM_CMD + cli, CMD_SCREENSAVER);
	cli += 4;
}

void cmd_sketch(int16_t x, int16_t y, int16_t w, int16_t h, uint32_t ptr, uint16_t format) {					// start continuous sketch update

	ft800memWrite32(RAM_CMD + cli, CMD_SKETCH);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((h << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, format);
	cli += 4;
}

void cmd_stop(void) {																								// stop any of spinner, screensaver or sketch

	ft800memWrite32(RAM_CMD + cli, CMD_STOP);
	cli += 4;
}

void cmd_setfont(uint32_t font, uint32_t ptr) {																		// set up a custom font

	ft800memWrite32(RAM_CMD + cli, CMD_SETFONT);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
}

void cmd_track(int16_t x, int16_t y, int16_t w, int16_t h, int16_t tag) {											// track touches for a graphics object

	ft800memWrite32(RAM_CMD + cli, CMD_TRACK);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((y << 16) | x));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ((h << 16) | w));
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, tag);
	cli += 4;
}

void cmd_snapshot(uint32_t ptr) {																					// take a snapshot of the current screen

	ft800memWrite32(RAM_CMD + cli, CMD_SNAPSHOT);
	cli += 4;
	ft800memWrite32(RAM_CMD + cli, ptr);
	cli += 4;
}

void cmd_logo(void) {																								// play FTDI logo animation

	ft800memWrite32(RAM_CMD + cli, CMD_LOGO);
	cli += 4;
}





