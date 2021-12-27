/**
 * @file    tsc200x.h
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

#ifndef _TSC2003_H
#define _TSC2003_H

#include "stm32f7xx_hal.h"

// =======================
// Defines
// =======================
#define TSC200X_ADDR                0x90

#define TSC200X_MEASURE_TEMP0       (0x0 << 4)
#define TSC200X_MEASURE_AUX         (0x2 << 4)
#define TSC200X_MEASURE_TEMP1		(0x4 << 4)
#define TSC200X_ACTIVATE_XN		    (0x8 << 4)
#define TSC200X_ACTIVATE_YN		    (0x9 << 4)
#define TSC200X_ACTIVATE_YP_XN		(0xa << 4)
#define TSC200X_SETUP			    (0xb << 4)  //tsc2007
#define TSC200X_MEASURE_X		    (0xc << 4)
#define TSC200X_MEASURE_Y		    (0xd << 4)
#define TSC200X_MEASURE_Z1		    (0xe << 4)
#define TSC200X_MEASURE_Z2		    (0xf << 4)

#define TSC200X_POWER_OFF_IRQ_EN	(0x0 << 2)
#define TSC200X_ADC_ON_IRQ_DIS0		(0x1 << 2)
#define TSC200X_ADC_OFF_IRQ_EN		(0x2 << 2)
#define TSC200X_ADC_ON_IRQ_DIS1		(0x3 << 2)

#define TSC200X_12BIT			    (0x0 << 1)
#define TSC200X_8BIT			    (0x1 << 1)

#define	MAX_12BIT			        ((1 << 12) - 1)

#define ADC_ON_12BIT	            (TSC200X_12BIT | TSC200X_ADC_ON_IRQ_DIS0)

#define READ_Y		(ADC_ON_12BIT | TSC200X_MEASURE_Y)
#define READ_Z1		(ADC_ON_12BIT | TSC200X_MEASURE_Z1)
#define READ_Z2		(ADC_ON_12BIT | TSC200X_MEASURE_Z2)
#define READ_X		(ADC_ON_12BIT | TSC200X_MEASURE_X)
#define PWRDOWN		(TSC200X_12BIT | TSC200X_POWER_OFF_IRQ_EN)

#define TSC200X_OK                  (0)
#define TSC200X_FAIL                (1)
#define TSC200X_ERROR               (-1)
 
#define TSC200X_MAX_HEIGHT          (800)
#define TSC200X_MAX_WIDTH           (400)
#define TSC200X_MAX_NB_TOUCH        (1)

// C++ Guards
#ifdef __cplusplus
extern "C" {
#endif

// =======================
// Public Types
// =======================
typedef int32_t (*TSC200X_Init_Func)        (void);
typedef int32_t (*TSC200X_DeInit_Func)      (void);
typedef uint32_t (*TSC200X_GetTick_Func)    (void);
typedef int32_t (*TSC200X_Delay_Func)       (uint32_t);
typedef int32_t (*TSC200X_WriteReg_Func)    (uint16_t, uint8_t*, uint16_t);
typedef int32_t (*TSC200X_ReadReg_Func)     (uint16_t, uint8_t*, uint16_t);
typedef int32_t (*TSC200X_Read_Func)        (void*, uint8_t, uint8_t*, uint16_t);
typedef int32_t (*TSC200X_Write_Func)       (void*, uint8_t, uint8_t*, uint16_t);

typedef struct
{
    TSC200X_Write_Func  WriteReg;
    TSC200X_Read_Func   ReadReg;
    void                *handle;
}
TSC200X_CTX_t;

typedef struct
{
    TSC200X_Init_Func       Init;
    TSC200X_DeInit_Func     DeInit;
    uint16_t                Address;
    TSC200X_WriteReg_Func   WriteReg;
    TSC200X_ReadReg_Func    ReadReg;
    TSC200X_GetTick_Func    GetTick;
    TSC200X_Delay_Func      Delay;
}
TSC200X_IO_t;

typedef struct
{
    uint32_t    TouchDetected;
    uint32_t    TouchX;
    uint32_t    TouchY;
}
TSC200X_State_t;

typedef struct
{
    uint32_t    TouchDetected;
    uint32_t    TouchX[TSC200X_MAX_NB_TOUCH];
    uint32_t    TouchY[TSC200X_MAX_NB_TOUCH];
    uint32_t    TouchWeight[TSC200X_MAX_NB_TOUCH];
    uint32_t    TouchEvent[TSC200X_MAX_NB_TOUCH];
    uint32_t    TouchArea[TSC200X_MAX_NB_TOUCH];
}
TSC2000X_MultiTouch_State_t;

typedef struct
{
    TSC200X_IO_t    IO;
    TSC200X_CTX_t   Ctx;
    uint8_t         IsInitialized;
}
TSC200X_Object_t;

typedef struct
{
    uint8_t     MultiTouch;
    uint8_t     Gesture;
    uint8_t     MaxTouch;
    uint32_t    MaxXl;
    uint32_t    MaxYl;
}
TSC200X_Capabilities_t;

typedef struct
{ 
  uint32_t  Radian;
  uint32_t  OffsetLeftRight;
  uint32_t  OffsetUpDown;
  uint32_t  DistanceLeftRight;
  uint32_t  DistanceUpDown;
  uint32_t  DistanceZoom;  
}
TSC200X_Gesture_Init_t;

typedef struct
{
    int32_t ( *Init                 ) ( TSC200X_Object_t *);
    int32_t ( *DeInit               ) ( TSC200X_Object_t * );
    int32_t ( *GestureConfig        ) ( TSC200X_Object_t *, TSC200X_Gesture_Init_t* );   
    int32_t ( *ReadID               ) ( TSC200X_Object_t *, uint32_t * ); 
    int32_t ( *GetState             ) ( TSC200X_Object_t *, TSC200X_State_t* );
    int32_t ( *GetMultiTouchState   ) ( TSC200X_Object_t *, TSC200X_MultiTouch_State_t* );
    int32_t ( *GetGesture           ) ( TSC200X_Object_t *, uint8_t* );
    int32_t ( *GetCapabilities      ) ( TSC200X_Object_t *, TSC200X_Capabilities_t * );
    int32_t ( *EnableIT             ) ( TSC200X_Object_t * );
    int32_t ( *DisableIT            ) ( TSC200X_Object_t * );
    int32_t ( *ClearIT              ) ( TSC200X_Object_t * );
    int32_t ( *ITStatus             ) ( TSC200X_Object_t * );  
}
TSC200X_TS_Drv_t;

// =======================
// Public Variables
// =======================
extern TSC200X_TS_Drv_t TSC200X_TS_Driver;

// =======================
// Public Functions
// =======================
int32_t TSC200X_RegisterBusIO (TSC200X_Object_t *pObj, TSC200X_IO_t *pIO);
int32_t TSC200X_Init(TSC200X_Object_t *pObj);
int32_t TSC200X_DeInit(TSC200X_Object_t *pObj);
int32_t TSC200X_GestureConfig(TSC200X_Object_t *pObj, TSC200X_Gesture_Init_t *GestureInit);
int32_t TSC200X_ReadID(TSC200X_Object_t *pObj, uint32_t *Id);
int32_t TSC200X_GetState(TSC200X_Object_t *pObj, TSC200X_State_t *State);
int32_t TSC200X_GetMultiTouchState(TSC200X_Object_t *pObj, TSC200X_MultiTouch_State_t *State);
int32_t TSC200X_GetGesture(TSC200X_Object_t *pObj, uint8_t *GestureId);
int32_t TSC200X_EnableIT(TSC200X_Object_t *pObj);
int32_t TSC200X_DisableIT(TSC200X_Object_t *pObj);
int32_t TSC200X_ITStatus(TSC200X_Object_t *pObj);
int32_t TSC200X_ClearIT(TSC200X_Object_t *pObj);
int32_t TSC200X_GetCapabilities(TSC200X_Object_t *pObj, TSC200X_Capabilities_t *Capabilities);

#ifdef __cplusplus
}
#endif

#endif /* _TSC2003_H_ */
