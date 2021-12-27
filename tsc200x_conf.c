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

#include "tsc200x_conf.h"
// Your includes
#include "i2c.h"

int32_t tsc200x_write_reg(uint16_t reg, uint8_t* data, uint16_t len);
int32_t tsc200x_read_reg(uint16_t reg, uint8_t* data, uint16_t len);

// =====================================
// Change these to suit your application
// =====================================

// IO bus configuration - set the functions for your
// IO driver.  Implement the WriteReg and ReadReg below
TSC200X_IO_t TSC200X_IO_Drv =
{
    .Init       = MX_I2C4_Init,
    .DeInit     = NULL,
    .Address    = TSC200X_ADDR,
    .WriteReg   = tsc200x_write_reg,
    .ReadReg    = tsc200x_read_reg,
    .GetTick    = HAL_GetTick,
    .Delay      = HAL_Delay
};
// Driver context - set the handle paramater to match
// your I2C driver handle if required
TSC200X_CTX_t TSC200X_Ctx_Drv =
{
    .handle     = &hi2c4,
    .ReadReg    = NULL,
    .WriteReg   = NULL
};

// The object - no configuration necessary 
TSC200X_Object_t TSC200X =
{
    .Ctx            = TSC200X_Ctx_Drv,
    .IO             = TSC200X_IO_Drv,
    .isInitialized  = 0;
};

/**
 * @brief   Function to write register data to device 
 * @param   reg     Register Address
 * @param   data    Pointer to data to write 
 * @param   len     Length of data in bytes 
 * @return  0 for success
 */
int32_t tsc200x_write_reg(uint16_t reg, uint8_t* data, uint16_t len)
{
    return HAL_I2C_Mem_Write(   (I2C_HandleTypeDef *)TSC200X.Ctx.handle,
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
int32_t tsc200x_read_reg(uint16_t reg, uint8_t* data, uint16_t len)
{
    return HAL_I2C_Mem_Read(    (I2C_Handle_TypeDef *)TSC200X.Ctx.handle,
                                TSC200X.IO.Address,
                                reg,
                                I2C_MEMADD_SIZE_8BIT,
                                data,
                                len,
                                1000);
}

