
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
		fun_IOT_StartData();
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
		
		//控制設備==========================
		//使用宏定義封裝5個設備控制器
		//收到對應的數據后，回復對應的數據
		if(DrvUartFormat.flag.b.IsRX_getAllSensors)//獲取設備控制列表
		{
			DrvUartFormat.flag.b.IsRX_getAllSensors = 0;
			GCC_DELAY(6000);//用定時器方法
			fun_IOT_response("J1",0);//J1
		}
		if(DrvUartFormat.flag.b.IsRX_updateSensor)//回復更新后數據
		{
			DrvUartFormat.flag.b.IsRX_updateSensor = 0;
			GCC_DELAY(6000);//用定時器方法
			fun_IOT_response(UpdateSensorName,UpdateSensorData);//J1
		}

		//發送數據==========================
		//定時30秒發送設備密碼
		//定時500ms更新一次數據
		if(AT_State == Send_Data)
		{
			AT_State = Send_Stop;
			fun_IOT_StartData();//更新设备状态，使设备在线一分钟，一分钟内需要重复发送保持在线
			while(!DrvUartFormat.flag.b.IsRX_ok)
			{
				V_fun_UART_RxData();
			}
			fun_IOT_SendData("T1",27);
		}
	}
}