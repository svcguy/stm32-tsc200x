/**
 * @file    tsc200x.c
 * @author  svcguy
 * @brief   A STM32Cube HAL based driver for the 
 *          TSC2003, TSC2007 resistive touch screen
 *          controllers
 * @version 0.1
 * @date    2021-12-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "tsc200x.h"
#include "tsc200x_conf.h"

// Touch screen driver structure initialization
TSC200X_TS_Drv_t TSC200X_TS_Driver =
{
    TSC200X_Init,
    TSC200X_DeInit,
    TSC200X_GestureConfig,
    TSC200X_ReadID,
    TSC200X_GetState,
    TSC200X_GetMultiTouchState,
    TSC200X_GetGesture,
    TSC200X_GetCapabilities,
    TSC200X_EnableIT,
    TSC200X_DisableIT,
    TSC200X_ClearIT,
    TSC200X_ITStatus
};

/**
  * @brief  Register IO bus to component object
  * @param  pObj    object pointer
  * @param  pIO     io structure pointer
  * @retval error status
  */
int32_t TSC200X_RegisterBusIO(TSC200X_Object_t *pObj, TSC200X_IO_t *pIO)
{
    int32_t ret = TSC200X_OK;

    if(pObj == NULL || pIO == NULL)
    {
        ret = TSC200X_ERROR;
    }
    else
    {
        pObj->IO.Init       = pIO->Init;
        pObj->IO.DeInit     = pIO->DeInit;
        pObj->IO.Address    = pIO->Address;
        pObj->IO.WriteReg   = pIO->WriteReg;
        pObj->IO.ReadReg    = pIO->ReadReg;
        pObj->IO.GetTick    = pIO->GetTick;
        pObj->IO.Delay      = pIO->Delay;
        pObj->IO.Handle     = pIO->Handle;

        if(pObj->IO.Init != NULL)
        {
            ret = pObj->IO.Init();
        }
        else
        {
            ret = TSC200X_ERROR;
        }
    }

    return ret;
}

/**
  * @brief  Initialize the TSC200X communication bus
  * @param  pObj        Component object pointer
  * @retval Component status.
  */
int32_t TSC200X_Init(TSC200X_Object_t *pObj)
{
    int32_t ret = TSC200X_OK;

    if(pObj == NULL || pObj->IO.Init == NULL)
    {
        return TSC200X_ERROR;
    }

    if(!pObj->IsInitialized)
    {
        if(pObj->IO.Init() != TSC200X_OK)
        {
            return TSC200X_ERROR;
        }
        else
        {
            pObj->IsInitialized = 1;
        }
    }

    return ret;
}

/**
  * @brief  De-Initialize the TSC200X communication bus
  * @param  pObj    Component object pointer
  * @retval Component status
  */
int32_t TSC200X_DeInit(TSC200X_Object_t *pObj)
{
    int32_t ret = TSC200X_OK;

    if(pObj == NULL || pObj->IO.DeInit == NULL)
    {
        return TSC200X_ERROR;
    }

    if(pObj->IsInitialized)
    {
        if(pObj->IO.DeInit() != TSC200X_OK)
        {
            return TSC200X_ERROR;
        }
        else
        {
            pObj->IsInitialized = 0;
        }
    }

    return ret;
}

/**
  * @brief  Configure the TSC200X gesture
  * @param  pObj        Component object pointer
  * @param  GestureInit Gesture init structure
  * @retval Component status
  */
int32_t TSC200X_GestureConfig(TSC200X_Object_t *pObj, TSC200X_Gesture_Init_t *GestureInit)
{
    /* Prevent unused argument(s) compilation warning */ 
    (void)(pObj);
    (void)(GestureInit);

    /* Feature not supported */
    return TSC200X_ERROR;
}

/**
 * @brief   Read the TSC200X ID 
 * @param   pObj  Component object pointer
 * @param   Id    Pointer to component ID value
 * @note    Not supported on TSC200X
 * @return  Component status. 
 */
int32_t TSC200X_ReadID(TSC200X_Object_t *pObj, uint32_t *Id)
{
    /* Prevent unused argument(s) compilation warning */  
    (void)(pObj);

    /* Feature not supported */
    *Id = 0;
    return TSC200X_ERROR;
}

/**
 * @brief   Get the touch state * 
 * @param   pObj    Component object pointer
 * @param   State   State structure.  State.TouchDetected
 *                  will be set to 1 if a touch is detected
 *                  and the x and y will be filled.  If
 *                  no touch is detected, TouchDetected will
 *                  be set to 0
 * @return Component Status
 */
int32_t TSC200X_GetState(TSC200X_Object_t *pObj, TSC200X_State_t *State)
{
    int32_t ret = TSC200X_OK;
    uint8_t buf[2];

    // Activate X and Y drivers
    pObj->IO.WriteReg((TSC200X_ACTIVATE_YP_XN | TSC200X_ADC_ON_IRQ_DIS0 | TSC200X_8BIT), buf, 1);

    // Delay
    pObj->IO.Delay(1);

    // Check Z1 to see if there is a touch occuring
    pObj->IO.ReadReg((TSC200X_MEASURE_Z1 | TSC200X_ADC_ON_IRQ_DIS0 | TSC200X_12BIT), buf, 2);
    int16_t z1 = (((int16_t)buf[0]) << 4) | ((int16_t)buf[1]);
    if(z1 < 50)
    {
        State->TouchDetected = 0;
        return TSC200X_OK;
    }

    // Read X
    pObj->IO.WriteReg((TSC200X_ACTIVATE_XN | TSC200X_ADC_ON_IRQ_DIS0 | TSC200X_12BIT), buf, 1);
    pObj->IO.Delay(1);
    pObj->IO.ReadReg((TSC200X_MEASURE_X | TSC200X_ADC_ON_IRQ_DIS0 | TSC200X_12BIT), buf, 2);
    int16_t x = (((int16_t)buf[0]) << 4) | ((int16_t)buf[1]);

    // Read Y
    pObj->IO.WriteReg((TSC200X_ACTIVATE_YN | TSC200X_ADC_ON_IRQ_DIS0 | TSC200X_12BIT), buf, 1);
    pObj->IO.Delay(1);
    pObj->IO.ReadReg((TSC200X_MEASURE_Y | TSC200X_ADC_ON_IRQ_DIS0 | TSC200X_12BIT), buf, 2);
    int16_t y = (((int16_t)buf[0]) << 4) | ((int16_t)buf[1]);

    State->TouchDetected = 1;
    State->TouchX = (uint32_t)x;
    State->TouchY = (uint32_t)y;

    return ret;
}

/**
  * @brief  Get the touch screen Xn and Yn positions values in multi-touch mode
  * @param  pObj    Component object pointer
  * @param  State   Multi Touch stucture pointer
  * @retval Component status.
  */
int32_t TSC200X_GetMultiTouchState(TSC200X_Object_t *pObj, TSC200X_MultiTouch_State_t *State)
{
    /* Prevent unused argument(s) compilation warning */  
    (void)(pObj);
    (void)(State);

    /* Feature not supported */
    return TSC200X_ERROR;
}

/**
  * @brief  Get Gesture ID
  * @param  pObj        Component object pointer
  * @param  GestureId   gesture ID
  * @retval Component status.
  */
int32_t TSC200X_GetGesture(TSC200X_Object_t *pObj, uint8_t *GestureId)
{
    /* Prevent unused argument(s) compilation warning */  
    (void)(pObj);
    (void)(GestureId);

    /* Feature not supported */
    return TSC200X_ERROR;
}

/**
  * @brief  Enable interrupts, set PD0 = 1
  * @param  pObj        Component object pointer
  * @retval Component status.
  */
int32_t TSC200X_EnableIT(TSC200X_Object_t *pObj)
{
    int32_t ret = TSC200X_OK;

    if(pObj == NULL)
    {
        return TSC200X_ERROR;
    }

    uint8_t reg = 0x00;

    if(pObj->IO.ReadReg(TSC200X_SETUP, &reg, 1) != TSC200X_OK)
    {
        return TSC200X_FAIL;
    }

    return ret;
}

/**
  * @brief  Disable interrupts, set PD0 = 0
  * @param  pObj        Component object pointer
  * @retval Component status.
  */
int32_t TSC200X_DisableIT(TSC200X_Object_t *pObj)
{
    int32_t ret = TSC200X_OK;

    if(pObj == NULL)
    {
        return TSC200X_ERROR;
    }

    uint8_t reg = 0x00;

    if(pObj->IO.ReadReg(TSC200X_SETUP, &reg, 1) != TSC200X_OK)
    {
        return TSC200X_FAIL;
    }

    return ret;
}

/**
  * @brief  Get IT status from TSC200X interrupt status registers
  *         Should be called Following an EXTI coming to the MCU to know the detailed
  *         reason of the interrupt.
  * @note   This feature is not applicable to TSC200X.
  * @param  pObj Component object pointer
  * @retval Component status.
  */
int32_t TSC200X_ITStatus(TSC200X_Object_t *pObj)
{
    /* Prevent unused argument(s) compilation warning */  
    (void)(pObj);

    /* Feature not supported */
    return TSC200X_ERROR;
}

/**
  * @brief  Clear IT status in TSC200X interrupt status clear registers
  *         Should be called Following an EXTI coming to the MCU.
  * @note   This feature is not applicable to TSC200X
  * @param  pObj Component object pointer
  * @retval Component status.
  */
int32_t TSC200X_ClearIT(TSC200X_Object_t *pObj)
{
    /* Prevent unused argument(s) compilation warning */  
    (void)(pObj);

    /* Feature not supported */
    return TSC200X_ERROR;
}

/**
  * @brief  Get TSC200X sensor capabilities
  * @param  pObj            Component object pointer
  * @param  Capabilities    Pointer to TSC200X sensor capabilities
  * @retval Component status
  */
int32_t TSC200X_GetCapabilities(TSC200X_Object_t *pObj, TSC200X_Capabilities_t *Capabilities)
{
    /* Prevent unused argument(s) compilation warning */  
    (void)(pObj);

    /* Store component's capabilities */
    Capabilities->MultiTouch    = 0;
    Capabilities->Gesture       = 0;
    Capabilities->MaxTouch      = TSC200X_MAX_NB_TOUCH;
    Capabilities->MaxXl         = TSC200X_MAX_WIDTH;
    Capabilities->MaxYl         = TSC200X_MAX_HEIGHT;

    return TSC200X_OK;
}
