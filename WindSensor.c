/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/


#include "project.h"
#include <stdio.h>
#include <stdlib.h>
#include "WindSensor.h"

void initWindSensor (void){
    USBUART_Start(0,USBUART_3V_OPERATION);
    UART_DEV_EN_Write(1);
    UART_1_Start();
}

uint16_t ModRTU_CRC(uint8_t * buf, int len)
{
  uint16_t crc = 0xFFFF;
  
  for (int pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc
  
    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;  
}

struct Measurements getData(){
    struct Measurements results;
    uint8_t command[8] = {0x01,0x03,0x00,0x00,0x00,0x02,0xC4,0x0B};
    uint8_t result[9];
    uint16_t speed ,direction,crc;
    
    unsigned long m = 0;
    #define TIMEOUT 300
        
    CyDelay(1000);
    UART_1_PutArray(command,8);
    CyDelay(50);
    int i=0;
           
    while ((i < 10) && (m < TIMEOUT)){
        if(UART_1_GetRxBufferSize()){
            result[i] = UART_1_GetByte();
            i++;
        } 
        else{
            m++;
            CyDelay(1);
        }
    }
         
    speed = result[3];
    speed = speed << 8;
    speed = speed | result[4];
        
    direction = result[5];
    direction = direction << 8;
    direction = direction | result[6];
        
    crc = result[8];
    crc = crc << 8;
    crc = crc | result[7];
        
    if (crc == ModRTU_CRC(result,7)){
        results.direction = direction;
        results.speed = speed/100.0;
        return results;
    }
}        


/* [] END OF FILE */
