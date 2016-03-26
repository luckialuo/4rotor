#ifndef _LAW_H_
#define _LAW_H_


#define EPS         0.001f

    extern FP32     ele_cmd, ail_cmd, engine_cmd, rud_cmd;
    extern FP32     ele_var, ail_var, engine_var, rud_var;
    extern FP32     theta_cmd, gama_cmd, height_cmd, Hdot_cmd, wy_cmd;
    extern FP32     theta_var, gama_var, height_var, Hdot_var;
    

    extern FP32     theta_mix, gama_mix, engine_mix,engine_mix0,engine_mix1, rud_mix,theta_mix0;
    extern FP32     ail_opt,ele_opt,eng_opt,rud_opt; 
     
    extern FP32     theta_int, gama_int, H_int, Z_int, L_int;

    extern FP32     KeH, KeIH, KedH, KaIGama, KeITheta;
    extern INT16S   tag_LongSwitch, tag_SaveEleSwitch, tag_SaveEngSwitch, tag_ViHoldON, tag_opt; 

    extern FP32     height_ini;
    extern FP32     M1out, M2ont, M3out, M4ont;
    extern FP32     Wx_cmd, Wy_cmd, Wz_cmd;
    extern unsigned long KeIH_cnt;
    extern FP32     ac_ddZ,ac_ddL;

/*---------------------------------------------------------------------------*/   

typedef struct {
    FP32    min;
    FP32    max;
    FP32    ratio;           /*[��������][*100]*/ 
    FP32    offset;          /*[ƫ����]  [*100]*/   
    FP64    vol;             /*[��ѹ][V] [BP=10]*/ 
    FP32    val;             /*[������]  [BP=7]*/   
} AnalogStruc;
        

extern AnalogStruc        PWMin[6];
extern AnalogStruc        PWMout[12];

/*---------------------------------------------------------------------------*/   

void        LAW_Task(void);               /*[�����ɽ�������]*/
void        LAW_Control(void);            /*[������]*/
void        LAW_Act(void);                /*[����������ת����ÿ����������ֵ]*/
void        LAW_Out(void);                /*[ÿ����������ˢ��]*/
void        LAW_CmdSmooth(void);          /*[��̬��ָ��ͷ�������ָ�����������]*/
void        LAW_ParmInit(void);           /*[�����ɲ�����ʼ��]*/
void        LAW_GetParm(void);            /*[��ȡ����ı궨ϵ��]*/
void        LAW_SetParm(void);            /*[�������ı궨ϵ��]*/
void        LAW_Sim(void);
         

#endif

/**************************************
  
����ͨ������

com1 ��̽ӿ�
com2 
com3 GPS(RS232)
com4 
com5 AHRS(RS232)
com6 ������̨(RS232)
com7 ������/ң��ң��
com8 ��������
com9 ������

PWM���

PO1 ������      A13
PO2 �Ҹ�����      A14
PO3 ���Ŷ�        A15
PO4 ������        D15
PO5 �����        B15
PO6 �ҹ�/���     C15
PO7 ����          B14
PO8 ��ɡ          C16

PWM����

PI1 �������źŲɼ�   B18
PI2 �Ҹ������źŲɼ�   A19
PI3 ���Ŷ��źŲɼ�     D18
PI4 �������źŲɼ�     C18
PI5 ������źŲɼ�     C17
PI6 �ҹ�/����źŲɼ�  D17
PI7 �л��źŲɼ�       A18
PI8 ��ɡ�źŲɼ�       B17

���������
DO1   B4
DO2   B5

����������
DI1   C1
DI2   C2

Ƶ�ʲɼ�����
ZSIN2   B16

ģ���ź�����
ADIN3 ģ���ź�����1   A24
ADIN5 ģ���ź�����2   A23


***************************************/