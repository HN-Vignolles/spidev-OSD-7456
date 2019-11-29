#include "main.h"
#include "max7456.h"

struct spi_ioc_transfer xfer;
int fd;
spi_t initspi;

int main(int argc, char **argv){
  int c;
  char buf[MAXLINE], *pEnd;
  long int x,y,mode;

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
  displayChar(1,1,0xFC,OSD_LBC);
  displayString(2, 2, "Hello World!", OSD_LBC);
  /*while(fgets(buf,MAXLINE,stdin)!=NULL){
    x = strtol(buf,&pEnd,10);
    y = strtol(pEnd,&pEnd,10);
    mode = strtol(pEnd,&pEnd,2);
    fprintf(stderr,"x:%li, y:%li, mode:%x, text: %s\n",x,y,mode<<5,pEnd);
    displayString(y,x,pEnd,mode<<5);
  }*/
  clearOSD();
  close(fd);
}

int spidev_init(void){
  //int ret;
  if((fd = open(initspi.filename,O_RDWR)) < 0){
	  perror(initspi.filename);
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
