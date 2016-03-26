#ifndef __MPWM__
#define __MPWM__

#include "mpc5534.h"

/*CPU∞ÂPWM*/
#define MPWMOUTCH1    0
#define MPWMOUTCH2    1
#define MPWMOUTCH3    2
#define MPWMOUTCH4    3
#define MPWMOUTCH5    4
#define MPWMOUTCH6    5
#define MPWMOUTCH7    6
#define MPWMOUTCH8    7
#define MPWMOUTCH9    8
#define MPWMOUTCH10   9
#define MPWMOUTCH11   10
#define MPWMOUTCH12   11

#define MPWMINCH1    0
#define MPWMINCH2    1
#define MPWMINCH3    2
#define MPWMINCH4    3
#define MPWMINCH5    4
#define MPWMINCH6    5


typedef struct{
    float pwmper;
    float pwmhi; 
	unsigned long pwmper_cnt;
	unsigned long pwmhi_cnt;
}mpwm_t;  /*unit = 1ms*/

extern mpwm_t  MPWMIN[6];
extern mpwm_t  MPWMOUT[12];


void MpwmInit(void);
int MpwmOutEnable(unsigned char channel);
int MpwmOutDisable(unsigned char channel);
int MpwmOutInit(unsigned char channel);
int MpwmOut(unsigned char channel);
int MpwmInEnable(unsigned char channel);
int MpwmInDisable(unsigned char channel);
int MpwmInInit(unsigned char channel);
int MpwmIn(unsigned char channel);
void EMIOS0Interrupt(void);
void EMIOS1Interrupt(void);
void EMIOS2Interrupt(void);
void EMIOS3Interrupt(void);
void EMIOS4Interrupt(void);
void EMIOS5Interrupt(void);
void EMIOS6Interrupt(void);
void EMIOS7Interrupt(void);
void EMIOS8Interrupt(void);
void EMIOS9Interrupt(void);
void EMIOS10Interrupt(void);
void EMIOS13Interrupt(void);

#endif
