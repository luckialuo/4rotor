#include "MPC.H"
#include <stdio.h>

/*--------------------------------------------------------------------------*/

    INT8U    tag_test,
             on_test_load,
             on_test_save,
             on_test_back;
    INT8U     ask_cmd,
             ask_idx; 
    INT8U     dot_total;        
    INT8U     echo_test;
    INT8U     on_DA_volts;

/*--------------------------------------------------------------------------*/

void  TEST_RxMan (INT8U Buf[])
{
    echo_test = Buf[18];
    switch (Buf[3]) {
                     /*---[地面检测控制字]---*/
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:  TEST_Class1(Buf);
                    break;

                     /*---[输出命令字]---*/
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26: 
        case 0x27: 
        case 0x28: 
        case 0x29: 
        case 0x2A: 
        case 0x2B:  TEST_Class2(Buf);
                    break;

                     /*---[用户参数设置命令]---*/
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
		case 0x35:
		case 0x36:
        case 0x39:  TEST_Class3(Buf);
                    break;
        
                     /*---[航路点设置命令]---*/
        case 0x41:  TEST_Class4(Buf);
                    break;

                     /*---[参数查询命令]---*/
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:     
        case 0x56:
        case 0x57:
		case 0x59:
        case 0x61:  TEST_Class5(Buf);
                    break;
    }
}

void  TEST_Class1 (INT8U Buf[])
{
    switch (Buf[3]) {
        case 0x11:  tag_test=True;
                    on_test_load=on_test_save=on_test_back=False;
                    ask_cmd=ask_idx=0;
                    break;
        case 0x12:  tag_test=False;
                    on_test_load=on_test_save=on_test_back=False;
                    ask_cmd=ask_idx=0;
                    break;
        case 0x13:  if (tag_test)   on_test_back=True;    break;
        case 0x14:  if (tag_test) { on_test_back=False; ask_cmd=ask_idx=0; } break;
        case 0x15:  if (tag_test) { on_test_load=True; on_test_save=False; } break;
        case 0x16:  if (tag_test) { on_test_load=False;on_test_save=False; } break;
        case 0x17:  if (on_test_load) {
        
                       // watchdog_disable();                               //保存装订
                        
                        BackupParmROM();
                               
                        ROM_SaveFlash();
                                              
                        RestoreParmROM();
                        //TEST_ResetHMS();
                        on_test_load = False;
                        LAW_ParmInit();
                        on_test_save = True;
                        
                       // watchdog_enable();
                    }
                    break;
        case 0x18:  if (on_test_load) {
                        ROM_DeleteWP();
                        dot_total=0;
                    }
                    break;
    }
}
 

void  TEST_Class2 (INT8U Buf[])
{
    union  { INT8U B[2]; INT16S   D; INT16U  W; } src;

    switch (Buf[3]) {
        case 0x21:  /*[离散输出]*/
                    //DO=Buf[4];
                     break;
        case 0x22:  /*[模拟通道电压输出]*/
                    if (Buf[4]<8) {
                    src.B[1]=Buf[5];
                    src.B[0]=Buf[6];    PWMout[Buf[4]].vol=src.D/100.0f;//电压输出分辨率为0.005
                    on_DA_volts=True;
                    }
                    break;
        case 0x23:  /*[升降舵机输出]*/
                    src.B[1]=Buf[4];
                    src.B[0]=Buf[5];    PWMout[1].val=src.D/10.0f;
                                        //ele_var=src.D/10.0f;
                    on_DA_volts=False;
                    break;
        case 0x24:  /*[左副翼舵机输出]*/
                    src.B[1]=Buf[4];
                    src.B[0]=Buf[5];    PWMout[0].val=src.D/10.0f;
                    on_DA_volts=False;
                    break;
                    
    	case 0x25:   /*[前轮输出]*/    	
                    src.B[1]=Buf[4];
                    src.B[0]=Buf[5];    PWMout[5].val=src.D/10.0f;
                    on_DA_volts=False;
                    break;    	
    	
        case 0x26:  /*[方向舵机输出]*/
                    src.B[1]=Buf[4];
                    src.B[0]=Buf[5];    PWMout[3].val=src.D/10.0f;
                                        //rud_var=src.D/10.0f;
                    on_DA_volts=False;
                    break;
        case 0x27:  /*[油门开度输出]*/
                    src.B[1]=Buf[4];
                    src.B[0]=Buf[5];    engine_cmd=MidVal(src.D*0.1f,0.0f,100.0f);
                    on_DA_volts=False;
                    break;   
    }
}


void  TEST_Class3 (INT8U Buf[])
{
    INT16S         idx;
    dWordStruc src;

    switch (Buf[3]) {
        case 0x31:  /*[模拟输入标定系数]*/
                    if (Buf[4]<2) {
                        src.B[1]=Buf[5];
                        src.B[0]=Buf[6];    //AD[Buf[4]].ratio =src.D[0]/100.0;
                        src.B[1]=Buf[7];
                        src.B[0]=Buf[8];    //AD[Buf[4]].offset=src.D[0]/100.0; 
                    }
                    break;
        case 0x32:  /*[PWM输出标定系数]*/
                    if (Buf[4]<8) {
                        src.B[1]=Buf[5];
                        src.B[0]=Buf[6];    PWMout[Buf[4]].ratio =src.D[0]/1000.0;
                        src.B[1]=Buf[7];
                        src.B[0]=Buf[8];    PWMout[Buf[4]].offset=src.D[0]/100.0;
                    }
                    break;
        case 0x33:  /*[发动机参数]*/
        
                    src.B[1]=Buf[4];
                    src.B[0]=Buf[5];    parm_eng[PW_EngineStop]   =src.W[0]/100.0f;
                    src.B[1]=Buf[6];
                    src.B[0]=Buf[7];    parm_eng[PW_EngineSlow]   =src.W[0]/100.0f;
                    src.B[1]=Buf[8];
                    src.B[0]=Buf[9];    parm_eng[PW_EngineCruise] =src.W[0]/100.0f;
                    src.B[1]=Buf[10];
                    src.B[0]=Buf[11];   parm_eng[PW_EngineNominal]=src.W[0]/100.0f;             
					src.B[1]=Buf[12];
					src.B[0]=Buf[13];  parm_eng[PW_EngineLarge] = src.W[0]/100.0f;
					src.B[1]=Buf[14];
					src.B[0]=Buf[15];  parm_eng[PW_EnginePlus] = src.W[0]/100.0f;					
                     break;
        case 0x34:  /*[用户参数]*/
                    for (idx=0;idx<sizeof(UserMsg);idx++) UserMsg[idx]=Buf[4+idx];
                    break;
        case 0x35:  /*[配置参数]*/
                    src.B[1] =Buf[4]; src.B[0]=Buf[5];     psi_offset_hmr = src.D[0]/10.0f;
                    simu_gps =Buf[6];
                    src.B[1]=Buf[7]; src.B[0]=Buf[8];    height_ini = src.D[0]/10.0f;
                                                   
                    break; 

        case 0x36:  /*[机场跑道参数]*/
					
                    break; 
        

        case 0x39:  /*[控制参数]*/
        	        ask_cmd = Buf[3];
					ask_idx = Buf[4]-0x12;
					src.B[1]= Buf[5]; src.B[0]= Buf[6];
					K.f[Buf[4]-0x12]=src.D[0]*0.01f;
                    break; 
                    
                    
    }
}


void  TEST_Class4 (INT8U Buf[])
{
    INT8U  idx, WP[13];
    
    if (Buf[4]) {
        for (idx=0;idx<sizeof(WP);idx++) WP[idx]=Buf[4+idx];
        ROM_WriteWP(Buf[4], WP, sizeof(WP));
        dot_total = Buf[4];
    }
    
}


void  TEST_Class5 (INT8U Buf[])
{
    if (on_test_back) {
        ask_cmd=Buf[3];
        ask_idx=Buf[4];
    }
}

