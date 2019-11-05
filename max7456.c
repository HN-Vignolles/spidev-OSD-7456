#include "main.h"
#include "max7456.h"

extern struct spi_ioc_transfer xfer;

void writeAddrData(uint8_t addr, uint8_t data){
  uint8_t buf[2];
  buf[0] = addr;
  buf[1] = data;
  xfer.tx_buf = (unsigned long)buf;
  xfer.len = 2;
  if((ioctl(fd, SPI_IOC_MESSAGE(1), &xfer)) < 0){
    perror("SPI_IOC_MESSAGE");
  }
}
