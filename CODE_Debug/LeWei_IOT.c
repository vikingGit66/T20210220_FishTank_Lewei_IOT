
#include "common.h"

volatile bit bitDebug;

const unsigned char DataDebug [] = "{\"method\": \"update\",\"gatewayNo\": \"02\",\"userkey\": \"a46950c875da40b2a8ab5ca5b0f58409\"}&^! "; // \r\n
const unsigned char DataDebug2[] = "{\"method\": \"upload\",\"data\":[{\"Name\":\"T1\",\"Value\":\"27\"}]}&^! ";//\r\n
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
		
		
		//V_const_UARTTxData(DataDebug,sizeof(DataDebug));
		
		
		/*UART_Send_Num_UserKey();
		GCC_DELAY(80000);
		UART_Send_UploadData_Num(1, 34);*/
		
		
		//UART_SendWiFiSet();
		AT_State = Send_1AT;
	}
	else
	{
		// WDT溢出復位初始化
		GCC_CLRWDT();
		
	}
	unsigned char i;	
	//主循環
	while(1)
	{
		GCC_CLRWDT();
		
		V_fun_UART_SendAT();
		if(AT_State == Send_Stop)
		{
			AT_State = 0x55;
			for(i = 0;i < 250;i++)
			{
				GCC_DELAY(65500);//12MHz:20ms
				GCC_CLRWDT();
			}
			
			V_const_UARTTxData(DataDebug,sizeof(DataDebug));
			for(i = 0;i < 100;i++)
			{
				GCC_DELAY(65500);//12MHz:20ms
				GCC_CLRWDT();
			}
			/*while(1)
			{
				GCC_NOP();
				GCC_CLRWDT();
				if(bitDebug == 1)
				{
					break;
				}
			}
			
			for(i = 0;i < 20;i++)
			{
				GCC_DELAY(65500);//12MHz:20ms
				GCC_CLRWDT();
			}*/
			/*while(!DrvUartFormat.flag.b.IsRX_Smallok)
			{
				GCC_CLRWDT();
			}*/
			DrvUartFormat.flag.b.IsRX_Smallok = 0;
			//_emi = 0;
			V_const_UARTTxData(DataDebug2,sizeof(DataDebug2));
			//_emi = 1;
			/*for(i = 0;i < 250;i++)
			{
				GCC_DELAY(65500);//12MHz:20ms
				GCC_CLRWDT();
			}*/
			while(1)
			{
				GCC_NOP();
				GCC_CLRWDT();
				if(bitDebug == 1)
				{
					break;
				}
			}
			if(DrvUartFormat.flag.b.IsRX_Smallok)
			{
				DrvUartFormat.flag.b.IsRX_Smallok = 0;
				GCC_NOP();
			}
			/*while(!DrvUartFormat.flag.b.IsRX_Smallok)
			{
				GCC_CLRWDT();
			}
			DrvUartFormat.flag.b.IsRX_Smallok = 0;*/
			/*UART_Send_Num_UserKey();
			GCC_DELAY(80000);
			UART_Send_UploadData_Num(1, 34);*/
		}
		if(DrvUartFormat.flag.b.IsRX_Smallok)
		{
			GCC_NOP();
		}
		if(gbv_1s)
		{
			gbv_1s = 0;
			//UART_Send_Num_UserKey();
		}
		if(DrvUartFormat.flag.b.IsRX_getAllSensors)
		{
			DrvUartFormat.flag.b.IsRX_getAllSensors = 0;
		}
		if(DrvUartFormat.flag.b.IsRX_updateSensor)
		{
			DrvUartFormat.flag.b.IsRX_updateSensor = 0;
		}
	}
}