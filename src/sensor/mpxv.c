#include "MPC.H"

SensorStruc	 ss_Mpxv;

/*---------------------------------------------------------------------------*/
	FP32           Vi_adc;                        /*[adc 空速][m]*/
    FP32        height_adc;                       /*[adc气压高度][m]*/
/*---------------------------------------------------------------------------*/
    static void update_window10(float buf[],int len,float data_new);
    static float avrg10(float buf[]);
				  				  
//气动数据库

//空速（1m/s为步长)转动压

float Violate[81] = { 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,10.0,11.0,12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,
			         20.0,21.0,22.0,23.0,24.0,25.0,26.0,27.0,28.0,29.0,30.0,31.0,32.0,33.0,34.0,35.0,36.0,37.0,38.0,39.0,
			         40.0,41.0,42.0,43.0,44.0,45.0,46.0,47.0,48.0,49.0,50.0,51.0,52.0,53.0,54.0,55.0,56.0,57.0,58.0,59.0,
			         60.0,61.0,62.0,63.0,64.0,65.0,66.0,67.0,68.0,69.0,70.0,71.0,72.0,73.0,74.0,75.0,76.0,77.0,78.0,79.0,
			         80.0};//(m/s)
			  

float dynpress[81] = {      0, 0.6125f, 2.4500f, 5.5126f, 9.8003f, 15.313f, 22.052f, 30.016f, 39.205f, 49.621f, 61.163f, 74.132f, 88.227f, 103.55f, 120.10f, 137.88f, 156.89f, 177.12f, 198.59f, 221.29f,
					  245.21f, 270.37f, 296.76f, 324.38f, 353.24f, 383.33f, 414.65f, 447.22f, 481.01f, 516.05f, 552.32f, 589.84f, 628.59f, 668.58f, 709.82f, 752.30f, 796.02f, 840.99f, 887.21f, 934.68f,
					  983.39f, 1033.4f,	1084.6f, 1137.0f, 1190.8f, 1245.7f, 1302.0f, 1359.5f, 1418.2f, 1478.3f, 1539.5f, 1602.1f, 1665.9f, 1731.0f,	1797.3f, 1864.9f, 1933.8f, 2004.0f,	2075.5f, 2148.2f,
					  2222.2f, 2297.5f,	2374.1f, 2451.9f, 2531.1f, 2611.5f,	2693.2f, 2776.3f, 2860.6f, 2946.2f, 3033.1f, 3121.4f, 3210.9f, 3301.7f,	3393.9f, 3487.4f, 3582.1f, 3678.2f,	3775.7f, 3874.4f,	
					  3974.5f};// (Pa)
			   

float speed_voltage[81] = {   1.02f, 1.0206f, 1.0225f, 1.0256f,   1.03f, 1.0356f, 1.0425f, 1.0506f,   1.06f, 1.0706f, 1.0825f, 1.0956f,   1.11f, 1.1256f, 1.1425f, 1.1606f,   1.18f, 1.2007f, 1.2226f, 1.2457f,
					  		1.2701f, 1.2958f, 1.3227f, 1.3509f, 1.3803f,  1.411f, 1.4429f, 1.4762f, 1.5106f, 1.5464f, 1.5834f, 1.6216f, 1.6612f,  1.702f,  1.744f, 1.7873f, 1.8319f, 1.8778f,  1.925f, 1.9734f,
				      		2.0231f,  2.074f, 2.1263f, 2.1798f, 2.2346f, 2.2907f,  2.348f, 2.4067f, 2.4666f, 2.5278f, 2.5903f, 2.6541f, 2.7192f, 2.7856f, 2.8533f, 2.9222f, 2.9925f, 3.0641f,  3.137f, 3.2111f,
				      		3.2866f, 3.3634f, 3.4415f,  3.521f, 3.6017f, 3.6837f, 3.7671f, 3.8518f, 3.9378f, 4.0251f, 4.1138f, 4.2038f, 4.2951f, 4.3878f, 4.4818f, 4.5771f, 4.6738f, 4.7718f, 4.8712f, 4.9719f,
				 	  		5.074f};//空速计电压(V) 
			  


//高度(m)转电压


float height[81] = {      0,  100.0,  200.0,  300.0,  400.0,  500.0,  600.0,  700.0,  800.0,  900.0, 1000.0, 1100.0, 1200.0, 1300.0, 1400.0, 1500.0, 1600.0, 1700.0, 1800.0, 1900.0,
			   		 2000.0, 2100.0, 2200.0, 2300.0, 2400.0, 2500.0, 2600.0, 2700.0, 2800.0, 2900.0, 3000.0, 3100.0, 3200.0, 3300.0, 3400.0, 3500.0, 3600.0, 3700.0, 3800.0, 3900.0,
			   		 4000.0, 4100.0, 4200.0, 4300.0, 4400.0, 4500.0, 4600.0, 4700.0, 4800.0, 4900.0, 5000.0, 5100.0, 5200.0, 5300.0, 5400.0, 5500.0, 5600.0, 5700.0, 5800.0, 5900.0,
			   		 6000.0, 6100.0, 6200.0, 6300.0, 6400.0, 6500.0, 6600.0, 6700.0, 6800.0, 6900.0, 7000.0, 7100.0, 7200.0, 7300.0, 7400.0, 7500.0, 7600.0, 7700.0, 7800.0, 7900.0,
			   	 	 8000.0};//高度（m）
			 

float stapress[81] = { 101.33f, 100.13f, 98.945f, 97.773f, 96.611f, 95.461f, 94.322f, 93.194f, 92.076f,  90.97f, 89.875f,  88.79f, 87.716f, 86.652f, 85.599f, 84.556f, 83.524f, 82.501f, 81.489f, 80.487f,
				 	   79.495f, 78.513f, 77.541f, 76.578f, 75.626f, 74.683f, 73.749f, 72.825f,  71.91f, 71.005f, 70.109f, 69.222f, 68.344f, 67.475f, 66.615f, 65.764f, 64.922f, 64.089f, 63.264f, 62.448f,
				  	    61.64f,  60.841,  60.05f, 59.268f, 58.494f, 57.728f, 56.971f, 56.221f, 55.479f, 54.746f,  54.02f, 53.302f, 52.592f, 51.889f, 51.194f, 50.507f, 49.827f, 49.154f, 48.489f, 47.832f,
				 	   47.181f,  46.538, 45.901f, 45.272f,  44.65f, 44.035f, 43.426f, 42.825f,  42.23f, 41.642f, 41.061f, 40.486f, 39.918f, 39.356f,   38.8f, 38.251f, 37.709f, 37.172f, 36.642f, 36.118f,	
				 	   35.6f};//静压(Pa)
			   

float height_voltage[81] = {4.1663f, 4.1114f, 4.0571f, 4.0033f, 3.9499f, 3.8972f, 3.8449f, 3.7931f, 3.7418f,  3.691f, 3.6407f, 3.5909f, 3.5416f, 3.4928f, 3.4445f, 3.3966f, 3.3492f, 3.3023f, 3.2559f, 3.2099f,
					  		3.1643f, 3.1193f, 3.0746f, 3.0304f, 2.9867f, 2.9434f, 2.9006f, 2.8582f, 2.8162f, 2.7746f, 2.7335f, 2.6928f, 2.6525f, 2.6126f, 2.5731f, 2.5341f, 2.4954f, 2.4572f, 2.4193f, 2.3819f,
					  		2.3448f, 2.3081f, 2.2718f, 2.2359f, 2.2004f, 2.1652f, 2.1305f,  2.096f,  2.062f, 2.0283f,  1.995f, 1.9621f, 1.9295f, 1.8972f, 1.8653f, 1.8338f, 1.8026f, 1.7717f, 1.7412f,  1.711f,
					  		1.6811f, 1.6516f, 1.6224f, 1.5935f, 1.5649f, 1.5367f, 1.5088f, 1.4812f, 1.4539f, 1.4269f, 1.4002f, 1.3738f, 1.3477f, 1.3219f, 1.2964f, 1.2712f, 1.2463f, 1.2217f, 1.1974f, 1.1733f,	
					  		1.1495f};//高度计电压(V)
					  		

/*float height_voltage[81] = {4.2663f, 4.2114f, 4.1571f, 4.1033f, 4.0499f, 3.9972f, 3.9449f, 3.8931f, 3.8418f,  3.791f, 3.7407f, 3.6909f, 3.6416f, 3.5928f, 3.5445f, 3.4966f, 3.4492f, 3.4023f, 3.3559f, 3.3099f,
					  		3.2643f, 3.2193f, 3.1746f, 3.1304f, 3.0867f, 3.0434f, 3.0006f, 2.9582f, 2.9162f, 2.8746f, 2.8335f, 2.7928f, 2.7525f, 2.7126f, 2.6731f, 2.6341f, 2.5954f, 2.5572f, 2.5193f, 2.4819f,
					  		2.4448f, 2.4081f, 2.3718f, 2.3359f, 2.3004f, 2.2652f, 2.2305f,  2.196f,  2.162f, 2.1283f,  2.095f, 2.0621f, 2.0295f, 1.9972f, 1.9653f, 1.9338f, 1.9026f, 1.8717f, 1.8412f,  1.811f,
					  		1.7811f, 1.7516f, 1.7224f, 1.6935f, 1.6649f, 1.6367f, 1.6088f, 1.5812f, 1.5539f, 1.5269f, 1.5002f, 1.4738f, 1.4477f, 1.4219f, 1.3964f, 1.3712f, 1.3463f, 1.3217f, 1.2974f, 1.2733f,	
					  		1.2495f};*/					 			  
//=============================================================================
//interp1
//=============================================================================


static int  PW2_find(float A[],float X,int len)
{
	int result=0;
	int i,P_Start,P_End;
	
	if (A[0] < A[len-1]) { /*[数组顺序排列]*/
		P_Start=0;     P_End=len;
		
		if      (X < A[0])      result = 0;		
		else if (X < A[len-1]) {
			if (X >= A[len/2]) P_Start = len/2;
			else		      P_End   = len/2+1;
			
			for (i=P_Start; i<P_End; i++) {
				if (X < A[i]) { result = i-1; break; }
			}
		}
		else                    result = len-2;
	}
	else {                 /*[数组逆序排列]*/
		P_Start=len-1; P_End=0; 
		
		if      (X >= A[0])		result = 0;
		else if (X > A[len-1]) {
			if (X > A[len/2]) P_Start = len/2+1;
			else	          P_End   = len/2;
			
			for (i=P_Start; i>=P_End; i--) {
				if (X < A[i]) { result = i; break; }
			}
		}
		else                    result = len-2;
	}
	return (result);
}

static float	PW2_interp1(float* A, float Dim1[], int Len1, float X1)
{
	int 	r;
	float  DA, Y;

	r = PW2_find(Dim1,X1,Len1);

	DA = (X1-Dim1[r])/(Dim1[r+1]-Dim1[r]);
	Y = A[r] + (A[r+1]-A[r])*DA; 	return (Y);
}

/****************************************************************************
* 名称：CaculHeight()
* 功能：测量飞行高度
* 入口参数：
* 出口参数：
****************************************************************************/


double CaculHeight(double vol)
{ 
   float H_height;

		/*if(vol >= height_voltage[0])
  		{
  			H_height = 0;
  		}
  		else if(vol <= height_voltage[80])
  		{
  			H_height = 8000L;
  		}
  		else
  		{
  			for(i=0;i<81;i++)
  			{
  				if(height_voltage[i] >= vol)
  				j = i;
  			}
  			H_height = height[j] + (height[j+1]-height[j])*(height_voltage[j]-vol)/(height_voltage[j]-height_voltage[j+1]);
  		}
  		press_tmp=PW2_interp1(stapress,height_voltage, 81, H_height);
  		H_height=PW2_interp1(height,stapress, 81, press_tmp);*/
  		H_height=PW2_interp1(height,height_voltage, 81, vol);

		
    return(H_height); 
}
  		
  		
/****************************************************************************
* 名称：Cacul()
* 功能：测量空速
* 入口参数：
* 出口参数：
****************************************************************************/

double CaculSpeed(double vol_sped)
{
   float sped;
   int i,j;


  	
  		if(vol_sped <= speed_voltage[0])
  		{
  			sped = 0;
  		}
  		else if(vol_sped >= speed_voltage[80])
  		{
  			sped = 80;
  		}
  		else
  		{
  			for(i=0;i<81;i++)
  			{
  				if(speed_voltage[i] <= vol_sped)
  				j = i;
  			}

  	    sped = Violate[j] + (vol_sped-speed_voltage[j])*(Violate[j+1]-Violate[j])/(speed_voltage[j+1]-speed_voltage[j]);

  		}
   
   return(sped);
}

/****************************************************************************
* 名称：MVPX_AD_Task(void)
* 功能：压力传感器数据采集任务
* 入口参数：无
* 出口参数：无
* 运行周期：100ms
****************************************************************************/
void    Task_MpxvRev(void)     
{
	
  //AnalogInReadDataSpi (ANALOGINSPICH1, &vol1);    //通道1－－高度计
  //AnalogInReadDataSpi (ANALOGINSPICH2, &vol2);    //通道2－－空速计
  float   vol1 = 0,vol2 = 0,vol3 = 0,vol4 = 0;
  float   H_height;


  
  static float H_adc[10];
  static INT8U cnt=0;
  static float height_adc_old;
  float tmp;
  
  /*[滑动窗口+一阶滤波]*/
	if(cnt<6)
	{
		AnalogIn(ANALOGINCH2, &vol1);
		height_adc=CaculHeight(vol1);
		H_adc[cnt]=height_adc;
		height_adc_old=height_adc;
		cnt++;
	}
	else 
	{
		AnalogIn(ANALOGINCH2, &vol1);
		tmp=CaculHeight(vol1);
		H_height=tmp;
		if((tmp-height_adc_old)>7.0f||(tmp-height_adc_old)<-7.0f) tmp=height_adc_old;
		update_window10(H_adc,6,tmp);
		tmp=avrg10(H_adc);
		height_adc=height_adc_old*0.98f+tmp*0.02f;//一阶滤波
		height_adc_old=height_adc;
	}
	
	
	//AnalogIn(ANALOGINCH2, &vol1);
	//height_adc=CaculHeight(vol1);
	//AnalogIn(40, &vol3); //参考电压
	//AnalogIn(41, &vol4); //地电压
	
    //printf("H %f H_raw %f CHP %f CH40 %f CH41 %f\r\n",height_adc,H_height,vol1,vol3,vol4);
	//AnalogIn(ANALOGINCH1, &vol2);    
 	//Vi_adc =CaculSpeed(vol2)-4.0f;
    
    //printf("%f\n ",height_adc);
    // printf("%f\n",vol1);
    ss_Mpxv.counter++;                            //计数值  lee                            

}


void  MPXV_Monitor(void)                       
{

    static INT8U	 cnt = 0;
    static INT8U  flag1s = FALSE;
    static INT16U	 old_counter;
	
	  cnt ++;
	  cnt %= 100;
	  if ((cnt%10) == 0)
	       flag1s = TRUE;                                    
    	    
	  if (flag1s) 
	  {
	       flag1s = FALSE;
		   ss_Mpxv.freq  = ss_Mpxv.counter - old_counter;   
		   old_counter  = ss_Mpxv.counter;
	  }
	  
}

static float avrg10(float buf[])
{
	int i;
	float result=0.0f;
	for(i=0;i<6;i++) result+=buf[i];
	return result/6.0f;
}

static void update_window10(float buf[],int len,float data_new)
{
	int i;
	for(i=0;i<len-1;i++) buf[i]=buf[i+1];
	buf[len-1]=data_new;
}