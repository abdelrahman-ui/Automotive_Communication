/*========================================================================================
===========================   - MCP2515_t_interface.h	      ============================
===========================   - Created:  10/3/2021     `	  ============================
===========================   - Author: Abdelrahman_Magdy     ============================
===========================   - Version : _1_				  ============================
===========================   - Note :
					  *-
					  *-
========================================================================================*/ 



/*========================================================================================
		
               * What i sell To Customer
               *  The Archictect Give The API :
						 - The Name Of Function 
						 - What is The Input 
						 - What Is The Output
						 - Macro 
						 
========================================================================================*/ 

/*======================================================================================
=======================  guard of file will call on time in .c	========================
========================================================================================*/

#ifndef CAN_T_INTERFACE_H_
#define CAN_T_INTERFACE_H_

u8 MCP2515_u8ReadRegiter(u8 Copy_RegAdress);
void MCP2515_vWriteRegiter(u8 Copy_RegAdress ,  u8 Copy_Data);
void MCP2515_vReseat();
void MCP2515_vModify(u8 Copy_u8RegAdress , u8 Copy_u8Mask  ,u8 Copy_u8Data);
void MCP2515_vSetBitTiming(u8 Copy_u8Cnf1Val , u8 Copy_u8Cnf2Val ,u8 Copy_u8Cnf3Val );
void MCP2515_vSetMode(u8 Copy_u8Mode);
void MCP2515_vInit(void);
void MCP2515_vSendMassage(u8 Copy_u8BufferId , u32 Copy_u32MassageId , u8 Copy_u8DLC , u8 * Copy_Ptru8Data );

#define READ_IS     0X03
#define WRITE_IS    0X02
#define REST_IS     0XC0
#define MODIFY_IS   0x05

#define MCP2515_REQ2SEND_B0	0X81



#define MCP2515_MODE_CONFIG 0x4
 #define MCP2515_MODE_NORMAL 0b0000


#endif /* CAN_T_INTERFACE_H_ */