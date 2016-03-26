#ifndef _MPC_H_
#define _MPC_H_

//#include <stdlib.h>
//#include <stdio.h>
//#include <limits.h>
//#include <math.h>
//#include <time.h>
#include "startup\includes.h"

#define LOBYTE(w)       ((BYTE)(w))
#define HIBYTE(w)       ((BYTE)(((UINT)(w) >> 8) & 0xFF))

#define True            1
#define False           0

#define FALSE           0
#define TRUE            1

#define DEFAULT_STACK  512

typedef union {
    INT8U   B[4];
    INT16S  D[2];
    INT16U  W[2];
    INT32S  DW;
}dWordStruc;

typedef struct  {
    INT16U        invalid;
    INT16U       counter;
    INT16S       fail;       
    INT16U        freq;
}SensorStruc;

typedef	struct {
	FP32 Ketheta, KeWz, KeH, KeIH, KedH, Kegama;
	FP32 Thetag_climb,Thetag_level,Thetag_dive,Thetag_land;
	FP32 Kagama, KaWx, KrWy, Kgpsi,KgZ,Kgdpsi;
	FP32 KaIZ,KgrZ,Kgrdpsi;
	FP32 KaIGama, KeITheta, KeTrim;
    //FP32 KePitch, KrHead, KeTrim;
    //FP32 KrZ, Krdpsi, KeItheta; //K for taxi and takeoff

} PIDStruc;

typedef  union {
	FP32   f[22];
	PIDStruc   P;
}KPIDStruc;

#define	Rad2Deg	57.2957795130823208767981548141052


#include "kernel\TASKMAN.h"

#include "control\PID.H"
#include "control\LAW.H"
#include "control\CONTROL.H"
#include "control\RPVS.H"
#include "control\ROM.H"

#include "device\ENGINE.H"


#include "guide\WP.H"
#include "guide\FUSION.H"
#include "guide\GUIDE.H"
#include "guide\HOVER.H"
#include "guide\HOME.H"
#include "guide\ALIP.H"

#include "misc\BITS.H"
#include "misc\MISC.H"
#include "misc\IMATH.H"

#include "sensor\srf02.h"
#include "sensor\gps.h"
#include "sensor\AHRS.h"
#include "sensor\mpxv.h"
#include "sensor\urg.h"

#include "startup\INIT.H"

#include "tele\TELE.H"
#include "tele\CMD.H"
#include "test\TEST.H"
#include "test\PARM.H"



#endif
