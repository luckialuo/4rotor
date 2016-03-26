#include "MPC.H"
#include <time.h>

static  INT16S     TimerTick;
INT8U   YEAR,MONTH,DAY,HOUR,MIN,SEC;

void  TEST_TxMan (void)
{
	static  INT16S     TimerTick;

    static  INT16S      count;
            INT16S      Tx[3], idx;
    INT8U    Buf[40];

    count = (count+1) % 100;    
    
    if ((count%5)==0)   Tx[0]=True;      //[200ms]
    else                Tx[0]=False;     
    if ((count%12)==0)  Tx[1]=True;      //[500ms]
    else                Tx[1]=False;
    if ((count%12)==1)  Tx[2]=True;      //[500ms]
    else                Tx[2]=False;


	
    for (idx=0;idx<3;idx++) {
        if (Tx[idx]) {
            switch (idx) {
                case 0: TEST_Frame1(Buf);  break;
                case 1: TEST_Frame2(Buf);  break;
                case 2: TEST_Frame3(Buf);  break;
            }     
            MakeCheckSum(Buf, sizeof(Buf));
           	UartCom2Out(Buf, sizeof(Buf)); 
          
		
        }    
    }
}

void  TEST_Frame1 (INT8U Buf[])
{
    dWordStruc  src;

    Buf[0]=0xEB;
    Buf[1]=0x90;
    Buf[2]='1';

    src.D[0]=(INT16S  )( theta_gyo*10);   Buf[3] =src.B[1];  Buf[4] =src.B[0];      /*[俯仰角]*/
    src.D[0]=(INT16S  )(  gama_gyo*10);   Buf[5] =src.B[1];  Buf[6] =src.B[0];    /*[滚转角]*/
    src.W[0]=(INT16U ) (   psi_hmr*10);   Buf[7] =src.B[1];  Buf[8] =src.B[0];      /*[磁航向]*/
    src.D[0]=(INT16S  )(    Wx_gyo*10);   Buf[9] =src.B[1];  Buf[10]=src.B[0];     /*[滚转角速率]*/
    src.D[0]=(INT16S  )(    Wy_gyo*10);   Buf[11]=src.B[1];  Buf[12]=src.B[0];    /*[偏航角速率]*/
    src.D[0]=(INT16S  )(    Wz_gyo*10);   Buf[13]=src.B[1];  Buf[14]=src.B[0];    /*[俯仰角速率]*/
 
    src.W[0]=(INT16S  )(height_adc*10);    Buf[15]=src.B[1];  Buf[16]=src.B[0];                   /*[气压高度]*/
    src.W[0]=(INT16U )(    Vi_adc*10);     Buf[17]=src.B[1];                                                   /*[指示空速]*/   
    src.W[0]=(INT16S  )((alt_gps)*10);   Buf[18]=src.B[1];  Buf[19]=src.B[0];     /*[红外高度]*/

    src.D[0]=(INT16S  )(PWMout[0].val*10);    Buf[20]=src.B[1];  Buf[21]=src.B[0];     /*[左副翼舵机]*/  
    src.D[0]=(INT16S  )(PWMout[5].val*10);    Buf[22]=src.B[1];  Buf[23]=src.B[0];     /*[前轮舵机]*/
    src.W[0]=(INT16U  )(PWMout[2].val*2);     Buf[24]=src.B[1];                                  /*[油门开度]*/   
    src.D[0]=(INT16S  )(PWMout[3].val*10);    Buf[25]=src.B[1];  Buf[26]=src.B[0];     /*[升降舵机]*/ 
    src.D[0]=(INT16S  )(PWMout[4].val*10);    Buf[27]=src.B[1];  Buf[28]=src.B[0];     /*[方向舵机]*/

    src.W[0]=( INT16U )(PWMin[3].vol*1000);    Buf[29]=src.B[1];  Buf[30]=src.B[0];                       /*[副翼]*/
    src.W[0]=( INT16U )(PWMin[4].vol*1000);    Buf[31]=src.B[1];  Buf[32]=src.B[0];                       /*[升降舵]*/
    src.W[0]=( INT16U )(PWMin[5].vol*1000);    Buf[33]=src.B[1];  Buf[34]=src.B[0];                       /*[油门开度]*/
    src.W[0]=( INT16U )(PWMin[0].vol*1000);    Buf[35]=src.B[1];  Buf[36]=src.B[0];                       /*[方向舵]*/
    src.W[0]=( INT16U )(PWMin[2].vol*1000);    Buf[37]=src.B[1];  Buf[38]=src.B[0];                       /*[安控]*/                                                                            
}                                                                               

void  TEST_Frame2 (INT8U Buf[])
{
    dWordStruc  src;

    Buf[0]=0xEB;
    Buf[1]=0x90;
    Buf[2]='2';

    src.DW=(INT32S   )(lon_gps*1e6);        Buf[3] =src.B[3];  Buf[4] =src.B[2];    /*[经度]*/
                                            Buf[5] =src.B[1];  Buf[6] =src.B[0];
    src.DW=(INT32S   )(lat_gps*1e6);        Buf[7] =src.B[3];  Buf[8] =src.B[2];     /*[纬度]*/
                                            Buf[9] =src.B[1];  Buf[10]=src.B[0];
    src.W[0]=(INT16S  )(  Vd_gps*10);       Buf[11]=src.B[1];                                  /*[地速]*/
    src.W[0]=(INT16S  )( psi_gps*10);       Buf[12]=src.B[1];  Buf[13]=src.B[0];     /*[航迹角]*/
    src.D[0]=(INT16S  )( alt_gps*10);       Buf[14]=src.B[1];  Buf[15]=src.B[0];       /*[海拔高度]*/
    src.D[0]=(INT16S  )(Hdot_gps*10);       Buf[16]=src.B[1];  Buf[17]=src.B[0];    /*[升降速度]*/
                                            Buf[18]=used_gps;                       /*[可见星数]*/
                                            Buf[19]=hms_gps[0];      /*[GMT:hh]*/
                                            Buf[20]=hms_gps[1];      /*[GMT:mm]*/
                                            Buf[21]=hms_gps[2];      /*[GMT:ss]*/

    src.D[0]=(INT16S  )(gdop_gps*100);    Buf[22]=src.B[1];  Buf[23]=src.B[0];    /*[GDOP]*/
    src.D[0]=(INT16S  )(pdop_gps*100);    Buf[24]=src.B[1];  Buf[25]=src.B[0];    /*[PDOP]*/
    src.D[0]=(INT16S  )(hdop_gps*100);    Buf[26]=src.B[1];  Buf[27]=src.B[0];    /*[HDOP]*/
    src.D[0]=(INT16S  )(vdop_gps*100);    Buf[28]=src.B[1];  Buf[29]=src.B[0];    /*[VDOP]*/

	//src.W[0]=(INT16U  )(AD[0].vol*10);    Buf[30]=src.B[1];  Buf[31]=src.B[0];                       /*[0＃电压]*/
    //src.W[0]=(INT16U  )(AD[1].vol*10);    Buf[32]=src.B[1];  Buf[33]=src.B[0];                       /*[1＃电压]*/
    
    //src.W[0]=( INT16U )(PWMin[1].vol*100);     Buf[34]=src.B[1];  Buf[35]=src.B[0];         /*[前轮采集]*/    
   	//src.W[0]=( INT16U )(PWMin[6].vol*100);     Buf[36]=src.B[1];  Buf[37]=src.B[0];         /*[襟翼采集]*/   
	//src.W[0]=( INT16U )(PWMin[7].vol*100);     Buf[38]=src.B[1];                            /*[切换采集]*/
  

}

void  TEST_Frame3 (INT8U Buf[])
{
    INT8U        WP[13]; 
    dWordStruc  src;
    INT16S          idx;

    Buf[0]=0xEB;
    Buf[1]=0x90;
    Buf[2]='3';

    Buf[3]=HOUR;    
    Buf[4]=MIN;
    Buf[5]=SEC; 
    Buf[6]=YEAR;
    Buf[7]=MONTH;
    Buf[8]=DAY;
    
    Buf[9]=CPULoad;
	Buf[10]=echo_test; 
    Buf[11]=0;                                                                 /*[地面检测状态字]*/
    if (tag_test)       SetBit(&Buf[11],0);
    if (on_test_load)   SetBit(&Buf[11],1);
    if (on_test_back)   SetBit(&Buf[11],2);
 
    for (idx=12;idx<27;idx++) Buf[idx]=0;
    switch (ask_cmd) {
    	
    	
    	
	   	case 0x39: /*控制律*/
						if(ask_idx<22)
						{
							Buf[12] = 0x39;
							Buf[13] = ask_idx;
						}
						break;

    	
        case 0x51: /*[A/D参数查询]*/
            if (ask_idx<4) {
                Buf[12]=0x51;
                Buf[13]=ask_idx;
                //src.D[0]=(INT16S  )(AD[ask_idx].ratio/0.01f);
                //                       Buf[14]=src.B[1];  Buf[15]=src.B[0];
                //src.D[0]=(INT16S  )(AD[ask_idx].offset/0.01f);
                //                       Buf[16]=src.B[1];  Buf[17]=src.B[0];
            }
            break;

        case 0x52: /*[PWM参数查询]*/
            if (ask_idx<8) {
                Buf[12]=0x52;
                Buf[13]=ask_idx;
                src.D[0]=(INT16S  )(PWMout[ask_idx].ratio/0.001f);					
                                       Buf[14]=src.B[1];  Buf[15]=src.B[0];
                src.D[0]=(INT16S  )(PWMout[ask_idx].offset/0.01f);
                                       Buf[16]=src.B[1];  Buf[17]=src.B[0];
            }
            break;

        case 0x53: /*[发动机参数查询]*/
            Buf[12]=0x53;
            src.D[0]=(INT16S  )(parm_eng[PW_EngineStop]/0.01f);
                                       Buf[13]=src.B[1]; Buf[14]=src.B[0];
            src.D[0]=(INT16S  )(parm_eng[PW_EngineSlow]/0.01f);
                                       Buf[15]=src.B[1]; Buf[16]=src.B[0];
            src.D[0]=(INT16S  )(parm_eng[PW_EngineCruise]/0.01f);
                                       Buf[17]=src.B[1]; Buf[18]=src.B[0];
            src.D[0]=(INT16S  )(parm_eng[PW_EngineNominal]/0.01f);
                                       Buf[19]=src.B[1]; Buf[20]=src.B[0];
            src.D[0]=(INT16S  )(parm_eng[PW_EngineLarge]/0.01f);
                                       Buf[21]=src.B[1]; Buf[22]=src.B[0];
            src.D[0]=(INT16S  )(parm_eng[PW_EnginePlus]/0.01f);
                                       Buf[23]=src.B[1]; Buf[24]=src.B[0];                                       
            break;

        case 0x54: /*[用户参数查询]*/
            Buf[12]=0x54;
            for (idx=0;idx<sizeof(UserMsg);idx++) Buf[13+idx]=UserMsg[idx];
            break;
             
        case 0x55: /*[修正配置参数]*/
            Buf[12]=0x55;   //TODO
                src.D[0]=(INT16S  )(psi_offset_hmr/0.1f);
                  Buf[13]=src.B[1]; Buf[14]=src.B[0];
             Buf[15]=(INT8U)(simu_gps);
                src.D[0]=(INT16S  )(height_ini/0.1f);
                  Buf[16]=src.B[1]; Buf[17]=src.B[0];
            break;   

        case 0x56: /*[机场跑道参数]*/
            break;   

        case 0x59: /*[控制参数]*/
            Buf[12]=0x59;   //TODO
			Buf[13]=ask_idx;
            src.D[0]=(INT16S  )(K.f[ask_idx]*100.0f);
            Buf[14]=src.B[1]; Buf[15]=src.B[0];
            break; 

        case 0x61: /*[航路数据查询]*/
            if (ask_idx) {
                Buf[12]=0x61;
                ROM_ReadWP(ask_idx, WP, sizeof(WP));
                if (WP[0]==ask_idx) {
                    for (idx=0;idx<sizeof(WP);idx++) Buf[13+idx]=WP[idx];
                }
                else  { Buf[12]=Buf[13]=0; }
            }
            break;
    }
                                              Buf[27]=dot_total;                       /*[航路点数]*/
    src.W[0]=(INT16U )(ss_AHRS.freq);         Buf[28]=src.B[1];                        /*[IMU频率]*/
    src.W[0]=(INT16U )(ss_Mpxv.freq);         Buf[29]=src.B[1];                        /*[高度空速频率]*/
    src.W[0]=(INT16U )(ss_Gps.freq);          Buf[30]=src.B[1];                        /*[GPS频率]*/
    src.W[0]=(INT16U )(ss_Srf.freq);          Buf[31]=src.B[1];                        /*[红外测高频率]*/
	//src.W[0]=(INT16U )( AD[0].val*10);        Buf[32]=src.B[1];                       /*[电源电压1]*/      
	//src.W[0]=(INT16U )( AD[1].val*10);        Buf[33]=src.B[1];                       /*[电源电压2]*/     
                                              //Buf[34]=DO;                             /*[离散输出0]*/
                                              //Buf[35]=DI;                             /*[离散输入]*/
                                              Buf[38]=TimerTick;                      /*[帧计数器]*/
}
