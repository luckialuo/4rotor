#ifndef __NVRAM__
#define __NVRAM__

#include "mpc5534.h"


#define COMMANDNWREN      0x06
#define COMMANDNWRDI      0x04
#define COMMANDNRDSR      0x05
#define COMMANNWRSR       0x01
#define COMMANDNREAD      0x03
#define COMMANDNWRITE     0x02
#define COMMANDNSLEEP     0xB9
#define COMMANDNWAKE      0xAB

#define MAX_OFFSET        0x20000

void   NvramInit(void);	
long   NvramRead(unsigned long offset,unsigned short * val);
long   NvramWrite(unsigned long offset,unsigned short val);



#endif