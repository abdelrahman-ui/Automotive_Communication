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

/*=============  INCLUDEAPP =============*/


/*=======================================*/



/*======================================================== Start_FUNCTION  ========================================================*/
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
	while(MCP2515_u8ReadRegiter(CAN_STAT>>5) !=Copy_u8Mode);
	
	
}

/*======================================================== END_FUNCTION  ========================================================*/
void MCP2515_vSetRollOver(void)
{
	 MCP2515_vModify(RXB0CTRL , 1<<3 , 1<<3);
	
}

void MCP2515_vSetMaskR(u8 Copy_u8MaskAddress , u32 Copy_u32Value ,u8 Copy_u8IsExtended )
{
	/* Enable SPI SS (Nude)  */
	SPI_VidChipSelect(1) ;
	/* Send Read Instruction */
	SPI_U8MasterTransmit(WRITE_IS);
	/* Send Address of mask */
	SPI_U8MasterTransmit(Copy_u8MaskAddress);
	/* if you have extended id or not extended  */
	if(Copy_u8IsExtended)
	{
		
		SPI_U8MasterTransmit((u8) (Copy_u32Value >> 3) ) ;
		SPI_U8MasterTransmit((u8) (Copy_u32Value << 5)  | (1<<3) |(u8)(Copy_u32Value >>27)) ;
		SPI_U8MasterTransmit((u8) (Copy_u32Value >> 19) ) ;
		SPI_U8MasterTransmit((u8) (Copy_u32Value << 11) ) ;	
		
	}
	else
	{
		/* Now with ID High that take ftom 3 : 10 */
		SPI_U8MasterTransmit((u8) (Copy_u32Value >> 3) ) ;
		/* Now with ID Low 0 : 2*/
		SPI_U8MasterTransmit((u8) (Copy_u32Value << 5) ) ;
	}
	
	/* Disable SPI SS (Nude) */
	SPI_VidChipSelect(0);
}


void MCP2515_vInitR()
{
	/* Must init SPI  */
	SPI_VidMasterInit();
	/* Reseat   */
	MCP2515_vReseat() ;
	/* Set configration mode and enable clk  */
	MCP2515_vWriteRegiter(CAN_CTRL , 0X84) ;
	/* Check the state changed or not read last 3 bit in canstate*/
	while( MCP2515_u8ReadRegiter(CAN_STAT>>5) !=MCP2515_MODE_CONFIG);
	/* Set Value of CNF1 & CNF2 & CNF3*/
	MCP2515_vSetBitTiming(0X80 , 0XB1 , 0X05) ;
	/* Set Mask Accept all */
	MCP2515_vSetMaskR(RXM0SIDH ,0X00000000 ,1 );
	MCP2515_vSetMaskR(RXM1SIDH ,0X00000000 ,1 );
	/* Enable Interrupt */
	MCP2515_vWriteRegiter(CANINTE , 1<<0);
	/* Set Normal Mode */
	MCP2515_vSetMode(MCP2515_MODE_NORMAL);
	
}




u8 array[14];
void MCP2515_vRecive(void)
{
	 /* Enable SPI SS (Nude)  */
	 SPI_VidChipSelect(1) ;
	 /* Send Read Instruction */
	 SPI_U8MasterTransmit(READ_IS);
	 /* Send Address*/
	 SPI_U8MasterTransmit(RXB0CTRL);
	 /* Send Dumy value to recive 14 byte 14 Reg */
	 for(u8 Local_u8Count = 0 ; Local_u8Count <14 ; Local_u8Count ++)
	 {
		array[Local_u8Count] = SPI_U8MasterTransmit(0); 
	 }
	 /* Disable SPI SS (Nude) */
	 SPI_VidChipSelect(0);
	 /* Clear Flag */
	 MCP2515_vWriteRegiter(CANINTF , 0);
	  
}