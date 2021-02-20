
#include "common.h"

volatile bit bitDebug;
volatile unsigned char IOT_SendData_State;
volatile bit gbv_JDQ_State_Is_Change;
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
		
		//JDQ===============================
		if(KeyControl1DataLast != KeyControl1Data)
		{
			gbv_JDQ_State_Is_Change = 1;
			KeyControl1DataLast = KeyControl1Data;
		}
		
		//控制設備==========================
		//使用宏定義封裝5個設備控制器
		//收到對應的數據后，回復對應的數據
		if(DrvUartFormat.flag.b.IsRX_getAllSensors)//獲取設備控制列表
		{
			DrvUartFormat.flag.b.IsRX_getAllSensors = 0;
			//KeyControl2Data = 1;
			GCC_DELAY(6000);//用定時器方法
			fun_IOT_response("J1",KeyControl1Data);//J1
			while(UART_TXIsBusy);
			//while(UART_TXIsBusy);
			//GCC_DELAY(60000);//用定時器方法
			//fun_IOT_response("J2",1);//J2
		}
		if(DrvUartFormat.flag.b.IsRX_updateSensor)//回復更新后數據
		{
			DrvUartFormat.flag.b.IsRX_updateSensor = 0;
			GCC_DELAY(6000);//用定時器方法
			fun_IOT_response(UpdateSensorName,UpdateSensorData);//J1
			while(UART_TXIsBusy);
			KeyControl1Data = UpdateSensorData;
		}

		//發送數據==========================
		if(AT_State == Send_Data)
		{
			AT_State = Send_Stop;
			gbv_UARTSendData_Is_10s  = 1;
			gbv_UARTSendData_Is_120s = 1;
		}
		
		if(AT_State == Send_Stop)
		{
			if(gbv_JDQ_State_Is_Change)
			{ 
				gbv_JDQ_State_Is_Change = 0;
				fun_IOT_StartData();//更新设备状态，使设备在线一分钟，一分钟内需要重复发送保持在线
				while(UART_TXIsBusy);
				while(!DrvUartFormat.flag.b.IsRX_ok)
				{
					V_fun_UART_RxData();
				}
				DrvUartFormat.flag.b.IsRX_ok = 0;
				GCC_DELAY(6000);//用定時器方法
				fun_IOT_SendData("J1",KeyControl1Data);
				while(UART_TXIsBusy);
				while(!DrvUartFormat.flag.b.IsRX_ok)
				{
					V_fun_UART_RxData();
				}
				DrvUartFormat.flag.b.IsRX_ok = 0;
			}
			if(gbv_UARTSendData_Is_120s)
			{
				if(gbv_UARTSendData_Is_10s)
				{
					gbv_UARTSendData_Is_10s = 0;
					IOT_SendData_State++;
					switch(IOT_SendData_State)
					{
						case 1:
							fun_IOT_StartData();//更新设备状态，使设备在线一分钟，一分钟内需要重复发送保持在线
							//while(UART_TXIsBusy);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
							GCC_DELAY(6000);//用定時器方法
							fun_IOT_SendData("T1",27);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
						break;
						case 2:
							fun_IOT_StartData();//更新设备状态，使设备在线一分钟，一分钟内需要重复发送保持在线
							//while(UART_TXIsBusy);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
							GCC_DELAY(6000);//用定時器方法
							fun_IOT_SendData("H1",77);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
						break;
						case 3:
							fun_IOT_StartData();//更新设备状态，使设备在线一分钟，一分钟内需要重复发送保持在线
							//while(UART_TXIsBusy);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
							GCC_DELAY(6000);//用定時器方法
							fun_IOT_SendData("T2",25);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
						break;
						case 4:
							fun_IOT_StartData();//更新设备状态，使设备在线一分钟，一分钟内需要重复发送保持在线
							//while(UART_TXIsBusy);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
							GCC_DELAY(6000);//用定時器方法
							fun_IOT_SendData("W2",25);
							while(!DrvUartFormat.flag.b.IsRX_ok)
							{
								V_fun_UART_RxData();
							}
							DrvUartFormat.flag.b.IsRX_ok = 0;
						break;
						default :
						break;
					}
					if(IOT_SendData_State > 4)
					{
						IOT_SendData_State = 0;
						gbv_UARTSendData_Is_120s = 0;
					}
				}
			}
		}
	}
}