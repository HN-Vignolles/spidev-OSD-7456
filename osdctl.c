#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

struct spi_ioc_transfer xfer;
typedef struct{
  char filename[PATH_MAX];
  uint8_t mode, bits;
  uint32_t speed;
}spi_t;
int fd;
spi_t initspi;

int spidev_init(void);
void writeAddrData(uint8_t addr, uint8_t data);

int main(int argc, char **argv){
  int c;
  if(argc < 3){
    fprintf(stderr, "Usage: %s -f </dev/spidev...>", argv[0]);
    return EXIT_FAILURE;
  }
  while((c = getopt(argc,argv,"f:")) != EOF){
    switch(c){
      case 'f':
        sprintf(initspi.filename,"%s",optarg);
        break;
      case '?':
        fprintf(stderr,"unrecognized option: -%c",c);
        return EXIT_FAILURE;
    }
  }
  initspi.mode = SPI_MODE_0;
  /*The SPI commands are 16 bits long with the 8 most significant bits (MSBs) representing the register address
    and the 8 least significant bits (LSBs) representing the data*/
  initspi.bits = 8;
  initspi.speed = 5000000;
  spidev_init();
  writeAddrData(0x23,0xef);
  close(fd);
}

int spidev_init(void){
  //int ret;
  if((fd = open(initspi.filename,O_RDWR)) < 0){
    perror("%s",initspi.filename);
    return EXIT_FAILURE;
  }
  if((ioctl(fd, SPI_IOC_WR_MODE, &initspi.mode)) < 0){
    perror("SPI_IOC_WR_MODE");
    return EXIT_FAILURE;
  }
  if((ioctl(fd, SPI_IOC_RD_MODE, &initspi.mode)) < 0){
    perror("SPI_IOC_RD_MODE");
    return EXIT_FAILURE;
  }
  if((ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &initspi.bits)) < 0){
    perror("SPI_IOC_WR_BITS_PER_WORD");
    return EXIT_FAILURE;
  }
	if((ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &initspi.bits)) < 0){
    perror("SPI_IOC_RD_BITS_PER_WORD");
    return EXIT_FAILURE;
  }
  if((ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &initspi.speed)) < 0){
    perror("SPI_IOC_WR_MAX_SPEED_HZ");
    return EXIT_FAILURE;
  }
	if((ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &initspi.speed)) < 0){
    perror("SPI_IOC_RD_MAX_SPEED_HZ");
    return EXIT_FAILURE;
  }
  xfer.cs_change = 0; //keep cs activated
  xfer.delay_usecs = 0;
  xfer.speed_hz = initspi.speed;
  xfer.bits_per_word = initspi.bits;
  return 0;
}

void writeAddrData(uint8_t addr, uint8_t data){
  uint8_t buf[2];
  buf[0] = addr;
  buf[1] = data;
  xfer.tx_buf = buf;
  xfer.len = 2;
  if((ioctl(fd, SPI_IOC_MESSAGE(1), xfer)) < 0){
    perror("SPI_IOC_MESSAGE");
    return EXIT_FAILURE;
  }
}
