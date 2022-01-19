/*
 * Main_MCP2515.c
 *
 * Created: 11/25/2021 2:49:24 AM
 * Author : Abdelrahman_Magdy
 */ 

#include <avr/io.h>
#include <util/delay.h>
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

/*=======================================*/
int main(void)
{
   MCP2515_vInit();
   u8 msgData[]={'a','b','c','d','e','f','g','h'};
   
    while (1) 
    {
		/* SEND ( Buffer , Massage ID   , DLC = Lenght & data   */
		MCP2515_vSendMassage(0, 0x7e1 , 8 , msgData );   
		for(u8 i=0;i<8;i++)
		{
			msgData[i]++;
		}
		_delay_ms(1000);
	}
}

