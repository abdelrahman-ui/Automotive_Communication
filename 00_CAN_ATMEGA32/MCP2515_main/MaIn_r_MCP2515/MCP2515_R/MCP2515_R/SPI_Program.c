#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "SPI_Registers.h"
#include "DIO_Interface.h"

void SPI_VidMasterInit(void)
{
	u8 temp_SPCR = 0;

	// Set MOSI pin direction output
	DIO_VidSetPinDirection(DIO_PORTB, DIO_PIN5, DIO_OUTPUT);
	// Set MISO pin direction input with pull-up resistance (Not necessary)
	DIO_VidSetPinDirection(DIO_PORTB, DIO_PIN6, DIO_INPUT);
	DIO_VidSetPinValue(DIO_PORTB, DIO_PIN6, DIO_HIGH);
	// Set clock pin direction output with
	DIO_VidSetPinDirection(DIO_PORTB, DIO_PIN7, DIO_OUTPUT);
//	DIO_VidSetPinValue(DIO_PORTB, DIO_PIN7, DIO_LOW);

	// enable SPI
	SET_BIT(temp_SPCR, 6);

	// data order >>>> transmit MSB first
	CLR_BIT(temp_SPCR, 5);

	// configure SS pin as output and choose master spi mode
	DIO_VidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_OUTPUT);
	DIO_VidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_HIGH);
	SET_BIT(temp_SPCR, 4);


	// clock polarity >>> leading rising edge
	CLR_BIT(temp_SPCR, 3);

	// clock phase >>>> sampling at rising edge
	CLR_BIT(temp_SPCR, 2);

	// clock oscillator >> F_CPU / 4
	CLR_BIT(temp_SPCR, 1);
	CLR_BIT(temp_SPCR, 0);
	CLR_BIT(SPSR, 0);

	SPCR = temp_SPCR;
}

void SPI_VidSlaveInit(void)
{
	u8 temp_SPCR=0;
	// enable SPI
	SET_BIT(temp_SPCR, 6);

	// data order >>>> transmit LSB first
	SET_BIT(temp_SPCR, 5);

	// configure SS pin as output and choose master spi mode
	DIO_VidSetPinDirection(DIO_PORTB, DIO_PIN4, DIO_INPUT);
	DIO_VidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_HIGH);
	CLR_BIT(temp_SPCR, 4);



	// clock polarity >>> leading rising edge
	CLR_BIT(temp_SPCR, 3);

	// clock phase >>>> setup at leading then sample at trailing
	SET_BIT(temp_SPCR, 2);

	// clock oscillator >> F_CPU / 4
	CLR_BIT(temp_SPCR, 1);
	CLR_BIT(temp_SPCR, 0);
	CLR_BIT(SPSR, 0);

	// enable interrupt
	SET_BIT(temp_SPCR, 7);

	SPCR = temp_SPCR;
}

void SPI_VidChipSelect(u8 state)
{
	if(state == 1)
	{
		DIO_VidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_LOW);
	}
	else
	{
		DIO_VidSetPinValue(DIO_PORTB, DIO_PIN4, DIO_HIGH);
	}
}


u8 SPI_U8MasterTransmit(u8 Local_U8Data)
{
	u8 dataRead=0;
	SPDR = Local_U8Data;
	while(GET_BIT(SPSR, 7)==0);
	dataRead = SPDR;
	return dataRead;
}


