#include "MPC.H"
#include <math.h>

FP32  Psi_360(FP32 angle)
{
	FP32 tmp_angle;
    if (angle<0)  tmp_angle = angle+360;
    else if(angle>360) tmp_angle = angle - 360;
	else       tmp_angle =angle;
	
	return(tmp_angle);
}



FP32   WP_Psi2Psi(FP32 angle)
{
    FP32    tmp_angle;

    if      (angle > 180.0f)    tmp_angle = angle - 360.0f;
    else if (angle <-180.0f)    tmp_angle = angle + 360.0f;
    else                        tmp_angle = angle;
    return (tmp_angle);
}

FP32    WP_Psi(FP32 x, FP32 y)
{
    FP32    tmp_psi;

    if ((fabs(x)+fabs(y))<1e-6) return (0.0f);

    tmp_psi = (FP32)atan2(y,x)*Rad2Deg;
    if ((tmp_psi<=180.0f) && (tmp_psi>90.0f))
        tmp_psi = 450.0f - tmp_psi;
    else
        tmp_psi =  90.0f - tmp_psi;

    return (tmp_psi);
}

void WP_BL2xy(double B, double L, double *x, double *y)
{   
    //sizeof(double) sizeof(float)
	static double a=6378137,  e2 =0.0066943799013, e22=0.00673949674227;
	static double sinB, cosB, cos3B, cos5B;
	static double l, l2, l3, l4, l5, l6;
	static double t, t2, t4, n2, n4;
	static double N, X;
	static double m0,m2,m4,m6,m8, a0,a2,a4,a6,a8;
	static double L0;

    //L0 =-121.0/Rad2Deg;  B =B/Rad2Deg;   L =L/Rad2Deg;
	L0 =floor(ac_lon)/Rad2Deg;  B =B/Rad2Deg;   L =L/Rad2Deg;
	sinB =sin(B);
	cosB =cos(B); cos3B=pow(cosB,3); cos5B =pow(cosB,5);
	l  =(L-L0); l2=l*l; l3=l2*l; l4=l3*l; l5=l4*l; l6=l5*l;

	t =tan(B); n2=e22*cosB*cosB; t2=t*t; t4=t2*t2;  n4=n2*n2;
	N = a/sqrt(1-e2*sinB*sinB);

	m0 =a*(1-e2);
	m2 =3*e2*m0/2.0;
	m4 =5*e2*m2/4.0;
	m6 =7*e2*m4/6.0;
	m8 =9*e2*m6/8.0;

	a0 =  m0    +   m2/2.0  + 3*m4/8.0  + 5*m6/16.0 + 35*m8/128.0;
	a2 =m2/2.0  +   m4/2.0  +15*m6/32.0 + 7*m8/16.0;
	a4 =m4/8.0  + 3*m6/16.0 + 7*m8/32.0;
	a6 =m6/32.0 +   m8/16.0;
	a8 =m8/128.0;

	X = a0*B - a2*sin(2*B)/2.0 + a4*sin(4*B)/4.0 - a6*sin(6*B)/6.0 + a8*sin(8*B)/8.0;

	*x =X +N*sinB*cosB*l2/2 + N*sinB*cos3B*(5-t2+9*n2+4*n4)*l4/24 
		 +N*sinB*cos5B*(61-58*t2+t4)*l6/720;
	*y =N*cosB*l + N*cos3B*(1-t2+n2)*l3/6 + N*cos5B*(5-18*t2+t4+14*n2-58*n2*t2)*l5/120;
	*y =*y +500000;
}

void  WP_Pos2XY (float lon_ref,float lat_ref, float lon,float lat, float *x,float *y)
{
/*  float   iPsi, Clat;
    float  dLon, dLat, X1;	
    
    dLon=lon-lon_ref; 
    dLat=lat-lat_ref;  

    iPsi = (lat_ref+lat)/2/Rad2Deg;
    Clat = cos(iPsi); 
   
    *x = (6383487.606f*Clat - 5357.31f*cos(3*iPsi)) * dLon/ Rad2Deg;
    *y = (6367449.134f - 32077.0f*cos(2*iPsi)) * dLat / Rad2Deg;
*/     

    static double x_ref, y_ref, x_des, y_des;		
	WP_BL2xy(lat, lon, &x_des, &y_des);
	WP_BL2xy(lat_ref, lon_ref, &x_ref, &y_ref);
	*y =x_des - x_ref; 
	*x =y_des - y_ref;

/*	static	float	iPsi, C1P, C2P, C3P;
	static	float	dLon, dLat;
	static	float	lonH, lonL, latH, latL;
	
    dLon=lon-lon_ref;
    dLat=lat-lat_ref;  

    iPsi = (lat_ref+lat)/114.5916;
    C1P = cos(iPsi); C2P = cos(2*iPsi); C3P = cos(3*iPsi);
   
    *x = (111412.876*C1P-93.503*C3P)*dLon;
    *y = (111132.952-559.849*C2P)*dLat;  

    int   iPsi, C1P, C2P, C3P;
    long  dLon, dLat, X1;
    long  lonH, lonL, latH, latL;
	long  lat_ref_L, lon_ref_L, lat_L, lon_L;

    lat_ref_L=lat_ref*1e6; lon_ref_L=lon_ref*1e6; lat_L=lat*1e6; lon_L=lon*1e6; 
    
    dLon=lon_L-lon_ref_L;  lonH=dLon/1000L;  lonL=dLon%1000L;
    dLat=lat_L-lat_ref_L;  latH=dLat/1000L;  latL=dLat%1000L;

    iPsi = (int)((lat_ref_L+lat_L)/25L*64L/28125L);
    C1P = icos(iPsi); C2P = icos(2*iPsi); C3P = icos(3*iPsi);

    X1=C1P*lonH/294L;
    *x = (X1 - C3P*lonH/350448L + C1P*lonL/294113L - X1*113L/294000L);
    *y = (111133L*latH/1000L + 111133L*latL/1000000L - C2P*latH/58530L); 
*/

}


void  WP_XY2Pos (float lon_ref, float lat_ref, float x, float y,  float *lon, float *lat)
{
    float  R=6378165.0f;
    float  Clat;   


    Clat = cos(lat_ref/Rad2Deg);

    *lon = lon_ref + x/Clat*Rad2Deg/R;
    *lat = lat_ref + y*Rad2Deg/R;
}


void  WP_RotateXY(float Xen, float Yen, float Psi, float *Xr, float *Yr)
{
    float  SPsi;
    float  CPsi;

    CPsi=cos(Psi/Rad2Deg); 
    SPsi=sin(Psi/Rad2Deg); 

    *Xr = (SPsi*Xen+CPsi*Yen);
    *Yr = (SPsi*Yen-CPsi*Xen);
}


INT16S   WP_GetPoint(INT16S  dot, PointStruc *A)
{
    dWordStruc  src;
    INT8U        wp[13];
    INT16S          flag=False;

    ROM_ReadWP(dot, wp, sizeof(wp));
    if (wp[0]==dot) {
        A->dot = wp[0];
            src.B[3]=wp[1]; src.B[2]=wp[2];
            src.B[1]=wp[3]; src.B[0]=wp[4];
        A->lon = src.DW*0.000001f;
	
            src.B[3]=wp[5]; src.B[2]=wp[6];
            src.B[1]=wp[7]; src.B[0]=wp[8];
        A->lat = src.DW*0.000001f;

            src.B[3]=wp[9]; src.B[2]=wp[10];
        A->alt = src.D[1];
            src.B[3]=wp[11]; src.B[2]=wp[12];
        A->vxd = src.W[1];
        flag = True;
    }
    return (flag);
}


int  WP_GetLine (int dot, LineStruc *AB)
{
    PointStruc  A, B;                                                     
    int         a, b, flag=False;
    int  dotnext;                                                                       
    a = WP_GetPoint(dot,   &A);
    dotnext=dot+1; if(dotnext>dot_total) dotnext=1;
    b = WP_GetPoint(dotnext, &B);
    if (a && b) {
        WP_MakeLine(A.lon,A.lat, B.lon,B.lat, AB);
        AB->alt = A.alt;
        AB->vxd = A.vxd;
        flag = True;
    }
    return (flag);
}


void  WP_MakeLine(float lon_a,float lat_a, float lon_b,float lat_b, LineStruc *AB)
{
    float  x=0,y=0;
    float  xw,yw;

    WP_Pos2XY(lon_a,lat_a, lon_b,lat_b, &x,&y);
    AB->psi = WP_Psi(x,y);
    AB->lon = lon_b;    
    AB->lat = lat_b;
    WP_RotateXY(x,y, AB->psi, &xw,&yw);    AB->len=xw;
}


void  WP_LateWay(LineStruc *AB, float lon,float lat,float psi, float *dZ,float *dL,float *dPsi)
{
    float  AxEN,AyEN;    /*[(lon,lat)在东北系的坐标]*/
    float  AxWP,AyWP;    /*[(lon,lat)在航段AB上的坐标]*/

    WP_Pos2XY(AB->lon,AB->lat, lon,lat, &AxEN,&AyEN);
    WP_RotateXY(AxEN,AyEN, AB->psi, &AxWP,&AyWP);

    *dPsi = WP_Psi2Psi(psi - AB->psi);            /*[相对航线偏航角][左偏为-,右偏为+]*/
    *dZ   = -AyWP;                                /*[侧偏距][左偏为-,右偏为+]*/ 
    *dL   = -AxWP;
}

