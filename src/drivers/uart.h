#ifndef __UART__
#define __UART__

#include "mpc5534.h"



#define  COM2           0
#define  COM3           1
#define  COM4           2
#define  COM5           3
#define  COM6           4
#define  COM7           5


#define  RS232  0
#define  RS422  1

#define  COM_PARITY_NONE        0               /*[Defines for setting parity]*/
#define  COM_PARITY_EVEN        1
#define  COM_PARITY_ODD         2

#define	BAUDRATE1200		1200	    /*   1200 baud */
#define	BAUDRATE2400		2400		/*   2400 baud */
#define	BAUDRATE4800		4800		/*   4800 baud */
#define	BAUDRATE9600		9600		/*   9600 baud */
#define	BAUDRATE19200	    19200		/*  19200 baud */
#define	BAUDRATE38400	    38400		/*  38400 baud */
#define	BAUDRATE57600	    57600		/*  57600 baud */
#define	BAUDRATE115200	    115200		/* 115200 baud */


#define  UART_ComTxBuffSize 256
                               
typedef struct {
	unsigned short  Base;
    unsigned char   Rxhead,Rxtail,RxBuf[UART_ComTxBuffSize];
    unsigned char   Txhead,Txtail;
    unsigned char   TxBuf[UART_ComTxBuffSize];
} UartStruc;


extern UartStruc      UART[6];


void           UartCom2Init(unsigned long baudRate, unsigned char mode,unsigned char  parityMode);
unsigned char  UartCom2RxLen (void);
unsigned char  UartCom2TxLen (void);
unsigned char  UartCom2In (unsigned char buf[], unsigned char len);
unsigned char  UartCom2Out(unsigned char buf[], unsigned char len);
void           UartCom3Init(unsigned long baudRate, unsigned char mode,unsigned char  parityMode);
unsigned char  UartCom3RxLen (void);
unsigned char  UartCom3TxLen (void);
unsigned char  UartCom3In (unsigned char buf[], unsigned char len);
unsigned char  UartCom3Out(unsigned char buf[], unsigned char len);
void           UartCom4Init(unsigned long baudRate, unsigned char mode,unsigned char  parityMode);
unsigned char  UartCom4RxLen (void);
unsigned char  UartCom4TxLen (void);
unsigned char  UartCom4In (unsigned char buf[], unsigned char len);
unsigned char  UartCom4Out(unsigned char buf[], unsigned char len);
void           UartCom5Init(unsigned long baudRate, unsigned char mode,unsigned char  parityMode);
unsigned char  UartCom5RxLen (void);
unsigned char  UartCom5TxLen (void);
unsigned char  UartCom5In (unsigned char buf[], unsigned char len);
unsigned char  UartCom5Out(unsigned char buf[], unsigned char len);
void           UartCom6Init(unsigned long baudRate, unsigned char mode,unsigned char  parityMode);
unsigned char  UartCom6RxLen (void);
unsigned char  UartCom6TxLen (void);
unsigned char  UartCom6In (unsigned char buf[], unsigned char len);
unsigned char  UartCom6Out(unsigned char buf[], unsigned char len);
void           UartCom7Init(unsigned long baudRate, unsigned char mode,unsigned char  parityMode);
unsigned char  UartCom7RxLen (void);
unsigned char  UartCom7TxLen (void);
unsigned char  UartCom7In (unsigned char buf[], unsigned char len);
unsigned char  UartCom7Out(unsigned char buf[], unsigned char len);


void UartInterrupt2Rx(void);
void UartInterrupt2Tx(void);
void UartInterrupt3Rx(void);
void UartInterrupt3Tx(void);
void UartInterrupt4Rx(void);
void UartInterrupt4Tx(void);
void UartInterrupt5Rx(void);
void UartInterrupt5Tx(void);
void UartInterrupt6Rx(void);
void UartInterrupt6Tx(void);
void UartInterrupt7Rx(void);
void UartInterrupt7Tx(void);

#endif

