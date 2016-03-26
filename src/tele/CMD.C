#include "MPC.H"

/*--------------------------------------------------------------------------*/

    INT16S      tag_cmd_blocked;
    INT16S      on_reset;
	FP32        K_adjust=0;
	INT16S      on_safe=0;
	INT16S      fail_gps=0;

/*--------------------------------------------------------------------------*/

void  TELE_Reset (void)
{
    ele_cmd=ail_cmd=rud_cmd=engine_cmd=0.0f;
    ele_var=ail_var=rud_var=engine_var=0.0f;
    PWMout[0].val=PWMout[1].val=PWMout[2].val=PWMout[3].val=PWMout[4].val=0.0f;

    KeH=KeIH=KedH=0.0f; KeITheta=KaIGama=0.0f;
    theta_cmd=gama_cmd=height_cmd=Hdot_cmd=psi_cmd=0.0f;
    theta_mix=gama_mix=engine_mix=engine_mix0=engine_mix1=rud_mix=theta_mix0=0.0f;

    token_long=TOKEN_LongNone;    mode_long=PW_LongNone; 
    token_late=TOKEN_LateNone;    mode_late=PW_LateNone;
    mode_guid=PW_GuideNone;       cmd_guid=PW_GuideDim3;    nav_guid=PW_NavNone; prompt_guid=False;
    ac_dot=0; ac_dZ=ac_dPsi=ac_dL=ac_dH=ac_Hdot=H_int=Z_int=L_int=ac_ddZ=ac_ddL=urg_dPsi1=0.0f;

    tag_opt=1;      //默认遥控增稳开   
    fail_gps=0;     //默认使用超声波高度
         
    tag_test=tag_cmd_blocked=False; 
    on_sky=on_takeoff=False;
    on_reset=True;
    tag_home=tag_land=tag_endwp=False;

    dZ_mix = 0.0f;dL_mix=0.0f;   
    
    gama_int=theta_int=0.0;
    RunwayAlt_mix=0.0;
    
    KeIH_cnt=0;
    
    if(simu_gps) on_safe=0;
   
    BackupRPVs();
    vision.fail=1;
    MPWMOUT[11].pwmhi=0.0;
    MpwmOut(11); //(蜂鸣器)    
    sound=SOUND_None;

}


void  TELE_CheckCmd (INT8U Cmd)
{
    switch (Cmd) {
        case 1: /*[切入自主]*/			
                if (!on_sky&&nav_guid!=PW_NavAuto) {
                   nav_guid=PW_NavAuto;
                }
                break;
        case 2: /*[发动机大车]*/
                ENG_Large();      
                break;
        case 3: /*[发动机额定]*/
                ENG_Nominal();  
                break;
        case 4: /*[发动机巡航]*/
                ENG_Cruise();   
                break;
        case 5: /*[发动机慢车]*/
                ENG_Slow();     
                break;
        case 6: /*[预停车]*/
                
                break;
        case 7: /*[停车]*/
                ENG_Stop();   engine_mix0 = 0.0f;   BackupRPVs(); 
                break;
        case 8: /*[爬升/前进]*/
                if ((on_sky)&&(token_long!=TOKEN_TurnForth)) {
                   token_long=TOKEN_TurnForth;
                }
                break;
        case 9: /*[发动机加力]*/
        		ENG_Plus();   
                break;
        case 10:/*[平飞]*/
                engine_mix0=0.0f;
                break;
        case 11:/*[大气高度开]*/
        		fail_gps=1;
                break;
        case 12:/*[下滑/后退]*/
                if ((on_sky)&&(token_long!=TOKEN_TurnBack)) {
                    token_long=TOKEN_TurnBack;
                }
                break;
        case 13:/*[辅助控制模式开]*/
        		if(!on_safe) 
        		tag_opt=1; 
                break;
        case 14:/*[辅助控制模式关]*/
        		if(!on_safe) 
        		tag_opt=0;
                break;
        case 15:/*[左转/左飞]*/
                if ((on_sky)&&(token_late!=TOKEN_TurnLeft)) {
                    token_late=TOKEN_TurnLeft;
                }
                break;
        case 16:/*[直飞/前进进入]*/
                if((on_sky)&&(nav_guid!=PW_NavEnter))
                nav_guid=PW_NavEnter;
                break;
        case 17:/*[大气高度关]*/
        		fail_gps=0;
                break;
        case 18:/*[右转/右飞]*/
                if ((on_sky)&&(token_late!=TOKEN_TurnRight)) {
                    token_late=TOKEN_TurnRight;
                }
                break;
        case 19:/*[定向]*/

                break;
        case 20:/*[导航/视觉导航]*/
                if (nav_guid!=PW_NavPosition) {
                   nav_guid=PW_NavPosition;
                }
                break;
        case 21:/*[复位]*/
			    ENG_Stop(); 
			    TELE_Reset();
                break;
        case 22:/*[GPS高度清零]*/
                break;
        case 23:/*[大气高度清零]*/
                if(!on_sky) height_ini =height_adc;
                break;
        case 24:/*[建立起飞角]*/

                break;
        case 25:/*[起飞]*/

                break;
        case 26:/*[滑行]*/  

                break;
        case 27:/*[速度控制开]*/

                break;
		case 28:/*[速度控制关]*/

                break;
        case 29:/*[悬停]*/
                if (on_sky && (nav_guid!=PW_NavHover)) {
                   nav_guid=PW_NavHover; 
                }
                break;
        case 30:/*[回家/加力]*/  
                if((on_sky)&&(nav_guid!=PW_NavSpec)) 
                {       
                   nav_guid=PW_NavSpec;
                   time_spec=1;
                }
                break;
       
    }
}

