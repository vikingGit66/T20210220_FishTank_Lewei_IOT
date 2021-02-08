#include "common.h"

const unsigned char UART_SendWiFi_1AT[]					="AT\r\n";
const unsigned char UART_SendWiFi_2CWAUTOCONN[]			="AT+CWAUTOCONN=0\r\n";
const unsigned char UART_SendWiFi_3CIPMODE[]			="AT+CIPMODE=1\r\n";
const unsigned char UART_SendWiFi_4RST[]				="AT+RST\r\n";
const unsigned char UART_SendWiFi_5CWJAP[]				="AT+CWJAP=\"realme_X7_Pro\",\"12345678\"\r\n";
const unsigned char UART_SendWiFi_6CIPMUX[]				="AT+CIPMUX=0\r\n";
const unsigned char UART_SendWiFi_7CIPMODE[]			="AT+CIPMODE=1\r\n";
//const unsigned char UART_SendWiFi_8CIPSTART1[]			="AT+CIPSTART=";
//const unsigned char UART_SendWiFi_8CIPSTART2[]			="\"TCP\",\"tcp.lewei50.com\",9960\r\n";//tcp,80
const unsigned char UART_SendWiFi_8CIPSTART[]			="AT+CIPSTART=\"TCP\",\"tcp.lewei50.com\",9960\r\n";//tcp,80

const unsigned char UART_SendWiFi_9CIPSEND[]			="AT+CIPSEND\r\n";
const unsigned char UART_SendWiFi_10Outsend[]			="+++";

const unsigned char UART_SendIOT_1StartData[] = "{\"method\": \"update\",\"gatewayNo\": \"02\",\"userkey\": \"a46950c875da40b2a8ab5ca5b0f58409\"}&^!"; // \r\n
const unsigned char UART_SendIOT_2SendData[]  = "{\"method\": \"upload\",\"data\":[{\"Name\":\"T1\",\"Value\":\"27\"}]}&^!";//\r\n
const unsigned char UART_SendIOT_3response[]  = "{\"method\":\"response\",\"result\":{\"successful\":true,\"message\":\"ok\",\"data\":[{\"id\":\"J1\",\"value\":\"1\"}]}}&^!";

void fun_IOT_StartData()
{
	//可傳入GatewayNo 與 userkey
	volatile unsigned char GatewayNo = 02;
	const unsigned char userkey[] = "a46950c875da40b2a8ab5ca5b0f58409";
	volatile unsigned char i;
	for(i = 0; i < sizeof(UART_SendIOT_1StartData); i++)
	{
		UART_TxBuf[i] = UART_SendIOT_1StartData[i];
	}
	UART_TxBuf[34] = GatewayNo / 10 + 0x30;
	UART_TxBuf[35] = GatewayNo % 10 + 0x30;
	for(i = 0; i < sizeof(userkey)-1; i++)
	{
		UART_TxBuf[i + 50] = userkey[i];
	}
	fun_UARTSendData(sizeof(UART_SendIOT_1StartData),0);
}

void fun_IOT_SendData(char *Name,unsigned char Value)
{
	//可傳入 Name 與 Value
	if(sizeof(Name) <= 2)
	{
		if(Value <= 99)
		{
			volatile unsigned char i;
			for(i = 0; i < sizeof(UART_SendIOT_2SendData); i++)
			{
				UART_TxBuf[i] = UART_SendIOT_2SendData[i];
			}
			UART_TxBuf[37] = Name[0];
			UART_TxBuf[38] = Name[1];
			UART_TxBuf[50] = Value / 10 + 0x30;
			UART_TxBuf[51] = Value % 10 + 0x30;
			fun_UARTSendData(sizeof(UART_SendIOT_2SendData),0);
		}
	}
}
void fun_IOT_response(char *Name,unsigned char Value)
{
	//可傳入 Name 與 Value
	if(sizeof(Name) <= 2)
	{
		if(Value <= 9)
		{
			volatile unsigned char i;
			for(i = 0; i < sizeof(UART_SendIOT_3response); i++)
			{
				UART_TxBuf[i] = UART_SendIOT_3response[i];
			}
			UART_TxBuf[79] = Name[0];
			UART_TxBuf[80] = Name[1];
			UART_TxBuf[92] = Value + 0x30;
			fun_UARTSendData(sizeof(UART_SendIOT_3response),0);
		}
	}
}




volatile bit gbv_UARTSendAT_Is_10s;
volatile unsigned char AT_State;
volatile unsigned char AT_State_Before;
volatile char UpdateSensorName[2];
volatile unsigned char UpdateSensorData;
void V_fun_UART_RxData()
{
	if(UART_RXOffset == 4)
	{
		if(	(UART_RxBuf[0] == 'O'	) && 
			(UART_RxBuf[1] == 'K'	) &&
		   	(UART_RxBuf[2] == '\r'	) && 
		   	(UART_RxBuf[3] == '\n'	))
		{
			DrvUartFormat.flag.b.IsRX_OK = 1;
			UART_RXOffset = 0;
		}
	}
	if(UART_RXOffset == 3)
	{
		if(	(UART_RxBuf[0] == 'o'	) && 
			(UART_RxBuf[1] == 'k'	) &&
		   	(UART_RxBuf[2] == '\"'	))
		{
			DrvUartFormat.flag.b.IsRX_ok = 1;
			UART_RXOffset = 0;
		}
	}
	if(UART_RXOffset == 5)
	{
		if(	(UART_RxBuf[0] == 'r'	) && 
			(UART_RxBuf[1] == 'e'	) &&
		   	(UART_RxBuf[2] == 'a'	) &&
			(UART_RxBuf[3] == 'd'	) && 
			(UART_RxBuf[4] == 'y'	) )
		{
			DrvUartFormat.flag.b.IsRX_ready = 1;
			UART_RXOffset = 0;
		}
	}
	if(UART_RXOffset == 6)//getAll--Sensors
	{
		if(	(UART_RxBuf[0] == 'g'	) && 
			(UART_RxBuf[1] == 'e'	) &&
		   	(UART_RxBuf[2] == 't'	) &&
			(UART_RxBuf[3] == 'A'	) && 
			(UART_RxBuf[4] == 'l'	) && 
			(UART_RxBuf[5] == 'l'	) )
		{
			DrvUartFormat.flag.b.IsRX_getAllSensors = 1;
			UART_RXOffset = 0;
		}
	}
	if(UART_RXOffset == 7)//p1":"c1  
	{
		if(	(UART_RxBuf[0] == 'p'	) && 
			(UART_RxBuf[1] == '1'	) &&
		   	(UART_RxBuf[2] == '\"'	) )
		{
			UpdateSensorName[0] = UART_RxBuf[5];
			UpdateSensorName[1] = UART_RxBuf[6];
			if((UART_RxBuf[16] > '0') && (UART_RxBuf[16] < '9'))
			{
				UpdateSensorData = (UART_RxBuf[15]-'0') * 10 + (UART_RxBuf[16]-'0');
			}
			else
			{
				UpdateSensorData = UART_RxBuf[15]-'0';
			}
			UART_RXOffset = 0;
		}
	}
	if(UART_RXOffset == 7)//p2":"0"
	{
		if(	(UART_RxBuf[0] == 'p'	) && 
			(UART_RxBuf[1] == '2'	) &&
		   	(UART_RxBuf[2] == '\"'	) )
		{
			DrvUartFormat.flag.b.IsRX_updateSensor = 1;
			if((UART_RxBuf[6] > '0') && (UART_RxBuf[6] < '9'))
			{
				UpdateSensorData = (UART_RxBuf[5]-'0') * 10 + (UART_RxBuf[6]-'0');
			}
			else
			{
				UpdateSensorData = UART_RxBuf[5]-'0';
			}
			UART_RXOffset = 0;
		}
	}
}
void fun_ESP8266_StartAT()
{
	AT_State = Send_1AT;
}
void V_fun_UART_SendAT()
{
	//外部IIC改變的熱點名稱，外部主機發送WIFI名稱與密碼
	const unsigned char WIFI_Name[]  = "realme_X7_Pro";
	const unsigned char WIFI_Seret[] = "12345678";
	if(    gbv_UARTSendAT_Is_10s
		|| (AT_State != AT_State_Before)
		|| DrvUartFormat.flag.b.IsRX_OK
		|| DrvUartFormat.flag.b.IsRX_ok
		|| DrvUartFormat.flag.b.IsRX_ready
		)
	{
		GCC_DELAY(2000);
		gbv_UARTSendAT_Is_10s = 0;
		AT_State_Before = AT_State;
		volatile unsigned char i;
		switch(AT_State)
		{
			case Send_1AT:
				if(DrvUartFormat.flag.b.IsRX_OK)
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_2CWAUTOCONN;
				}
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_1AT); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_1AT[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_1AT),0);
				}
				break;
			case Send_2CWAUTOCONN:
				if(DrvUartFormat.flag.b.IsRX_OK)
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_3CIPMODE;
				}
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_2CWAUTOCONN); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_2CWAUTOCONN[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_2CWAUTOCONN),0);
				}
				break;
			case Send_3CIPMODE:
				if(DrvUartFormat.flag.b.IsRX_OK)
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_4RST;
				}
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_3CIPMODE); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_3CIPMODE[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_3CIPMODE),0);
				}
				break;
			case Send_4RST:
				if(DrvUartFormat.flag.b.IsRX_ready)//
				{
					DrvUartFormat.flag.b.IsRX_ready = 0;
					AT_State = Send_5CWJAP;
				}
				else if(!DrvUartFormat.flag.b.IsRX_OK)//只有ready有效
				{
					for(i = 0; i < sizeof(UART_SendWiFi_4RST); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_4RST[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_4RST),0);
				}
				break;
			case Send_5CWJAP:
				if(DrvUartFormat.flag.b.IsRX_OK)
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_6CIPMUX;
				}
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_5CWJAP); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_5CWJAP[i];
					}
					
					//設置WIFI名稱與密碼
					for(i = 0; i < sizeof(WIFI_Name) - 1; i++)
					{
						UART_TxBuf[10 + i] = WIFI_Name[i];
					}
					UART_TxBuf[10 + i + 0] = '\"';
					UART_TxBuf[10 + i + 1] = ',';
					UART_TxBuf[10 + i + 2] = '\"';
					for(i = 0; i < sizeof(WIFI_Seret)-1; i++)
					{
						UART_TxBuf[10 + sizeof(WIFI_Name) + 2 + i] = WIFI_Seret[i];
					}
					UART_TxBuf[10 + sizeof(WIFI_Name) + 2 + i + 0] = '\"';
					UART_TxBuf[10 + sizeof(WIFI_Name) + 2 + i + 1] = '\r';
					UART_TxBuf[10 + sizeof(WIFI_Name) + 2 + i + 2] = '\n';
					//AT+CWJAP=\"realme_X7_Pro\",\"12345678\"\r\n";
					fun_UARTSendData(10 + sizeof(WIFI_Name) + 2 + i + 2 + 2 ,0);
				}
				break;
			case Send_6CIPMUX:
				if(DrvUartFormat.flag.b.IsRX_OK)
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_7CIPMODE;
				}
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_6CIPMUX); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_6CIPMUX[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_6CIPMUX),0);
				}
				break;
			case Send_7CIPMODE:
				if(DrvUartFormat.flag.b.IsRX_OK)
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_8CIPSTART;
				}
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_7CIPMODE); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_7CIPMODE[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_7CIPMODE),0);
				}
				break;
			case Send_8CIPSTART:
				if(DrvUartFormat.flag.b.IsRX_OK)
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_9CIPSEND;
				}
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_8CIPSTART); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_8CIPSTART[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_8CIPSTART),0);
				}
				break;
			case Send_9CIPSEND:
				if(DrvUartFormat.flag.b.IsRX_OK)//IsRX_tcpsendIsOK
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_Data;
				}
				/*if(DrvUartFormat.flag.b.IsRX_tcpsendIsOK)//IsRX_tcpsendIsOK
				{
					AT_State = Send_Stop;
					DrvUartFormat.flag.b.IsRX_tcpsendIsOK = 0;
				}*/
				else
				{
					for(i = 0; i < sizeof(UART_SendWiFi_9CIPSEND); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_9CIPSEND[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_9CIPSEND),0);
				}
				break;
			case Send_10Outsend:
					for(i = 0; i < sizeof(UART_SendWiFi_10Outsend); i++)
					{
						UART_TxBuf[i] = UART_SendWiFi_10Outsend[i];
					}
					fun_UARTSendData(sizeof(UART_SendWiFi_10Outsend),0);
					
					if(DrvUartFormat.flag.b.IsRX_OK)
					{
						DrvUartFormat.flag.b.IsRX_OK = 0;
						AT_State = Send_Stop;
					}
					else
					{
						for(i = 0; i < sizeof(UART_SendWiFi_1AT); i++)
						{
							UART_TxBuf[i] = UART_SendWiFi_1AT[i];
						}
						fun_UARTSendData(sizeof(UART_SendWiFi_1AT),0);
					}
				break;
			case Send_Stop:
				AT_State_Before = AT_State;
				break;
			default:
				break;
		}
		if(DrvUartFormat.flag.b.IsRX_OK)
			DrvUartFormat.flag.b.IsRX_OK = 0;
		else 
		if(DrvUartFormat.flag.b.IsRX_ready)
			DrvUartFormat.flag.b.IsRX_ready = 0;
		else
		if(DrvUartFormat.flag.b.IsRX_tcpsendIsOK)
			DrvUartFormat.flag.b.IsRX_tcpsendIsOK = 0;	
		
	}
}
#define None_RXState_ESP8266 	0
#define O_RXState_ESP8266 		1
#define OK_RXState_ESP8266 		2

#define r_RXState_ESP8266 		3
#define e_RXState_ESP8266 		4
#define a_RXState_ESP8266 		5
#define d_RXState_ESP8266 		6
#define y_RXState_ESP8266 		7
#define ready_RXState_ESP8266 	8

#define o_RXState_ESP8266 		9
#define ok_RXState_ESP8266 		10
//void V_UART_RX_ESP8266_Data(unsigned char value)
//{
//	//'>'
//	if(value == '>')
//	{
//	//	DrvUartFormat.flag.b.IsRX_tcpsendIsOK = 1;
//	}
//	//OK
//	if(value == 'O')
//	{
//		//DrvUartFormat.RXState_ESP8266 = O_RXState_ESP8266;
//	}
//	else
//	{
//		switch(DrvUartFormat.RXState_ESP8266)
//		{
//			case O_RXState_ESP8266 : 
//				if(value == 'K') 
//				{
//					DrvUartFormat.RXState_ESP8266 = OK_RXState_ESP8266;
//					DrvUartFormat.flag.b.IsRX_OK = 1;
//				}
//				else
//				{	
//					DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
//				}
//				break;
//			default :
//				break;
//		}
//	}
//	//ok
//	if(value == 'o')
//	{
//		DrvUartFormat.RXState_ESP8266 = o_RXState_ESP8266;
//	}
//	else
//	{
//		switch(DrvUartFormat.RXState_ESP8266)
//		{
//			case o_RXState_ESP8266 : 
//				if(value == 'k') 
//				{
//					DrvUartFormat.RXState_ESP8266 = ok_RXState_ESP8266;
//					DrvUartFormat.flag.b.IsRX_Smallok = 1;
//					bitDebug = 1;
//				}
//				else
//				{	
//					DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
//				}
//				break;
//			default :
//				break;
//		}
//	}
//	//ready
//	if(value == 'r')
//	{
//		DrvUartFormat.RXState_ESP8266 = r_RXState_ESP8266;
//	}
//	else
//	{
//		switch(DrvUartFormat.RXState_ESP8266)
//		{
//			case r_RXState_ESP8266 : 
//				if(value == 'e') 	DrvUartFormat.RXState_ESP8266 = e_RXState_ESP8266;
//				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
//				break;
//			case e_RXState_ESP8266 : 
//				if(value == 'a') 	DrvUartFormat.RXState_ESP8266 = a_RXState_ESP8266;
//				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
//				break;
//			case a_RXState_ESP8266 : 
//				if(value == 'd') 	DrvUartFormat.RXState_ESP8266 = d_RXState_ESP8266;
//				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
//				break;
//			case d_RXState_ESP8266 : 
//				if(value == 'y'){ 	DrvUartFormat.RXState_ESP8266 = y_RXState_ESP8266;
//									DrvUartFormat.flag.b.IsRX_ready = 1;
//								}
//				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
//				break;
//			default :
//				break;
//		}
//	}
//}