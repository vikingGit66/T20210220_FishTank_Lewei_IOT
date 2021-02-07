/*
 * @LED 開關
 * @創建時間：T20201028
 * @作者：Viking
 * @版本號：V2.0
 * @注：
 */
#include "common.h"

extern volatile u8 Time1_1S_Flag;//定時器1s的標誌位
extern volatile u8 LED_Power_Data;//小夜燈選擇，三個
extern volatile u8 KEY0_Up_Falg;//按鍵按下的標誌位
extern volatile u8 KEY1_Up_Falg;//按鍵按下的標誌位
extern volatile u8 LED1_8_Data;//小夜燈打開的時間，8位
/*
 * @ 比較器打開，中斷未配置
 * @
 */
void V_Compare_ON()
{
	SET_PB4_C_POWER();
//	SET_PA3_CX();
	SET_PB6_C_P();
	SET_PB5_C_N();
	_cen = 1;
}
/*
 * @ 比較器關閉，中斷未配置
 * @
 */
void V_Compare_OFF()
{
	CLR_PB4_C_POWER();
	SET_PA3_CX();
	CLR_PB6_C_P();
	CLR_PB5_C_N();
	_cen = 0;
}
/*
 * @ 比較器定時打開
 * @ 判斷小夜燈的顏色
 * @ 倒計時關閉，由亮再次喚醒
 * @ 包含校準時間，目前為10s
 */
void V_Compare_Work()
{
	static volatile u16 Compare_Time; //小夜燈打開時間的判斷，內部使用
	u8 G_Time_Temp = 0;
	switch(LED1_8_Data)
	{
		case 1: G_Time_Temp = G_Time_Min_2; break;
		case 2:	G_Time_Temp = G_Time_Min_5; break;
		case 3:	G_Time_Temp = G_Time_Min_10; break;
		case 4:	G_Time_Temp = G_Time_Min_20; break;
		case 5:	G_Time_Temp = G_Time_Min_30; break;
		case 6:	G_Time_Temp = G_Time_Min_60; break;
		case 7:	G_Time_Temp = G_Time_Min_90; break;
		case 8:	G_Time_Temp = G_Time_Min_120; break;
		
		default :break;
	}
	
	if((KEY0_Up_Falg == 0) && (KEY1_Up_Falg == 0))
	{
		if(Time1_1S_Flag == 1)
		{
			Time1_1S_Flag = 0;
			V_Compare_ON();
			if((G_G == GL))//暗
			{
				GCC_DELAY(80);//125us *800 = 10ms
				if((G_G == GL) && (Compare_Time != 65535))//暗
				{
					
					Compare_Time ++;
				    if(Compare_Time <= (G_Time_Temp * (60-LED_TIme_OffSet_s)))
				    {
				    	V_LED1_3_Power_Work(LED_Power_Data);
				    	
				    }
					else
					{
						Compare_Time = 65535;
					}
				}
				else if(Compare_Time == 65535)
				{
					V_LED1_3_Power_Work(LED_OFF);
				}
			}
			else if((G_G == GH))
			{
				V_LED1_3_Power_Work(LED_OFF);
				Compare_Time = 0;
			}
			V_Compare_OFF();
		}
	}
}
