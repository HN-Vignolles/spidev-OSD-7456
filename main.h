#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#define PATH_MAX 4096

typedef struct{
  char filename[PATH_MAX];
  uint8_t mode, bits;
  uint32_t speed;
}spi_t;

int spidev_init(void);

#endif
