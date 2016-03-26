#include "MPC.H"

     

/*---------------------------------------------------------------------------*/
//ahrs.C
/*---------------------------------------------------------------------------*/

FP32  Wx_gyo,Wy_gyo,Wz_gyo;
FP32  theta_gyo, gama_gyo, psi_hmr;
FP32  psi_offset_hmr;
FP32  lat_ahrs,lon_ahrs,height_ahrs,vel_x,vel_y,vel_z;
FP32   accx;
FP32   accy;
FP32   accz;
INT8U  AHRS_status;
SensorStruc	 ss_AHRS;

FP32 mti_Wx_gyo,mti_Wy_gyo,mti_Wz_gyo,mti_gama_gyo,mti_theta_gyo,mti_psi_hmr;

/*---------------------------------------------------------------------------*/
void	MTiG700_Rx(BYTE Buf[])
{		
	union {unsigned char B[4];  unsigned short W[2];  short D[2]; float f;  }   src;
	
	src.B[0]=Buf[4];  src.B[1]=Buf[5];   src.B[2]=Buf[6];     src.B[3]=Buf[7];     mti_Wx_gyo =src.f*Rad2Deg;//前向过载
	src.B[0]=Buf[8];  src.B[1]=Buf[9];   src.B[2]=Buf[10];    src.B[3]=Buf[11];    mti_Wz_gyo =-src.f*Rad2Deg;//侧向过载
	src.B[0]=Buf[12];  src.B[1]=Buf[13];   src.B[2]=Buf[14];  src.B[3]=Buf[15];    mti_Wy_gyo =src.f*Rad2Deg;//法向过载
   
	src.B[0]=Buf[16];  src.B[1]=Buf[17];   src.B[2]=Buf[18];  src.B[3]=Buf[19];    mti_gama_gyo =src.f;   //右滚为正
	src.B[0]=Buf[20];  src.B[1]=Buf[21];   src.B[2]=Buf[22];  src.B[3]=Buf[23];    mti_theta_gyo =-src.f;  //上俯仰为正
	src.B[0]=Buf[24];  src.B[1]=Buf[25];   src.B[2]=Buf[26];  src.B[3]=Buf[27];    mti_psi_hmr =Psi_360(Psi_360(-src.f)+psi_offset_hmr);   //逆时针偏航为正
	
	Wx_gyo = mti_Wx_gyo;	Wz_gyo = mti_Wz_gyo;	Wy_gyo = mti_Wy_gyo;
	gama_gyo = mti_gama_gyo;		theta_gyo = mti_theta_gyo;		psi_hmr = mti_psi_hmr;
	ac_psi = psi_hmr; 
}
	 
/*     
void AHRSRx(BYTE Buf[])
{

    static union {unsigned char B[4];  unsigned short W[2];  short D[2]; float f;  }   src;	
    static FP32  Wx_gyo_old,Wy_gyo_old,Wz_gyo_old;
   
    //src.B[0]=Buf[16];  src.B[1]=Buf[17];   src.B[2]=Buf[18];  src.B[3]=Buf[19];    Wx_gyo =src.f*Rad2Deg;//red弧度
    //src.B[0]=Buf[20];  src.B[1]=Buf[21];   src.B[2]=Buf[22];  src.B[3]=Buf[23];    Wz_gyo =-src.f*Rad2Deg;
    //src.B[0]=Buf[24];  src.B[1]=Buf[25];   src.B[2]=Buf[26];  src.B[3]=Buf[27];    Wy_gyo =src.f*Rad2Deg;
    
    //src.B[0]=Buf[40];  src.B[1]=Buf[41];   src.B[2]=Buf[42];  src.B[3]=Buf[43];    gama_gyo =src.f;//deg角度
    //src.B[0]=Buf[44];  src.B[1]=Buf[45];   src.B[2]=Buf[46];  src.B[3]=Buf[47];    theta_gyo =-src.f;
    //src.B[0]=Buf[48];  src.B[1]=Buf[49];   src.B[2]=Buf[50];  src.B[3]=Buf[51];    psi_hmr =Psi_360(Psi_360(-src.f)+psi_offset_hmr);//顺时针为正 
  
	
	src.B[0]=Buf[4];   src.B[1]=Buf[5];    src.B[2]=Buf[6];   src.B[3]=Buf[7];     Wx_gyo =src.f*Rad2Deg;//red弧度
    src.B[0]=Buf[8];   src.B[1]=Buf[9];    src.B[2]=Buf[10];  src.B[3]=Buf[11];    Wz_gyo =-src.f*Rad2Deg;
    src.B[0]=Buf[12];  src.B[1]=Buf[13];   src.B[2]=Buf[14];  src.B[3]=Buf[15];    Wy_gyo =src.f*Rad2Deg;
    
    src.B[0]=Buf[16];  src.B[1]=Buf[17];   src.B[2]=Buf[18];  src.B[3]=Buf[19];    gama_gyo =src.f;//deg角度
    src.B[0]=Buf[20];  src.B[1]=Buf[21];   src.B[2]=Buf[22];  src.B[3]=Buf[23];    theta_gyo =-src.f;
    src.B[0]=Buf[24];  src.B[1]=Buf[25];   src.B[2]=Buf[26];  src.B[3]=Buf[27];    psi_hmr =Psi_360(Psi_360(-src.f)+psi_offset_hmr);//顺时针为正 
	
	
	AHRS_status =Buf[28];
	
	//Wx_gyo=Wx_gyo_old*0.875+Wx_gyo*0.125;
	//Wx_gyo_old=Wx_gyo;
	
	//Wz_gyo=Wz_gyo_old*0.875+Wz_gyo*0.125;
	//Wz_gyo_old=Wz_gyo;
	
	//Wy_gyo=Wy_gyo_old*0.875+Wy_gyo*0.125;
	//Wy_gyo_old=Wy_gyo;
	
	ac_psi = psi_hmr; 
	
	/*
	AHRS偏移量
	俯仰 -0.584 0.384
	滚转 0.917  -0.109
	*/ 	
  
//}


void  Task_AHRSRev(void)
{
    volatile  static  BYTE    buf[256], head=0, tail=0,tmp=0;
    static            BYTE    ptr, len, check, FCCdata[30];
    static            int     RxQueLen, numread, idx;
			
    RxQueLen=UartCom3RxLen();
    numread=RxQueLen>30?30:RxQueLen;
    if (numread) {
         UartCom3In(FCCdata,numread);  
        for (idx=0;idx<numread;idx++) { buf[head++]=FCCdata[idx]; }
    }

    len=head-tail;
    while (len>=sizeof(FCCdata)) {
		tmp =tail+1;
        if((buf[tail]==0xFA) && (buf[tail+1]==0xFF)) {
            ptr=tail; for(idx=0;idx<sizeof(FCCdata);idx++) FCCdata[idx]=buf[ptr++];
            check=0;  for(idx=1;idx<sizeof(FCCdata);idx++) check+=FCCdata[idx];
            if (check==0) {
		//AHRSRx(FCCdata);
            	MTiG700_Rx(FCCdata);
            	ss_AHRS.invalid=ss_AHRS.fail=0;ss_AHRS.counter++;
				tail += sizeof(FCCdata); 				
            }
			else tail ++;
        }
        else tail ++;
        len=head-tail;
    }
}




void AHRS_Monitor(void)                       
{

    static INT8U	 cnt = 0;
    static INT8U   flag1s = FALSE;
    static INT16U	 old_counter;
	
	ss_AHRS.invalid +=1;    
    if (ss_AHRS.invalid>=20) ss_AHRS.fail=1;
    
	  cnt ++;
	  cnt %= 100;
	  if ((cnt%10) == 0)
	       flag1s = TRUE;                              
    	    
	  if (flag1s) 
	  {
	       flag1s = FALSE;
	       ss_AHRS.freq = ss_AHRS.counter - old_counter;		   
		   old_counter  = ss_AHRS.counter;
	  }
	  
}


