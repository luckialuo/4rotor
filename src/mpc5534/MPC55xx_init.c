
/*
 *
 * FILE : MPC55xx_init.c
 *
 * DESCRIPTION:
 *  This file contains the MPC55xx derivative needed initializations. 
 *  usr_init() is called by the startup code of the application at initialization time
 *  You can add needed hardware initializations here.
 *  This file also contains the RCHW and Reset Vector setup:
/*  The chip is by default setup to boot from internal Flash and the watchdog is disabled.
 */

#include "Exceptions.h"    /* IVPR and default exception handlers setup */
#include "INTCInterrupts.h" /* INTC Interrupts Requests configuration */
#include "MPC5534_HWInit.h"

#pragma section code_type ".init"

#define INIT_DERIVATIVE_INTERNAL_SETUP 1
#define INIT_EXTERNAL_BUS_INTERFACE_SETUP 1

#ifndef INIT_DERIVATIVE_INTERNAL_SETUP
#pragma error INIT_DERIVATIVE_INTERNAL_SETUP should be defined !
#endif

#ifndef INIT_EXTERNAL_BUS_INTERFACE_SETUP
#pragma error INIT_EXTERNAL_BUS_INTERFACE_SETUP should be defined !
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern __asm void __start();
__asm void usr_init();
/*lint -esym(752,__start) */

#ifdef __cplusplus
}
#endif

/*****************************************************************/
/* usr_init():                                                   */
/*   Define here the needed hardware initializations at startup  */

__asm void usr_init()
{
    /* Add needed hardware initializations in this function */
    nofralloc

    mflr     r30                         /* Save off return address in NV reg */

#if INIT_DERIVATIVE_INTERNAL_SETUP==1
    bl      INIT_Derivative              /* Derivative specific hardware initializations */
#endif
#if INIT_EXTERNAL_BUS_INTERFACE_SETUP==1
    bl      INIT_ExternalBusAndMemory    /* Set up access to external memory (inc. chip select and MMU) */
#endif
    bl      EXCEP_InitExceptionHandlers   /* Set up Default Exception handling */
    bl      INTC_InitINTCInterrupts       /* Set up INTC Interrupts Requests handling */

    mtlr    r30                          /* Get saved return address */

    blr
}



