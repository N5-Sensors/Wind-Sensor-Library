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

#include<stdio.h>

#ifndef WindSensor_h
#define WindSensor_h
    
    void initWindSensor (void);  // this function will initialize the wind sensor
    
    uint16_t ModRTU_CRC(uint8_t * buf, int len);  //this function returns the MODRTU CRC of the data
    
    struct Measurements{
        uint16_t direction;
        float speed;
    };
    
    struct Measurements getData();
    
    
#endif

/* [] END OF FILE */
