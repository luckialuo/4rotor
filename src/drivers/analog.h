#ifndef __ANALOG__
#define __ANALOG__

#include "startup\includes.h"

#define ANALOGINCH1     3       /*MPX5004 ���ټ�*/
#define ANALOGINCH2     2       /*MPX6115 �߶ȼ�*/
#define ANALOGINCH3     6       /*��ص���*/
#define ANALOGINCH4     24      /*��ص�ѹ*/



void   AnalogInit(void);  
short  AnalogIn(unsigned char ch, float *volts);   // *volts   Ϊ 0.0~5.0 V

#endif