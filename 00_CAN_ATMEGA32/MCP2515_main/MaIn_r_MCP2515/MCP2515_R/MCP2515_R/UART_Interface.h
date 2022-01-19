
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


void UART_VidInit(void);
void UART_VidSendData(u8 Copy_U8Data);
u8 UART_U8ReadData(void);
void UART_VidSendString(u8 * ptr_U8String);



#endif /* UART_INTERFACE_H */
