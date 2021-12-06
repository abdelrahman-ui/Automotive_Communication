
#ifndef UART_REGISTERS_H
#define UART_REGISTERS_H


void __vector_13(void) __attribute__((signal));


#define UDR		*((volatile u8 *) 0x2C)
#define UCSRA	*((volatile u8 *) 0x2B)
#define UCSRB	*((volatile u8 *) 0x2A)
#define UCSRC	*((volatile u8 *) 0x40)
#define UBRRH	*((volatile u8 *) 0x40)
#define UBRRL	*((volatile u8 *) 0x29)


#endif /* UART_REGISTERS_H */
