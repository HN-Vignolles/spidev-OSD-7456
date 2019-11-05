#include "main.h"
#include "max7456.h"

extern struct spi_ioc_transfer xfer;
extern int fd;

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

void writeData(uint8_t data){
  xfer.tx_buf = (unsigned long)&data;
  xfer.len = 1;
  if((ioctl(fd, SPI_IOC_MESSAGE(1), &xfer)) < 0){
    perror("SPI_IOC_MESSAGE");
  }
}

void displayChar(uint8_t y, uint8_t x, uint16_t addr){ 
  uint16_t ca; //character address
  uint8_t addrH, attr; 

  ca = y * 30 + x; //30 characters per row
  addrH = ca >> 8; 
  //Read factory preset before write (p36)... writeAddrData(OSDBL,0X00);
  writeAddrData(DMM, 0x40); //8-bit operation mode
  writeAddrData(DMAH, addrH | 0x2); //0x2(bit 1): Character Attribute byte is written
                                    //(DMDI[7:0] contains the Character Attribute Byte)
                                    //bit 0: Display Memory Address Bit 8. 7-0 in DMAL
  writeAddrData(DMAL, ca); //This byte is the lower 8 bits of the display-memory address
  /*j = CHAR_LBC << 5; 
  if ((addr >> 8) != 0)
    j |= 0x10; */
  writeAddrData(DMDI, attr);//Write the Character Attribute byte
  
  writeAddrData(DMAH, addrH); 
  writeAddrData(DMAL, ca); 
  writeAddrData(DMDI, addr);
  writeAddrData(VM0, 0x48); 
}

void clearOSD(void){ 
  writeAddrData(DMM, 0x01); 
}
