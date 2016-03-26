#include "MPC.H"

/*---------------------------------------------------------------------------*/
//GPS.C
/*---------------------------------------------------------------------------*/


#define CRC32_POLYNOMIAL 0xEDB88320L


#define NARROW_INT	 50
#define SINGAL		 16
#define NARROW_FLOAT 34
#define L1_FLOAT     32
#define L1_INT       48

unsigned long  POS_TYPE;

    FP32           lon_gps, 		    
                   lat_gps;         
    INT16U          psi_gps;         
    FP32           alt_gps,         
                   Hdot_gps;         
    FP32           Vd_gps;         
    INT8U           hms_gps[3],
                   ymd_gps[3];               /*[年:月:日][BCD]*/      

    INT8U          type_gps,         
                 valid_gps,         
                  used_gps,         
                  star_gps;         

    FP32          gdop_gps,         
                  pdop_gps,         
                  hdop_gps,         
                  vdop_gps,         
                  tdop_gps; 
    INT8U         tag_DGPS;         
    

    INT8U          simu_gps;

	FP32   ALign_length, ALign_pitch, ALign_heading,ac_palt,ALign_length_temp, ALign_pitch_temp,ALign_alt,ALign_lon;

    SensorStruc	 ss_Gps;
    
    
    BYTE UBX_buffer[40];
	BYTE ck_a 					= 0;
	BYTE ck_b 					= 0;
	BYTE UBX_class				= 0;
	BYTE UBX_id					= 0;
	BYTE UBX_payload_length_hi	= 0;
	BYTE UBX_payload_length_lo	= 0;
	BYTE UBX_payload_counter	= 0;
	BYTE UBX_ck_a 				= 0;
	BYTE UBX_ck_b				= 0;



    
/*---------------------------------------------------------------------------*/

union long_union {
	long dword;
	unsigned char byte[4];
} longUnion;


long join_4_bytes(BYTE Buffer[])
{
	longUnion.byte[3] = *Buffer;
	longUnion.byte[2] = *(Buffer+1);
	longUnion.byte[1] = *(Buffer+2);
	longUnion.byte[0] = *(Buffer+3);
	return(longUnion.dword);
}

void checksum(BYTE data)
{
	ck_a += data;
	ck_b += ck_a; 
}

void GPS_join_data(void);

void  Task_GpsRev(void)       //从com4口接收GPS
{
	static unsigned long GPS_timer=0;
	static BYTE GPS_step = 0;
	BYTE data;
	int numc,i;
	unsigned char buf[100];
	
	if(!simu_gps) 
	{
		numc = UartCom4RxLen();  
		if(numc>100) numc=100;
		if (numc > 0){
		UartCom4In(buf,numc);  
		for (i=0;i<numc;i++)	
		{
			data=buf[i];
			switch(GPS_step)		 
			{
				case 0:	
					if(data==0xB5)	 GPS_step++;
					break; 
				case 1:	
					if(data==0x62)	GPS_step++;	
					else  GPS_step=0;	 	 
					break;
				case 2:
					UBX_class=data;   
					checksum(UBX_class);
					GPS_step++;
					break;
				case 3:
					UBX_id = data;
					checksum(UBX_id);
					GPS_step++;
					break;
				case 4:
					UBX_payload_length_hi=data;
					checksum(UBX_payload_length_hi);
					GPS_step++;
					break;
				case 5:
					UBX_payload_length_lo=data;
					checksum(UBX_payload_length_lo);
					GPS_step++;
					break;
				case 6: 
					UBX_buffer[UBX_payload_counter] = data;
					checksum(data);
					UBX_payload_counter++;
					if (UBX_payload_counter >= UBX_payload_length_hi) GPS_step++; 
					break;

				case 7:
					UBX_ck_a=data;	 
					GPS_step++;
					break;
				case 8:
					UBX_ck_b=data;	 				 
					if((ck_a == UBX_ck_a) && (ck_b == UBX_ck_b)){ 
						GPS_join_data();							
					}
					GPS_step = 0;
					UBX_payload_counter = 0;
					ck_a = 0;
					ck_b = 0;
					break;
			}
		}	
	}
	}

}

/****************************************************************
 		解码GPS数据
 ****************************************************************/
void GPS_join_data(void)
{
	int j;
	static FP32 Vd_gps_old=0;
	if(UBX_class == 0x01) 
	{
		switch(UBX_id){
		
		case 0x02: //ID NAV-POSLLH 
			j=0;
		
			j+=4;
			lon_gps = join_4_bytes(&UBX_buffer[j])/10000000.0f;
			j+=4;
			lat_gps = join_4_bytes(&UBX_buffer[j])/10000000.0f;
		//	j+=4;
			j+=8;
			alt_gps = join_4_bytes(&UBX_buffer[j])/1000.0f; //alt_MSL
			j+=4;
			/*
		    if(used_gps>3)
		    {
		    	ss_Gps.invalid=ss_Gps.fail=0;	
		    	fusion_refresh_gps (lon_gps, lat_gps, psi_gps);  
		    }
			*/
			break;
			
		case 0x03://ID NAV-STATUS 
			
			if(UBX_buffer[4] >= 0x03)
			{
				if(used_gps>3)
			    {
			    	ss_Gps.invalid=ss_Gps.fail=0;	
			    	fusion_refresh_gps (lon_gps, lat_gps, psi_gps);  
			    }
			
			//	GPS_fix = VALID_GPS; 		//valid position
			//	GPS_update = GPS_NONE;
			} 
			else 
			{
				ss_Gps.fail=1;
			//	GPS_fix = BAD_GPS; 			//invalid position
			}
			break;
			
		case 0x06:
			used_gps=UBX_buffer[47];
			break;
		case 0x12:// ID NAV-VELNED 
			j=12;
			Hdot_gps = -join_4_bytes(&UBX_buffer[j])/100.0f; //Hdot m/s
			j+=8;
			Vd_gps = join_4_bytes(&UBX_buffer[j])/100.0f; // Ground speed 2D
			j+=4;

			if (Vd_gps >= 0.12f){
				psi_gps = join_4_bytes(&UBX_buffer[j])/100000.0f; // Heading 2D
			}
			j+=4;
			//GPS_update |= GPS_HEADING;
			break; 
		default:break;
			
		}
	}
}


void  GPS_Monitor(void)                                 //放入100ms的任务
{

    static INT8U	 cnt = 0;
    static INT8U  flag1s = FALSE;
    static INT16U	 old_counter;
    ss_Gps.invalid +=1;    
    if (ss_Gps.invalid>=20)   ss_Gps.fail=1;
    	
	  cnt ++;
	  cnt %= 100;
	  if ((cnt%10) == 0)
	       flag1s = TRUE;                                   //GPS_Monitor 100ms跑一次  
    	    
	  if (flag1s) 
	  {
	       flag1s = FALSE;
		   ss_Gps.freq  = ss_Gps.counter - old_counter;       //ss_gps.counter是GPS任务内的计数值    
		   old_counter  = ss_Gps.counter;
	  }
	  
}


