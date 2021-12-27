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

// ====================
// Private Functions
// ====================

static int32_t tsc200x_write_reg(TSC200X_CTX_t *ctx, uint8_t reg, uint8_t *pbuf, uint16_t length)
{
    return ctx->WriteReg(ctx->handle, reg, pbuf, length);
}
static int32_t tsc200x_read_reg(TSC200X_CTX_t *ctx, uint8_t reg, uint8_t *pbuf, uint16_t length)
{
    return ctx->ReadReg(ctx->handle, reg, pbuf, length);
}

static int32_t tsc200x_detectTouch(TSC200X_Obj_t *pObj, uint8_t *pData, uint32_t length)
{
    int32_t ret;

    return ret;
}

/**
  * @brief  Register IO bus to component object
  * @param  pObj    object pointer
  * @param  pIO     io structure pointer
  * @retval error status
  */
int32_t TSC200X_RegisterBusIO (TSC200X_Object_t *pObj, TSC200X_IO_t *pIO)
{
    int32_t ret = TSC200X_OK;

    if(pObj == NULL)
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

        pObj->Ctx.ReadReg   = ReadRegWrap;
        pObj->Ctx.WriteReg  = WriteRegWrap;
        pObj->Ctx.handle    = pObj;

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

int32_t TSC200X_Init(TSC200X_Object_t *pObj)
{

}

/**
  * @brief  De-Initialize the TSC200X communication bus
  *         from MCU to EXC7200 : ie I2C channel initialization (if required).
  * @param  pObj    Component object pointer
  * @retval Component status
  */
int32_t TSC200X_DeInit(TSC200X_Object_t *pObj)
{
    int32_t ret = TSC200X_OK;

    if(pObj.isInitialized)
    {
        if(pObj->IO.DeInit() != TSC200X_OK)
        {
            return TSC200X_ERROR;
        }
        else
        {
            pObj.isInitialized = 0;
        }
    }

    return ret;
}

/**
  * @brief  Configure the EXC7200 gesture
  * @param  pObj        Component object pointer
  * @param  GestureInit Gesture init structure
  * @retval Component status
  */
int32_t TSC200X_GestureConfig(TSC200X_Object_t *pObj, TSC200X_Gesture_Init_t *GestureInit)
{
    /* Prevent unused argument(s) compilation warning */  
    (void)(pObj);

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

int32_t TSC200X_GetState(TSC200X_Object_t *pObj, TSC200X_State_t *State)
{

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
}

int32_t TSC200X_EnableIT(TSC200X_Object_t *pObj)
{

}

int32_t TSC200X_DisableIT(TSC200X_Object_t *pObj)
{

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
    Capabilities->Getsture      = 0;
    Capabilities->MaxTouch      = TSC200X_MAX_NB_TOUCH;
    Capabilities->MaxXl         = TSC200X_MAX_WIDTH;
    Capabilities->MaxYl         = TSC200X_MAX_HEIGHT;

    return TSC200X_OK;
}
