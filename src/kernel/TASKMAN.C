#include "taskman.h"

#ifndef	NULL
#define NULL    ((void *)0)
#endif

#ifndef	NUM_TASK
#define NUM_TASK	50
#endif

static void		(*WaitTask[NUM_TASK])();
static int		WaitTaskTimer[NUM_TASK];

static void		(*ActiveTask[NUM_TASK])();
static int		head, tail;

void 	CreatTask(void (*fun)(), int d_time) 
{
	int	idx;
	
	if ( d_time==0 ) {
		ActiveTask[head] = fun;
		head = (head + 1) % NUM_TASK;
	}
	else
		for (idx=0; idx<NUM_TASK; idx++)
			if ( WaitTaskTimer[idx]==0 )
			{
				WaitTask[idx] = fun;
				WaitTaskTimer[idx] = d_time;
				break;
			}
}


void 	(*GetActiveTask(void))()
{
	void (*fun)();
	
	if ( head==tail ) 
		return (NULL);
	else {
		fun = ActiveTask[tail];
		tail = (tail + 1) % NUM_TASK;
	}
	return(fun);
}


void 	ModifyWaitTaskTimer(void)
{
	int	idx;
	
	for (idx=0; idx<NUM_TASK; idx++)
		if ( WaitTaskTimer[idx]>0 )  {//
			 
			WaitTaskTimer[idx] --;
			if ( WaitTaskTimer[idx]==0 ) {// Wait Task Ready!
				ActiveTask[head] = WaitTask[idx];
			 	head = (head + 1) % NUM_TASK;
			 	WaitTask[idx] = NULL;
			}
		}
}


void 	DelWaitTask(void (*fun)())
{
	int	idx;
	
	for (idx=0; idx<NUM_TASK; idx++)
		if ( WaitTask[idx]==fun ) {
			WaitTask[idx] = NULL;	// reset;
			WaitTaskTimer[idx] = 0;
		}
}

						