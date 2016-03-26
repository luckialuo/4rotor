#ifndef __GPS__
#define __GPS__

#include "ppc_oscom.h"

/*---------------------------------------------------------------------------*/
//GPS.C
/*---------------------------------------------------------------------------*/
    extern FP32          lon_gps, 		    
                   lat_gps;         
    extern INT16U          psi_gps;         
    extern FP32          alt_gps,         
                   Hdot_gps;         
    extern FP32          Vd_gps;         
    extern INT8U           hms_gps[3],
                   ymd_gps[3];               /*[Äê:ÔÂ:ÈÕ][BCD]*/      

    extern INT8U          type_gps,         
                 valid_gps,         
                  used_gps,         
                  star_gps;         

    extern FP32          gdop_gps,         
                  pdop_gps,         
                  hdop_gps,         
                  vdop_gps,         
                  tdop_gps;  
    extern INT8U  tag_DGPS;        
    
    extern SensorStruc	 ss_Gps;
    extern INT8U          simu_gps;
	extern FP32   ALign_length, ALign_pitch, ALign_heading,ac_palt,ALign_length_temp, ALign_pitch_temp,ALign_alt,ALign_lon;

    
/*---------------------------------------------------------------------------*/


void  Task_GpsRev(void);
void  GPS_Monitor(void);



#endif