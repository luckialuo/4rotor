#include "MPC.H"


/*--------------------------------------------------------------------------*/

    FP32         ac_dZ, 
                 ac_dL, 
                 ac_dH,
                 ac_Hdot, 
                 urg_dPsi1,
                 ac_dPsi;
    INT8U        ac_dot;
	INT8U        land_dot;
    LineStruc    AB;
    FP32         psi_cmd;
    INT8U        cmd_guid,
                 mode_guid,
                 info_guid,
                 nav_guid,
                 sound,
                 urg_guid;
                
    INT16S       prompt_guid,dZ_mix0,
                     dL_mix0;
	float        dZ_mix,
	             dL_mix;

    //INT16S       step_enter;
    //INT16S   step_spec=0;
    INT16U   time_spec=0,spec_cnt=0;

/*--------------------------------------------------------------------------*/

void sound_bibi(void)
{
	 if(sound==SOUND_BiBi)
	 {	 	 
	 static INT8U i_bibi=0;
	 i_bibi++;   
	 i_bibi%=5;
	 
	     if(i_bibi==4)
	       {
	 	MPWMOUT[11].pwmhi=10;//蜂鸣器响	  
	       }
	     else 
	        {
	 	MPWMOUT[11].pwmhi=0.0;
	        }
	      	MpwmOut(11); //(蜂鸣器)  
	 	CreatTask(sound_bibi,Timer50ms);
	 }
	 else CreatTask(sound_bibi,Timer50ms);
}

void GUID_AutoFly(void)       //切入自主
{
	if (nav_guid==PW_NavAuto) 
	{
		mode_guid=PW_GuideAuto;
                  mode_long=0;mode_late=0;
		on_reset=False; on_sky=True;
		token_late=TOKEN_LateNone;gama_cmd=0.0f;
		token_long=TOKEN_LongNone;theta_cmd=0.0f;
		token_vert=TOKEN_VertNone;height_cmd=ac_height;//锁定高度
		token_rota=TOKEN_RotaNone;psi_cmd=ac_psi;//锁定航向	
		
		//nav_guid=PW_NavSpec;
		nav_guid=PW_NavNone;
		CreatTask(GUID_AutoFly,Timer100ms);
	}
	
	else CreatTask(GUID_AutoFly,Timer100ms);
}

void GUID_Hover(void)       //悬停
{
	if (nav_guid==PW_NavHover) 
	{
		mode_guid=PW_GuideHover;
		mode_long=0;mode_late=0;		
		token_late=TOKEN_LateNone;gama_cmd=0.0f;
		token_long=TOKEN_LongNone;theta_cmd=0.0f;
		token_vert=TOKEN_VertNone;
		token_rota=TOKEN_RotaNone;
		nav_guid=PW_NavNone;
		CreatTask(GUID_Hover,Timer100ms);
	}
	
	else CreatTask(GUID_Hover,Timer100ms);
}




void  GUID_Spec(void)
{
    static INT16S   step_spec=0; 
    static INT32U	 cnt4= 0;
    static INT32U	 land_cnt = 0,psi_cnt=0;
    
    if (nav_guid==PW_NavSpec) {    	
    	
    		switch (step_spec) {
    		case 0: /*---[加力起飞]---*/  
    		urg_guid=URG_Tkoff;
                   if(on_sky)
                    {

                    //engine_mix0=30.0f;//手控起飞，不加油门遥调。
                    
                    if(height_alt00>=0.35)
                    {
                     if (!urg04lx.fail)
                    {
                      ac_dL=urg_deal_union.urg_deal_data.urg_dL -3400+dL_mix*100; //停在窗前3m
                      ac_dZ=urg_deal_union.urg_deal_data.urg_dZ+dZ_mix*100;
                      
                     urg_dPsi1=urg_deal_union.urg_deal_data.urg_dPsi;
                      
                      ac_ddZ = urg_deal_union.urg_deal_data.urg_ddZ;
                      ac_ddL = urg_deal_union.urg_deal_data.urg_ddL;
    	            
                      mode_guid=PW_GuideAuto;                    	
                    }
                    else 
                    {
                      ac_dL=ac_dZ=ac_ddZ=ac_ddL=urg_dPsi1=0.0;
                      mode_guid=PW_GuideAuto;	
                    }	
                    }
                   
                      if(height_alt00>=1.1)  
                      {
                      	step_spec=1; 
                      }		                        	
                    }
                    CreatTask(GUID_Spec,Timer50ms);
		break;
                    
    		case 1: /*悬停于窗前1.5m等待进入*/
    		   
                   
                   if (!urg04lx.fail)
                    {	
                      ac_dL=urg_deal_union.urg_deal_data.urg_dL - 2000+dL_mix*100; //停在窗前1.5m
                      ac_dZ=urg_deal_union.urg_deal_data.urg_dZ+dZ_mix*100;
                      urg_dPsi1=urg_deal_union.urg_deal_data.urg_dPsi;
                      ac_ddZ = urg_deal_union.urg_deal_data.urg_ddZ;
                      ac_ddL = urg_deal_union.urg_deal_data.urg_ddL;
    	            
                      mode_guid=PW_GuideAuto;                    	
                    }
                    else 
                    {
                      ac_dL=ac_dZ=ac_ddZ=ac_ddL=urg_dPsi1=0.0;
                      mode_guid=PW_GuideAuto;	
                    }
                                       
                    
                       if((abs(urg_deal_union.urg_deal_data.urg_dZ)<=300)&&(urg_deal_union.urg_deal_data.urg_dL<=2200))
                         {
	                  step_spec=2;
	                  mode_guid=PW_GuideAuto;
                         }                    
                    
                   if(height_alt00<0.4)
                     {
                          engine_mix0=-35.0;
                          sound=SOUND_BiBi;//蜂鸣器响 
                      }
                  CreatTask(GUID_Spec,Timer50ms);  			    									   				    				    					 		
		break;	
			    				     
    		case 2: /*前进到窗前0.5米准备进窗*/ 
    		   	

                   if (!urg04lx.fail)
                    {                     	    
                      ac_dL=urg_deal_union.urg_deal_data.urg_dL-1000 +dL_mix*100; 
                      ac_dZ=urg_deal_union.urg_deal_data.urg_dZ +dZ_mix*100;
                      urg_dPsi1=urg_deal_union.urg_deal_data.urg_dPsi;
                      ac_ddZ = urg_deal_union.urg_deal_data.urg_ddZ;
                      ac_ddL = urg_deal_union.urg_deal_data.urg_ddL;
    	            
                      mode_guid=PW_GuideAuto;                    	
                    }
                    else 
                    {
                      ac_dL=ac_dZ=ac_ddZ=ac_ddL=urg_dPsi1=0.0;
                      mode_guid=PW_GuideAuto;	
                    }
                                    
                         
                       if((urg_deal_union.urg_deal_data.urg_dL<=1100)&&(abs(urg_deal_union.urg_deal_data.urg_dZ)<=200)
                            &&(urg_deal_union.urg_deal_data.urg_dL!=-500)) 
                         {
                   	 step_spec=3;
                         }
                   
                   if(height_alt00<0.4)
                   {
                    engine_mix0=-35.0;
                   sound=SOUND_BiBi;//蜂鸣器响 
                   }
                  CreatTask(GUID_Spec,Timer50ms); 
		break;
									
    		case 3:/*俯仰-10度，进窗*/

                   urg_guid=URG_Enter;	
    		if (!urg04lx.fail)
                    {
                      ac_dL=urg_deal_union.urg_deal_data.urg_dL+300+dL_mix*100; 	//为了抵消地效，加一米待飞
                      ac_dZ=urg_deal_union.urg_deal_data.urg_dZ +dZ_mix*100;
                      urg_dPsi1=urg_deal_union.urg_deal_data.urg_dPsi;
                      ac_ddZ = urg_deal_union.urg_deal_data.urg_ddZ;
                      ac_ddL = urg_deal_union.urg_deal_data.urg_ddL;
    	            
                      mode_guid=PW_GuideAuto;                    	
                    }
                    else 
                    {
                      ac_dL=ac_dZ=ac_ddZ=ac_ddL=urg_dPsi1=0.0;
                      mode_guid=PW_GuideAuto;	
                    }
                    
                 if(urg_deal_union.urg_deal_data.urg_dL==-500)
                  {
                  	step_spec=1;
                  	urg_guid=URG_None;
                  }
                    
                    if((urg_deal_union.urg_deal_data.urg_dL<=500) &&(abs(urg_deal_union.urg_deal_data.urg_dZ)<=250)                
                        &&(urg_deal_union.urg_deal_data.urg_dL!=-500)) 
                    	{                   	      
                    	       step_spec=4;
                    	        theta_mix =-3.0;             	                           	      
                    	}                                                    

                 CreatTask(GUID_Spec,Timer50ms);
                   break; 
                    
    		case 4: /*走廊*/
    		urg_guid=URG_Enter;
    		land_cnt++;land_cnt%=1200;
    		
    		if (!urg04lx.fail)
                    {
                      ac_dL=urg_deal_union.urg_deal_data.urg_dL +dL_mix*100; 
                      ac_dZ=urg_deal_union.urg_deal_data.urg_dZ +dZ_mix*100;
                      urg_dPsi1=urg_deal_union.urg_deal_data.urg_dPsi;
                      ac_ddZ = urg_deal_union.urg_deal_data.urg_ddZ;
                      ac_ddL = urg_deal_union.urg_deal_data.urg_ddL;
    	            
                      mode_guid=PW_GuideAuto;                    	
                    }
                    else 
                    {
                      ac_dL=ac_dZ=ac_ddZ=ac_ddL=urg_dPsi1=0.0;
                      mode_guid=PW_GuideAuto;	
                    } 
                    
                    if(urg_deal_union.urg_deal_data.urg_right_point<=2000)
                    {
                    	theta_mix=0;
                    }
                    
                 if(urg_dPsi1==45)   
                 {
                        ++psi_cnt;
                        if(psi_cnt==1)
                        {rud_mix+=45;  }
                 }
                    	
  
                   if ((urg_deal_union.urg_deal_data.urg_dL==30)&&(urg_deal_union.urg_deal_data.urg_dZ==30))//无路可走，着陆
                   {
                   	step_spec=5;
                   	mode_guid=PW_GuideAuto;
                   }
                   else if(land_cnt==5999)//5min后着陆�
                   {
                           step_spec=5;
                           land_cnt=0;
                   	mode_guid=PW_GuideAuto;	
                   }
                   
                   if(height_alt00<0.4)
                   {
                   engine_mix0=-35.0;
                   sound=SOUND_BiBi;//蜂鸣器响 
                   }
                   CreatTask(GUID_Spec,Timer50ms);
                   break;
                   
    		case 5:/*减油门，着陆*/
                    
                    engine_mix0= -35.0f;
                    
                   if(height_alt00<0.4)
                   {
                   engine_mix0=-35.0;
                   sound=SOUND_BiBi;//蜂鸣器响 
                   }
                CreatTask(GUID_Spec,Timer50ms);
		break;	    	
    		}
    		
    	}
    	else { step_spec=0; 
		CreatTask(GUID_Spec,Timer50ms);}
   
}




void  GUID_Exit (void)
{
    nav_guid=PW_NavNone; mode_guid=PW_GuideNone;  
    on_takeoff = False;
    prompt_guid = False;
    ac_dot=0; ac_dZ=ac_dPsi=ac_dL=0.0f;
    tag_home=tag_land=tag_endwp=False;

    token_long=TOKEN_LongNone;
    token_late=TOKEN_LateNone;
    token_vert=TOKEN_VertNone;
    token_rota=TOKEN_RotaNone;
    
}

