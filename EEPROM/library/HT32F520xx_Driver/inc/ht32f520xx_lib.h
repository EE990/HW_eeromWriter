/*********************************************************************************************************//**
 * @file    ht32f520xx_lib.h
 * @version $Rev:: 957          $
 * @date    $Date:: 2016-08-15 #$
 * @brief   The header file includes all the header files of the libraries.
 *************************************************************************************************************
 * @attention
 *
 * Firmware Disclaimer Information
 *
 * 1. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, which is supplied by Holtek Semiconductor Inc., (hereinafter referred to as "HOLTEK") is the
 *    proprietary and confidential intellectual property of HOLTEK, and is protected by copyright law and
 *    other intellectual property laws.
 *
 * 2. The customer hereby acknowledges and agrees that the program technical documentation, including the
 *    code, is confidential information belonging to HOLTEK, and must not be disclosed to any third parties
 *    other than HOLTEK and the customer.
 *
 * 3. The program technical documentation, including the code, is provided "as is" and for customer reference
 *    only. After delivery by HOLTEK, the customer shall use the program technical documentation, including
 *    the code, at their own risk. HOLTEK disclaims any expressed, implied or statutory warranties, including
 *    the warranties of merchantability, satisfactory quality and fitness for a particular purpose.
 *
 * <h2><center>Copyright (C) Holtek Semiconductor Inc. All rights reserved</center></h2>
 ************************************************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------------------------------------*/
#ifndef __HT32F520XX_LIB_H
#define __HT32F520XX_LIB_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Settings ------------------------------------------------------------------------------------------------*/
#if defined(USE_HT32F52220_30)
  #include "ht32f52220_30_libcfg.h"
#endif
#if defined(USE_HT32F52231_41)
  #include "ht32f52231_41_libcfg.h"
#endif
#if defined(USE_HT32F52331_41)
  #include "ht32f52331_41_libcfg.h"
#endif
#if defined(USE_HT32F52342_52)
  #include "ht32f52342_52_libcfg.h"
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "ht32f520xx_01_conf.h"

#if (HT32_LIB_DEBUG == 1)
/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed.
  *   If expr is true, it returns no value.
  * @retval None
  */
#define Assert_Param(expr) ((expr) ? (void)0 : assert_error((u8 *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- ------------------------------*/
void assert_error(u8* file, u32 line);
#else

#define Assert_Param(expr) ((void)0)

#endif /* DEBUG --------------------------------------------------------------------------------------------*/


#if _ADC
  #include "ht32f520xx_adc.h"
#endif

#if _BFTM
  #include "ht32f520xx_bftm.h"
#endif

#if _CKCU
  #include "ht32f520xx_ckcu.h"
#endif

#if _CMP && (defined(LIBCFG_CMP))
  #include "ht32f520xx_cmp.h"
#endif

#if _CRC && (defined(LIBCFG_CRC))
  #include "ht32f520xx_crc.h"
#endif

#if _EBI && (defined(LIBCFG_EBI))
  #include "ht32f520xx_ebi.h"
#endif

#if _EXTI
  #include "ht32f520xx_exti.h"
#endif

#if _FLASH
  #include "ht32f520xx_flash.h"
#endif

#if _GPIO
  #include "ht32f520xx_gpio.h"
#endif

#if _GPTM
  #include "ht32f520xx_tm_type.h"
  #include "ht32f520xx_tm.h"
#endif

#if _I2C
  #include "ht32f520xx_i2c.h"
#endif

#if _I2S && (defined(LIBCFG_I2S))
  #include "ht32f520xx_i2s.h"
#endif

#if _MCTM && (defined(LIBCFG_MCTM0))
  #include "ht32f520xx_tm_type.h"
  #include "ht32f520xx_tm.h"
  #include "ht32f520xx_mctm.h"
#endif

#if _PDMA && (defined(LIBCFG_PDMA))
  #include "ht32f520xx_pdma.h"
#endif

#if _PWRCU
  #include "ht32f520xx_pwrcu.h"
#endif

#if _RSTCU
  #include "ht32f520xx_rstcu.h"
#endif

#if _RTC
  #include "ht32f520xx_rtc.h"
#endif

#if _SCI && (defined(LIBCFG_SCI0) || defined(LIBCFG_SCI1))
  #include "ht32f520xx_sci.h"
#endif

#if _SCTM
  #include "ht32f520xx_tm_type.h"
  #include "ht32f520xx_tm.h"
#endif

#if _SPI
  #include "ht32f520xx_spi.h"
#endif

#if _USART
  #include "ht32f520xx_usart.h"
#endif

#if _USB && (defined(LIBCFG_USBD))
  #include "ht32f523xx_usbd.h"
#endif

#if _WDT
  #include "ht32f520xx_wdt.h"
#endif

#if _MISC
  #include "ht32_cm0plus_misc.h"
#endif

#if (_RETARGET)
  #if defined (__GNUC__)
    #undef getchar
    #define getchar SERIAL_GetChar
  #endif
#endif

#include "ht32_serial.h"
#include "ht32_div.h"
#include "ht32_rand.h"

#ifdef __cplusplus
}
#endif

#endif
