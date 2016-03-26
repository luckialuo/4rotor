#include "MPC.H"

/*--------------------------------------------------------------------------*/

    float    gama1_AoL,           /*[¶¸ÏÂ»¬½Ç](deg)*/
             gama1_AoL_mix;
	float    RunwayAlt_mix;

/*--------------------------------------------------------------------------*/

           
void  ALIP_Init (void)
{
    gama1_AoL = -3.5f;    /*[-5.0¶È]*/
}


float  ALIP_Profile (float X)
{
    float Hcmd;
    
    Hcmd = X*tan((gama1_AoL+gama1_AoL_mix)/Rad2Deg);

    return (Hcmd);
}

