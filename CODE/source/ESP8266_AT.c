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

const unsigned char UART_SendIOT_1StartData[] = "{\"method\": \"update\",\"gatewayNo\": \"02\",\"userkey\": \"a46950c875da40b2a8ab5ca5b0f58409\"}&^! "; // \r\n
const unsigned char UART_SendIOT_2SendData[]  = "{\"method\": \"upload\",\"data\":[{\"Name\":\"T1\",\"Value\":\"27\"}]}&^! ";//\r\n

//void fun_IOT_StartData()
//{
//	for(i = 0; i < sizeof(UART_SendIOT_1StartData); i++)
//	{
//		UART_TxBuf[i] = UART_SendIOT_1StartData[i];
//	}
//	fun_UARTSendData(sizeof(UART_SendIOT_1StartData),0);
//}







volatile bit gbv_UARTSendAT_Is_10s;
volatile unsigned char AT_State;
volatile unsigned char AT_State_Before;

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
}
void fun_ESP8266_StartAT()
{
	AT_State = Send_1AT;
}
void V_fun_UART_SendAT()
{
	if(    gbv_UARTSendAT_Is_10s
		|| (AT_State != AT_State_Before)
		|| DrvUartFormat.flag.b.IsRX_OK
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
				if(DrvUartFormat.flag.b.IsRX_OK)//ready 暫時不用
				{
					DrvUartFormat.flag.b.IsRX_OK = 0;
					AT_State = Send_5CWJAP;
				}
				/*if(DrvUartFormat.flag.b.IsRX_ready)//ready 暫時不用
				{
					//DrvUartFormat.flag.b.IsRX_OK = 0;
					DrvUartFormat.flag.b.IsRX_ready = 0;
					AT_State = Send_5CWJAP;
				}*/
				else
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
					
					//外部IIC改變的熱點名稱，外部主機發送WIFI名稱與密碼
					/*volatile temp;
					#define WIFI_Name_StartNum 	10
					for(i = 0;i < sizeof(MasterSend_WIFI_Name); i++)
					{
						UART_TxBuf[WIFI_Name_StartNum + i] = sizeofMasterSend_WIFI_NameSeret[i];
					}
					UART_TxBuf[i + 1] = '\"'	;
					UART_TxBuf[i + 2] = ','	;
					UART_TxBuf[i + 3] = '\"'	;
					temp = i + 3;
					for(i;i < sizeof(MasterSend_WIFI_Seret); i++)
					{
						UART_TxBuf[temp + i] = sizeofMasterSend_WIFI_NameSeret[i];
					}
					UART_TxBuf[temp + i + 1] = '\"'	;
					UART_TxBuf[temp + i + 2] = '\r'	;
					UART_TxBuf[temp + i + 3] = '\n'	;
					//AT+CWJAP=\"realme_X7_Pro\",\"12345678\"\r\n";*/
					
					fun_UARTSendData(sizeof(UART_SendWiFi_5CWJAP),0);
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
					AT_State = Send_Stop;
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
		DrvUartFormat.flag.b.IsRX_OK = 0;
			
		DrvUartFormat.flag.b.IsRX_ready = 0;
			
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