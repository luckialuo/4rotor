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
    FP32    ratio;           /*[比例因子][*100]*/ 
    FP32    offset;          /*[偏移量]  [*100]*/   
    FP64    vol;             /*[电压][V] [BP=10]*/ 
    FP32    val;             /*[物理量]  [BP=7]*/   
} AnalogStruc;
        

extern AnalogStruc        PWMin[6];
extern AnalogStruc        PWMout[12];

/*---------------------------------------------------------------------------*/   

void        LAW_Task(void);               /*[控制律解算任务]*/
void        LAW_Control(void);            /*[控制律]*/
void        LAW_Act(void);                /*[将气动舵面转换化每个舵机的输出值]*/
void        LAW_Out(void);                /*[每个舵机的输出刷新]*/
void        LAW_CmdSmooth(void);          /*[姿态角指令和发动机角指令的软化计算]*/
void        LAW_ParmInit(void);           /*[控制律参数初始化]*/
void        LAW_GetParm(void);            /*[获取舵机的标定系数]*/
void        LAW_SetParm(void);            /*[保存舵机的标定系数]*/
void        LAW_Sim(void);
         

#endif

/**************************************
  
串口通道定义

com1 编程接口
com2 
com3 GPS(RS232)
com4 
com5 AHRS(RS232)
com6 数传电台(RS232)
com7 地面检测/遥控遥测
com8 备用数传
com9 红外测距

PWM输出

PO1 左副翼舵      A13
PO2 右副翼舵      A14
PO3 油门舵        A15
PO4 升降舵        D15
PO5 方向舵        B15
PO6 挂钩/点火     C15
PO7 备用          B14
PO8 开伞          C16

PWM输入

PI1 左副翼舵信号采集   B18
PI2 右副翼舵信号采集   A19
PI3 油门舵信号采集     D18
PI4 升降舵信号采集     C18
PI5 方向舵信号采集     C17
PI6 挂钩/点火信号采集  D17
PI7 切换信号采集       A18
PI8 开伞信号采集       B17

开关量输出
DO1   B4
DO2   B5

开关量输入
DI1   C1
DI2   C2

频率采集输入
ZSIN2   B16

模拟信号输入
ADIN3 模拟信号输入1   A24
ADIN5 模拟信号输入2   A23


***************************************/
