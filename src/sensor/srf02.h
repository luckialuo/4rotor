#ifndef __SRF02__
#define __SRF02__


#include"uart.h"

extern  SensorStruc        ss_Srf; 
extern  FP32    height_alt,height_alt_2,height_alt_3,height_alt_4,height_speed,height_alt0,height_alt1,height_alt2,height_alt3,height_alt4,height_alt5,height_alt6;
extern  FP32    height_speed,height_speed1,height_speed2,height_speed3,height_speed4,height_speed5,height_speed6;
extern  FP32    height_alt00,height_alt10,height_alt20,height_alt30,height_alt40,height_alt50,height_alt60;  
extern  INT32U    dtime,dtime2,dtime3,dtime1,dtime4,dtime5,dtime6;
extern  FP32    srf_dZ,srf_dL,srf_ddZ,srf_ddL;   


typedef struct Data
{
  unsigned char high[256];
} DataSet;

extern DataSet ds[8];

void Task_SrfRev(void);
void Task_SrfRev2(void);
void Task_SrfRev3(void);
void Task_SrfRev4(void);
void sendBreak1(void);
void sendBreak2(void);
void sendBreak3(void);
void sendBreak4(void);
void changeAddr(void);
void SRF_Monitor(void); 
#endif