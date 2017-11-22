/*
 * FT80x.h
 *
 *  Created on: 22 но€б. 2017 г.
 *      Author: Dima
 */

#include "FT_DataTypes.h"
#include "stm32f0xx_hal.h"
#include "stm32f0xx_hal_spi.h"


ft_uint32_t dli, cli, cli__, cli_dub, cli_temp;


SPI_HandleTypeDef hspi1;
#define TIMEOUTSPI 5

#define FT800_PD_N	GPIO_PIN_8
#define FT800_CS_N	GPIO_PIN_6

#define MEM_WRITE							0x80			// FT800 Host Memory Write
#define MEM_READ							0x00			// FT800 Host Memory Read

#ifndef FT801_INC_FT80X_H_
#define FT801_INC_FT80X_H_

#define FT800_ACTIVE					0x00			// Initializes FT800
#define FT800_STANDBY					0x41			// Place FT800 in Standby (clk running)
#define FT800_SLEEP						0x42			// Place FT800 in Sleep (clk off)
#define FT800_PWRDOWN					0x50			// Place FT800 in Power Down (core off)
#define FT800_CLKEXT					0x44			// Select external clock source
#define FT800_CLK48M					0x62			// Select 48MHz PLL
#define FT800_CLK36M					0x61			// Select 36MHz PLL
#define FT800_CORERST					0x68			// Reset core - all registers default

// Display list commands to be embedded in Graphics Processor
#define DL_ALPHA_FUNC       	0x09000000UL // requires OR'd arguments
#define DL_BITMAP_HANDLE    	0x05000000UL // requires OR'd arguments
#define DL_BITMAP_LAYOUT    	0x07000000UL // requires OR'd arguments
#define DL_BITMAP_SIZE      	0x08000000UL // requires OR'd arguments
#define DL_BITMAP_SOURCE    	0x01000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_A   	0x15000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_B   	0x16000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_C   	0x17000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_D   	0x18000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_E   	0x19000000UL // requires OR'd arguments
#define DL_BITMAP_TFORM_F   	0x1A000000UL // requires OR'd arguments
#define DL_BLEND_FUNC       	0x0B000000UL // requires OR'd arguments
#define DL_BEGIN            	0x1F000000UL // requires OR'd arguments
#define DL_CALL             	0x1D000000UL // requires OR'd arguments
#define DL_CLEAR            	0x26000000UL // requires OR'd arguments
#define DL_CELL             	0x06000000UL // requires OR'd arguments
#define DL_CLEAR_RGB        	0x02000000UL // requires OR'd arguments
#define DL_CLEAR_STENCIL    	0x11000000UL // requires OR'd arguments
#define DL_CLEAR_TAG        	0x12000000UL // requires OR'd arguments
#define DL_COLOR_A          	0x0F000000UL // requires OR'd arguments
#define DL_COLOR_MASK       	0x20000000UL // requires OR'd arguments
#define DL_COLOR_RGB        	0x04000000UL // requires OR'd arguments
#define DL_DISPLAY          	0x00000000UL
#define DL_END              	0x21000000UL
#define DL_JUMP             	0x1E000000UL // requires OR'd arguments
#define DL_LINE_WIDTH       	0x0E000000UL // requires OR'd arguments
#define DL_MACRO            	0x25000000UL // requires OR'd arguments
#define DL_POINT_SIZE       	0x0D000000UL // requires OR'd arguments
#define DL_RESTORE_CONTEXT  	0x23000000UL
#define DL_RETURN           	0x24000000UL
#define DL_SAVE_CONTEXT     	0x22000000UL
#define DL_SCISSOR_SIZE     	0x1C000000UL // requires OR'd arguments
#define DL_SCISSOR_XY       	0x1B000000UL // requires OR'd arguments
#define DL_STENCIL_FUNC     	0x0A000000UL // requires OR'd arguments
#define DL_STENCIL_MASK     	0x13000000UL // requires OR'd arguments
#define DL_STENCIL_OP       	0x0C000000UL // requires OR'd arguments
#define DL_TAG             		0x03000000UL // requires OR'd arguments
#define DL_TAG_MASK         	0x14000000UL // requires OR'd arguments
#define DL_VERTEX2F         	0x40000000UL // requires OR'd arguments
#define DL_VERTEX2II        	0x02000000UL // requires OR'd arguments



// Command and register value options
#define CLR_COL               0x4
#define CLR_STN               0x2
#define CLR_TAG               0x1
#define DECR                  4UL
#define DECR_WRAP             7UL
#define DLSWAP_DONE           0UL
#define DLSWAP_FRAME          2UL
#define DLSWAP_LINE           1UL
#define DST_ALPHA             3UL
#define EDGE_STRIP_A          7UL
#define EDGE_STRIP_B          8UL
#define EDGE_STRIP_L          6UL
#define EDGE_STRIP_R          5UL
#define EQUAL                 5UL
#define GEQUAL                4UL
#define GREATER               3UL
#define INCR                  3UL
#define INCR_WRAP             6UL
#define INT_CMDEMPTY          32UL
#define INT_CMDFLAG           64UL
#define INT_CONVCOMPLETE      128UL
#define INT_PLAYBACK          16UL
#define INT_SOUND             8UL
#define INT_SWAP              1UL
#define INT_TAG               4UL
#define INT_TOUCH             2UL
#define INVERT                5UL
#define KEEP                  1UL
#define L1                    1UL
#define L4                    2UL
#define L8                    3UL
#define LEQUAL                2UL
#define LESS                  1UL
#define LINEAR_SAMPLES        0UL
#define LINES                 3UL
#define LINE_STRIP            4UL
#define NEAREST               0UL
#define NEVER                 0UL
#define NOTEQUAL              6UL
#define ONE                   1UL
#define ONE_MINUS_DST_ALPHA   5UL
#define ONE_MINUS_SRC_ALPHA   4UL
#define OPT_CENTER            1536UL    // 0x6000
#define OPT_CENTERX           512UL     // 0x0200
#define OPT_CENTERY           1024UL    // 0x0400
#define OPT_FLAT              256UL     // 0x0100
#define OPT_MONO              1UL
#define OPT_NOBACK            4096UL    // 0x1000
#define OPT_NODL              2UL
#define OPT_NOHANDS           49152UL   // 0xC168
#define OPT_NOHM              16384UL   // 0x4000
#define OPT_NOPOINTER         16384UL   // 0x4000
#define OPT_NOSECS            32768UL   // 0x8000
#define OPT_NOTICKS           8192UL    // 0x2000
#define OPT_RIGHTX            2048UL    // 0x0800
#define OPT_SIGNED            256UL     // 0x0100
#define PALETTED              8UL
#define PLAYCOLOR             0x00a0a080
#define FTPOINTS              2UL       // "POINTS" is a reserved word
#define RECTS                 9UL
#define REPEAT                1UL
#define REPLACE               2UL
#define RGB332                4UL
#define RGB565                7UL
#define SRC_ALPHA             2UL
#define TEXT8X8               9UL
#define TEXTVGA               10UL
#define TOUCHMODE_CONTINUOUS  3UL
#define TOUCHMODE_FRAME       2UL
#define TOUCHMODE_OFF         0UL
#define TOUCHMODE_ONESHOT     1UL
#define ULAW_SAMPLES          1UL
#define ZERO                  0UL



#endif /* FT801_INC_FT80X_H_ */
