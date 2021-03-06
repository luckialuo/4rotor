#ifndef	_BIT_H
#define	_BIT_H

/*===========================================================================*
 *
 * FUNCTION:    Bit operation prototypes
 * 
 * ENTRY POINT16S S: 
 * 
 *	  ClearBit   - make specified bit 0
 *    SetBit     - make specified bit 1
 *	  BitStatus  - return specified bit state, 0 or 1
 *
 * NOTE:	parameter valid in 0-7
 *      
 *===========================================================================*/
void	ClearBit (INT8U  *B, INT8U  idx);
void	SetBit   (INT8U  *B, INT8U  idx);
INT16S 		BitStatus(INT8U   B, INT8U  idx);

#endif
