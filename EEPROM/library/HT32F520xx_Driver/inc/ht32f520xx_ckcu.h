/*********************************************************************************************************//**
 * @file    ht32f520xx_ckcu.h
 * @version $Rev:: 834          $
 * @date    $Date:: 2016-06-25 #$
 * @brief   The header file of the Clock Control Unit library.
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
#ifndef __HT32F520XX_CKCU_H
#define __HT32F520XX_CKCU_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f520xx_01.h"

/** @addtogroup HT32F520xx_Peripheral_Driver HT32F520xx Peripheral Driver
  * @{
  */

/** @addtogroup CKCU
  * @{
  */


/* Exported types ------------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Types CKCU exported types
  * @{
  */

/**
 * @brief Enumeration of APB peripheral prescaler.
 */
typedef enum
{
  CKCU_APBCLKPRE_DIV1 = 0,
  CKCU_APBCLKPRE_DIV2,
  CKCU_APBCLKPRE_DIV4,
  CKCU_APBCLKPRE_DIV8,
  CKCU_APBCLKPRE_DIV16,
  CKCU_APBCLKPRE_DIV32
} CKCU_APBCLKPRE_TypeDef;

/**
 * @brief Enumeration of CK_REF prescaler.
 */
typedef enum
{
  CKCU_CKREFPRE_DIV2 = 0,
  CKCU_CKREFPRE_DIV4,
  CKCU_CKREFPRE_DIV6,
  CKCU_CKREFPRE_DIV8,
  CKCU_CKREFPRE_DIV10,
  CKCU_CKREFPRE_DIV12,
  CKCU_CKREFPRE_DIV14,
  CKCU_CKREFPRE_DIV16,
  CKCU_CKREFPRE_DIV18,
  CKCU_CKREFPRE_DIV20,
  CKCU_CKREFPRE_DIV22,
  CKCU_CKREFPRE_DIV24,
  CKCU_CKREFPRE_DIV26,
  CKCU_CKREFPRE_DIV28,
  CKCU_CKREFPRE_DIV30,
  CKCU_CKREFPRE_DIV32,
  CKCU_CKREFPRE_DIV34,
  CKCU_CKREFPRE_DIV36,
  CKCU_CKREFPRE_DIV38,
  CKCU_CKREFPRE_DIV40,
  CKCU_CKREFPRE_DIV42,
  CKCU_CKREFPRE_DIV44,
  CKCU_CKREFPRE_DIV46,
  CKCU_CKREFPRE_DIV48,
  CKCU_CKREFPRE_DIV50,
  CKCU_CKREFPRE_DIV52,
  CKCU_CKREFPRE_DIV54,
  CKCU_CKREFPRE_DIV56,
  CKCU_CKREFPRE_DIV58,
  CKCU_CKREFPRE_DIV60,
  CKCU_CKREFPRE_DIV62,
  CKCU_CKREFPRE_DIV64
} CKCU_CKREFPRE_TypeDef;

/**
 * @brief Enumeration of PLL clock source.
 */
typedef enum
{
  CKCU_PLLSRC_HSE = 0,
  CKCU_PLLSRC_HSI
} CKCU_PLLSRC_TypeDef;

#if defined(LIBCFG_LSE) || defined(LIBCFG_USBD)
/**
 * @brief Enumeration of HSI auto-trim clock source.
 */
typedef enum
{
  #if defined(LIBCFG_LSE)
  CKCU_ATC_LSE = 0,
  #endif
  #if defined(LIBCFG_USBD)
  CKCU_ATC_USB,
  #endif
} CKCU_ATC_TypeDef;
#endif

/**
 * @brief Enumeration of CK_AHB prescaler.
 */
typedef enum
{
  CKCU_SYSCLK_DIV1 = 0,
  CKCU_SYSCLK_DIV2,
  CKCU_SYSCLK_DIV4,
  CKCU_SYSCLK_DIV8,
  CKCU_SYSCLK_DIV16,
  CKCU_SYSCLK_DIV32
} CKCU_SYSCLKDIV_TypeDef;

/**
 * @brief Enumeration of CK_ADC prescaler.
 */
typedef enum
{
  CKCU_ADCPRE_DIV1 = 0,
  CKCU_ADCPRE_DIV2,
  CKCU_ADCPRE_DIV4,
  CKCU_ADCPRE_DIV8,
  CKCU_ADCPRE_DIV16,
  CKCU_ADCPRE_DIV32,
  CKCU_ADCPRE_DIV64,
  CKCU_ADCPRE_DIV3
} CKCU_ADCPRE_TypeDef;

/**
 * @brief Enumeration of System clock source.
 */
typedef enum
{
  CKCU_SW_PLL = 1,
  CKCU_SW_HSE = 2,
  CKCU_SW_HSI = 3,
  #if defined(LIBCFG_LSE)
  CKCU_SW_LSE = 6,
  #endif
  CKCU_SW_LSI = 7
} CKCU_SW_TypeDef;

/**
 * @brief Enumeration of CKOUT clock source.
 */
typedef enum
{
  CKCU_CKOUTSRC_REFCK       = 0,
  CKCU_CKOUTSRC_HCLK_DIV16  = 1,
  CKCU_CKOUTSRC_SYSCK_DIV16 = 2,
  CKCU_CKOUTSRC_HSECK_DIV16 = 3,
  CKCU_CKOUTSRC_HSICK_DIV16 = 4,
  #if defined(LIBCFG_LSE)
  CKCU_CKOUTSRC_LSECK       = 5,
  #endif
  CKCU_CKOUTSRC_LSICK       = 6
} CKCU_CKOUTSRC_TypeDef;

/**
 * @brief Enumeration of PLL clock source status.
 */
typedef enum
{
  CKCU_PLLST_SYSCK  = 1,
  #if defined(LIBCFG_USBD)
  CKCU_PLLST_USB    = 4,
  #endif
  CKCU_PLLST_REFCK  = 8
} CKCU_PLLST_TypeDef;

/**
 * @brief Enumeration of HSI clock source status.
 */
typedef enum
{
  CKCU_HSIST_SYSCK  = 1,
  CKCU_HSIST_PLL    = 2,
  CKCU_HSIST_CKM    = 4
} CKCU_HSIST_TypeDef;

/**
 * @brief Enumeration of HSE clock source status.
 */
typedef enum
{
  CKCU_HSEST_SYSCK  = 1,
  CKCU_HSEST_PLL
} CKCU_HSEST_TypeDef;

/**
 * @brief Definition of initial structure for CKOUT function.
 */
typedef struct
{
  CKCU_CKOUTSRC_TypeDef CKOUTSRC;
} CKCU_CKOUTInitTypeDef;

/**
 * @brief Definition of initial structure of PLL frequency.
 */
typedef struct
{
  u32 CFG;
  CKCU_PLLSRC_TypeDef ClockSource;
  EventStatus BYPASSCmd;
} CKCU_PLLInitTypeDef;

/**
 * @brief Definition of structure for clock frequency.
 */
typedef struct
{
  u32 PLL_Freq;
  u32 SYSCK_Freq;
  u32 HCLK_Freq;
  u32 ADC_Freq;
} CKCU_ClocksTypeDef;

/**
 * @brief Definition of initial structure of peripheral clock control.
 */
typedef union
{
  struct
  {
    unsigned long FMC        :1;
    unsigned long            :1;
    unsigned long SRAM       :1;
    unsigned long            :1;
    unsigned long PDMA       :1;
    unsigned long BM         :1;
    unsigned long APB        :1;
    unsigned long            :3;
    unsigned long USBD       :1;
    unsigned long CKREF      :1;
    unsigned long EBI        :1;
    unsigned long CRC        :1;
    unsigned long            :2;
    unsigned long PA         :1;
    unsigned long PB         :1;
    unsigned long PC         :1;
    unsigned long PD         :1;
    unsigned long            :12;

    unsigned long I2C0       :1;
    unsigned long I2C1       :1;
    unsigned long            :2;
    unsigned long SPI0       :1;
    unsigned long SPI1       :1;
    unsigned long            :2;
    unsigned long USART0     :1;
    unsigned long USART1     :1;
    unsigned long UART0      :1;
    unsigned long UART1      :1;
    unsigned long            :2;
    unsigned long AFIO       :1;
    unsigned long EXTI       :1;
    unsigned long            :8;
    unsigned long SCI0       :1;
    unsigned long I2S        :1;
    unsigned long            :1;
    unsigned long SCI1       :1;
    unsigned long            :4;

    unsigned long MCTM0      :1;
    unsigned long            :3;
    unsigned long WDT        :1;
    unsigned long            :1;
    unsigned long BKP        :1;
    unsigned long            :1;
    unsigned long GPTM0      :1;
    unsigned long GPTM1      :1;
    unsigned long            :6;
    unsigned long BFTM0      :1;
    unsigned long BFTM1      :1;
    unsigned long            :4;
    unsigned long CMP        :1;
    unsigned long            :1;
    unsigned long ADC        :1;
    unsigned long            :3;
    unsigned long SCTM0      :1;
    unsigned long SCTM1      :1;
    unsigned long SCTM2      :1;
    unsigned long SCTM3      :1;
  } Bit;
  u32 Reg[3];
} CKCU_PeripClockConfig_TypeDef;

#define CKCU_APBPCSR_OFFSET      (5)
#define CKCU_APBPCSR0            (0 << CKCU_APBPCSR_OFFSET)
#define CKCU_APBPCSR1            (1 << CKCU_APBPCSR_OFFSET)
typedef enum
{
  CKCU_PCLK_I2C0     = (CKCU_APBPCSR0 | 0),
  #if defined(LIBCFG_I2C1)
  CKCU_PCLK_I2C1     = (CKCU_APBPCSR0 | 2),
  #endif
  CKCU_PCLK_SPI0     = (CKCU_APBPCSR0 | 4),
  #if defined(LIBCFG_SPI1)
  CKCU_PCLK_SPI1     = (CKCU_APBPCSR0 | 6),
  #endif
  CKCU_PCLK_BFTM0    = (CKCU_APBPCSR0 | 12),
  #if defined(LIBCFG_BFTM1)
  CKCU_PCLK_BFTM1    = (CKCU_APBPCSR0 | 14),
  #endif
  #if defined(LIBCFG_MCTM0)
  CKCU_PCLK_MCTM0    = (CKCU_APBPCSR0 | 16),
  #endif
  CKCU_PCLK_GPTM0    = (CKCU_APBPCSR0 | 20),
  #if defined(LIBCFG_GPTM1)
  CKCU_PCLK_GPTM1    = (CKCU_APBPCSR0 | 22),
  #endif
  CKCU_PCLK_USART0   = (CKCU_APBPCSR0 | 24),
  #if defined(LIBCFG_USART1)
  CKCU_PCLK_USART1   = (CKCU_APBPCSR0 | 26),
  #endif
  CKCU_PCLK_UART0    = (CKCU_APBPCSR0 | 28),
  #if defined(LIBCFG_UART1)
  CKCU_PCLK_UART1    = (CKCU_APBPCSR0 | 30),
  #endif
  CKCU_PCLK_AFIO     = (CKCU_APBPCSR1 | 0),
  CKCU_PCLK_EXTI     = (CKCU_APBPCSR1 | 2),
  CKCU_PCLK_ADC      = (CKCU_APBPCSR1 | 4),
  #if defined(LIBCFG_CMP)
  CKCU_PCLK_CMP      = (CKCU_APBPCSR1 | 8),
  #endif
  CKCU_PCLK_WDTR     = (CKCU_APBPCSR1 | 12),
  CKCU_PCLK_BKPR     = (CKCU_APBPCSR1 | 14),
  #if defined(LIBCFG_SCI0)
  CKCU_PCLK_SCI0     = (CKCU_APBPCSR1 | 16),
  #endif
  #if defined(LIBCFG_SCI1)
  CKCU_PCLK_SCI1     = (CKCU_APBPCSR1 | 18),
  #endif
  #if defined(LIBCFG_I2S)
  CKCU_PCLK_I2S      = (CKCU_APBPCSR1 | 20),
  #endif
  CKCU_PCLK_SCTM0    = (CKCU_APBPCSR1 | 24),
  CKCU_PCLK_SCTM1    = (CKCU_APBPCSR1 | 26),
  #if defined(LIBCFG_SCTM2)
  CKCU_PCLK_SCTM2    = (CKCU_APBPCSR1 | 28),
  #endif
  #if defined(LIBCFG_SCTM3)
  CKCU_PCLK_SCTM3    = (CKCU_APBPCSR1 | 30),
  #endif
} CKCU_PeripPrescaler_TypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Constants CKCU exported constants
  * @{
  */

/* Definitions of clock ready flag                                                                          */
#define CKCU_FLAG_PLLRDY        (1UL << 1)
#define CKCU_FLAG_HSERDY        (1UL << 2)
#define CKCU_FLAG_HSIRDY        (1UL << 3)
#if defined(LIBCFG_LSE)
#define CKCU_FLAG_LSERDY        (1UL << 4)
#endif
#define CKCU_FLAG_LSIRDY        (1UL << 5)

#define IS_CKCU_FLAG(FLAG)      (((FLAG & 0xFFFFFFC1) == 0) && (FLAG != 0))

/* Definitions of clock interrupt & flag                                                                    */
#define CKCU_INT_CKS            (1UL)
#define CKCU_INT_PLLRDY         (1UL << 2)
#define CKCU_INT_HSERDY         (1UL << 3)
#define CKCU_INT_HSIRDY         (1UL << 4)
#if defined(LIBCFG_LSE)
#define CKCU_INT_LSERDY         (1UL << 5)
#endif
#define CKCU_INT_LSIRDY         (1UL << 6)

#define IS_CKCU_INT_FLAG(FLAG)  (((FLAG & 0xFFFFFF82) == 0) && (FLAG != 0))

#define CKCU_INT_CKSIE          (1UL << 16)
#define CKCU_INT_PLLRDYIE       (1UL << 18)
#define CKCU_INT_HSERDYIE       (1UL << 19)
#define CKCU_INT_HSIRDYIE       (1UL << 20)
#if defined(LIBCFG_LSE)
#define CKCU_INT_LSERDYIE       (1UL << 21)
#endif
#define CKCU_INT_LSIRDYIE       (1UL << 22)

#define IS_CKCU_INT(IT)         (((IT & 0xFF82FFFF) == 0) && (IT != 0))

/* Definitions of PLL frequency                                                                             */
#define CKCU_PLL_4M_48M         ((12UL << 23) | (0UL << 21))
#define CKCU_PLL_4M_40M         ((10UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_48M         (( 6UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_40M         (( 5UL << 23) | (0UL << 21))
#define CKCU_PLL_8M_32M         (( 4UL << 23) | (0UL << 21))
#define CKCU_PLL_12M_48M        (( 4UL << 23) | (0UL << 21))
#define CKCU_PLL_16M_48M        (( 3UL << 23) | (0UL << 21))


/* Definitions of MCU debug control                                                                         */
#define CKCU_DBG_SLEEP          (1UL)
#define CKCU_DBG_DEEPSLEEP1     (1UL << 1)
#define CKCU_DBG_POWERDOWN      (1UL << 2)
#define CKCU_DBG_WDT_HALT       (1UL << 3)
#if defined(LIBCFG_MCTM0)
#define CKCU_DBG_MCTM0_HALT     (1UL << 4)
#endif
#define CKCU_DBG_GPTM0_HALT     (1UL << 6)
#if defined(LIBCFG_GPTM1)
#define CKCU_DBG_GPTM1_HALT     (1UL << 7)
#endif
#define CKCU_DBG_USART0_HALT    (1UL << 8)
#if defined(LIBCFG_USART1)
#define CKCU_DBG_USART1_HALT    (1UL << 9)
#endif
#define CKCU_DBG_SPI0_HALT      (1UL << 10)
#if defined(LIBCFG_SPI1)
#define CKCU_DBG_SPI1_HALT      (1UL << 11)
#endif
#define CKCU_DBG_I2C0_HALT      (1UL << 12)
#if defined(LIBCFG_I2C1)
#define CKCU_DBG_I2C1_HALT      (1UL << 13)
#endif
#define CKCU_DBG_DEEPSLEEP2     (1UL << 14)
#if defined(LIBCFG_SCI0)
#define CKCU_DBG_SCI0_HALT      (1UL << 15)
#endif
#define CKCU_DBG_BFTM0_HALT     (1UL << 16)
#if defined(LIBCFG_BFTM1)
#define CKCU_DBG_BFTM1_HALT     (1UL << 17)
#endif
#define CKCU_DBG_UART0_HALT     (1UL << 18)
#if defined(LIBCFG_UART1)
#define CKCU_DBG_UART1_HALT     (1UL << 19)
#endif
#if defined(LIBCFG_SCI1)
#define CKCU_DBG_SCI1_HALT      (1UL << 21)
#endif
#define CKCU_DBG_SCTM0_HALT     (1UL << 22)
#define CKCU_DBG_SCTM1_HALT     (1UL << 23)
#if defined(LIBCFG_SCTM2)
#define CKCU_DBG_SCTM2_HALT     (1UL << 24)
#endif
#if defined(LIBCFG_SCTM3)
#define CKCU_DBG_SCTM3_HALT     (1UL << 25)
#endif

#define IS_CKCU_DBG(MODE)       (((MODE & ~(0x03FFFFDF)) == 0) && (MODE != 0))

/* Definitions of AHB clock control                                                                         */
#define CKCU_AHBEN_SLEEP_FMC    (1UL)
#define CKCU_AHBEN_SLEEP_SRAM   (1UL << 2)
#define CKCU_AHBEN_SLEEP_BM     (1UL << 5)
#define CKCU_AHBEN_SLEEP_APB    (1UL << 6)

#define IS_CKCU_SLEEP_AHB(PERIPH)  (((PERIPH & 0xFFFFFF9A) == 0) && (PERIPH != 0))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------------------------------------*/
/** @defgroup CKCU_Exported_Functions CKCU exported functions
  * @{
  */
void CKCU_DeInit(void);

void CKCU_HSICmd(EventStatus Cmd);
void CKCU_HSECmd(EventStatus Cmd);
void CKCU_PLLCmd(EventStatus Cmd);
bool CKCU_IS_HSI_USED(CKCU_HSIST_TypeDef Target);
bool CKCU_IS_HSE_USED(CKCU_HSEST_TypeDef Target);
bool CKCU_IS_PLL_USED(CKCU_PLLST_TypeDef Target);
FlagStatus CKCU_GetClockReadyStatus(u32 CKCU_FLAG);
ErrStatus CKCU_WaitHSEReady(void);

ErrStatus CKCU_SysClockConfig(CKCU_SW_TypeDef CLKSRC);
u32 CKCU_GetSysClockSource(void);

void CKCU_PLLInit(CKCU_PLLInitTypeDef *PLLInit);
void CKCU_PeripClockConfig(CKCU_PeripClockConfig_TypeDef Clock, ControlStatus Cmd);
void CKCU_SleepClockConfig(u32 CKCU_CLK, ControlStatus Cmd);

void CKCU_SetHCLKPrescaler(CKCU_SYSCLKDIV_TypeDef HCLKPRE);
void CKCU_SetCKREFPrescaler(CKCU_CKREFPRE_TypeDef CKREFPRE);
void CKCU_SetADCPrescaler(CKCU_ADCPRE_TypeDef ADCPRE);
void CKCU_SetPeripPrescaler(CKCU_PeripPrescaler_TypeDef Perip, CKCU_APBCLKPRE_TypeDef PCLKPRE);

void CKCU_GetClocksFrequency(CKCU_ClocksTypeDef* CKCU_Clk);
u32 CKCU_GetPLLFrequency(void);
u32 CKCU_GetPeripFrequency(CKCU_PeripPrescaler_TypeDef Perip);

void CKCU_CKMCmd(ControlStatus Cmd);
void CKCU_PSRCWKUPCmd(ControlStatus Cmd);
void CKCU_BKISOCmd(EventStatus Cmd);
void CKCU_CKOUTConfig(CKCU_CKOUTInitTypeDef *CKOUTInit);
void CKCU_MCUDBGConfig(u32 CKCU_DBGx, ControlStatus Cmd);

void CKCU_IntConfig(u32 CKCU_INT, ControlStatus Cmd);
FlagStatus CKCU_GetIntStatus(u8 CKCU_INT);
void CKCU_ClearIntFlag(u8 CKCU_INT);

#if defined(LIBCFG_LSE) || defined(LIBCFG_USBD)
void CKCU_HSIAutoTrimClkConfig(CKCU_ATC_TypeDef CLKSRC);
void CKCU_HSIAutoTrimCmd(EventStatus Cmd);
bool CKCU_HSIAutoTrimIsReady(void);
#endif
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif
