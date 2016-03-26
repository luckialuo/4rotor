#ifndef __SPIFLASH__
#define __SPIFLASH__

#include "mpc5534.h"


#define COMMANDREAD      0x3
#define COMMANDWRDI      0x4
#define COMMANDRDSR      0x5
#define COMMANDWREN      0x6
#define COMMANDSE        0xD8
#define COMMANDBE        0xC7
#define COMMANDPP        0x02
#define COMMANWRSR       0x01




void   SpiFlashInit(void);
void   SpiFlashEraseSector(unsigned long flashAdrs);
void   SpiFlashProg(unsigned long flashAdrs,unsigned long val);
unsigned long SpiFlashRead(unsigned long flashAdrs);
#endif
