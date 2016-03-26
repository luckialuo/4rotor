#include "MPC.H"

/*--------------------------------------------------------------------------*/
	FP32       engine_val;
    FP32       parm_eng[8];

    INT8U         mode_eng;
    INT8U        OnStop_eng;
    INT16U           RPM_eng;

    INT32S     timer_eng,timer_par;
/*--------------------------------------------------------------------------*/

void  ENG_Plus (void)
{
    mode_eng = PW_EnginePlus;
    engine_cmd = parm_eng[mode_eng];  //engine_mix = 0.0f;
}  

void  ENG_Large (void)
{
    mode_eng = PW_EngineLarge;
    engine_cmd = parm_eng[mode_eng];  //engine_mix = 0.0f;
}


void  ENG_Nominal (void)
{
    mode_eng = PW_EngineNominal;
    engine_cmd = parm_eng[mode_eng];  //engine_mix = 0.0f;
}


void  ENG_Cruise (void)
{
    mode_eng = PW_EngineCruise;
    engine_cmd = parm_eng[mode_eng];  //engine_mix = 0.0f;
}


void  ENG_Slow (void)
{
    mode_eng = PW_EngineSlow;
    engine_cmd = parm_eng[mode_eng];  //engine_mix = 0.0f;  
}


void  ENG_Stop (void)
{
    mode_eng = PW_EngineStop;
    engine_cmd = parm_eng[mode_eng];  //engine_mix = 0.0f; 
}

   	
void  ENG_SetParm (void)
{
    INT8U   Buf[32];
    union  { INT8U B[2]; INT16S   D; INT16U  W; } src;

    src.D=(INT16S  )parm_eng[PW_EngineLarge]*128;        Buf[0] =src.B[1];  Buf[1] =src.B[0];
    src.D=(INT16S  )parm_eng[PW_EngineNominal]*128;      Buf[2] =src.B[1];  Buf[3] =src.B[0];
    src.D=(INT16S  )parm_eng[PW_EngineCruise]*128;       Buf[4] =src.B[1];  Buf[5] =src.B[0];
    src.D=(INT16S  )parm_eng[PW_EngineSlow]*128;         Buf[6] =src.B[1];  Buf[7] =src.B[0];
    src.D=(INT16S  )parm_eng[PW_EngineStop]*128;         Buf[8] =src.B[1];  Buf[9] =src.B[0];
    src.D=(INT16S  )parm_eng[PW_EnginePlus]*128;         Buf[10] =src.B[1];  Buf[11] =src.B[0];
    
    ROM_WriteBlock(5, Buf, sizeof(Buf));
}


void  ENG_GetParm (void)
{
    INT8U   Buf[32];
    union  { INT8U B[2]; INT16S   D; INT16U  W; } src;
    
    ROM_ReadBlock(5, Buf, sizeof(Buf));

    src.B[1]=Buf[0];  src.B[0]=Buf[1];     parm_eng[PW_EngineLarge]  = src.W/128.0f;
    src.B[1]=Buf[2];  src.B[0]=Buf[3];     parm_eng[PW_EngineNominal]= src.W/128.0f;
    src.B[1]=Buf[4];  src.B[0]=Buf[5];     parm_eng[PW_EngineCruise] = src.W/128.0f;
    src.B[1]=Buf[6];  src.B[0]=Buf[7];     parm_eng[PW_EngineSlow]   = src.W/128.0f;
    src.B[1]=Buf[8];  src.B[0]=Buf[9];     parm_eng[PW_EngineStop]   = src.W/128.0f;
    src.B[1]=Buf[10];  src.B[0]=Buf[11];     parm_eng[PW_EnginePlus]   = src.W/128.0f;
    
}


void ENG_fpm(void)
{
//	RPM_eng=FPMVAULE[1];         //HZ
	//printf("%d\n",RPM_eng);
}

