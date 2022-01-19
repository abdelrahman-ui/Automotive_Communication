/*
 * MCP2515_R.c
 *
 * Created: 12/22/2021 1:48:27 AM
 * Author : Pro
 */ 

#include <avr/io.h>

/*============= INCLUDE LIB =============*/
#include "STD_TYPE.h"
#include "BIT_MATH.h"
/*=======================================*/

/*============= INCLUDE MCAL =============*/
#include "DIO_Interface.h"
#include "SPI_Interface.h"
#include "UART_Interface.h"
/*=======================================*/

/*============= INCLUDE HAL =============*/
#include "MCP2515_r_interface.h"
/*=======================================*/
#include <util/delay.h>


#define  SREG *((volatile u8 *) 0x5F )

extern u8 readBuffer[]; 

int main(void)
{
    MCP2515_vInitReceive(void);
	UART_VidInit(void);
	DIO_VidSetPinDirection(DIO_PORTD,DIO_PIN2,DIO_INPUT);
	u8 dataR=0;
    while (1) 
    {
		if(DIO_U8GetPinValue(DIO_PORTD,DIO_PIN2,DIO_INPUT) == 0)
		{
		MCP2515_vResiveMessage();
		for(u8 i=0 ; i<8 ; i++)
			{
				dataR = readBuffer[6+i];
				UART_VidSendData(dataR);
			}
		UART_VidSendData('\r');
		UART_VidSendData('\n');
			
		}
    }
}

