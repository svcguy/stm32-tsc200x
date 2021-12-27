/**
 * @file    tsc200x_conf.h
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

#ifndef _TSC2003_CONF_H
#define _TSC2003_CONF_H

// C++ Guards
#ifdef __cplusplus
extern "C" {
#endif

// Change these to suit your application
#define TSC200X_X_SIZE  480
#define TSC200X_Y_SIZE  272

// Goto to tsc200x_conf.c to change these
// to suit your application
extern TSC200X_IO_t     TSC200X_IO_Drv;
extern TSC200X_CTX_t    TSC200X_Ctx_Drv;
extern TSC200X_Object_t TSC200X;

#ifdef __cplusplus
}
#endif

#endif /* _TSC2003_CONF_H_ */
