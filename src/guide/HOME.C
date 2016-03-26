#include "MPC.H"

/*--------------------------------------------------------------------------*/

    FP32     HomeLon,
             HomeLat;  

/*--------------------------------------------------------------------------*/

static INT16U   HomeGPS;

void  GUID_HomeCheckGPS (void)
{
    if (ss_Gps.fail) HomeGPS++;
    else             HomeGPS=0;
    
    if ((HomeGPS>=600) && on_sky && (nav_guid!=PW_NavHome) && (nav_guid!=PW_NavNone)) {
       // nav_guid=PW_NavHome;
        ac_dot=0;
    } 
}

void  GUID_HomePsi (FP32 ac_lon, FP32 ac_lat, FP32 *psi)
{
    float x,y;
    
    WP_Pos2XY(ac_lon,ac_lat, HomeLon,HomeLat, &x,&y);
    *psi = WP_Psi(x,y);
}


void  GUID_HomeLine (FP32 ac_lon, FP32 ac_lat, LineStruc *AB)
{
    WP_MakeLine(ac_lon,ac_lat, HomeLon,HomeLat, AB);    
    AB->alt = ac_height;
    AB->vxd = 0;
}


void  GUID_Home (void)
{                            
   static INT16S          step=0;
    PointStruc  A;


        if (nav_guid==PW_NavHome)
		{
            switch(step) {
            case 0:    
                WP_GetPoint(1,&A);    HomeLon=A.lon; HomeLat=A.lat;
                mode_guid=PW_GuideNone;
                if (mode_long!=PW_LongNone) token_long=TOKEN_LongNone;
                BackupRPVs();
                step++;   
				CreatTask(GUID_Home, 3*Timer1s);
                break;
            
            case 1:
                GUID_HomePsi(ac_lon,ac_lat, &psi_cmd);
                ac_dPsi=WP_Psi2Psi(ac_psi-psi_cmd);
                mode_guid=PW_GuideDim1;  //token_late=TOKEN_TrackPsi;
                step++;  
				CreatTask(GUID_Home, Timer200ms);
                break;
            
            case 2:/*---[1]---[make |ac_dPsi|<10deg]----------------------------------------*/
                GUID_HomePsi(ac_lon, ac_lat, &psi_cmd);
                ac_dPsi=WP_Psi2Psi(ac_psi-psi_cmd);
                if (fabs(ac_dPsi)<10.0f) step++;
                CreatTask(GUID_Home,Timer200ms);
                break;
            
            case 3:/*---[2]---[make autonomous guidance]-----------------------------------------------*/
                GUID_HomeLine(ac_lon, ac_lat, &AB);
                WP_LateWay(&AB, ac_lon,ac_lat,ac_psi, &ac_dZ,&ac_dL,&ac_dPsi);
                mode_guid=PW_GuideDim2;    token_late=TOKEN_TrackWay;
                step++;    
				CreatTask(GUID_Home, 3*Timer1s);
                break;
            
            case 4:    
                WP_LateWay(&AB, ac_lon,ac_lat,ac_psi, &ac_dZ,&ac_dL,&ac_dPsi);         
                if (ac_dL<100.0f) GUID_Exit();
                CreatTask(GUID_Home,Timer200ms);
                break;
            }
        }
        else { step=0; CreatTask(GUID_Home,Timer50ms);}
}
