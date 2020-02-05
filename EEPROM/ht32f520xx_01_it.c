/*********************************************************************************************************//**
 * @file    I2C/EEPROM/ht32f520xx_01_it.c
 * @version $Rev:: 219          $
 * @date    $Date:: 2016-02-16 #$
 * @brief   This file provides all interrupt service routine.
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
#include "ht32.h"
#include "common/i2c_eeprom.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup I2C_Examples I2C
  * @{
  */

/** @addtogroup EEPROM
  * @{
  */


/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
 * @brief   This function handles NMI exception.
 * @retval  None
 ************************************************************************************************************/
void NMI_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles Hard Fault exception.
 * @retval  None
 ************************************************************************************************************/
void HardFault_Handler(void)
{
  while (1);
}

/*********************************************************************************************************//**
 * @brief   This function handles SVCall exception.
 * @retval  None
 ************************************************************************************************************/
void SVC_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles PendSVC exception.
 * @retval  None
 ************************************************************************************************************/
void PendSV_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles SysTick Handler.
 * @retval  None
 ************************************************************************************************************/
void SysTick_Handler(void)
{
}

/*********************************************************************************************************//**
 * @brief   This function handles UART interrupt.
 * @retval  None
 ************************************************************************************************************/
extern u8 serial_eerom_wBuffer[];
extern u8 serialHeadF;
extern u8 serialHeadCnt;
extern u32 serial_eerom_wBuffer_Cnt;
extern u32 serial_eerom_wPage;
extern u32 serial_eerom_rPageStart;
extern u32 serial_eerom_rPageEnd;
void UART1_IRQHandler(void)
{
	u8 dataTemp;
	const u8 head[8]="+++Rom:";
	static u8 pageTableByteCnt;
	static u8 serial_eerom_RWF;
	
	 while(USART_GetFlagStatus(HT_UART1, USART_FLAG_RXDR) == SET)
	 {
		 /*if((HT_UART1->SR & USART_FLAG_TXC) != 0)
				HT_UART1->DR = USART_ReceiveData(HT_UART1);*/
		 
		 dataTemp=USART_ReceiveData(HT_UART1);
		 
		 //restart BFTM
		 BFTM_ClearFlag(HT_BFTM0);
		 BFTM_SetCounter(HT_BFTM0, 0);
		 BFTM_EnaCmd(HT_BFTM0, ENABLE);
		 
		 if(serialHeadF==0)//******cmpare head
		 {
			 serial_eerom_wBuffer_Cnt=0;
			 
			 if(dataTemp==head[serialHeadCnt]) serialHeadCnt++;
					else serialHeadCnt=0;
			 
			 if(serialHeadCnt>=7)
			 {
				 serialHeadCnt=0;
				 pageTableByteCnt=0;
				 serial_eerom_wPage=0;
				 serial_eerom_rPageStart=0;
				 serial_eerom_rPageEnd=0;
				 serialHeadF=1;
			 }
		 }
		 else if(serialHeadF==1)//******wirte(1) or read(0)
		 {
			 serial_eerom_RWF=dataTemp;
			 serialHeadF=2;
		 }
		 else if(serialHeadF==2)//******get parameter(page)
		 {
			 if(serial_eerom_RWF)//page for write
			 {
				 if(pageTableByteCnt<=3)//the page for write to eeprom
				 {
					 serial_eerom_wPage |= (dataTemp << ((3-pageTableByteCnt)*8));
					 pageTableByteCnt++;
					 
					 if(pageTableByteCnt==4)
					 {
						 pageTableByteCnt=0;
						 serialHeadF=3;
					 }
				 }
				 else
				 {
					 pageTableByteCnt=0;
					 serialHeadF=0;
				 }
			 }
			 else//page for read
			 {
				 if(pageTableByteCnt<=3)//the page for read from eeprom(start page)
				 {
					 serial_eerom_rPageStart |= (dataTemp << ((3-pageTableByteCnt)*8));
					 pageTableByteCnt++;
				 }
				 else if(pageTableByteCnt<=7)//the page for read from eeprom(end page)
				 {
					 serial_eerom_rPageEnd |= (dataTemp << ((7-pageTableByteCnt)*8));
					 pageTableByteCnt++;
					 
					 if(pageTableByteCnt==8)//end this command
					 {
						 serial_eerom_rPageStart=serial_eerom_rPageStart+1;//dont be zero
						 serial_eerom_rPageEnd=serial_eerom_rPageEnd+1;//dont be zero
						 
						 pageTableByteCnt=0;
						 serialHeadF=0;
					 }
				 }
			 }
		 }
		 else//******read for write eeprom
		 { 
			 serial_eerom_wBuffer[serial_eerom_wBuffer_Cnt]=dataTemp;//read in buffer
				
			 serial_eerom_wBuffer_Cnt++;
			 if(serial_eerom_wBuffer_Cnt>=I2C_EEPROM_PAGE_SIZE)
			 {
				 //printf("\n [To Long , Outside The Buffer]\n");
				 serial_eerom_wBuffer_Cnt=0;
			 }
		 }
	 }
	
	 __DSB();
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
