
#include "common.h"

volatile bit bitDebug;


void main()
{
	
	// 判斷是否為上電復位或者非正常情況下的復位
	// 如果是上電復位，執行上電復位初始化，反之執行WDT溢出初始化
	if (_to == 0 || _pdf ==0)
	{
		// System
		WDT_Disable_1024ms();
		V_GPIOPowerOnInit();
		V_SysClock_8MHz_Init();
		V_RamInit();
		Drv_UART_Init();
		V_Timer_Init();
		
		fun_ESP8266_StartAT();
		
	}
	else
	{
		// WDT溢出復位初始化
		GCC_CLRWDT();
		
	}
	//主循環
	while(1)
	{
		GCC_CLRWDT();
		V_fun_UART_RxData();
		V_fun_UART_SendAT();
	}
}