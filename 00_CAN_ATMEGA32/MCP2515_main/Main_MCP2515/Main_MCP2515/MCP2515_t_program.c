/*=======================================================================================
===========================  - MCP2515_t.c					 ============================
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
	#include "MCP2515_t_interface.h"
	#include "MCP2515_t_private.h"
	#include "MCP2515_t_config.h"
	
/*=======================================*/


/*======================================================== Start_FUNCTION  ========================================================*/

u8 MCP2515_u8ReadRegiter(u8 Copy_RegAdress)
{
	/* Var to read  register */
   u8 Local_u8ReadData = 0 ;
	/* Enable SPI SS (Nude)  */
  SPI_VidChipSelect(1) ;
	/* Send Read Instruction */
  SPI_U8MasterTransmit(READ_IS); 
	/* Send Addres os Register */
  SPI_U8MasterTransmit(Copy_RegAdress); 
	/* Send Any Massage & Resive Data to return data  */
  Local_u8ReadData=SPI_U8MasterTransmit(0); 
    /* must Disable SPI SS (Nude)  */
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
/* To change spasific bits in REG  like |= */
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
  /* MUST be configration mode in configration but after config when used make it Normal mode */
void MCP2515_vSetMode(u8 Copy_u8Mode)
{
		/* Write only at last 3 bit ( 0XE0 : 0b1110 000)  & Sheft 5 untile pins of mode */
	MCP2515_vModify(CAN_CTRL,0xE0,(Copy_u8Mode<<5));
		/* Check the state changed or not read last 3 bit in canstate*/
	while(MCP2515_u8ReadRegiter(CAN_STAT>>5) !=Copy_u8Mode);   
	
	
}
  

/*======================================================== Start_FUNCTION  ========================================================*/

void MCP2515_vSendMassage(u8 Copy_u8BufferId , u32 Copy_u32MassageId , u8 Copy_u8DLC , u8 * Copy_Ptru8Data )
{
		/* Take the bus */
	SPI_VidChipSelect(1) ;
		/* Send Write Instruction */
	SPI_U8MasterTransmit(WRITE_IS);
		/* Send Address & must write value from ctrl reg and it will increase automatic it's u32. Here must be for buffer choise  */
	SPI_U8MasterTransmit(TXB0CTRL);
		/* You can writ value to choice priority the other bit not care 
			Any value  but mandatory to write*/
	SPI_U8MasterTransmit(Copy_u8DLC >> 6) ;	
		/* Now with ID High that take ftom 3 : 10 */
	SPI_U8MasterTransmit((u8) (Copy_u32MassageId >> 3) ) ;
		/* Now with ID Low 0 : 2*/
	SPI_U8MasterTransmit((u8) (Copy_u32MassageId << 5) ) ;
		/* For Extend i'm not need need it so send any value for high and low */
	SPI_U8MasterTransmit(0);
	SPI_U8MasterTransmit(0);
		/* Send DLC frist 4 bit the bigest value 1000 even if you write 1111 it will write 1000 */
	SPI_U8MasterTransmit(Copy_u8DLC& 0x0f);
		/* Send data */
	for(u8 Local_u8Count = 0 ; Local_u8Count < (Copy_u8DLC& 0x0f) ; Local_u8Count ++ )
		{	
			SPI_U8MasterTransmit(Copy_Ptru8Data[Local_u8Count]);	
		}
		/* Now Lelease bus */
	SPI_VidChipSelect(0);
		/* Take the bus */	
	SPI_VidChipSelect(1);
		/* Now must send request to send for buffer 0*/
	SPI_U8MasterTransmit(MCP2515_REQ2SEND_B0);
		/* Now Lelease bus */
	SPI_VidChipSelect(0);
		
}
/*======================================================== END_FUNCTION  ========================================================*/

/*======================================================== Start_FUNCTION  ========================================================*/

void MCP2515_vInit(void)
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
		/* Return to Normal mode To send and recive */
	MCP2515_vSetMode(MCP2515_MODE_NORMAL) ;
	
}
/*======================================================== END_FUNCTION  ========================================================*/
