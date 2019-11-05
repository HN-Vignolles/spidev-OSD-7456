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
  int fd;
  uint8_t mode, lsb, bits;
  uint32_t speed=5000000;
}spi_t;

int spidev_init(void);

int main(int argc, char **argv){
  int c;
  if(argc < 3){
    fprintf(stderr, "Usage: %s -f </dev/spidev...>", argv[0]);
    return EXIT_FAILURE;
  }
  while((c = getopt(argc,argv,"f:")) != EOF){
