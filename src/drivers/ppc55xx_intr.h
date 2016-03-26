#ifndef _PPC55XXINTR_H
#define _PPC55XXINTR_H

#include "mpc5534.h"
#include "INTCInterrupts.h"
#include <ansi_fp.h>


typedef union decimalt
	{
	     unsigned char        B[8];
	     unsigned short       UW[4];
	     unsigned long        DW[2];
         unsigned long long   VAL;	
} decimalt;

#define  ETPUA0_INT_VECTOR    68  
#define  ETPUA1_INT_VECTOR    69
#define  ETPUA2_INT_VECTOR    70  
#define  ETPUA3_INT_VECTOR    71
#define  ETPUA4_INT_VECTOR    72  
#define  ETPUA5_INT_VECTOR    73
#define  ETPUA6_INT_VECTOR    74  
#define  ETPUA7_INT_VECTOR    75
#define  ETPUA8_INT_VECTOR    76  
#define  ETPUA9_INT_VECTOR    77
#define  ETPUA10_INT_VECTOR   78  
#define  ETPUA11_INT_VECTOR   79
#define  ETPUA12_INT_VECTOR   80  
#define  ETPUA13_INT_VECTOR   81
#define  ETPUA14_INT_VECTOR   82  
#define  ETPUA15_INT_VECTOR   83
#define  ETPUA16_INT_VECTOR   84
#define  ETPUA17_INT_VECTOR   85
#define  ETPUA18_INT_VECTOR   86
#define  ETPUA19_INT_VECTOR   87
#define  ETPUA20_INT_VECTOR   88 
#define  ETPUA21_INT_VECTOR   89  
#define  ETPUA22_INT_VECTOR   90
#define  ETPUA23_INT_VECTOR   91  
#define  ETPUA24_INT_VECTOR   92
#define  ETPUA25_INT_VECTOR   93  
#define  ETPUA26_INT_VECTOR   94
#define  ETPUA27_INT_VECTOR   95  
#define  ETPUA28_INT_VECTOR   96
#define  ETPUA29_INT_VECTOR   97  
#define  ETPUA30_INT_VECTOR   98
#define  ETPUA31_INT_VECTOR   99  


#define  EMIOS0_INT_VECTOR    51
#define  EMIOS1_INT_VECTOR    52
#define  EMIOS2_INT_VECTOR    53
#define  EMIOS3_INT_VECTOR    54
#define  EMIOS4_INT_VECTOR    55
#define  EMIOS5_INT_VECTOR    56
#define  EMIOS6_INT_VECTOR    57
#define  EMIOS7_INT_VECTOR    58
#define  EMIOS8_INT_VECTOR    59
#define  EMIOS9_INT_VECTOR    60
#define  EMIOS10_INT_VECTOR   61
#define  EMIOS11_INT_VECTOR   62
#define  EMIOS12_INT_VECTOR   63
#define  EMIOS13_INT_VECTOR   64
#define  EMIOS14_INT_VECTOR   65
#define  EMIOS15_INT_VECTOR   66

#define  EMIOS16_INT_VECTOR   202
#define  EMIOS17_INT_VECTOR   203
#define  EMIOS18_INT_VECTOR   204
#define  EMIOS19_INT_VECTOR   205
#define  EMIOS20_INT_VECTOR   203
#define  EMIOS21_INT_VECTOR   207
#define  EMIOS22_INT_VECTOR   208
#define  EMIOS23_INT_VECTOR   209


#define  ESCIA_INT_VECTOR   146
#define  ESCIB_INT_VECTOR   149


void intInit(void);                          // 中断初始化
void disableIrq(void); 
void enableIrq(void);
void initPll(void);                          // 系统时钟倍频初始化

double dec2num_matrix(const decimalt *d);    // 64位整型 (IEEE double 格式) 转 浮点 

#endif

