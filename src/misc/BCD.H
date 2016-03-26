#ifndef	_BCD_H
#define _BCD_H

/*===========================================================================*
 *
 * FUNCTION:    BCD <-> BIN operation prototypes
 * 
 * ENTRY POINT16S S: 
 * 
 *	  Bin2Bcd   - make binary code to bcd code
 *    Bcd2Bin   - make bcd code to binary code
 *
 *===========================================================================*/
INT8U 	Bin2Bcd(INT8U  B);
INT8U 	Bcd2Bin(INT8U  B);

#endif
