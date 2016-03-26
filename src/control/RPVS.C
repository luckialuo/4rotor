#include "MPC.H"


void    BackupRPVs(void)
{
    INT8U i=0;
    INT8U    RPVS=0;
    dWordStruc  src;
    INT8U  buff[32];

    if (nav_guid!=PW_NavNone)       SetBit(&RPVS,0);
    if (on_takeoff)     SetBit(&RPVS,1);
    if (on_reset)       SetBit(&RPVS,2);
    if (on_sky)         SetBit(&RPVS,5);
    
    
    buff[0] =  RPVS;
    buff[1] =  ac_dot;
    buff[2] =  mode_guid;
    buff[3] =  cmd_guid;
    buff[4] =  mode_long;
    buff[5] = (INT8S)(theta_var*2.0f);
    buff[6] =  mode_late;
    buff[7] = (INT8S)(gama_var*2.0f);
    buff[8] =  mode_eng;
    src.DW  = ac_lon*1e6;
    buff[9] = src.B[0]; 
    buff[10] = src.B[1];
    buff[11] = src.B[2];
    buff[12] = src.B[3];
    src.DW   = ac_lat*1e6;
    buff[13] = src.B[0]; 
    buff[14] = src.B[1];
    buff[15] = src.B[2];
    buff[16] = src.B[3];
    buff[17] = nav_guid;
    buff[18] = on_safe;
    buff[19] = tag_opt;
    buff[20] = tag_ViHoldON;   
  
  
    for(i=0;i<32;i+=2) 
    {
        src.B[0] =buff[i]; src.B[1] =buff[i+1];
        NvramWrite(i,src.D[0]);
    }    


}

void    RestoreRPVs(void)
{
    INT8U  i;
    INT8U    RPVS=0;
    INT8U    cmd_nav;
    dWordStruc src;
    INT8U  buff[32];
    for(i=0;i<32;i+=2) NvramRead(i,(unsigned short *)(&buff[i])); 

    
    RPVS   = buff[0]; if(!BitStatus(RPVS,0)) nav_guid=PW_NavNone;
                                             on_takeoff = BitStatus(RPVS,1);
                                             on_reset   = BitStatus(RPVS,2);
                                             on_sky     = BitStatus(RPVS,5);
     
                                            
     ac_dot   = buff[1];   
    mode_guid = buff[2];
     cmd_guid = buff[3];
    mode_long = buff[4];
    theta_var = ((INT8S)buff[5])/2.0f;    /*theta_var = 0.5f*B;*/
    mode_late = buff[6];
    gama_var  = ((INT8S)buff[7])/2.0f;     /*gama_var = 0.5f*B;*/
    mode_eng  = buff[8];
             
     src.B[0] = buff[9];
     src.B[1] = buff[10];
     src.B[2] = buff[11];
     src.B[3] = buff[12];  ac_lon =(FP32)src.DW*1e-6;  
     
     src.B[0] = buff[13];  
     src.B[1] = buff[14];
     src.B[2] = buff[15];
     src.B[3] = buff[16];  ac_lat = (FP32)src.DW*1e-6;   
     cmd_nav = buff[17];
     on_safe = buff[18];  
     tag_opt = buff[19];
     tag_ViHoldON = buff[20];
     
     //if(on_safe) PwmOutMode(EXTMODE);
     //else PwmOutMode(CPUMODE);

    fusion_refresh_gps(ac_lon,ac_lat,0);

    mode_guid=PW_GuideNone; 

    switch (cmd_nav ) {
        case PW_NavSpec:
            break;
        case PW_NavPosition:
             //nav_guid=PW_NavHover;
            break;
        case PW_NavHover:
             //nav_guid=PW_NavHover;
            break;
        case PW_NavHome:
            //nav_guid =PW_NavHome;
            break; 
        }
    if(cmd_nav ==PW_NavNone){
          if(on_takeoff){
            //token_long=TOKEN_CmdClimb;
            //token_late=TOKEN_Straight;
            //ac_dot =1;
            //if (WP_GetLine(ac_dot,&AB)) { step_enter=0; nav_guid=PW_NavEnter; }
          }
        else {
            if (on_reset)   TELE_Reset();
            else {
                switch (mode_long){
                    /*case PW_LongLevel:
                         token_long=TOKEN_CmdLevel;
                         break;
                    case PW_LongClimb:
                         token_long=TOKEN_CmdClimb;
                         break;
                    case PW_LongDive:
                         token_long=TOKEN_CmdDive;
                         break;
                    case TOKEN_WayPass:
                         token_long=TOKEN_WayPass;
                         break;
                    case TOKEN_WayNet:
                         token_long=TOKEN_WayNet;
                         break;
                    case TOKEN_LevelNet:
                         token_long=TOKEN_LevelNet;
                         break;
                    case TOKEN_WayLand:
                         token_long=TOKEN_WayLand;
                         break;*/
                    default:
                         //token_long=TOKEN_CmdLevel;
                         break;
                }
                switch (mode_late){
                    /*case PW_LateStraight:
                         token_late=TOKEN_Straight;
                         break;
                    case PW_LateLeft:
                         token_late=TOKEN_TurnLeft;
                         break;
                    case PW_LateRight:
                         token_late=TOKEN_TurnRight;
                         break;*/
                    default:
                         //token_late=TOKEN_TurnLeft;
                         break;
                }
            }
        }
    }
}
