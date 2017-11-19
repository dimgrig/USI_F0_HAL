#include "t14-ssi.h"


void SSI_CLK_HIGH()
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
}

void SSI_CLK_LOW()
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
}

uint8_t SSI_DATA_PORT()
{
  return HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
}

uint32_t ReadSSI(void)  
{ 
    uint8_t  bit_count; 
    uint32_t result = 0; 
    uint32_t  portdata; 
    uint16_t N = 0;
    uint16_t M = 2;
    
    SSI_CLK_HIGH();
    
    for (int i = 0; i < M; )
      i++;  
    
    SSI_CLK_LOW();
    
    for (int i = 0; i < M; )
      i++;  
    
    SSI_CLK_HIGH();
    
    for (int i = 0; i < M; )
      i++;  
    
    SSI_CLK_LOW();
    
    uint16_t j = 0;
    
    for (int i = 0; i < 100; )
    {
      i++; 
      if (SSI_DATA_PORT()==0)
      {
        break;
      }
    }
    
    SSI_CLK_HIGH();
         
    for (int i = 0; i < M; )
      i++;
        
    for (bit_count=0; bit_count<19; bit_count++) 
    { 
        // falling edge on clock port 
        //SSI_CLK_PORT &= ~(1 << SSI_CLK_BIT);         
        SSI_CLK_LOW();
        
        for (int i = 0; i < N; )
          i++;
      
        // left-shift the current result 
        result = (result << 1);    
 
        // read the port data  
        portdata = SSI_DATA_PORT(); 
        
        for (int i = 0; i < N; )
          i++;
        
        result = result | portdata;
        // rising edge on clock port, data changes 
        //SSI_CLK_PORT |= (1 << SSI_CLK_BIT);  
        SSI_CLK_HIGH();
 
        // evaluate the port data (port set or clear) 
/*        if ( (portdata & (1 << SSI_DATA_PORT())) != 0) 
        { 
            // bit is set, set LSB of result 
            result = result | 0x01;   
        }  // if */
        
        for (int i = 0; i < N; )
          i++;
    } // for 
    return result; 
} 
