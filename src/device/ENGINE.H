#ifndef _ENGINE_H_
#define _ENGINE_H_

#define PW_EngineNone      0                      /*[无定义]*/
#define PW_EngineLarge     1                      /*[发动机大车状态]*/
#define PW_EngineNominal   2                      /*[发动机额定状态]*/
#define PW_EngineCruise    3                      /*[发动机巡航状态]*/
#define PW_EngineSlow      4                      /*[发动机慢车状态]*/
#define PW_EngineStop      5                      /*[发动机停车状态]*/
#define PW_EnginePlus      6                      /*[发动机加力状态]*/

extern	FP32       engine_val;	      /*[发动机油门]*/
extern  INT16U           RPM_eng;                    /*[发动机转速](RPM)*/
extern  INT8U         mode_eng;                    /*[当前发动机状态]*/
extern  INT8U        OnStop_eng;                   /*[预停车有效标志][1=有效][0=无效]*/
extern  FP32         parm_eng[8];                 /*[发动机状态参数][%]*/

void    ENG_Plus (void);
void    ENG_Large(void);                          /*[发动机大车状态]*/
void    ENG_Nominal(void);                        /*[发动机额定状态]*/
void    ENG_Cruise(void);                         /*[发动机巡航状态]*/
void    ENG_Slow(void);                           /*[发动机慢车状态]*/
void    ENG_Stop(void);                           /*[发动机停车状态]*/
void    ENG_SetParm(void);                        /*[设置发动机状态参数]*/
void    ENG_GetParm(void);                        /*[读取发动机状态参数]*/
void    ENG_fpm(void);

#endif
