# handlers.s - INTC software vector mode example
# Description:  Creates prolog, epilog for C ISR and enables nested interrupts
# Rev 1.0: April 23, 2004, S Mihalik, 
# Rev 1.1 Aug 2, 2004 SM - delayed writing to EOIR until after disabling EE in epilog
# Rev 1.2 Sept 8 2004 SM - optimized & corrected r3,r4 restore sequence from rev 1.1
# Rev 1.2 Sept 21 2004 SM - optimized by minimizing time interrupts are disabled
# Rev 1.3 Jul  2 2007 SM - Changes for MPC551x and mapped to .ivor_handlers section */
# Copyright Freescale Semiconductor, Inc. 2007. All rights reserved
 
# STACK FRAME DESIGN: Depth: 20 words (0xA0, or 80 bytes)
#            ************* ______________
#   0x4C     *  GPR12    *    ^
#   0x48     *  GPR11    *    |
#   0x44     *  GPR10    *    |
#   0x40     *  GPR9     *    |
#   0x3C     *  GPR8     *    |
#   0x38     *  GPR7     *  GPRs (32 bit)
#   0x34     *  GPR6     *    |
#   0x30     *  GPR5     *    |
#   0x2C     *  GPR4     *    |
#   0x28     *  GPR3     *    |
#   0x24     *  GPR0     * ___v__________
#   0x20     *  CR       * __CR__________
#   0x1C     *  XER      *    ^
#   0x18     *  CTR      *    |
#   0x14     *  LR       * locals & padding for 16 B alignment
#   0x10     *  SRR1	 *    |
#   0x0C     *  SRR0     *    |
#   0x08     *  padding  * ___v__________
#   0x04     * resvd- LR * Reserved for calling function 
#   0x00     *  SP       * Backchain (same as gpr1 in GPRs)
#            ************* 

  .extern   time_isr
  .globl IVOR10Handler
  .section .ivor_handlers     
  	
  .align 16				# Align IVOR handlers on a 16 byte boundary
                    # GHS, Cygnus, Diab(default) use .align 4; Metrowerks .align 16
 

IVOR10Handler:
prolog10:							# PROLOGUE 
	stwu		r1, -0x50 (r1)	# Create stack frame and store back chain
	stw			r12, 0x4C (r1)	# Store gprs
	stw			r11, 0x48 (r1)
	stw			r10, 0x44 (r1)
	stw			r9,  0x40 (r1)
	stw			r8,  0x3C (r1)
	stw			r7,  0x38 (r1)
	stw			r6,  0x34 (r1)
	stw			r5,  0x30 (r1)
	stw			r4,  0x2C (r1)
	stw			r3,  0x28 (r1)
	stw			r0,  0x24 (r1)	
	mfCR		r0				# Store CR
	stw			r0,  0x20 (r1)
	mfXER		r0				# Store XER
	stw			r0,  0x1C (r1)
	mfCTR		r0				# Store CTR
	stw			r0,  0x18 (r1)
	mfLR		r0				# Store LR
	stw			r0,  0x14 (r1)				
	 
	bl			time_isr			# Execute time_isr, but return here

epilog10:							# EPILOGUE
	lwz			r0,  0x14 (r1)	# Restore LR
	mtLR		r0
	lwz			r0,  0x18 (r1)	# Restore CTR
	mtCTR		r0
	lwz			r0,  0x1C (r1)	# Restore XER
	mtXER		r0
	lwz			r0,  0x20 (r1)	# Restore CR
	mtcrf		0xff, r0
	lwz			r0,  0x24 (r1)	# Restore gprs
	lwz			r3,  0x28 (r1)
	lwz			r4,  0x2C (r1)
	lwz			r5,  0x30 (r1)
	lwz			r6,  0x34 (r1)
	lwz			r7,  0x38 (r1)
	lwz			r8,  0x3C (r1)
	lwz			r9,  0x40 (r1)
	lwz			r10, 0x44 (r1)
	lwz			r11, 0x48 (r1)
	lwz			r12, 0x4C (r1)
	addi		r1, r1, 0x50	# Restore space on stack
	rfi							# End of Interrupt
