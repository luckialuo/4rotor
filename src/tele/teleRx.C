#include "MPC.H"

/*--------------------------------------------------------------------------*/

     INT8U           RemoteCmd,
                    RemoteCode;
     INT8U           echo_tele;
     SensorStruc         tele;
     SensorStruc         vision;
     SensorStruc         vision0;
     FP32           vision_dZ,vision_dL,vision_dPsi,vision_dH,dv_dZ,dv_dL,vision_dZ0,vision_dL0;
     FP32           Arry[6];
     INT32U         dtime_vis;

/*--------------------------------------------------------------------------*/

static void  sort(INT8U a[], INT16S  len)
{
    INT16S      idx, jdx;
    INT8U    tmp;
    
    for (jdx=len-1; jdx>0; jdx--) {
        for (idx=0; idx<jdx; idx++) {
            if (a[idx]>a[idx+1]) { tmp=a[idx]; a[idx]=a[idx+1]; a[idx+1]=tmp; }
        }
    }
}


void    Vision_RxMan(INT8U Buf[])
{   
    union { INT8U B[2]; INT16U  W; INT16S   D; } src; 
    static INT32U  win_time_vis,old_time_vis;
    static FP32   vision_dZ_old=0.0,vision_dL_old=3.8;
    
    src.B[1]=Buf[3];  src.B[0]=Buf[4];  vision_dZ0=src.D/100.0f;
    src.B[1]=Buf[5];  src.B[0]=Buf[6];  vision_dL0=src.D/100.0f;
    src.B[1]=Buf[7];  src.B[0]=Buf[8];  vision_dPsi=src.D/100.0f;
    src.B[1]=Buf[9];  src.B[0]=Buf[10]; vision_dH=src.D/100.0f;
    //src.B[1]=Buf[11]; src.B[0]=Buf[12]; dv_dZ=src.D/100.0f;
    //src.B[1]=Buf[13]; src.B[0]=Buf[14]; dv_dL=src.D/100.0f;
    vision.fail=Buf[15];
    
    vision_dZ=-vision_dZ0*cos(ac_dPsi/Rad2Deg)-vision_dL0*sin(ac_dPsi/Rad2Deg);
    vision_dL=vision_dL0*cos(ac_dPsi/Rad2Deg)-vision_dZ0*sin(ac_dPsi/Rad2Deg);     
        
    win_time_vis = time_cnt;
    dtime_vis = win_time_vis - old_time_vis;
    
    dv_dZ=(vision_dZ-vision_dZ_old)/(dtime/1000.0);
    dv_dZ=MidVal(dv_dZ,-0.5f,0.5f); 
    dv_dL=(vision_dL-vision_dL_old)/(dtime/1000.0);
    dv_dL=MidVal(dv_dL,-0.5f,0.5f); 
    
    vision_dZ_old=vision_dZ;
    vision_dL_old=vision_dL;
    old_time_vis=win_time_vis;
          
            

}




void    TELE_RxMan(INT8U Buf[])
{
    union { INT8U B[2]; INT16U  W; INT16S   D; } src;         
    INT8U    a[5];
    INT16S   idx, f1,f2,f3;
    INT8S    val;
    INT8U    WP[13];

    echo_tele = Buf[18];
    
    if (Buf[3]==0xCC) {       /*cmd参数*/
        for (idx=0; idx<5; idx++) a[idx]=Buf[4+idx];
        sort(a,5);
        f1 = (a[0]==a[1]) && (a[1]==a[2]);
        f2 = (a[1]==a[2]) && (a[2]==a[3]);
        f3 = (a[2]==a[3]) && (a[3]==a[4]);
        if (f1 || f2 || f3) {
            RemoteCmd = TELE_GetCmd(a[2]); RemoteCode=RemoteCmd;
            TELE_CheckCmd(RemoteCmd); 
        }
    }
    else if(Buf[3]==0xBB ) {
    if(Buf[4]==7)
    {
        if (Buf[5]<=(dot_total+1)) {
        for (idx=0;idx<sizeof(WP);idx++) WP[idx]=Buf[5+idx];
        ROM_WriteWP(Buf[5], WP, sizeof(WP));
        if(Buf[5]==(dot_total+1)) dot_total= Buf[5];RemoteCode = 0x07;

            }
    }
    else if(Buf[4]==3)          /*油门设置*/
    {
            src.B[1]=Buf[5];
            src.B[0]=Buf[6];    parm_eng[PW_EngineStop]   =src.W/100.0f;
            src.B[1]=Buf[7];
            src.B[0]=Buf[8];    parm_eng[PW_EngineSlow]   =src.W/100.0f;
            src.B[1]=Buf[9];
            src.B[0]=Buf[10];   parm_eng[PW_EngineCruise] =src.W/100.0f;
            src.B[1]=Buf[11];
            src.B[0]=Buf[12];   parm_eng[PW_EngineNominal]=src.W/100.0f;             
            src.B[1]=Buf[13];
            src.B[0]=Buf[14];   parm_eng[PW_EngineLarge] = src.W/100.0f;
            src.B[1]=Buf[15];
            src.B[0]=Buf[16];   parm_eng[PW_EnginePlus] = src.W/100.0f;
            RemoteCode = 0x03;
    }
    }
            

    if (Buf[9]==0xAA) {  /*控制律参数*/
        if( Buf[10]>=0x12 && Buf[10]<=0x30) {              
                src.B[1]= Buf[11]; src.B[0]= Buf[12];
                K_mix.f[Buf[10]-0x12]=src.D/100.0f; K.f[Buf[10]-0x12] =K0.f[Buf[10]-0x12] +K_mix.f[Buf[10]-0x12];
                RemoteCode = Buf[10]+0xD0; K_adjust =K.f[Buf[10]-0x12];
                
                if(K.P.KeH>EPS) {KeH =K.P.KeH; KedH =K.P.KedH; KeIH =K.P.KeIH;}
                if(K.P.Kagama>EPS)  {KaIGama=K.P.KaIGama;}
                if(K.P.Ketheta>EPS) {KeITheta=K.P.KeITheta;}
                
                if(fabs(K.P.Kagama)<EPS)   K.P.Kagama=0.01f;
                if(fabs(K.P.Ketheta)<EPS)  K.P.Ketheta=0.01f;   

        }
        else {
        switch (Buf[10]) {
            case 1: /*[点号遥调][1~10]*/
                if (Buf[11]<=dot_total) {
                        //GUID_Exit();
                        if (WP_GetLine(Buf[11], &AB)) {
                            ac_dot = Buf[11];
                            //step_enter=0;    nav_guid=PW_NavEnter;
                            RemoteCode = 0xF1;
                         }  
                }
                break;

            case 2: /*[航向遥调][0~360][deg]*/
                src.B[1]= Buf[11];
                src.B[0]= Buf[12];
                if (src.W<3600) {
                    if ((nav_guid==PW_NavNone) && (mode_guid==PW_GuideDim1)) {
                         psi_cmd=src.W*0.1f;
                         RemoteCode = 0xF2;
                    }
                }
                break;            
                
            case 3: /*[俯仰角遥调][-10~+10][deg]*/
                val=(INT8S)(Buf[11]);
                if (fabs(val)<=120.0f)  { theta_mix = val*0.1f;  RemoteCode = 0xF3; }
                break;

            case 4: /*[滚转角遥调][-10~+10][deg]*/
                val=(INT8S)Buf[11];
                if (fabs(val)<=120.0f)  {  gama_mix = val*0.1f;  RemoteCode = 0xF4; }
                break;
            
            case 5: /*[油门开度遥调][-20~+20][%]*/
                val =(INT8S)Buf[11];
                if (fabs(val)<=80.0f)  { engine_mix1 = val;       RemoteCode = 0xF5; }
                break; 

            case 6: /*[侧偏遥调][-125~+125][cm]*/
                val=(INT8S)Buf[11];
                if (abs(val)<=125.0f)  { dZ_mix=(float)val;      RemoteCode = 0xF6; }
                break;    

            case 7: /*[场高遥调][-500~+500][m]*/
                src.B[1]=Buf[11]; 
                src.B[0]=Buf[12];
                if ((src.D>=-5000) && (src.D<=5000))
                    {  RunwayAlt_mix=src.D*0.01f;     
                       RemoteCode = 0xF7; 
                     }
                break; 

            case 8: /*[轨迹线遥调][-12.7~+12.7][deg]*/
                val=(INT8S)Buf[11];
                if (abs(val)<=127)   {  gama1_AoL_mix =val*0.1f;  RemoteCode = 0xF8; }
                break;    
                         
            case 9: /*[空速遥调/前进角遥调]*/
                val=(INT8S)Buf[11];
                if (abs(val)<=10)   {  
                theta_mix0=(float)val;  
                RemoteCode = 0xF9; }
                break;  
                
            case 10: /*待飞遥调*/
                val=(INT8S)Buf[11];
                if ((val>=-50)&&(val<=100))   {  dL_mix=(float)val;  RemoteCode = 0xFA; }
                break; 
                
            case 11: /*[方向舵/着陆俯仰角遥调]*/
                src.B[1]= Buf[11];
                src.B[0]= Buf[12];
                if ((src.D<=18000.0)&&(src.D>=-18000.0)) {
                rud_mix=src.D*0.01f;
                RemoteCode = 0xFB;
                }
                break;

            case 12: /*[点号删除]*/
                if(Buf[11]>0 && Buf[11]<dot_total) 
                { dot_total= Buf[11]; RemoteCode = 0xFC;}
                break;


                         
        }
        }
    }
}


void    TELE_TaskRx(void)
{
    static INT8U    buf[256];
    static INT8U  head=0, tail=0, ptr, len;
    static INT8U    LINK[20];
    static INT8U  check, tmp;
    static INT8U   numread, RxBufferLen, idx,idxx;

    
        RxBufferLen = UartCom2RxLen();
        numread = RxBufferLen>20 ? 20:RxBufferLen;
        if (numread) {
           UartCom2In(LINK, numread);  //从com7口收数传数据
           for (idx=0; idx<numread; idx++) buf[head++]=LINK[idx];
        }
        
        
        len=head-tail; 
        while (len>=sizeof(LINK)) {
            tmp = tail+1;
            if ((buf[tail]==0xEB) && (buf[tmp]==0x90)) {
                ptr=tail; for (idx=0;idx<sizeof(LINK);idx++) LINK[idx]=buf[ptr++];
                check=0;  for (idx=0;idx<sizeof(LINK);idx++) check+=LINK[idx];
                
                if (check==0) {
                    tail += sizeof(LINK);
                    if (LINK[2]=='A') {
                        TELE_RxMan(LINK); tele.invalid=tele.fail=0; tele.counter++;
                        TELE_TxMan();  
                        tag_test = False;
                    }
                    if (LINK[2]=='B') {
                        if (!on_sky) { 
                        TEST_RxMan(LINK);                        
                        if (tag_test)TEST_TxMan();
                        }
                        else  tag_test = False;
                    }
                    if (LINK[2]=='C') {
                        Vision_RxMan(LINK); 
                        vision.invalid=vision0.fail=0; vision.counter++;
                    }
                }
                else { 
                       TELE_TxMan();
                       tail++;
                      } 
            }  
            else  tail++;
            len = head -tail;
        }
}




void    TELE_Monitor(void)
{
    static INT16U     flag=0, cnt=0, old=0;

    tele.invalid +=1;    if (tele.invalid>=10) tele.fail=1;

    cnt=(cnt+1)%100;    if ((cnt%10)==0) flag=1;
    if (flag) {  
        flag=0;
        tele.freq = tele.counter-old;  old=tele.counter;
    }
}


void    VISION_Monitor(void)
{
    static INT16U     flag=0, cnt=0, old=0;

    vision.invalid +=1;    if (vision.invalid>=5) vision0.fail=1;

    cnt=(cnt+1)%100;    if ((cnt%10)==0) flag=1;
    if (flag) {  
        flag=0;
        vision.freq = vision.counter-old;  old=vision.counter;
    }
}


INT8U    TELE_GetCmd(INT8U B)
{
    INT8U    cmd=0;  
    
    switch(B){
         case 0x33: cmd =  1; break;//切入自主
         case 0x35: cmd =  2; break;//油门大车
         case 0x36: cmd =  3; break;//油门额定
         case 0x39: cmd =  4; break;//油门巡航
         case 0x3A: cmd =  5; break;//油门慢车
         case 0x3C: cmd =  6; break;//预停车
         case 0x53: cmd =  7; break;//停车
         case 0x55: cmd =  8; break;//爬升
         case 0x56: cmd =  9; break;//油门加力
         case 0x59: cmd = 10; break;//平飞
         case 0x5A: cmd = 11; break;//大气高度开
         case 0x5C: cmd = 12; break;//下滑
         case 0x63: cmd = 13; break;//辅助控制开
         case 0x65: cmd = 14; break;//辅助控制关
         case 0x69: cmd = 15; break;//左转
         case 0x6A: cmd = 16; break;//直飞
         case 0x6C: cmd = 17; break;//大气高度关
         case 0x93: cmd = 18; break;//右转
         case 0x95: cmd = 19; break;//定向
         case 0x96: cmd = 20; break;//导航
         case 0x9A: cmd = 21; break;//复原
         case 0x9C: cmd = 22; break;//GPS高度清零
         case 0xA3: cmd = 23; break;//大气高度清零
         case 0xA5: cmd = 24; break;//建立起飞角
         case 0xA6: cmd = 25; break;//起飞
         case 0xA9: cmd = 26; break;//滑行
         case 0xC3: cmd = 27; break;//速度控制开
         case 0xC5: cmd = 28; break;//速度控制关
         case 0xC6: cmd = 29; break;//悬停
         case 0xC9: cmd = 30; break;//返航

         default:   cmd = 0;  break;
    }
    return (cmd);
}


