#include "MPC.H"

/*--------------------------------------------------------------------------*/

AnalogStruc            PWMin[6];
AnalogStruc            PWMout[12];

/*---------------------------------------------------------------------------*/
    FP32     ele_cmd, ail_cmd, engine_cmd, rud_cmd;
    FP32     ele_var, ail_var, engine_var, rud_var,psi_var;
    FP32     theta_cmd, gama_cmd, height_cmd, Hdot_cmd, wy_cmd;
    FP32     theta_var, gama_var, height_var, Hdot_var;
   
    FP32     theta_mix, gama_mix, engine_mix,engine_mix0,engine_mix1, rud_mix,theta_mix0;
    FP32     ail_opt=0.0f,ele_opt=0.0f,eng_opt=0.0f,rud_opt=0.0f; 
     
    FP32     theta_int, gama_int, H_int, Z_int, L_int;

    FP32     KeH, KeIH, KedH, KaIGama, KeITheta;
    INT16S   tag_LongSwitch=0, tag_SaveEleSwitch=0, tag_SaveEngSwitch=0, tag_ViHoldON=0, tag_opt=1; 

    FP32     height_ini;
    FP32     M1out, M2ont, M3out, M4ont;
    FP32     Wx_cmd, Wy_cmd, Wz_cmd,Hy_cmd;
    FP32     Vx_cmd, Vy_cmd, Vz_cmd;
    unsigned long KeIH_cnt=0;
    FP32     ac_ddZ,ac_ddL;
 


/*--------------------------------------------------------------------------*/

void  LAW_Task (void)   
{
   
   if (!tag_test) {
      if (!on_reset) 
      {
        LAW_Control();
      }
        LAW_Act();
      }
      
      
}


void LAW_Control(void)  //4ms 250Hz
{

    static  INT16S  flag=0, cnt=0;
    static  FP32    dH, dHI, dTheta, dGama,dPsi;
   
            
    static  const FP32    ele_unit = 2.0f,
                          ail_unit = 2.0f,
                          engine_unit =0.2f;
                          
    static  float    dZ,dIZ,dL,dIL;    
    static  INT16S    Long20ms=0, LongCNT=0,Long100ms=0;
    
    LongCNT++; LongCNT%=1000;  if ((LongCNT%5)==0) Long20ms=1;
    
    if ((LongCNT%25)==0) Long100ms=1;
    if(Long100ms)
    {
    	Long100ms=0;
    	 /*[�����ƫ����]*/ 
        dZ = ac_dZ / 100.0f;
        if(K.P.KaIZ>0.0f)
        {
           dIZ = MidVal(dZ,-5.0f,+5.0f);     /*[����ʱ��ƫ�޷���Χ+/-10m]*/
           if (fabs(dZ)<0.02f) dIZ = 0.0f;      /*[����ʱ��ƫ������Χ+/-0.5m]*/
           Z_int += K.P.KaIZ*dIZ*0.1f;         /*����Ϊ1ƫ��Ϊ1ʱ1s��5���Ƕ�*/
           Z_int = MidVal(Z_int, -10.0f, 10.0f);                  
        }
        else Z_int=0.0f;        
        
        /*[������ɾ����]*/ 
        dL = ac_dL/100.0f;
        if(K.P.Kegama>0.0f)
        {
           dIL = MidVal(dL,-5.0f,+5.0f);     /*[����ʱ��ƫ�޷���Χ+/-10m]*/
           if (fabs(dZ)<0.02f) dIL = 0.0f;      /*[����ʱ��ƫ������Χ+/-0.5m]*/
           L_int += K.P.Kegama*dIL*0.1f;         /*����Ϊ1ƫ��Ϊ1ʱ1s��5���Ƕ�*/
           L_int = MidVal(L_int, -10.0f,10.0f);                  
        }
        else L_int=0.0f;
        
        /*[����λ���⻷PID����50Hz]*/
        //Vx_cmd = -K.P.KgZ*ac_dZ / 100.0f - Z_int;   //100Ϊ�����ı���
        //gama_cmd = -K.P.Kgdpsi * (ac_ddZ - Vx_cmd);
        gama_cmd =( -K.P.KgZ*MidVal(ac_dZ, -1000.0f, 1000.0f) - K.P.Kgdpsi*ac_ddZ - Z_int)/100;        
        gama_cmd = MidVal(gama_cmd,-15.0f,15.0f);
        
        //Vy_cmd = -K.P.KgrZ*ac_dL / 100.0f- L_int;
        //theta_cmd = -K.P.Kgpsi * (ac_ddL - Vy_cmd);
        theta_cmd = (-K.P.KgrZ*MidVal(ac_dL, -1000.0f, 1000.0f)  - K.P.Kgpsi*ac_ddL - L_int)/100;
        theta_cmd = MidVal(theta_cmd,-10.0f,10.0f);
    }
   
    

   if (Long20ms) {               //20ms 50Hz
         Long20ms=0;
   
       if (K.P.KeH>0.0f) {
             ac_dH = ac_height - height_var;
             ac_dH = MidVal(ac_dH,-2.0f,+2.0f);
         }
         else ac_dH=0.0f;
         
         if (K.P.KedH>0.0f) {
             ac_Hdot = MidVal(height_speed,-2.0f,+2.0f);      
         }
         else ac_Hdot=0.0f;
    
        
         /*[����߶Ȳ����]*/     
         //if((ac_height>height_cmd + RunwayAlt_mix-0.1)&&(ac_height<height_cmd + RunwayAlt_mix+0.1))
         if((on_sky)&&(ac_height>0.35)) 
         {
            KeIH_cnt++;KeIH_cnt%=1000000000;    
         }
         if ((K.P.KeIH>0.0f)&&(KeIH_cnt>=1)) 
         {     
            dHI = MidVal(ac_dH,-2.0f,+2.0f);        /*[����ʱ�߶Ȳ��޷���Χ+/-2m]*/
            if (fabs(ac_dH)<0.02f) dHI = 0;       /*[������ΧΪ+/-0.2][deg]*/
            H_int += KeIH*dHI*0.1f;                 /*����Ϊ1ƫ��Ϊ1ʱ1s��5������*/
            H_int = MidVal(H_int,-10.0f,10.0f);
         }
         else H_int=0;
         
         /*[���ڸ߶Ȼ�·PID����50Hz]*/
         engine_cmd = -K.P.KeH*ac_dH - H_int - K.P.KedH*ac_Hdot;
         
         /*---[smoothing engine_cmd]---*/    
         if (tag_SaveEngSwitch) {
            tag_SaveEngSwitch = False;
            engine_var = PWMin[1].val;
         }
         
         
         if (engine_mix < engine_mix0) {
             engine_mix += engine_unit;
         if (engine_mix > engine_mix0) engine_mix = engine_mix0;
         }
         else {
             engine_mix -= engine_unit;
         if (engine_mix < engine_mix0)  engine_mix = engine_mix0;
         }
         
         engine_var = engine_cmd + engine_mix + eng_opt;        
        
       //here

    }
   

    if (K.P.Kgrdpsi>0.0f) {
    
        ac_dPsi = WP_Psi2Psi(ac_psi - psi_cmd - rud_mix);//-urg_dPsi1
        ac_dPsi = MidVal(ac_dPsi,-10.0f,+10.0f);
    }
    else ac_dPsi=0.0f; 
    
    
    

    
    
/////////////////////////////////////////////////////////      
   /*�����ת�ǻ���*/
         if(KaIGama>0.0f)
         {
            dGama = gama_gyo-gama_var;             /*[dGama=gama_gyo-gama_var]*/
            if (fabs(dGama)<1.0f) dGama = 0.0f;    /*[������ΧΪ+/-0.25][deg]*/
            if (dGama> 5.0f) dGama= 5.0f;          /*[�޷���ΧΪ+/-5][deg]*/
            if (dGama<-5.0f) dGama=-5.0f;
            gama_int += KaIGama*dGama*0.004f;           /*1s��10����������1*/
            gama_int = MidVal(gama_int,-5.0f,5.0f); 
         }
         else gama_int =0.0f;   
    
    
         /*[���㸩���ǻ���]*/
         if (KeITheta>0.0f) 
         { 
            dTheta = theta_gyo-theta_var;           /*[dTheta=theta_gyo-theta_var]*/
            if (fabs(dTheta)<1.0f) dTheta = 0.0f;   /*[������ΧΪ+/-0.25][deg]*/
            if (dTheta> 5.0f) dTheta= 5.0f;         /*[�޷���ΧΪ+/-5][deg]*/
            if (dTheta<-5.0f) dTheta=-5.0f;
            theta_int += KeITheta*dTheta*0.004f;          /*1s��10����������1*/
            theta_int = MidVal(theta_int,-5.0f,5.0f);
         }
         else theta_int =0.0f;
         
    /////////////////////////////////////////////  
    //��̬�⻷PI����250Hz   
    //Wx_cmd = -K.P.Kagama*(gama_gyo-gama_var)+gama_int;
    //Wz_cmd = -K.P.Ketheta*(theta_gyo-theta_var)+theta_int;
    Wy_cmd = K.P.Kgrdpsi*ac_dPsi;
      
    //��̬�ڻ�P����250Hz      
    //ail_cmd = K.P.KaWx*(Wx_gyo-Wx_cmd);
    //ele_cmd = K.P.KeWz*(Wz_gyo-Wz_cmd);   
    rud_cmd = K.P.KrWy*(Wy_gyo-Wy_cmd);
    
    ail_cmd =K.P.Kagama*(gama_gyo-gama_var) +K.P.KaWx*Wx_gyo+gama_int;
     ele_cmd =K.P.Ketheta*(theta_gyo-theta_var) +K.P.KeWz*Wz_gyo+theta_int;

    
 
    /*---[smoothing ail_cmd]---*/
    ail_var = ail_cmd;
    ail_var =  MidVal(ail_var,-25.0f,25.0f);

    /*---[smoothing ele_cmd]---*/
    ele_var = ele_cmd;  
    ele_var =  MidVal(ele_var,-25.0f,25.0f);
}

void  LAW_CmdSmooth (void)     //4ms 250Hz
{
    static const FP32    theta_unit =5.0f,//1.0f, 
                                    gama_unit = 5.0f,//1.0f,
                                    rud_unit =3.0f,//2.0f
                                    psi_unit = 3.0f,//1.0f
                                    height_unit = 0.06f;//0.02f
     FP32    theta_total, 
                 gama_total, 
                 rud_total,
                 height_total,
                 psi_rate;
   
    /*---[smoothing theta_cmd]---*/
   if (ele_opt < 4 && ele_opt > -4) {
 
    	theta_total = theta_cmd + theta_mix;
    } else {    	
    	theta_total = theta_cmd + theta_mix + ele_opt;
    }
    
    if (theta_var < theta_total) {
        theta_var += theta_unit;
        if (theta_var > theta_total)    theta_var = theta_total;
    }
    else {
        theta_var -= theta_unit;
        if (theta_var < theta_total)    theta_var = theta_total;
        
    }
   

    /*---[smoothing gama_cmd]---*/
    if (ail_opt < 4 && ail_opt > -4) {
    	gama_total = gama_cmd + gama_mix;
    } else {    	
    	gama_total = gama_cmd + gama_mix - ail_opt;
    }
    
    if (gama_var < gama_total) {
        gama_var += gama_unit;
        if (gama_var > gama_total)       gama_var = gama_total;
    }
    else {
        gama_var -= gama_unit;
        if (gama_var < gama_total)       gama_var = gama_total;
    } 
    
    /*---[smoothing height_cmd]---*/
    height_total= height_cmd + RunwayAlt_mix;
   if( height_total>1.4) height_total=1.4;//�߶�ָ���޸�1.4m
    if (height_var < height_total) {
        height_var += height_unit;
    if (height_var > height_total)    height_var = height_total;
    }
    else {
            height_var -= height_unit;
            if (height_var < theta_total)    height_var = height_total;
         } 

   
    
    
     //ң�������ں���
    psi_rate = rud_opt*2/250;   //���ƺ���仯��
    if (rud_opt < 5&& rud_opt > -5) psi_rate=0;//5�Ȳ�ת�򣬱��ֺ����ȶ�  
    psi_cmd -= psi_rate;    
    
    /*---[smoothing rud_cmd]---*/
    rud_total = rud_cmd; 
    if (rud_var < rud_total) {
        rud_var += rud_unit;
        if (rud_var > rud_total)       rud_var = rud_total;
    }
    else {
        rud_var -= rud_unit;
        if (rud_var < rud_total)       rud_var = rud_total;
    }    
    rud_var =  MidVal(rud_var,-25.0f,25.0f);
    
    
    
}


/********************************
*********************************/
/*********************************
M1  PWMOUT[3]  ���ͨ��4  A4   ����
M2  PWMOUT[2]  ���ͨ��3  A5   ����
M3  PWMOUT[5]  ���ͨ��6  A6   ����
M4  PWMOUT[6]  ���ͨ��7  A7   ����

Mode Xģʽ

    M2   M1
          X   
    M3   M4
    
���Ϊ-,�ҹ�Ϊ+;
����Ϊ+,�¸�Ϊ-;
��ƫΪ+,��ƫΪ-;

ail��+��-;
ele��-��+;
eng��+��-;
rud��-��+;

M1,M3��ʱ��
M2,M4˳ʱ��
*********************************/
void  LAW_Act (void)
{

  
    PWMout[0].val = MidVal(ail_var, PWMout[0].min, PWMout[0].max);            //ailerion
    PWMout[1].val = MidVal(ele_var, PWMout[1].min, PWMout[1].max);            //elevator
    PWMout[2].val = MidVal(engine_var, PWMout[2].min, PWMout[2].max);         //engine
    PWMout[3].val = MidVal(rud_var, PWMout[3].min, PWMout[3].max);            //rudder
    
    //Xģʽ
    M1out=PWMout[2].val + PWMout[0].val - PWMout[1].val + PWMout[3].val;
    M2ont=PWMout[2].val - PWMout[0].val - PWMout[1].val - PWMout[3].val;
    M3out=PWMout[2].val - PWMout[0].val + PWMout[1].val + PWMout[3].val;
    M4ont=PWMout[2].val + PWMout[0].val + PWMout[1].val - PWMout[3].val;
    

}



void LAW_Out(void)   //10ms
{
   INT8U i=0;
    
   if(!on_DA_volts)
   {    
    //PWMout[0].vol=(M1out*PWMout[0].ratio+PWMout[0].offset+1.0);           /*M1*/
    //PWMout[1].vol=(M2ont*PWMout[1].ratio+PWMout[1].offset+1.0);           /*M2*/
    //PWMout[2].vol=(M3out*PWMout[2].ratio+PWMout[2].offset+1.0);           /*M3*/      
    //PWMout[3].vol=(M4ont*PWMout[3].ratio+PWMout[3].offset+1.0);           /*M4*/
    
    PWMout[0].vol=(M1out*0.01+1.0);           /*M1*/
    PWMout[1].vol=(M2ont*0.01+1.0);           /*M2*/
    PWMout[2].vol=(M3out*0.01+1.0);           /*M3*/    
    PWMout[3].vol=(M4ont*0.01+1.0);           /*M4*/
        
   }
   if(on_safe)  { 
  
      //Xģʽ
      MPWMOUT[3].pwmhi = MidVal(((PWMin[2].val + PWMin[0].val + PWMin[1].val  - PWMin[3].val)*0.01+1.0),1.00,1.90); /*M1 ����A4*/
      MPWMOUT[2].pwmhi = MidVal(((PWMin[2].val  - PWMin[0].val + PWMin[1].val + PWMin[3].val)*0.01+1.0),1.00,1.90); /*M2 ����A5*/
      MPWMOUT[5].pwmhi = MidVal(((PWMin[2].val  - PWMin[0].val  - PWMin[1].val  - PWMin[3].val)*0.01+1.0),1.00,1.90); /*M3 ����A6*/    
      MPWMOUT[6].pwmhi = MidVal(((PWMin[2].val + PWMin[0].val  - PWMin[1].val + PWMin[3].val)*0.01+1.0),1.00,1.90); /*M4 ����A7*/
      
   }
   else 
   {
      MPWMOUT[3].pwmhi = MidVal(PWMout[0].vol + PWMout[4].offset*0.1,1.00,1.90);    /*M1*/
      MPWMOUT[2].pwmhi = MidVal(PWMout[1].vol + PWMout[5].offset*0.1,1.00,1.90);    /*M2*/
      MPWMOUT[5].pwmhi = MidVal(PWMout[2].vol + PWMout[6].offset*0.1,1.00,1.90);    /*M3*/
      MPWMOUT[6].pwmhi = MidVal(PWMout[3].vol + PWMout[7].offset*0.1,1.00,1.90);    /*M4*/
   } 

   for(i=2;i<=6;i++)  MpwmOut(i);
   //MpwmOut(11); //(������)     
    
}



void  LAW_ParmInit (void)
{
    PWMout[0].min= -50.0f;    PWMout[0].max=  50.0f;          /*[ailerion]*/
    PWMout[1].min= -50.0f;    PWMout[1].max=  50.0f;          /*[elevator]*/ 
    PWMout[2].min=   0.0f;    PWMout[2].max= 100.0f;          /*[engine]*/
    PWMout[3].min= -50.0f;    PWMout[3].max=  50.0f;          /*[rudder]*/
        
    PWMin[3].vol=PWMin[4].vol=PWMin[0].vol=1.5f;
    PWMin[5].vol=1.0f;  
    PWMin[2].vol=1.1f;
}


void  LAW_GetParm (void)
{
    INT16S   idx;
    INT8U    Buf[32];
    union   { INT8U B[2]; INT16S   D; } src;
    
    ROM_ReadBlock(4, Buf, sizeof(Buf));
    for (idx=0; idx<8; idx++) {
        src.B[1]=Buf[4*idx+0]; src.B[0]=Buf[4*idx+1];  PWMout[idx].ratio = src.D*0.001f;
        src.B[1]=Buf[4*idx+2]; src.B[0]=Buf[4*idx+3];  PWMout[idx].offset= src.D*0.001f;
    }
    
}


void  LAW_SetParm (void)
{
    INT16S   idx;
    INT8U    Buf[32];
    union   { INT8U B[2]; INT16S   D; } src;
    
    for (idx=0; idx<8; idx++) {
        src.D=(INT16S  )(PWMout[idx].ratio /0.001f);   Buf[4*idx+0]=src.B[1]; Buf[4*idx+1]=src.B[0];
        src.D=(INT16S  )(PWMout[idx].offset/0.001f);   Buf[4*idx+2]=src.B[1]; Buf[4*idx+3]=src.B[0];
    }
    ROM_WriteBlock(4, Buf, sizeof(Buf));
}



void  LAW_Sim (void)//��AHRS�ڷ��ͷ�������
{
    INT8U   Buf[12];
    dWordStruc  src;
    
        Buf[0]=0xAA;
        Buf[1]=0x55;
      
        src.D[0]= (INT16S  )(MPWMOUT[4].pwmhi*100.0f);     Buf[2] =src.B[1];  Buf[3] =src.B[0];    /*[����]*/
        src.D[0]= (INT16S  )(MPWMOUT[6].pwmhi*100.0f);     Buf[4] =src.B[1];  Buf[5] =src.B[0];    /*[����]*/
        src.D[0]= (INT16S  )(MPWMOUT[3].pwmhi*100.0f);     Buf[6] =src.B[1];  Buf[7] =src.B[0];    /*[������]*/
        src.D[0]= (INT16S  )(MPWMOUT[5].pwmhi*100.0f);     Buf[8] =src.B[1];  Buf[9] =src.B[0];    /*[�����]*/
        MakeCheckSum(Buf, sizeof(Buf));
        UartCom3Out(Buf,sizeof(Buf));
    

}