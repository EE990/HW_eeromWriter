/*********************************************************************************************************//**
 * @file    ht32f520xx_pwrcu.c
 * @version $Rev:: 207          $
 * @date    $Date:: 2016-01-04 #$
 * @brief   This file provides all the Power Control Unit firmware functions.
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

/* Includes ------------------------------------------------------------------------------------------------*/
#include "ht32f520xx_pwrcu.h"

/** @addtogroup HT32F520xx_Peripheral_Driver HT32F520xx Peripheral Driver
  * @{
  */

/** @defgroup PWRCU PWRCU
  * @brief PWRCU driver modules
  * @{
  */


/* Private constants ---------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Private_Define PWRCU private definitions
  * @{
  */
#define Set_RTCEN         SetBit_BB((u32)&HT_CKCU->APBCCR1, 6);
#define Reset_RTCEN       ResetBit_BB((u32)&HT_CKCU->APBCCR1, 6);
#define Get_RTCEN         GetBit_BB((u32)&HT_CKCU->APBCCR1, 6)

#define Set_LDOMODE       SetBit_BB((u32)&HT_PWRCU->CR, 2)
#define Reset_LDOMODE     ResetBit_BB((u32)&HT_PWRCU->CR, 2)

#define Set_LDOOFF        SetBit_BB((u32)&HT_PWRCU->CR, 3)
#define Reset_LDOOFF      ResetBit_BB((u32)&HT_PWRCU->CR, 3)

#define Set_DMOSON        SetBit_BB((u32)&HT_PWRCU->CR, 7)
#define Reset_DMOSON      ResetBit_BB((u32)&HT_PWRCU->CR, 7)

#define Set_WUPEN         SetBit_BB((u32)&HT_PWRCU->CR, 8)
#define Reset_WUPEN       ResetBit_BB((u32)&HT_PWRCU->CR, 8)

#define Set_WUPIEN        SetBit_BB((u32)&HT_PWRCU->CR, 9)
#define Reset_WUPIEN      ResetBit_BB((u32)&HT_PWRCU->CR, 9)

#define Set_V15RDYSC      SetBit_BB((u32)&HT_PWRCU->CR, 12)
#define Reset_V15RDYSC    ResetBit_BB((u32)&HT_PWRCU->CR, 12)

#define Set_DMOSSTS       SetBit_BB((u32)&HT_PWRCU->CR, 15)
#define Reset_DMOSSTS     ResetBit_BB((u32)&HT_PWRCU->CR, 15)
#define Get_DMOSSTS       GetBit_BB((u32)&HT_PWRCU->CR, 15)

#define Set_BODEN         SetBit_BB((u32)&HT_PWRCU->LVDCSR, 0)
#define Reset_BODEN       ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 0)

#define Set_BODRIS        SetBit_BB((u32)&HT_PWRCU->LVDCSR, 1)
#define Reset_BODRIS      ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 1)

#define Set_BODF          SetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)
#define Reset_BODF        ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)
#define Get_BODF          GetBit_BB((u32)&HT_PWRCU->LVDCSR, 3)

#define Set_LVDEN         SetBit_BB((u32)&HT_PWRCU->LVDCSR, 16)
#define Reset_LVDEN       ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 16)

#define Set_LVDF          SetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)
#define Reset_LVDF        ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)
#define Get_LVDF          GetBit_BB((u32)&HT_PWRCU->LVDCSR, 19)

#define Set_LVDIWEN       SetBit_BB((u32)&HT_PWRCU->LVDCSR, 20)
#define Reset_LVDIWEN     ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 20)

#define Set_LVDEWEN       SetBit_BB((u32)&HT_PWRCU->LVDCSR, 21)
#define Reset_LVDEWEN     ResetBit_BB((u32)&HT_PWRCU->LVDCSR, 21)

#define Set_SLEEPDEEP     SetBit_BB((u32)&SCB->SCR, 2)     /*!< Cortex SLEEPDEEP bit */
#define Reset_SLEEPDEEP   ResetBit_BB((u32)&SCB->SCR, 2)

#define LVDS_MASK         0xFFB9FFFF
#define PWRRST_SET        0x1
#define PWRTEST_READY     0x27
#define TIME_OUT          24000000
/**
  * @}
  */

/* Global functions ----------------------------------------------------------------------------------------*/
/** @defgroup PWRCU_Exported_Functions PWRCU exported functions
  * @{
  */
/*********************************************************************************************************//**
 * @brief Deinitial backup domain which contains PWRCU and RTC units.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeInit(void)
{
  HT_PWRCU->CR = PWRRST_SET;
  #if USE_HT32F52342_52
  while (HT_PWRCU->CR);
  #else
  while (HT_PWRCU->CR != 0x1000);
  #endif
  while (HT_PWRCU->SR);    /* Waits until the PWRPORF be cleared by read                                    */
}

/*********************************************************************************************************//**
 * @brief Waits, until the PWRCU can be accessed.
 * @return PWRCU_TIMEOUT or PWRCU_OK
 ************************************************************************************************************/
PWRCU_Status PWRCU_CheckReadyAccessed(void)
{
  u32 wTimeOutCnt = TIME_OUT;

  /* Set the V33_ISO bit                                                                                    */
  HT_CKCU->LPCR = 0x1;

  while (--wTimeOutCnt)
  {
    if (HT_PWRCU->TEST == PWRTEST_READY)
    {
      return PWRCU_OK;
    }
  }
  return PWRCU_TIMEOUT;
}

/*********************************************************************************************************//**
 * @brief Return the flags of PWRCU.
 * @return This function will return one of following:
 *   - 0x0000                                   : There is no flag is set.
 *   - 0x0001 (PWRCU_FLAG_PWRPOR)               : VDD power domain power-on reset flag has been set.
 *   - 0x0002 (PWRCU_FLAG_PD)                   : Power-Down flag has been set.
 *   - 0x0100 (PWRCU_FLAG_WUP)                  : External WAKEUP pin flag has been set.
 *   - 0x0102 (PWRCU_FLAG_PD | PWRCU_FLAG_WUP)  : Both PDF and WUPF flags have been set.
 ************************************************************************************************************/
u16 PWRCU_GetFlagStatus(void)
{
  return HT_PWRCU->SR;
}

#if defined(LIBCFG_BAKREG)
/*********************************************************************************************************//**
 * @brief Return the value of specified backup register.
 * @param BAKREGx: Number of backup register. Where x can be 0 ~ 9.
 * @return Between 0x0 ~ 0xFFFFFFFF.
 ************************************************************************************************************/
u32 PWRCU_ReadBackupRegister(PWRCU_BAKREG_Enum BAKREGx)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BAKREG(BAKREGx));

  return HT_PWRCU->BAKREG[BAKREGx];
}

/*********************************************************************************************************//**
 * @brief Write the DATA to specified backup register.
 * @param BAKREGx : Number of backup registers. Where x can be 0 ~ 9.
 * @param DATA : Must between 0x0 ~ 0xFFFFFFFF.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WriteBackupRegister(PWRCU_BAKREG_Enum BAKREGx, u32 DATA)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BAKREG(BAKREGx));

  HT_PWRCU->BAKREG[BAKREGx] = DATA;
}
#endif

/*********************************************************************************************************//**
 * @brief Enter SLEEP mode.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *   @arg PWRCU_SLEEP_ENTRY_WFE: Enters SLEEP mode via WFE instruction.
 *   @arg PWRCU_SLEEP_ENTRY_WFI: Enters SLEEP mode via WFI instruction.
 * @retval None
 ************************************************************************************************************/
void PWRCU_Sleep(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  /* Clear SLEEPDEEP bit of Cortex System Control Register                                                  */
  Reset_SLEEPDEEP;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }
}

/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 1.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *   @arg PWRCU_SLEEP_ENTRY_WFE: Enters SLEEP mode via WFE instruction.
 *   @arg PWRCU_SLEEP_ENTRY_WFI: Enters SLEEP mode via WFI instruction.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep1(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  Reset_DMOSON;
  Reset_LDOOFF;

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  Set_SLEEPDEEP;

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  Reset_SLEEPDEEP;
}

/*********************************************************************************************************//**
 * @brief Enter DEEP-SLEEP Mode 2.
 * @param SleepEntry : Enters sleep mode instruction that is used to WFI or WFE.
 *   This parameter can be one of the following values:
 *   @arg PWRCU_SLEEP_ENTRY_WFE: Enters SLEEP mode via WFE instruction.
 *   @arg PWRCU_SLEEP_ENTRY_WFI: Enters SLEEP mode via WFI instruction.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DeepSleep2(PWRCU_SLEEP_ENTRY_Enum SleepEntry)
{
  u32 uRTCStatus = 0;
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_SLEEP_ENTRY(SleepEntry));

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  if (Get_DMOSSTS == 0)
  {
    Reset_DMOSON;
    Set_DMOSON;
  }
  Reset_LDOOFF;

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  Set_SLEEPDEEP;

  if (SleepEntry == PWRCU_SLEEP_ENTRY_WFE)
  {
    /* Wait for event                                                                                       */
    __SEV();
    __WFE();
    __WFE();
  }
  else
  {
    /* Wait for interrupt                                                                                   */
    __WFI();
  }

  Reset_SLEEPDEEP;
}

/*********************************************************************************************************//**
 * @brief Enter POWER-DOWN Mode.
 * @retval None
 ************************************************************************************************************/
void PWRCU_PowerDown(void)
{
  u32 uRTCStatus = 0;

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  Reset_DMOSON;
  Set_LDOOFF;

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }

  /* Sets SLEEPDEEP bit of Cortex System Control Register                                                   */
  Set_SLEEPDEEP;

  /* Enters power-down mode                                                                                 */
  __WFI();
}

/*********************************************************************************************************//**
 * @brief Configure LVD voltage level.
 * @param Level: Low voltage detect level.
 *   This parameter can be one of following:
 *   @arg PWRCU_LVDS_2V25: 2.25 V
 *   @arg PWRCU_LVDS_2V4 : 2.40 V
 *   @arg PWRCU_LVDS_2V55: 2.55 V
 *   @arg PWRCU_LVDS_2V7 : 2.70 V
 *   @arg PWRCU_LVDS_2V85: 2.85 V
 *   @arg PWRCU_LVDS_3V  : 3.00 V
 *   @arg PWRCU_LVDS_3V15: 3.15 V
 *   @arg PWRCU_LVDS_3V3 : 3.30 V
 * @retval None
 ************************************************************************************************************/
void PWRCU_SetLVDS(PWRCU_LVDS_Enum Level)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LVDS(Level));

  HT_PWRCU->LVDCSR = (HT_PWRCU->LVDCSR & LVDS_MASK) | Level;
}

/*********************************************************************************************************//**
 * @brief Enable or Disable LVD function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDEN;
  }
  else
  {
    Reset_LVDEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable BOD reset function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_BODEN;
  }
  else
  {
    Reset_BODEN;
  }
}

/*********************************************************************************************************//**
 * @brief Select when the BOD occurs, the action for the cause Reset or Interrupt.
 * @param Selection: BOD reset or interrupt selection.
 *   This parameter can be one of following:
 *   @arg PWRCU_BODRIS_RESET: Reset the whole chip
 *   @arg PWRCU_BODRIS_INT: Assert interrupt
 * @retval None
 ************************************************************************************************************/
void PWRCU_BODRISConfig(PWRCU_BODRIS_Enum Selection)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_BODRIS(Selection));

  if (Selection != PWRCU_BODRIS_RESET)
  {
    Set_BODRIS;
  }
  else
  {
    Reset_BODRIS;
  }
}

/*********************************************************************************************************//**
 * @brief Return the flag status of LVD.
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetLVDFlagStatus(void)
{
  return (FlagStatus)Get_LVDF;
}

/*********************************************************************************************************//**
 * @brief Return the flag status of BOD.
 * @return SET or RESET
 ************************************************************************************************************/
FlagStatus PWRCU_GetBODFlagStatus(void)
{
  return (FlagStatus)Get_BODF;
}

/*********************************************************************************************************//**
 * @brief Return the DMOS status.
 * @return This function will return one of following:
 *    - PWRCU_DMOS_STS_ON              : DMOS on
 *    - PWRCU_DMOS_STS_OFF             : DMOS off
 *    - PWRCU_DMOS_STS_OFF_BY_BODRESET : DMOS off caused by brow out reset
 ************************************************************************************************************/
PWRCU_DMOSStatus PWRCU_GetDMOSStatus(void)
{
  u32 wDmosStatus = HT_PWRCU->CR & 0x8080;

  if (wDmosStatus == 0x0)
  {
    return PWRCU_DMOS_STS_OFF;
  }
  else if (wDmosStatus == 0x8080)
  {
    return PWRCU_DMOS_STS_ON;
  }
  else
  {
    return PWRCU_DMOS_STS_OFF_BY_BODRESET;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable DMOS function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_DMOSCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (Get_DMOSSTS == 0)
  {
    Reset_DMOSON;
  }

  if (NewState != DISABLE)
  {
    Set_DMOSON;
  }
  else
  {
    Reset_DMOSON;
  }
}

/*********************************************************************************************************//**
 * @brief Configure LDO operation mode.
 * @param Sel: Specify LDO mode.
 *    @arg PWRCU_LDO_NORMAL     : The LDO is operated in normal current mode.
 *    @arg PWRCU_LDO_LOWCURRENT : The LDO is operated in low current mode.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LDOConfig(PWRCU_LDOMODE_Enum Sel)
{
  u32 uRTCStatus = 0;

  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_LDOMODE(Sel));

  uRTCStatus = Get_RTCEN;
  Set_RTCEN;

  if (Sel == PWRCU_LDO_NORMAL)
  {
    Reset_LDOMODE;
  }
  else
  {
    Set_LDOMODE;
  }

  if (uRTCStatus == 0)
  {
    Reset_RTCEN;
  }
}

/*********************************************************************************************************//**
 * @brief Configure VDD15 power good source.
 * @param Sel: Specify VDD15 power good source.
 *    @arg PWRCU_V15RDYSC_V33ISO : Vdd15 power good source come from V33_ISO bit in CKCU unit
 *    @arg PWRCU_V15RDYSC_V15POR : Vdd15 power good source come from Vdd15 power-on reset
 * @retval None
 ************************************************************************************************************/
void PWRCU_V15RDYSourceConfig(PWRCU_V15RDYSC_Enum Sel)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_V15RDYSC(Sel));

  if (Sel == PWRCU_V15RDYSC_V33ISO)
  {
    Reset_V15RDYSC;
  }
  else
  {
    Set_V15RDYSC;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable LVD interrupt wakeup function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDIntWakeupConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDIWEN;
  }
  else
  {
    Reset_LVDIWEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable LVD event wakeup function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_LVDEventWakeupConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_LVDEWEN;
  }
  else
  {
    Reset_LVDEWEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable external WAKEUP pin function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinCmd(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_WUPEN;
  }
  else
  {
    Reset_WUPEN;
  }
}

/*********************************************************************************************************//**
 * @brief Enable or Disable external WAKEUP pin interrupt function.
 * @param NewState: ENABLE or DISABLE.
 * @retval None
 ************************************************************************************************************/
void PWRCU_WakeupPinIntConfig(ControlStatus NewState)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_CONTROL_STATUS(NewState));

  if (NewState != DISABLE)
  {
    Set_WUPIEN;
  }
  else
  {
    Reset_WUPIEN;
  }
}

#if defined(USE_HT32F52342_52)
/*********************************************************************************************************//**
 * @brief Configure HSI ready counter bit length.
 * @param BitLength: HSI ready counter bit length.
 *   This parameter can be one of following:
 *   @arg PWRCU_HSIRCBL_4: 4 bits
 *   @arg PWRCU_HSIRCBL_5: 5 bits
 *   @arg PWRCU_HSIRCBL_6: 6 bits
 *   @arg PWRCU_HSIRCBL_7: 7 bits (Default)
 * @retval None
 ************************************************************************************************************/
void PWRCU_HSIReadyCounterBitLengthConfig(PWRCU_HSIRCBL_Enum BitLength)
{
  /* Check the parameters                                                                                   */
  Assert_Param(IS_PWRCU_HSIRCBL(BitLength));

  HT_PWRCU->HSIRCR = BitLength;
}
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
