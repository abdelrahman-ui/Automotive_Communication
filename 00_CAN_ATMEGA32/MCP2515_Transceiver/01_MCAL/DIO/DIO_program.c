
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_private.h"

void DIO_VidInit(void)
{

}

void DIO_VidSetPortDirection(u8 Copy_U8Port, u8 Copy_U8Direction)
{
    switch(Copy_U8Port)
    {
        case 0 :    DDRA = Copy_U8Direction; break;
        case 1 :    DDRB = Copy_U8Direction; break;
        case 2 :    DDRC = Copy_U8Direction; break;
        case 3 :    DDRD = Copy_U8Direction; break;
    }
}

void DIO_VidSetPinDirection(u8 Copy_U8Port, u8 Copy_U8Pin, u8 Copy_U8Direction)
{
    if(Copy_U8Direction == 1)
    {
        switch (Copy_U8Port)
        {
            case 0 : SET_BIT(DDRA,Copy_U8Pin); break;
            case 1 : SET_BIT(DDRB,Copy_U8Pin); break;
            case 2 : SET_BIT(DDRC,Copy_U8Pin); break;
            case 3 : SET_BIT(DDRD,Copy_U8Pin); break;
        }
    }
    else if (Copy_U8Direction == 0)
    {
        switch (Copy_U8Port)
        {
            case 0 : CLR_BIT(DDRA,Copy_U8Pin); break;
            case 1 : CLR_BIT(DDRB,Copy_U8Pin); break;
            case 2 : CLR_BIT(DDRC,Copy_U8Pin); break;
            case 3 : CLR_BIT(DDRD,Copy_U8Pin); break;
        }        
    }
    else
    {

    }
}

void DIO_VidSetPortValue(u8 Copy_U8Port, u8 Copy_U8Value)
{
    switch(Copy_U8Port)
    {
        case 0 :    PORTA = Copy_U8Value; break;
        case 1 :    PORTB = Copy_U8Value; break;
        case 2 :    PORTC = Copy_U8Value; break;
        case 3 :    PORTD = Copy_U8Value; break;
    }
}

void DIO_VidSetPinValue(u8 Copy_U8Port, u8 Copy_U8Pin , u8 Copy_U8Value)
{
    if (1 == Copy_U8Value)
    {
        switch(Copy_U8Port)
        {
            case 0 : SET_BIT(PORTA,Copy_U8Pin); break;
            case 1 : SET_BIT(PORTB,Copy_U8Pin); break;
            case 2 : SET_BIT(PORTC,Copy_U8Pin); break;
            case 3 : SET_BIT(PORTD,Copy_U8Pin); break;            
        }
    }
    else if (0== Copy_U8Value)
    {
        switch (Copy_U8Port)
        {
            case 0 : CLR_BIT(PORTA,Copy_U8Pin); break;
            case 1 : CLR_BIT(PORTB,Copy_U8Pin); break;
            case 2 : CLR_BIT(PORTC,Copy_U8Pin); break;
            case 3 : CLR_BIT(PORTD,Copy_U8Pin); break;
        } 
    }
}

void DIO_VidTogglePin(u8 Copy_U8Port, u8 Copy_U8Pin)
{
    switch (Copy_U8Port)
    {
        case 0 : TOGGLE_BIT(PORTA,Copy_U8Pin); break;
        case 1 : TOGGLE_BIT(PORTB,Copy_U8Pin); break;
        case 2 : TOGGLE_BIT(PORTC,Copy_U8Pin); break;
        case 3 : TOGGLE_BIT(PORTD,Copy_U8Pin); break;
    } 
}

u8 DIO_U8GetPinValue(u8 Copy_U8Port, u8 Copy_U8Pin)
{
    u8 Local_U8Value;
    switch (Copy_U8Port)
    {
        case 0 : Local_U8Value = GET_BIT(PINA,Copy_U8Pin); break;
        case 1 : Local_U8Value = GET_BIT(PINB,Copy_U8Pin); break;
        case 2 : Local_U8Value = GET_BIT(PINC,Copy_U8Pin); break;
        case 3 : Local_U8Value = GET_BIT(PIND,Copy_U8Pin); break;
    }
    return Local_U8Value;    
}

u8 DIO_U8GetPortValue(u8 Copy_U8Port)
{
	u8 Local_U8Value;
	switch(Copy_U8Port)
	{
		case 0 : Local_U8Value = PINA; break;
		case 1 : Local_U8Value = PINB; break;
		case 2 : Local_U8Value = PINC; break;
		case 3 : Local_U8Value = PIND; break;
	}
	return Local_U8Value;
}
