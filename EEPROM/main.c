/*********************************************************************************************************//**
 * @file    I2C/EEPROM/main.c
 * @version $Rev:: 219          $
 * @date    $Date:: 2016-02-16 #$
 * @brief   Main program.
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
#include <stdlib.h>
#include <string.h>
#include "ht32.h"
#include "ht32_board.h"

/** @addtogroup HT32_Series_Peripheral_Examples HT32 Peripheral Examples
  * @{
  */

/** @addtogroup I2C_Examples I2C
  * @{
  */

/** @addtogroup EEPROM
  * @{
  */

u8 buffw[I2C_EEPROM_PAGE_SIZE+1];
u8 buffr[I2C_EEPROM_PAGE_SIZE+1];
u8 serial_eerom_wBuffer[I2C_EEPROM_PAGE_SIZE+1];
u8 serialHeadF;
u8 serialHeadCnt;
u32 serial_eerom_wBuffer_Cnt;
u32 serial_eerom_wPage;
u32 serial_eerom_rPageStart;
u32 serial_eerom_rPageEnd;

/* Private constants ---------------------------------------------------------------------------------------*/
/*#define WRITE_BUF_ADDR    (0x20000600)
#define READ_BUF_ADDR     (0x20000700)*/
#define WRITE_BUF_ADDR    (buffw)
#define READ_BUF_ADDR     (buffr)
#define EEPROM_PAGE_MAX   (I2C_EEPROM_CAPACITY / I2C_EEPROM_PAGE_SIZE)

void CKCU_Configuration(void);
void BFTM_Configuration(void);
void print_EEROM_data(u32 startPage,u32 endPage);

/* Global functions ----------------------------------------------------------------------------------------*/
/*********************************************************************************************************//**
  * @brief  Main program.
  * @retval None
  ***********************************************************************************************************/
int main(void)
{
	u32 temp_u32_1;
  u32 i, j;//, *pBuf;

  RETARGET_Configuration();           /* Retarget Related configuration                                     */
	USART_RXTLConfig(COM1_PORT, USART_RXTL_01);
  USART_IntConfig(COM1_PORT, USART_INT_RXDR, ENABLE);
  NVIC_EnableIRQ(COM1_IRQn);

  /* print message                                                                                          */
  //printf("\r\n*** HT32 I2C Example Code ***");
  //printf("\r\n24LC02 EEPROM verifying : ");

	/* init CKCU                                                                                            */
	CKCU_Configuration();
	/* init BFTM                                                                                            */
	BFTM_Configuration();
  /* init EEPROM                                                                                            */
  I2C_EEPROM_Init();
	I2C_Cmd(EEPROM_I2C, ENABLE);

	//read full chip data
	printf("[Start Read]:  full data,  I2C_EEPROM_CAPACITY=%d  I2C_EEPROM_PAGE_SIZE=%d  EEPROM_PAGE_MAX=%d\r\n",I2C_EEPROM_CAPACITY,I2C_EEPROM_PAGE_SIZE,EEPROM_PAGE_MAX);
	print_EEROM_data(0,EEPROM_PAGE_MAX-1);
  printf("\r\n[Read success]\r\n");
	
	serial_eerom_wBuffer_Cnt=0;
  while (1)
	{
		//Get data to write chip
		while(BFTM_GetFlagStatus(HT_BFTM0)==RESET);
		NVIC_DisableIRQ(COM1_IRQn);
		serialHeadF=0;
		serialHeadCnt=0;
		if(serial_eerom_wBuffer_Cnt!=0)//write
		{
			temp_u32_1=serial_eerom_wBuffer_Cnt;
			serial_eerom_wBuffer_Cnt=0;
			
			#if !I2C_EEPROM_READ_ONLY
			if(serial_eerom_wPage<EEPROM_PAGE_MAX)
			{
				I2C_EEPROM_BufferWrite((u8 *)serialBuffer, I2C_EEPROM_PAGE_SIZE * serial_eerom_wPage, temp_u32_1);
				I2C_EEPROM_BufferRead((u8 *)READ_BUF_ADDR, I2C_EEPROM_PAGE_SIZE * serial_eerom_wPage, temp_u32_1);
				if (memcmp((u8 *)serialBuffer, (u8 *)READ_BUF_ADDR, I2C_EEPROM_PAGE_SIZE) != 0)
				{
					printf("[Write Failed]:page%d\r\n",serial_eerom_wPage);
				}
				else
				{
			printf("[Write success]:page%d\r\n",serial_eerom_wPage);
				}
				//printf("\r\t\t\t\t%d%%", (int)((j + 1) * 100)/EEPROM_PAGE_CNT);
			}
			else
			{
				printf("[Failed]:page out the range,MAX Page=%d\r\n",EEPROM_PAGE_MAX-1);
			}
			#else
			if(serial_eerom_wPage<EEPROM_PAGE_MAX)
			{
				printf("[READ ONLY]:(just return your data,not eerom)write page %d :\r\n",(int)serial_eerom_wPage);
				for(i=0;i<temp_u32_1;i++)
				{
					printf( "%2x,",serial_eerom_wBuffer[i]);
				}
			}
			else
			{
				printf("[Failed]:page out the range,MAX Page=%d\r\n",EEPROM_PAGE_MAX-1);
			}
			#endif
		}
		if(serial_eerom_rPageStart!=0 && serial_eerom_rPageEnd!=0)//read
		{
			//if(serial_eerom_rPageStart<EEPROM_PAGE_MAX && serial_eerom_rPageEnd<EEPROM_PAGE_MAX)
			{
				serial_eerom_rPageStart--;//restitute
				serial_eerom_rPageEnd--;//restitute
			
				printf("[Start Read]:  page%ld -> page%ld,  I2C_EEPROM_CAPACITY=%d  I2C_EEPROM_PAGE_SIZE=%d  EEPROM_PAGE_MAX=%d\r\n",serial_eerom_rPageStart,serial_eerom_rPageEnd,I2C_EEPROM_CAPACITY,I2C_EEPROM_PAGE_SIZE,EEPROM_PAGE_MAX);
				
				if(serial_eerom_rPageStart > serial_eerom_rPageEnd)//decrease progressively
				{
					for(i=serial_eerom_rPageStart;i!=serial_eerom_rPageEnd;i--)
					{
						print_EEROM_data(i,i);
						//printf("Page %ld\r\n",i);
					}
					print_EEROM_data(serial_eerom_rPageEnd,serial_eerom_rPageEnd);
					//printf("Page %ld\r\n",serial_eerom_rPageEnd);
				}
				else//progressively increase
				{
					print_EEROM_data(serial_eerom_rPageStart,serial_eerom_rPageEnd);
				}
				printf("\r\n[Read success]\r\n");
			}
			/*else 
			{
				printf("[Read Failed]:page outside the range\r\n");
			}*/
				
			serial_eerom_rPageStart=serial_eerom_rPageEnd=0;
		}			
		
		NVIC_EnableIRQ(COM1_IRQn);
		
		//stop BFTM 
		BFTM_ClearFlag(HT_BFTM0);
		BFTM_EnaCmd(HT_BFTM0, DISABLE);
	}
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

  while (1)
  {
  }
}
#endif

/*********************************************************************************************************//**
  * @brief  Configure the system clocks.
  * @retval None
  ***********************************************************************************************************/
void CKCU_Configuration(void)
{
/*
//<e0> Enable Peripheral Clock
//  <h> Communication
//    <q5> EBI
//    <q11> I2C0   <q12> I2C1
//    <q23> I2S
//    <q21> SCI0 <q22> SCI1
//    <q13> SPI0   <q14> SPI1
//    <q17> UART0  <q18> UART1
//    <q15> USART0 <q16> USART1
//    <q3>  USB
//  </h>
//  <h> IO
//    <q7> GPIO Port A <q8>  GPIO Port B <q9>  GPIO Port C <q10>  GPIO Port D
//    <q19> AFIO
//    <q20> EXTI
//  </h>
//  <h> System
//    <q32> ADC
//    <q4>  CKREF
//    <q6>  CRC
//    <q31> CMP
//    <q2>  PDMA
//    <q26> PWRCU
//  </h>
//  <h> Timer
//    <q29> BFTM0 <q30> BFTM1
//    <q33> SCTM0 <q34> SCTM1 <q35> SCTM2 <q36> SCTM3
//    <q27> GPTM0 <q28> GPTM1
//    <q24> MCTM0
//    <q26> RTC   <q25> WDT
//  </h>
//</e>
*/
  CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
  CKCUClock.Bit.PDMA       = 0;
  CKCUClock.Bit.USBD       = 0;
  CKCUClock.Bit.CKREF      = 0;
  CKCUClock.Bit.EBI        = 0;
  CKCUClock.Bit.CRC        = 0;
  CKCUClock.Bit.PA         = 0;
  CKCUClock.Bit.PB         = 0;
  CKCUClock.Bit.PC         = 0;
  CKCUClock.Bit.PD         = 0;
  CKCUClock.Bit.I2C0       = 1;
  CKCUClock.Bit.I2C1       = 1;
  CKCUClock.Bit.SPI0       = 0;
  CKCUClock.Bit.SPI1       = 0;
  CKCUClock.Bit.USART0     = 1;
  CKCUClock.Bit.USART1     = 0;
  CKCUClock.Bit.UART0      = 1;
  CKCUClock.Bit.UART1      = 1;
  CKCUClock.Bit.AFIO       = 1;
  CKCUClock.Bit.EXTI       = 0;
  CKCUClock.Bit.SCI0       = 0;
  CKCUClock.Bit.SCI1       = 0;
  CKCUClock.Bit.I2S        = 0;
  CKCUClock.Bit.MCTM0      = 0;
  CKCUClock.Bit.WDT        = 0;
  CKCUClock.Bit.BKP        = 0;
  CKCUClock.Bit.GPTM0      = 0;
  CKCUClock.Bit.GPTM1      = 0;
  CKCUClock.Bit.BFTM0      = 1;
  CKCUClock.Bit.BFTM1      = 0;
  CKCUClock.Bit.CMP        = 0;
  CKCUClock.Bit.ADC        = 0;
  CKCUClock.Bit.SCTM0      = 0;
  CKCUClock.Bit.SCTM1      = 0;
  CKCUClock.Bit.SCTM2      = 0;
  CKCUClock.Bit.SCTM3      = 0;
  CKCU_PeripClockConfig(CKCUClock, ENABLE);
}

/**
  * @}
  */
void BFTM_Configuration(void)
{
	//---------BFTM0---------------------------------------//
	BFTM_SetCompare(HT_BFTM0,(SystemCoreClock/100));//10ms
	BFTM_SetCounter(HT_BFTM0, 0);
	BFTM_IntConfig(HT_BFTM0, DISABLE);
	BFTM_OneShotModeCmd(HT_BFTM0, ENABLE);
	BFTM_EnaCmd(HT_BFTM0, DISABLE);
}

/**
  * @}
  */
void print_EEROM_data(u32 startPage,u32 endPage)
{
	u32 i,j;
	
	for (j = startPage; j <= endPage; j++)
  {
    //memset((u8 *)READ_BUF_ADDR, 0xC3, I2C_EEPROM_PAGE_SIZE);
    I2C_EEPROM_BufferRead((u8 *)READ_BUF_ADDR, I2C_EEPROM_PAGE_SIZE * j, I2C_EEPROM_PAGE_SIZE);

		for (i = 0; i < (I2C_EEPROM_PAGE_SIZE ); i++)
    {
      printf(" %2x,",READ_BUF_ADDR[i]);//printf(" %x\t",READ_BUF_ADDR[i]);
			
			if((i&1))
			{
				//printf("\r\n");
			}
    }
  }
}

/**
  * @}
  */
