#include "MPC.H"

/*===========================================================================*
 *
 * FUNCTION:    Bit operation prototypes
 * 
 * ENTRY POINT16S S: 
 * 
 *    ClearBit   - make specified bit 0
 *    SetBit     - make specified bit 1
 *    BitStatus  - return specified bit state, 0 or 1
 *
 * NOTE:    parameter valid in 0-7
 *      
 *===========================================================================*/

static  INT8U    Twos[8] = { 1, 2, 4, 8, 16, 32, 64, 128 };

void    SetBit( INT8U  *B, INT8U  idx )
{   if (idx<8) *B |= Twos[idx]; }          // Set desired bit 


void    ClearBit( INT8U  *B, INT8U  idx )
{   if (idx<8) *B &= (255 - Twos[idx]); }   // Clear desired bit 
                                   
INT16S  BitStatus( INT8U  B, INT8U  idx )
{   if (idx<8) return((B&Twos[idx])/Twos[idx]);
    else return(0);
}
