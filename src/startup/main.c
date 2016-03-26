#include "MPC.H"


void    (*task)(); 

INT8U Buf[2]=
{0xEB,0x90};
  
void main(void) 
{

  	Sys_Init();

   	CreatTask(LAW_Task, 0);
	CreatTask(task_100ms, 0);

	CreatTask(LATE, 0);
	CreatTask(LONG, 0);
	CreatTask(VERT, 0);
	CreatTask(ROTA, 0);
	
	CreatTask(GUID_AutoFly, 0);
	CreatTask(GUID_Hover, 0);
	CreatTask(GUID_Spec,0);
	
	 CreatTask(sound_bibi,0);

    while (1)
    {                        
          IdleCount++;
          task = GetActiveTask();   if (task!=NULL) (*task)();
            
        if (tag_2ms)
        {
        	tag_2ms  = FALSE;
        Task_AHRSRev();        	            
        }
        
        if (tag_4ms)
        {
        	   tag_4ms  = FALSE;
        	   LAW_Task();
            LAW_CmdSmooth();       
        }    
    
        if (tag_10ms)
        {   
            tag_10ms = FALSE; 
            LAW_Out();
            //Task_UrgRev();           
        } 

        if (tag_15ms)
        {              
            tag_15ms = FALSE; 
            //Task_MpxvRev();			 		   			  
        }                 
                  
        if (tag_20ms)
        {   
            tag_20ms = FALSE;
            TELE_TaskRx();
            PWM_IN();                    
        }    

        if (tag_40ms)
        {
            tag_40ms= FALSE;   	    		    
        }
             
        if (tag_50ms)
        {
            tag_50ms = FALSE;                                   
            ModifyWaitTaskTimer();
            sendBreak3();                            
        }
         
        if (tag_500ms)
        {
            tag_500ms = FALSE;
            
            CPULoad =(WORD)(100.0-IdleCount/(2200.0));
           	IdleCount=0;
         }
                
        if (tag_1s)
        {	tag_1s=FALSE; 
        
        if(urg_guid!=URG_Enter)
        {
        	      if(on_sky && height_alt00>0.5 && fabs(urg_dPsi1)>0.5) rud_mix+=MidVal(urg_dPsi1,-1.5f,1.5f);
        }
            /*if(time_spec) spec_cnt++;
            if(spec_cnt==300) 
            {
             engine_mix0=0.0f;
             nav_guid=PW_NavNone;            	
            }
            */


        }
 
         
    }      
     

}



