/*
 * @時基配置
 * @創建時間：T20201028
 * @作者：Viking
 * @版本號：V2.0
 * @注：
 */
#include "common.h"
/*
 * @ 時基時間初始化1s
 * @
 */
void V_Timer_Init()
{
	//TimeBase0_8ms_Init();
	TimeBase1_1s_Init();//
	//TimeBase0_INT_On();//開啟中斷
	TimeBase1_INT_On();
	_tbck = 0;
	_tbon = 1;
}
//@----------Timebase0 中斷入口函數-----------@
DEFINE_ISR(TIMEBASE0_ISR, 0x01c)
{
	 // User Code
	 //gbv_8ms_Using_Key_Scan = 1;
}
//@----------Timebase1 中斷入口函數-----------@
DEFINE_ISR(TIMEBASE1_ISR, 0x020)
{
    // User Code
    static unsigned char gu8v_10s_Temp;
	gu8v_10s_Temp ++;
	if(gu8v_10s_Temp == 10)
	{
		gu8v_10s_Temp = 0;
		gbv_UARTSendAT_Is_10s = 1;
	}
}

