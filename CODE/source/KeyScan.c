//___________________________________________________________________
//___________________________________________________________________
//  Copyright : 2015 BY HOLTEK SEMICONDUCTOR INC
//  File Name : KeyScan.c
// Description: 按鍵掃描程序
//   Customer : Holtek Demo Code
//Targer Board: HT45F75 BodyFat-ESK0.2
//     Note   :
//___________________________________________________________________
//___________________________________________________________________
#include "common.H"
volatile bit gbv_8ms_Using_Key_Scan;		//8ms進入掃描標誌位
volatile bit gbv_Key_Press;					//按鍵按下
volatile bit gbv_Key_Long_Press;			//按鍵長按
volatile bit gbv_Key_Clear_Count;			//按鍵按下時間計數清零
volatile bit gbv_Key_Rise;					//按鍵鬆開
volatile unsigned int gu16v_Key_Debounce_Cnt; // 按鍵Debounce的次數

#define KEY0_INT0_Down() 	{ _int0s1 = 1; _int0s0 =0;}
#define KEY1_INT1_Down() 	{ _int1s1 = 1; _int1s0 =0;}

#define EMI_On()			{ _emi = 1;}
#define EMI_Off()			{ _emi = 0;}

#define KEY0_INT0_On() 		{ _int0e = 1;}
#define KEY1_INT1_On() 		{ _int1e = 1;}

#define KEY0_INT0_Off() 	{ _int0e = 0;}
#define KEY1_INT1_Off() 	{ _int1e = 0;}

//volatile char gbv_Key_Time;
/********************************************************************
Function: 按鍵掃描子程序
IO_IS_INPUT	:
OUTPUT	:
NOTE	:
********************************************************************/
void fun_KeyInit()
{
	KEY0_INT0_Down();
	KEY0_INT0_On();
	EMI_On();
	//KEY1_INT1_Down();
	//KEY1_INT1_On();
}
//@----------INT0 中斷入口函數-----------@
DEFINE_ISR(INT0_ISR, 0x004)
{
	 // User Code
	 gbv_KeyIs0 = 1;
}
//@----------INT1 中斷入口函數-----------@
DEFINE_ISR(INT1_ISR, 0x024)
{
    // User Code
    //gbv_KeyIs1 = 1;
}

void fun_KeyScan()
{
	if (gbv_8ms_Using_Key_Scan)
	{
		gbv_8ms_Using_Key_Scan = 0;
		KEYCAL_C = IO_IS_INPUT;
		KEYCAL_Pu = IO_IS_PULL_UP;
		GCC_NOP(); //延遲，IO狀態穩定需要時間
		GCC_NOP();
		if (!KEYCAL)//按鍵按下
		{
			// 按鍵未抬起，首次按下后未抬起
			if (gbv_Key_Press)
			{
				gu16v_Key_Debounce_Cnt++; // Key Debounce //溢出處理
				if (gu16v_Key_Debounce_Cnt >= KEY_LOOG_PRESS)//長按時間到后，為長按
				{
					gbv_Key_Long_Press = 1;//長按標誌位
					gbv_Key_Clear_Count = 1;//清零長按時間計數標誌位
					if (gu16v_Key_Debounce_Cnt >= 255)
					{
						gu16v_Key_Debounce_Cnt = 255;
					}
				}
			}
			else//首次按下
			{
				gbv_Key_Press = 1;//首次按下，不清時間計數
				gu16v_Key_Debounce_Cnt = 0;
			}
		}
		else
		{
			// 按鍵抬起
			if (gbv_Key_Press)
			{
				// 第一次有按键按下
				gbv_Key_Rise = 1;
				gbv_Key_Press = 0;
			}
			else//無動作
			{
				gbv_Key_Press = 0;
				gu16v_Key_Debounce_Cnt = 0;
			}
		}
	}
	
	if (gbv_Key_Long_Press) // 長按切換模式
	{
		gbv_Key_Long_Press = 0;
		gu16v_Key_Debounce_Cnt = 0;
		fun_Key_Long_Press();
	}
	else if (gbv_Key_Rise)
	{
		gbv_Key_Rise = 0;
		gbv_Key_Clear_Count = 0;
		if (KEY_SHORT_PRESS < gu16v_Key_Debounce_Cnt)//小於短按時間為短按
		{
			fun_Key_Short_Press();				
		}
		gu16v_Key_Debounce_Cnt = 0;
	}
	
	if (gbv_Key_Clear_Count)
	{
		gu16v_Key_Debounce_Cnt = 0;
	}
}
void fun_Key_Long_Press()
{
	gu8v_KeyState = Key_State_LongPress;
}

void fun_Key_Short_Press()
{
	gu8v_KeyState = Key_State_ShortPress;
}
