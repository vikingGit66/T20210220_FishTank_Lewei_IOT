

#ifndef _TIMER_H_
#define _TIMER_H_

extern volatile bit gbv_UARTSendAT_Is_10s;


#define TimeBase0_8ms_Init() { _tb02 = 0 ; _tb01 = 0; _tb00 = 0;}

#define TimeBase1_1s_Init() { _tb11 = 1 ; _tb10 = 1;}//11-1s

#define TimeBase0_INT_On()	{ _tb0f = 0; _tb0e = 1; _emi = 1;}
#define TimeBase1_INT_On()	{ _tb1f = 0; _tb1e = 1; _emi = 1;}

#define TimeBase0_INT_Off()	{ _tb0e = 0; }
#define TimeBase1_INT_Off()	{ _tb1e = 0; }

#define TimeBase0_INT_OFF()	{ _tb0e = 0;}
#define TimeBase1_INT_OFF()	{ _tb1e = 0;}

void V_Timer_Init();


#endif


