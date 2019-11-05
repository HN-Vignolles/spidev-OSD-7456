#ifndef _MAX7456_H_
#define _MAX7456_H_

//Register name - Write Address
#define VM0 0x00 // Video Mode0
  /*6:  0=NTSC, 1=PAL
  5-4:  0x=AutosyncSelect, 10=External, 11=Internal 
    3:  0=OSD_off, 1=OSD_on
    2:  0=Enable OSD immediately, 1=Enable OSD at the next ~VSYNC
    1:  Software reset bit
    0:  0=Video Buffer Enable, 1=Video Buffer Disable */
#define VM1 0x01 // Video Mode1
  /*7:  Background Mode
        0 = The Local Background Control bit (see DMM[5] and DMDI[7])
            sets the state of each character background.
        1 = Sets all displayed background pixels to gray. The gray level is specified by bits VM1[6:4] below.
            This bit overrides the local background control bit.
  6-4:  Background Mode Brightness (% of OSD White Level)
        000 = 0% --- 111 = 49%
  3-2:  Blinking Time (BT)
        00 = 2 fields (33ms in NTSC mode, 40ms in PAL mode)
        01 = 4 fields (67ms in NTSC mode, 80ms in PAL mode)
        10 = 6 fields (100ms in NTSC mode, 120ms in PAL mode)
        11 = 8 fields (133ms in NTSC mode, 160ms in PAL mode)
  1-0:  Blinking Duty Cycle (On : Off)
        00 = BT : BT
        01 = BT : (2 x BT)
        10 = BT : (3 x BT)
        11 = (3 x BT) : BT */
#define HOS 0x02 // Horizontal Offset 
 /*5-0: 00 0000 = Farthest left (-32 pixels)
         ...
        10 0000 = No horizontal offset
         ...
        11 1111 = Farthest right (+31 pixels)*/
#define VOS 0x03 // Vertical Offset 
  /*(OSD video can be vertically shifted into the vertical blanking lines)
   4-0: 0 0000 = Farthest up (+16 pixels)
         ...
        1 0000 = No vertical offset
         ...
        1 1111 = Farthest down (-15 pixels)*/
#define DMM 0x04 // Display Memory Mode 
#define DMAH 0x05 // Display Memory Address High 
#define DMAL 0x06 // Display Memory Address Low 
#define DMDI 0x07 // Display Memory Data In 
#define CMM 0x08 // Character Memory Mode 
#define CMAH 0x09 // Character Memory Address High 
#define CMAL 0x0a // Character Memory Address Low 
#define CMDI 0x0b // Character Memory Data In
#define OSDM 0x0c // OSD Insertion Mux 
#define RB0 0x10 // Row 0 Brightness 
#define RB1 0x11 // Row 1 Brightness 
#define RB2 0x12 // Row 2 Brightness 
#define RB3 0x13 // Row 3 Brightness 
#define RB4 0x14 // Row 4 Brightness 
#define RB5 0x15 // Row 5 Brightness 
#define RB6 0x16 // Row 6 Brightness 
#define RB7 0x17 // Row 7 Brightness 
#define RB8 0x18 // Row 8 Brightness 
#define RB9 0x19 // Row 9 Brightness 
#define RB10 0x1a // Row 10 Brightness 
#define RB11 0x1b // Row 11 Brightness 
#define RB12 0x1c // Row 12 Brightness 
#define RB13 0x1d // Row 13 Brightness 
#define RB14 0x1e // Row 14 Brightness 
#define RB15 0x1f // Row 15 Brightness 
#define OSDBL 0x6c // OSD Black Level

//Register name - Read Address
#define STAT 0x20 // Status 
#define DMDO 0x30 // Display Memory Data Out 
#define CMDO 0x40 // Character Memory Data Out

extern struct spi_ioc_transfer xfer;
extern int fd;

void writeAddrData(uint8_t addr, uint8_t data);
void writeData(uint8_t data);
void displayChar(uint8_t y, uint8_t x, uint16_t addr);
void clearOSD(void);

#endif
