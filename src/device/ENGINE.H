#ifndef _ENGINE_H_
#define _ENGINE_H_

#define PW_EngineNone      0                      /*[�޶���]*/
#define PW_EngineLarge     1                      /*[��������״̬]*/
#define PW_EngineNominal   2                      /*[�������״̬]*/
#define PW_EngineCruise    3                      /*[������Ѳ��״̬]*/
#define PW_EngineSlow      4                      /*[����������״̬]*/
#define PW_EngineStop      5                      /*[������ͣ��״̬]*/
#define PW_EnginePlus      6                      /*[����������״̬]*/

extern	FP32       engine_val;	      /*[����������]*/
extern  INT16U           RPM_eng;                    /*[������ת��](RPM)*/
extern  INT8U         mode_eng;                    /*[��ǰ������״̬]*/
extern  INT8U        OnStop_eng;                   /*[Ԥͣ����Ч��־][1=��Ч][0=��Ч]*/
extern  FP32         parm_eng[8];                 /*[������״̬����][%]*/

void    ENG_Plus (void);
void    ENG_Large(void);                          /*[��������״̬]*/
void    ENG_Nominal(void);                        /*[�������״̬]*/
void    ENG_Cruise(void);                         /*[������Ѳ��״̬]*/
void    ENG_Slow(void);                           /*[����������״̬]*/
void    ENG_Stop(void);                           /*[������ͣ��״̬]*/
void    ENG_SetParm(void);                        /*[���÷�����״̬����]*/
void    ENG_GetParm(void);                        /*[��ȡ������״̬����]*/
void    ENG_fpm(void);

#endif