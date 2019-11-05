#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

typedef struct{
  char filename[PATH_MAX];
  int fd;
  uint8_t mode, bits;
  uint32_t speed=5000000;
}spi_t;
spi_t initspi;

int spidev_init(void);

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
  spidev_init();
}

int spidev_init(void){
  //int ret;
  if((initspi.fd = open(initspi.filename,O_RDWR)) < 0){
    perror("%s",initspi.filename);
    return EXIT_FAILURE;
  }
  if((ioctl(initspi.fd, SPI_IOC_WR_MODE, &mode)) < 0){
    perror("ioctl");
    return EXIT_FAILURE;
  }
  if((ioctl(initspi.fd, SPI_IOC_RD_MODE, &mode)) < 0){
    perror("ioctl");
    return EXIT_FAILURE;
  }
  
}
