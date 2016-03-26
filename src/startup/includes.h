#ifndef _INCLUDES_H_
#define _INCLUDES_H_

typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned long  INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   long  INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */
typedef unsigned char  UINT8;

typedef unsigned char   BOOLEAN;
typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned long   DWORD;


#define LOBYTE(w)       ((BYTE)(w))
#define HIBYTE(w)       ((BYTE)(((UINT)(w) >> 8) & 0xFF))

#define NULL 0


#define TRUE   1
#define FALSE  0

/*
typedef union {
    BYTE    B[4];
    short   D[2];
    WORD    W[2];
    long    DW;
    unsigned long UDW;
} dWordStruc;


typedef struct  {
    WORD        invalid;
    WORD        counter;
    int         fail;       
    WORD        freq;
} SensorStruc;

*/

#include <ansi_fp.h>
#include "stdio.h"
#include "stdlib.h"

#include "mpc5534\mpc5534.h"                    
#include "drivers\nvram.h"  
#include "drivers\ppc55xx_intr.h"
#include "drivers\spiflash.h"
#include "drivers\time.h"  
#include "drivers\ppc_oscom.h"  
#include "drivers\etpu_init.h"
#include "drivers\uart.h"
#include "drivers\led.h" 
#include "drivers\mpwm.h"            
#include "startup\init.h"
#include "drivers\analog.h"

#endif