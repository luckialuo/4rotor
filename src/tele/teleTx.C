#include "MPC.H"


static  INT16S     TimerTick;

void  TELE_TxMan (void)
{
    static  INT16S     TimerTick;
    static  INT16S      count;
    INT8U  Buf[80];
    count = (count+1)%100;    
   
        TELE_FrameA(Buf);
        MakeCheckSum(Buf, 40); 
        TELE_FrameB(&(Buf[40]));
        MakeCheckSum(&(Buf[40]), 40);  
        
        UartCom2Out(Buf, sizeof(Buf));  

}



void  TELE_TaskTx (void)
{
        //CreatTask(TELE_TaskTx, Timer100ms);
    
        if (tag_test) TEST_TxMan();
        else          TELE_TxMan();
}


void  TELE_FrameA (INT8U Buf[])
{
    dWordStruc  src;

    Buf[0]=0xEB;
    Buf[1]=0x90;
    Buf[2]='A';
 
    src.D[0]=(INT16S  )(theta_gyo*10);    Buf[ 3]=src.B[1];  Buf[ 4]=src.B[0];    /*[俯仰角]*/
    src.D[0]=(INT16S  )( gama_gyo*10);   Buf[ 5]=src.B[1];  Buf[ 6]=src.B[0];    /*[滚转角]*/
    src.W[0]=(INT16U  )(  psi_hmr*10);    Buf[ 7]=src.B[1];  Buf[ 8]=src.B[0];    /*[真航向]*/
    src.D[0]=(INT16S  )(Wx_gyo*10);       Buf[ 9]=src.B[1];  Buf[10]=src.B[0];    /*[滚转角速率]*/
    src.D[0]=(INT16S  )(Wy_gyo*10);       Buf[11]=src.B[1];  Buf[12]=src.B[0];    /*[偏航角速率]*/
    src.D[0]=(INT16S  )(Wz_gyo*10);       Buf[13]=src.B[1];  Buf[14]=src.B[0];    /*[俯仰角速率]*/

    //src.W[0]=(INT16U )(    Vi_adc*2);     Buf[15]=src.B[1];                                /*[指示空速]*/
    src.W[0]=(INT16S  )(ac_height*10);   Buf[16]=src.B[1];  Buf[17]=src.B[0];    /*[气压高度]*/
    src.W[0]=(INT16S  )(height_ini*10);   Buf[18]=src.B[1];  Buf[19]=src.B[0];    /*[初始气压高度]*/

   src.D[0]=(INT16S  )(ail_var);    Buf[20]=src.B[1];                          /*[副翼舵机]*/
    src.W[0]=(INT16U  )(engine_var);   Buf[21]=src.B[1];                   /*[油门开度]*/
    src.D[0]=(INT16S  )(ele_var);    Buf[22]=src.B[1];                         /*[升降舵机]*/
    src.D[0]=(INT16S  )(rud_var);    Buf[23]=src.B[1];                         /*[方向舵机]*/
    src.W[0]=(INT16U  )(Psi_360(psi_cmd+rud_mix));  Buf[24]=src.B[1]; Buf[15]=src.B[0]; /*[航向给定]*/
   
    src.D[0]=(INT16S  )(theta_var*2);     Buf[25]=src.B[1];                        /*[俯仰角指令]*/
    src.D[0]=(INT16S  )( gama_var*2);     Buf[26]=src.B[1];                        /*[滚转角指令]*/ 
 
    src.D[0]=(INT16S)((height_cmd+RunwayAlt_mix)*100);  Buf[27]=src.B[1];  Buf[28]=src.B[0];  /*[高度给定量]*/   
                           
    src.D[0]=(INT16S  )(H_int*10);             Buf[29]=src.B[1];                              /*[高度积分]*/
    src.D[0]=(INT16S  )(vision_dH*10);     Buf[30]=src.B[1];                               /*[高度差]*/   
                                                                   Buf[31]=echo_tele;                           /*[回馈标志]*/
                                                                   Buf[32]=RemoteCode;                     /*[遥控指令回报]*/
    src.D[0]=(INT16S  )(K_adjust*100);     Buf[33]=src.B[1];   Buf[34]=src.B[0];   /*[遥调参数回报]*/
    
    src.D[0]=(INT16S)(PWMin[0].val);    Buf[35]=src.B[1];                       /*[左副翼遥控]*/
    src.D[0]=(INT16S)(PWMin[3].val);    Buf[36]=src.B[1];                       /*[方向舵遥控]*/
    src.W[0]=(INT16U)(PWMin[2].val);   Buf[37]=src.B[1];                       /*[油门遥控]*/
    src.D[0]=(INT16S)(PWMin[1].val);    Buf[38]=src.B[1];                       /*[升降舵遥控]*/
}

void  TELE_FrameB (INT8U Buf[])
{
    dWordStruc  src;

    Buf[0]=0xEB;
    Buf[1]=0x90;
    Buf[2]='B';

    src.DW  =(INT32S)(lon_gps*1e6);    Buf[ 3]=src.B[3];  Buf[ 4]=src.B[2];             /*[经度]*/
                                                               Buf[ 5]=src.B[1];  Buf[ 6]=src.B[0];
    src.DW  =(INT32S)(lat_gps*1e6);     Buf[ 7]=src.B[3];  Buf[ 8]=src.B[2];             /*[纬度]*/
                                                               Buf[ 9]=src.B[1];  Buf[10]=src.B[0];
    src.D[0]=(INT16S  )(urg_deal_union.urg_deal_data.urg_ddL);  Buf[11]=src.B[1];  Buf[12]=src.B[0];         /* URG前向移动速率 */ 
    src.D[0]=(INT16S )(height_alt00*100);    Buf[14]=src.B[1];  Buf[15]=src.B[0];     /*[超声波高度]*/
    src.D[0]=(INT16S )(height_speed*10);    Buf[16]=src.B[1];  Buf[17]=src.B[0];     /*[升降速度]*/
    src.W[0]= used_gps;                     Buf[18]=src.B[1];        /*[可见星数]*/

    Buf[19]=mode_late + mode_long*8 + mode_vert*64;      /*[系统状态字1]*/                                                         
    Buf[20]=mode_rota;                                                           /*[系统状态字2]*/
    if (!tele.fail)     SetBit(&Buf[20],3);                                      /*[数据电台数据链通]*/
    if (!ss_AHRS.fail)  SetBit(&Buf[20],4);                               /*[AHRS数据链通]*/
    if (!urg04lx.fail)       SetBit(&Buf[20],5);                              /*[URG数据链通]*/
    if (!vision.fail)   SetBit(&Buf[20],6);                                     /*[GPS数据链通]*/    
    if (!ss_Srf.fail)   SetBit(&Buf[20],7);                                    /*[超声波数据链路]*/

    Buf[21]=0;                                                                           /*[系统状态字3]*/
    if (on_reset)                SetBit(&Buf[21],0);                          /*[复位]*/
    //if (on_takeoff)            SetBit(&Buf[21],1);                         /*[起飞]*/
    if (mode_eng==PW_EngineStop) SetBit(&Buf[21],2);       /*[发动机停车]*/
    if (on_safe)                 SetBit(&Buf[21],3);                          /*[安控状态]*/
       
    Buf[21]=Buf[21] + mode_guid*32;                
   
    Buf[22]=0;                                                                    /*[系统状态字4]*/
    if (on_sky)                SetBit(&Buf[22],0);                     /*[飞机在空中]*/
    //if (nav_guid!=PW_NavNone)  SetBit(&Buf[22],1);    /*[自主导航]*/
    if (tag_opt)               SetBit(&Buf[22],2);                      /*[辅助控制状态]*/
    //if (fail_gps)              SetBit(&Buf[22],3);                    /*[大气高度]*/
    //if (tag_ViHoldON)          SetBit(&Buf[22],4);             /*[空速控制]*/

    src.D[0]=(INT16S  )(urg_deal_union.urg_deal_data.urg_dPsi);      Buf[23] =src.B[1];  Buf[24] =src.B[0];       /*[URG偏航角]*/
                                                                                                    Buf[25] =(INT8U)urg04lx.freq;                /*[URG数据帧频率]*/
    src.D[0]=(INT16S  )(urg_deal_union.urg_deal_data.urg_dL);        Buf[26]=src.B[1];  Buf[27]=src.B[0];          /*[URG待飞距离]*/
    src.D[0]=(INT16S  )(urg_deal_union.urg_deal_data.urg_dZ);        Buf[28]=src.B[1];  Buf[29]=src.B[0];          /*[URG侧偏距]*/

    src.D[0]=(INT16S)(urg_deal_union.urg_deal_data.urg_front_point);   Buf[30]=src.B[1];  Buf[31]=src.B[0];    /* URG正前方障碍物距离 */
    src.D[0]=(INT16S)(urg_deal_union.urg_deal_data.urg_ddL);     Buf[32]=src.B[1];  Buf[33]=src.B[0];     /* URG正左方障碍物距离 */
    src.D[0]=(INT16S)(urg_deal_union.urg_deal_data.urg_ddZ);  Buf[34]=src.B[1];  Buf[35]=src.B[0];     /* URG正右方障碍物距离 */
                                                                     
    Buf[36]=tele.freq*2;                                                                                                                                             /*[上行帧频率]*/                                          

    src.D[0]=(INT16S  )(urg_deal_union.urg_deal_data.urg_ddZ);       Buf[37]=src.B[1];  Buf[38]=src.B[0];          /* URG侧向移动速率 */                           
}


