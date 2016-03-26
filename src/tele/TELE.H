#ifndef _TELE_H_
#define _TELE_H_

extern  INT8U    YEAR,MONTH,DAY,HOUR,MIN,SEC;
extern  INT8U           RemoteCmd,                /*[离散遥控指令]*/
                       RemoteCode;                /*[遥控指令回报]*/
extern  INT8U           echo_tele;                /*[回馈标志]*/
extern  SensorStruc         tele;
extern  SensorStruc         vision;
extern  SensorStruc         vision0;
extern  FP32           vision_dZ,vision_dL,vision_dPsi,vision_dH,dv_dZ,dv_dL,vision_dZ0,vision_dL0;
extern  INT32U         dtime_vis;

        void        TELE_TaskRx(void);            /*[遥控和地面检测上行链接收任务][Task]*/

        void        TELE_RxMan(INT8U Buf[]);      /*[对遥控数据帧进行综合处理]*/
        void        TELE_Monitor(void);           /*[遥控数据链监控][100ms调度]*/

        void        TELE_TaskTx(void);            /*[遥测和地面检测下行发送任务][Task]*/
        void        TELE_TxMan(void);             /*[遥测数据帧发送管理]*/
        void        TELE_FrameA(INT8U Buf[]);     /*[遥测数据A帧]*/
        void        TELE_FrameB(INT8U Buf[]);     /*[遥测数据B帧]*/
        void        Vision_RxMan(INT8U Buf[]);

        
#endif





