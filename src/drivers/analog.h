#ifndef __ANALOG__
#define __ANALOG__

#include "startup\includes.h"

#define ANALOGINCH1     3       /*MPX5004 空速计*/
#define ANALOGINCH2     2       /*MPX6115 高度计*/
#define ANALOGINCH3     6       /*电池电流*/
#define ANALOGINCH4     24      /*电池电压*/



void   AnalogInit(void);  
short  AnalogIn(unsigned char ch, float *volts);   // *volts   为 0.0~5.0 V

#endif