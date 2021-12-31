/**
 * @file    tsc200x_conf.c
 * @author  svcguy
 * @brief   Configuration file for TSC200X touch
 *          screen driver
 * @version 0.1
 * @date 2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "tsc200x.h"
#include "tsc200x_conf.h"
// Your includes
#include "main.h"
#include "stm32h7xx_hal.h"

// =====================================
// Change these to suit your application
// =====================================
TSC200X_Object_t TSC200X =
{
    .IO.Address = TSC200X_ADDR,
    .IO.Init = i2c_init,
    .IO.DeInit = NULL,
    .IO.ReadReg = tsc200x_read,
    .IO.WriteReg = tsc200x_write,
    .IO.GetTick = HAL_GetTick,
    .IO.Delay = HAL_Delay,
    .IO.Handle = (void *)&hi2c1
};

/**
 * @brief   Function to write register data to device 
 * @param   reg     Register Address
 * @param   data    Pointer to data to write 
 * @param   len     Length of data in bytes 
 * @return  0 for success
 */
int32_t tsc200x_write(uint16_t reg, uint8_t* data, uint16_t len)
{
    return HAL_I2C_Mem_Write(   (I2C_HandleTypeDef *)TSC200X.IO.Handle,
                                TSC200X.IO.Address,
                                reg,
                                I2C_MEMADD_SIZE_8BIT,
                                data,
                                len,
                                1000);
}

/**
 * @brief   Function to read register data from device 
 * @param   reg     Register Address 
 * @param   data    Pointer to data to write 
 * @param   len     Length of data in bytes 
 * @return  0 for success 
 */
int32_t tsc200x_read(uint16_t reg, uint8_t* data, uint16_t len)
{
    return HAL_I2C_Mem_Read(    (I2C_HandleTypeDef *)TSC200X.IO.Handle,
                                TSC200X.IO.Address,
                                reg,
                                I2C_MEMADD_SIZE_8BIT,
                                data,
                                len,
                                1000);
}

