/*======================================================================================
===========================  - MCP2515_private.h		     ============================
===========================  - Created: 10/3/2021	         ============================
===========================  - Author: Abdelrahman_Magdy     ============================
===========================  - Version : _1_				 ============================
===========================  - Note :
					      *-
					      *-
 ======================================================================================*/ 


/*======================================================================================
          *        Developer can't Edit in it    
          *        Register _ Defination		
          *        Design : 
				- #define	:	YES
				- Union		:	NO
				- Struct	:	NO
======================================================================================*/

/*======================================================================================
=======================  guard of file will call on time in .c	========================
========================================================================================*/


#ifndef MCP2515_R_PRIVATE_H_
#define MCP2515_R_PRIVATE_H_


#define  CNF1	  (0x2A)
#define  CNF2	  (0x29)
#define  CNF3	  (0x28)

#define  CAN_CTRL (0X0F)
#define  CAN_STAT (0X0E)


#define RXB0CTRL  (0b01100000)
#define RXM0SIDH  (0x20)
#define RXM1SIDH  (0x24)
#define CANINTE   (0b00101011)
#define CANINTF   (0X2c)
#define READ_IS     0X03
#define WRITE_IS    0X02
#define REST_IS     0XC0
#define MODIFY_IS   0x05

#define MCP2515_REQ2SEND_B0	0X81

#define MCP2515_MODE_CONFIG 0x4
#define MCP2515_MODE_NORMAL 0X0



#endif /* MCP2515_R_PRIVATE_H_ */