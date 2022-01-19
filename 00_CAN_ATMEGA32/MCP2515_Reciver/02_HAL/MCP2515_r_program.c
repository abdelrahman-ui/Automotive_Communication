/*=======================================================================================
===========================  - MCP2515_r.c					 ============================
===========================  - Created: 10/3/2021			 ============================
===========================  - Author: Abdelrahman_Magdy     ============================
===========================  - Version : _1_				 ============================
===========================  - Note :
					      *-
					      *-
 =======================================================================================*/


/*======================================================================================
============================   The Foundation Of Function   ============================
========================================================================================*/


/*============= INCLUDE LIB =============*/
	#include "STD_TYPE.h"
	#include "BIT_MATH.h"
/*=======================================*/

/*============= INCLUDE MCAL =============*/
	#include "DIO_Interface.h"
	#include "SPI_Interface.h"
/*=======================================*/

/*============= INCLUDE HAL =============*/
	#include "MCP2515_r_interface.h"
	#include "MCP2515_r_private.h"
	#include "MCP2515_r_config.h"	
/*=======================================*/


/*======================================================== Start_FUNCTION  ========================================================*/

/*
 * Initialization :
 *					- Set bit timming .
 *					- Set Mask ID . 
 *					- Enable interrput .
*/
 void MCP2515_vInitReceive(void)
 {
	 /* Must init SPI  */
	 SPI_VidMasterInit();
	 /* Reseat   */
	 MCP2515_vReseat() ;
	 /* Set configration mode and enable clk  */
	 MCP2515_vWriteRegiter(CAN_CTRL , 0X84) ;
	 /* Check the state changed or not read last 3 bit in canstate*/
	 while(MCP2515_u8ReadRegiter(CAN_STAT>>5) !=MCP2515_MODE_CONFIG);
	 /* Set Value of CNF1 & CNF2 & CNF3*/
	 MCP2515_vSetBitTiming( CNF1_REG,CNF2_REG  ,CNF3_REG ) ;
	
	 /* Set Mask =0000 0000 SO Accept all */ 
	 MCP2515_vSetMask( RXM0SIDH , 0X00000000 , 1 );
	 MCP2515_vSetMask( RXM1SIDH , 0X00000000 , 1 );
	
	/* To enable interrput */
	MCP2515_vWriteRegiter(CANINTE,  1<<0);
	
	/* Return to Normal mode To send and recive */
	MCP2515_vSetMode(MCP2515_MODE_NORMAL) ;
 }


/*======================================================== END_FUNCTION  ========================================================*/


/*======================================================== Start_FUNCTION  ========================================================*/
/*
  * Read resive buffer and clear flag .
  * For One Buffer can recive  Filtter ( 0 : 5 ) 6 ID.
  * Filtter mode ( Normal -->  All must be the same | Mask ( value & mask ) (only compare spasific bit) ) . 
  * To resive all ID so no compare bit at mask so all mask 0 . 
*/

u8 readBuffer[14];
void MCP2515_vResiveMessage(void)
{
	/* Enable SPI SS (Nude)  */
	SPI_VidChipSelect(1) ;
	/* Send Read Instruction */
	SPI_U8MasterTransmit(READ_IS);
	/* Send Address*/
	SPI_U8MasterTransmit(RXB0CTRL);
	/* Send dumy to resive 14 element*/
	for(u8 i=0 ; i<14 ; i++)
	{
		readBuffer[i]=SPI_U8MasterTransmit(0);
		
	}
	/* Disable SPI SS (Nude)  */
	SPI_VidChipSelect(0);
	/* Must clear flag */
	MCP2515_vWriteRegiter(CANINTF , 0);
}

/*======================================================== END_FUNCTION  ========================================================*/
 
/*======================================================== Start_FUNCTION  ========================================================*/ 
/*
 * The Rollover when resive buffer full so resive in anthor buffer 
 */
 void MCP2515_vSetRollOver(void)
 {
	 MCP2515_vModify(RXB0CTRL , 1<<3 , 1<<3 ) ;
	 
 }   
/*======================================================== END_FUNCTION  ========================================================*/

/*======================================================== Start_FUNCTION  ========================================================*/

void MCP2515_vSetMask(u8 Copy_u8MaskAdress ,u32 Copy_u32Value ,u8 Copy_u8Extended  )
{
	/* Enable SPI SS (Nude)  */
 SPI_VidChipSelect(1);
   /* Send Write Instruction */
 SPI_U8MasterTransmit(WRITE_IS);
   /* Send Address*/
 SPI_U8MasterTransmit(Copy_u8MaskAdress);
   /* Write the value ( Normal ID OR Extended ) */
  if(Copy_u8Extended )
  {
	  SPI_U8MasterTransmit((u8)(Copy_u32Value >> 3)) ;
	  /* And 1 for Extended  */
	  SPI_U8MasterTransmit((u8)(Copy_u32Value << 5) | ( 1<< 3) |(u8) (Copy_u32Value >> 27) ) ;
	  SPI_U8MasterTransmit((u8)(Copy_u32Value >> 19)) ;
	  SPI_U8MasterTransmit((u8)(Copy_u32Value << 11)) ;
  }
  else
  {
	 SPI_U8MasterTransmit((u8)(Copy_u32Value >> 3)) ;
	 SPI_U8MasterTransmit((u8)(Copy_u32Value << 5)) ;
  }
   /* Disable SPI SS (Nude)  */
   SPI_VidChipSelect(0);
  }
  
/*======================================================== END_FUNCTION  ========================================================*/

/*======================================================== Start_FUNCTION  ========================================================*/

u8 MCP2515_u8ReadRegiter(u8 Copy_RegAdress)
{
	u8 Local_u8ReadData = 0 ;
	/* Enable SPI SS (Nude)  */
	SPI_VidChipSelect(1) ;
	/* Send Read Instruction */
	SPI_U8MasterTransmit(READ_IS);
	/* Send Address*/
	SPI_U8MasterTransmit(Copy_RegAdress);
	/* Send Any Massage & Resive Data */
	Local_u8ReadData=SPI_U8MasterTransmit(0);
	/* Disable SPI SS (Nude)  */
	SPI_VidChipSelect(0);
	return Local_u8ReadData ;
}

/*======================================================== END_FUNCTION  ========================================================*/


/*======================================================== Start_FUNCTION  ========================================================*/

void MCP2515_vWriteRegiter(u8 Copy_RegAdress ,  u8 Copy_Data)
{
	/* Enable SPI SS (Nude)  */
	SPI_VidChipSelect(1) ;
	/* Send Read Instruction */
	SPI_U8MasterTransmit(WRITE_IS);
	/* Send Address*/
	SPI_U8MasterTransmit(Copy_RegAdress);
	/* Send Data*/
	SPI_U8MasterTransmit(Copy_Data);
	/* Disable SPI SS (Nude) */
	SPI_VidChipSelect(0);
}
/*======================================================== END_FUNCTION  ========================================================*/

/*======================================================== Start_FUNCTION  ========================================================*/
void MCP2515_vReseat()
{
	/* Enable SPI SS (Nude)  */
	SPI_VidChipSelect(1) ;
	/* Send Reseat Instruction */
	SPI_U8MasterTransmit(REST_IS);
	/* Disable SPI SS (Nude) */
	SPI_VidChipSelect(0);
	
}
/*======================================================== END_FUNCTION  ========================================================*/


/*======================================================== Start_FUNCTION  ========================================================*/

void MCP2515_vModify(u8 Copy_u8RegAdress , u8 Copy_u8Mask  ,u8 Copy_u8Data)
{
	/* Enable SPI SS (Nude)  */
	SPI_VidChipSelect(1) ;
	/* Send Read Instruction */
	SPI_U8MasterTransmit(MODIFY_IS);
	/* Send Address*/
	SPI_U8MasterTransmit(Copy_u8RegAdress);
	/* Send The place of the bit you wont to modify it */
	SPI_U8MasterTransmit(Copy_u8Mask);
	/* Send Modifay data*/
	SPI_U8MasterTransmit(Copy_u8Data);
	/* Disable SPI SS (Nude) */
	SPI_VidChipSelect(0);
}
/*======================================================== END_FUNCTION  ========================================================*/

/*======================================================== Start_FUNCTION  ========================================================*/

void MCP2515_vSetBitTiming(u8 Copy_u8Cnf1Val , u8 Copy_u8Cnf2Val ,u8 Copy_u8Cnf3Val )
{
	/* Change mode to configration mode  */
	
	/* Write on CNF1 */
	MCP2515_vWriteRegiter(CNF1 ,Copy_u8Cnf1Val );
	/* Write on CNF2 */
	MCP2515_vWriteRegiter(CNF2 ,Copy_u8Cnf2Val );
	/* Write on CNF3 */
	MCP2515_vWriteRegiter(CNF3 ,Copy_u8Cnf3Val );
	
}
/*======================================================== END_FUNCTION  ========================================================*/


/*======================================================== Start_FUNCTION  ========================================================*/

void MCP2515_vSetMode(u8 Copy_u8Mode)
{
	/* Write only at last 3 bit ( 0XE0 : 0b1110 000)  & Sheft 5 untile pins of mode */
	MCP2515_vModify(CAN_CTRL,0xE0,(Copy_u8Mode<<5));
	/* Check the state changed or not read last 3 bit in canstate*/
	while(MCP2515_vReadRegiter(CAN_STAT>>5) !=Copy_u8Mode);
	
	
}

/*======================================================== END_FUNCTION  ========================================================*/
