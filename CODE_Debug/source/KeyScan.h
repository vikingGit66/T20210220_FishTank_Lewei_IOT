//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : KeyScan.h
// Description: 按鍵掃描程序
//   Customer : Holtek Demo Code
//Targer Board: HT45F75 BodyFat-ESK0.2
//     Note   : 
//___________________________________________________________________
//___________________________________________________________________
#ifndef _KEY_SCAN_H
#define _KEY_SCAN_H

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void fun_KeyInit();
void fun_KeyScan();
void fun_Key_Long_Press();
void fun_Key_Short_Press();
//@@@@@@@@@@@@@@@@@@@ 變量聲明 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
extern   volatile bit  	Key_Press;
extern   volatile bit  	Key_Rise;	
extern   volatile bit  	Key_Short_Press	;
extern   volatile bit  	Key_Long_Press	;
extern   volatile bit   gbv_8ms_Using_Key_Scan ;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 按鍵相關 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define	KEYCAL       		_pb0	//按鍵為pb0
#define	KEYCAL_C       		_pbc0	//IO模式
#define	KEYCAL_Pu       	_pbpu0	//上拉

#define KEYSCANCYCLE		8
#define KEY_LOOG_PRESS		1500/KEYSCANCYCLE  
#define KEY_SHORT_PRESS		50/KEYSCANCYCLE //按键按下会有抖动现象

#define IO_IS_INPUT	      1
#define IO_IS_PULL_UP     1

#endif



