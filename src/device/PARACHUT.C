#include "MPC.H"

/*--------------------------------------------------------------------------*/

    INT16S           open_par,
                 safe_par,
                 auto_par;

/*--------------------------------------------------------------------------*/

void  PAR_Monitor (void)
{
   static INT32S     timer;

    timer = 10*Timer1s;
    //while (1) {
        if (open_par) {
            timer -= Timer100ms;
            if (timer==0L) open_par = False;
        }
        else    timer = 10*Timer1s;
	    CreatTask(PAR_Monitor, Timer100ms);
    //}
}

void  PAR_ON (void)
{
    //MPWMOUT[7].pwmhi=2.0;
 	//MpwmOut(7); 

}


void  PAR_OFF (void)
{
    //MPWMOUT[7].pwmhi=1.0;
 	//MpwmOut(7); 

}

void  PAR_AutoOpen (void)
{
    static INT16S   step=0;
   
  //  while (1) {
        if (auto_par) {
            switch (step) {
            case 0:
                ENG_Stop();  BackupRPVs();                   /*[发动机停车状态]*/
                step++; 
				CreatTask(PAR_AutoOpen, 5*Timer1s);

                break;
            case 1:
                PAR_ON(); BackupRPVs();                      /*[输出开伞控制信号]*/
                auto_par=False;
				CreatTask(PAR_AutoOpen, Timer100ms);

                break;
            }
        }
        else { step=0; 
		CreatTask(PAR_AutoOpen, Timer50ms);}
}

void  PAR_SafeOpen (void)
{
    static const FP32    height_safe=50.0f;
    static INT16U     cnt_adc=0, cnt300=0;
    
    if (mode_long==PW_LongDive && !tag_land) {
        if (ac_dH<height_safe) cnt_adc++;
        else                cnt_adc=0;
        if (cnt_adc>20) { PAR_ON(); ENG_Stop(); BackupRPVs(); }
    }
    else  cnt_adc=0;
}       
