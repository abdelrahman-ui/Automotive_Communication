
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "UART_Registers.h"
#include "UART_Config.h"

void UART_VidInit(void)
{
	u8 temp_UCSRC= 0b10000000;
	u8 temp_UBRRH= 0b00000000;
	// interrupt enable
//	SET_BIT(UCSRB, 7);

	// Receiver enable
	SET_BIT(UCSRB, 4);

	// Transmitter enable
	SET_BIT(UCSRB, 3);

	// choose the data size
	// data size = 8 bits
	CLR_BIT(UCSRB, 2);
	SET_BIT(temp_UCSRC, 2);
	SET_BIT(temp_UCSRC, 1);

	// set UART mode as Asynchronous
	CLR_BIT(temp_UCSRC, 6);

	// parity mode >>> disabled
	CLR_BIT(temp_UCSRC, 5);
	CLR_BIT(temp_UCSRC, 4);

	// stop bit >>> 1-bit
	CLR_BIT(temp_UCSRC, 3);

	// write the special UCSRC register in one operation
	// you can access this register only if the data you
	// need to write contain 1 in the 8th bit
	// the 8th bit considered part of the address to this
	// register , that is because the AVR tries to limit
	// their I/O registers to 64 place in the memory only
	// >> the reason for only 64 place is that the argument
	// of the IN / OUT assembly instructions takes 6-bit value
	// >> also with this register can't do read-modify-write
	// operation , as it has special way to read it
	UCSRC = temp_UCSRC;

	// set baud rate to 9600 while F_CBU = 8MHz >>> 51
	UBRRL = 51; // 12 >>> 38400
}

void UART_VidSendData(u8 Copy_U8Data)
{
	// loop till Data register empty flag is 1 >>> empty
	while(GET_BIT(UCSRA, 5)==0);

	// write the data
	UDR = Copy_U8Data;
}

//u8 UART_U8ReadBuffer(void)
//{
//	// apply circular buffer algorithm to read
//	u8 temp_readIdx = Read_buffer;
//}

u8 UART_U8ReadData(void)
{
	u8 Local_U8Data = 0;
	if(GET_BIT(UCSRA, 7) == 1)
	{
		Local_U8Data = UDR;
	}

	return Local_U8Data;
}

void UART_VidSendString(u8 * ptr_U8String)
{
	u8 i=0;
	while(ptr_U8String[i])
	{
		UART_VidSendData(ptr_U8String[i]);
		i++;
	}
}

// receive interrupt
u8 UART_Data;
u8 UART_ReadFlag;
void __vector_13(void)
{
	UART_Data = UDR;
	UART_ReadFlag = 1;
}
