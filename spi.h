#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>
#include <stddef.h>

// low level functions
void    spi_init(void);
uint8_t spi_xmit(uint8_t data);

// functions
void    spi_xfer(uint8_t *in_data, const uint8_t *out_data, size_t count);
#define spi_write(out_data, count) spi_xfer(NULL, (out_data), (count))
#define spi_read(in_data, count) spi_xfer((in_data), NULL, (count))


#endif // SPI_H_
