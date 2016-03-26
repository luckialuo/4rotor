#include "MPC.H"

/*--------------------------------------------------------------------------*/

    PointStruc   HoverWay[7];
    INT16S           HoverDot,
                 HoverNum;        

/*--------------------------------------------------------------------------*/


void  GUID_HoverInit (INT16S  clockwise)
{
    static FP32  LEN[6]={60.0f, 120.0f, 120.0f, 120.0f, 120.0f, 120.0f};
           FP32  PSI[6], Ax, Ay;
      LineStruc  prev;
           INT16S    idx;
           FP32 iPsi;
    
    if (ac_dot) {   /*[自主导航时计算HoverWay[0]]*/
        WP_GetLine(ac_dot-1, &prev);
        HoverWay[0].lon=prev.lon; 
        HoverWay[0].lat=prev.lat;
        HoverWay[0].alt=ac_height;
        HoverWay[0].vxd=0;
        HoverWay[0].dot=0;
        
        //WP_GetLine(ac_dot-1, &prev);
        PSI[0]=prev.psi;  
    }
    else {          /*[指令导航时计算HoverWay[0]]*/
        HoverWay[0].lon=ac_lon; 
        HoverWay[0].lat=ac_lat;
        HoverWay[0].alt=ac_height;
        HoverWay[0].vxd=0;
        HoverWay[0].dot=0;
        
        PSI[0]=ac_psi;
    }

    for (idx=1; idx<6; idx++) {
        if (clockwise) { /*[顺时针]*/
            PSI[idx] = PSI[idx-1] + 90.0f;             /*[Psi=Psi+90.0]*/
            if (PSI[idx]>=360.0f) PSI[idx] -= 360.0f;
        }
        else {           /*[逆时针]*/
            PSI[idx] = PSI[idx-1] - 90.0f;             /*[Psi=Psi-90.0]*/
            if (PSI[idx]<0.0f)    PSI[idx] += 360.0f;
        }
    }

    for (idx=1; idx<7; idx++) {
        HoverWay[idx].dot=idx;
        HoverWay[idx].vxd=0;
        HoverWay[idx].alt=HoverWay[0].alt;
        
        Ax = LEN[idx-1]*sin(PSI[idx-1]/Rad2Deg);
        Ay = LEN[idx-1]*cos(PSI[idx-1]/Rad2Deg);
        WP_XY2Pos(HoverWay[idx-1].lon, HoverWay[idx-1].lat, Ax,Ay,
                 &HoverWay[idx  ].lon,&HoverWay[idx  ].lat);
    }
}


void  GUID_HoverLine (INT16S  dot, LineStruc *AB)
{
    WP_MakeLine(HoverWay[dot  ].lon, HoverWay[dot  ].lat, 
                HoverWay[dot+1].lon, HoverWay[dot+1].lat, AB);
    AB->alt = HoverWay[dot].alt;
    AB->vxd = HoverWay[dot].vxd;
}


void  GUID_Hover (void)
{
   static FP32  psi_tmp, radius;

        if (nav_guid==PW_NavHover) {
            WP_LateWay(&AB, ac_lon,ac_lat,ac_psi, &ac_dZ,&ac_dL,&ac_dPsi);

            radius = ac_Vd*ac_Vd/9.8f/0.700f;          /*[0.577=tan(30)]*/
            if (ac_dL<(radius+30.0f+Pre_mix)) {
                HoverDot+=1;
                if (HoverDot==6) { HoverDot=1;  HoverNum--; }
                if (HoverNum) GUID_HoverLine(HoverDot, &AB);
                else { WP_GetLine(ac_dot,&AB);  step_enter=0;  nav_guid=PW_NavEnter; }
                psi_cmd=AB.psi;  mode_guid=PW_GuideDim1;  token_late=TOKEN_TrackPsi;
            }

            if (mode_guid==PW_GuideDim1) {
                psi_tmp = WP_Psi2Psi(AB.psi-ac_psi);
                if (fabs(psi_tmp)<10.0f) {
                    mode_guid=PW_GuideDim2;
                    token_late=TOKEN_TrackWay;
                }
            }
			CreatTask(GUID_Hover, Timer200ms);
        }
        else CreatTask(GUID_Hover, Timer50ms); 
}
