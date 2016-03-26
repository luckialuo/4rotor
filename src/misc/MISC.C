#include "MPC.H"

void  MakeCheckSum (INT8U Buf[], INT16S  len)
{
    INT8U  sum, idx;
    
    sum=0; for(idx=0;idx<(len-1);idx++) sum+=Buf[idx];
    Buf[len-1] = 256 - sum;
}


FP32  MidVal (FP32 x, FP32 y,FP32 z)
{
    FP32   min, max, middle;
    
    if (x>=y)   { max = x;  min = y; }
    else        { max = y;  min = x; }
    
    if      (z<min)     middle = min;
    else if (z>max)     middle = max;
    else                middle = z;

    return (middle);
}


/*****************************************
ENG     PWMIN[5]  采集通道6    A14	              
AIL     PWMIN[3]  采集通道4    B14	               
ELE     PWMIN[4]  采集通道5    C14	               
RUD     PWMIN[0]  采集通道1    A13	               
SAFE    PWMIN[2]  采集通道3    B13

M1  PWMOUT[3]  输出通道4  A4 
M2  PWMOUT[2]  输出通道3  A5 
M3  PWMOUT[5]  输出通道6  A6 
M4  PWMOUT[6]  输出通道7  A7 
******************************************/


void PWM_IN(void)
{
    INT8U idx;
    static INT8U cnt_safe=0, cnt_auto=0;
    
    for(idx=0;idx<6;idx++) 
    {  MpwmIn(idx); }
    

    for(idx=0;idx<6;idx++)
    {
	    if((MPWMIN[idx].pwmhi>=0.80)&&(MPWMIN[idx].pwmhi<=2.20))
	    {
	    	PWMin[idx].vol =MPWMIN[idx].pwmhi;
	    } 	
    }	

    
    
    if((PWMin[2].vol>=1.6)&&(PWMin[2].vol<=2.2))        //Safe                   接线B13 
    {cnt_safe++; cnt_auto=0;	}
    else if((PWMin[2].vol<=1.4)&&(PWMin[2].vol>=0.8))   //Auto
    {cnt_auto++; cnt_safe=0;	}
    else 
    {cnt_safe=0; cnt_auto=0;	}
    
    if(cnt_safe>=3) 
    {
    	on_safe=True;
    	KeIH_cnt=0; 
    }
    
    else if(cnt_auto>=3) 
    {	
    	if(on_safe) 
    	{
    	   tag_SaveEleSwitch=True; tag_SaveEngSwitch=True;	tag_opt=1;
    	   if (on_sky) {
                   //nav_guid=PW_NavHover;
                }
    	   
    	}
    	on_safe=False;
    }

        
    PWMin[0].val = (PWMin[3].vol*1000-1500-PWMout[0].offset*10)/PWMout[0].ratio; //Ail    接线B14
    PWMin[1].val = (PWMin[4].vol*1000-1500-PWMout[1].offset*10)/PWMout[1].ratio; //Ele    接线C14
    PWMin[2].val = (PWMin[5].vol*1000-1000-PWMout[2].offset*10)/PWMout[2].ratio; //Eng    接线A14
    PWMin[3].val = (PWMin[0].vol*1000-1500-PWMout[3].offset*10)/PWMout[3].ratio; //Rud    接线A13        

    
    if(tag_opt&&!on_safe) //辅助控制
    {
    	ail_opt = PWMin[0].val;
    	ele_opt = PWMin[1].val;
    	eng_opt = PWMin[2].val;
    	rud_opt = PWMin[3].val;
    	
    }
    else
    {
    	ail_opt = 0;
    	ele_opt = 0;
    	eng_opt = 0;
    	rud_opt = 0;
    }
        
}


void  task_100ms (void)
{
    CreatTask(task_100ms, Timer100ms);
    fusion_slow();
  
    AHRS_Monitor();
    TELE_Monitor();
    SRF_Monitor();
    URG_Monitor();
    VISION_Monitor();
        
	   
}

 
void  RestoreParmROM (void)
{

    LAW_GetParm();
    ENG_GetParm();
    MSG_GetParm();
    CFG_GetParm();
	PID_GetParm();
}


void  BackupParmROM (void)
{

    LAW_SetParm();
    ENG_SetParm();
    MSG_SetParm();
    CFG_SetParm();
	PID_SetParm();
}

