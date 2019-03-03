#include <avr/io.h>
#include <stdio.h>

#include "spi.h"

// spi pin definitions
#define PIN_SS       PIN2
#define PIN_MOSI     PIN3
#define PIN_MISO     PIN4
#define PIN_SCLK     PIN5


//----------------------------------------------------------------------------------------------------
// open and initialize spi bus
//----------------------------------------------------------------------------------------------------
void spi_init(void)
	{
	// setup spi pins
	DDRB  &= (uint8_t)~((1 << PIN_MOSI) | (1 << PIN_SS) | (1 << PIN_SCLK));  // set pins for input
	PORTB |= ((1 << PIN_MOSI) | (1 << PIN_SS) | (1 << PIN_SCLK));            // turn on pull-up resistors

	DDRB &= (uint8_t)~((1 << PIN_MISO));                      // input pins
	DDRB |= ((1 << PIN_MOSI) | (1 << PIN_SS) | (1 << PIN_SCLK));  // output pins

	// configure spi
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);                // enable spi master mode with clock/16 (1 mhz)
	}

//----------------------------------------------------------------------------------------------------
// spi xmit
//----------------------------------------------------------------------------------------------------
uint8_t spi_xmit(uint8_t byte)
	{
	// put byte on spi bus
	SPDR = byte;

	// wait for transfer to complete
	while (!(SPSR & (1 << SPIF)))
		;

	// return byte received
	return SPDR;
	}

//----------------------------------------------------------------------------------------------------
// spi transfer
//----------------------------------------------------------------------------------------------------
void spi_xfer(uint8_t *in_data, const uint8_t *out_data, size_t count)
	{
	PORTB &= (uint8_t)~((1 << PIN_SS)); // slave select low

	for (size_t i = 0; i < count; i++)
		{
		// set up outbound data
		if (out_data != NULL)
			SPDR = out_data[i];
		else
			SPDR = 0xff; // dummy data

		// spi transfer
		while (!(SPSR & (1 << SPIF)))
			;

		// save inbound data
		if (in_data != NULL)
			in_data[i] = SPDR;
		}

	PORTB |= (1 << PIN_SS); // slave select high
	}

