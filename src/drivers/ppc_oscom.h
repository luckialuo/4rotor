#ifndef _PPC_OSCOM_
#define _PPC_OSCOM_

#include <stdio.h>
#include "mpc5534.h"

/* DLL/DLM (Divisor Latch) data table (Clock 50MHz) */
#define	DL_1200		((SYS_CLOCK_FREQ/8/(1200)+1)/2)	/*   1200 baud */
#define	DL_2400		((SYS_CLOCK_FREQ/8/(2400)+1)/2)		/*   2400 baud */
#define	DL_4800		((SYS_CLOCK_FREQ/8/(4800)+1)/2)		/*   4800 baud */
#define	DL_9600		((SYS_CLOCK_FREQ/8/(9600)+1)/2)		/*   9600 baud */
#define	DL_19200	((SYS_CLOCK_FREQ/8/(19200)+1)/2)		/*  19200 baud */
#define	DL_38400	((SYS_CLOCK_FREQ/8/(38400)+1)/2)		/*  38400 baud */
#define	DL_57600	((SYS_CLOCK_FREQ/8/(57600)+1)/2)		/*  57600 baud */
#define	DL_115200	((SYS_CLOCK_FREQ/8/(115200)+1)/2)		/* 115200 baud */

#define  COM1           0


#define  COM_PARITY_NONE        0               /*[Defines for setting parity]*/
#define  COM_PARITY_EVEN        1
#define  COM_PARITY_ODD         2

#define  PPC_ComTxBuffSize 256

typedef struct {
    unsigned char   Rxhead,Rxtail,RxBuf[PPC_ComTxBuffSize];
    unsigned char   Txhead,Txtail;
    unsigned char   TxBuf[PPC_ComTxBuffSize];
} CommStruc;

extern CommStruc            COM[1];

void    PPC_Com1Init(unsigned long BaudRate,unsigned char ParityMode);
unsigned char   PPC_Com1In (unsigned char Buf[], unsigned char len);
unsigned char   PPC_Com1Out(unsigned char Buf[], unsigned char len);
unsigned char   PPC_Com1RxLen(void);
unsigned char   PPC_Com1TxLen(void);
void    PPC_Com1EnableInterrupt(void);
void    PPC_Com1InterruptHandler(void);

#endif
