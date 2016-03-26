#include "MPC.H"

/*--------------------------------------------------------------------------*/
    FP32        ac_lon, ac_lat;         
    FP32        ac_Vd;                  
    FP32        ac_psi;                 
    FP32        ac_height;
    FP32        psi_cat;
    INT32S      info_alt;               /*[高度信息源]*/    
/*--------------------------------------------------------------------------*/

static  FP32   x,y, psi_int;
static  FP32   lon_ini,lat_ini, psi_ini;
static  FP32   psi_int =0;              /*[积分航向,(BP=7)*(10)]*/
static INT16S    dL_mix0=0,  dZ_mix0=0;


void  fusion_refresh_gps (FP32 lon, FP32 lat, FP32 psi)
{
    x=0.0f; y=0.0f; lon_ini=lon; lat_ini=lat;
    if (Vd_gps>=0.6f) { psi_ini=psi; psi_int=0.0f; }
}

void fusion_guide(void)
{
	    if (!urg04lx.fail)
                    {
                      ac_dL=urg_deal_union.urg_deal_data.urg_dL +dL_mix*100+dL_mix0; 
                      ac_dZ=urg_deal_union.urg_deal_data.urg_dZ +dZ_mix*100+dZ_mix0;
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

void  fusion_slow (void)   //注意，此函数在urg.c中的Task_UrgRev()有被调用
{
    if((nav_guid!=PW_NavSpec)&&(nav_guid!=PW_NavEnter))
    {
        //选择侧偏信息源 左-右+
        //选择待飞距信息源 前-后+

     if (!urg04lx.fail) 
        {
      
           {   
            ac_dZ =urg_deal_union.urg_deal_data.urg_dZ+dZ_mix*100; 	
            ac_dL= urg_deal_union.urg_deal_data.urg_dL -3400+dL_mix*100;  
            urg_dPsi1=urg_deal_union.urg_deal_data.urg_dPsi;
            ac_ddZ = urg_deal_union.urg_deal_data.urg_ddZ;
            ac_ddL = urg_deal_union.urg_deal_data.urg_ddL;
            if(on_sky) 
            {
            	mode_guid=PW_GuideAuto;
            }
            }
        } 
        
     else {
            ac_dZ=0;
            ac_dL=0;
            urg_dPsi1=0;
            ac_ddZ=0;
            ac_ddL=0;
            if(on_sky) mode_guid=PW_GuideAuto;
      }
    }   
}