#include <avr/io.h>
#include <stdio.h>

#include "uart.h"
#include "spi.h"


int main(void)
	{
	uart_init_115200();           // initialize uart
	printf("uart initialized\n");
	getchar();

	// initialize spi
	spi_init();

	printf("spi initialized\n");
	getchar();

	uint8_t data_tx[] =
			{
//			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x00,
//			0x00, 0x00, 0x00, 0x95, 0xFF, 0xFF, 0xFF, 0xFF,
//			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//			0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDE, 0xAD,
//			0xBE, 0xEF, 0xBA, 0xAD, 0xF0, 0x0D, 0x11, 0x22
			0xBE, 0xEF
			};

	#define DATA_TX_SIZE (sizeof(data_tx)/sizeof(data_tx[0]))
	uint8_t data_rx[DATA_TX_SIZE] = {0};

	// send/receive data
	spi_xfer(&data_rx[0], &data_tx[0], DATA_TX_SIZE);
	printf("xfer complete\n");

	for (unsigned int i = 0; i < DATA_TX_SIZE; i++)
		{
		if (!(i % 8))
			printf("\n");
		printf("0x%02hX ", data_rx[i]);
		}
	printf("\nend program\n");

	return 0;
	}
