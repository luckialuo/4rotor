#ifndef	_TASKMAN_H
#define _TASKMAN_H

/*===========================================================================*
 *
 * FUNCTION:    task manage prototypes
 * 
 * ENTRY POINTS: 
 * 
 *	 CreatTask          - creat a new active/wait task
 *   GetActiveTask      - get one current active task from active-task-queue
 *	 ModifyWaitTaskTimer- manage waiting tasks, and if any waiting task is 
 *                        active, then put it into active-task-queue
 *	 DelWaitTask        - delete specified wait-task from wait-task-queue
 *
 * NOTE:	ModifyWaitTaskTimer is called every 500ms
 *      
 *===========================================================================*/

#ifndef	NULL
#define NULL    ((void *)0)
#endif

#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <math.h>
#include    <setjmp.h>

#define Timer50ms         1
#define Timer100ms        2
#define Timer200ms        4
#define Timer500ms        10
#define Timer1s           20
#define Timer2s           40
#define Timer3s           60
#define Timer5s          100
#define Timer10s         200
#define Timer12s         240

void	CreatTask(void (*fun)(), int d_time);
void 	(*GetActiveTask(void))();
void	ModifyWaitTaskTimer(void);
void	DelWaitTask(void (*fun)());

#endif
