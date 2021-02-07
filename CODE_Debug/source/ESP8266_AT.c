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

#define SetRxTimeOutCnt1_ESP8266  250 //20ms*x = 20 * 250 = 5s
#define SetRxTimeOutCnt2_ESP8266   50 //20ms*x = 20 * 50 =1s

#define ESP8266_Rx_None			0
#define ESP8266_Rx_OK 			1
#define ESP8266_Rx_ready 		2
#define ESP8266_Rx_LinkOK 		3
#define ESP8266_Rx_SendOK 		4
#define ESP8266_Rx_tcpOK 		5
unsigned char UART_ESP8266_Wait(unsigned char TypeRX, const unsigned char *data, unsigned char cnt)
{
	GCC_DELAY(65500);//12MHz:20ms
	GCC_CLRWDT();
	DrvUartFormat.RxTimeOutCnt_ESP8266 ++;
	if((TypeRX == ESP8266_Rx_OK) || (TypeRX == ESP8266_Rx_LinkOK))
	{
		if(!DrvUartFormat.flag.b.IsRX_OK)
		{
			if(DrvUartFormat.RxTimeOutCnt_ESP8266 == 1)
			{
				UART_SendData(data,cnt);
			}
			if((TypeRX == ESP8266_Rx_LinkOK)
			&&(DrvUartFormat.RxTimeOutCnt_ESP8266 == SetRxTimeOutCnt1_ESP8266) )
			{
				DrvUartFormat.RxTimeOutCnt_ESP8266 = 2;
				UART_SendData(data,cnt);
			}
			else if((TypeRX == ESP8266_Rx_OK)
			&&(DrvUartFormat.RxTimeOutCnt_ESP8266 == SetRxTimeOutCnt2_ESP8266) )
			{
				DrvUartFormat.RxTimeOutCnt_ESP8266 = 2;
				UART_SendData(data,cnt);
			}
			return 1;
		}
		else if(DrvUartFormat.flag.b.IsRX_OK)
		{
			DrvUartFormat.RxTimeOutCnt_ESP8266 = 0;
		}
	}
	else if(TypeRX == ESP8266_Rx_ready)
	{
		if(!DrvUartFormat.flag.b.IsRX_ready)
		{
			if(DrvUartFormat.RxTimeOutCnt_ESP8266 == 1)
			{
				UART_SendData(data,cnt);
			}
			if(DrvUartFormat.RxTimeOutCnt_ESP8266 == SetRxTimeOutCnt2_ESP8266)
			{
				DrvUartFormat.RxTimeOutCnt_ESP8266 = 2;
				UART_SendData(data,cnt);
			}
			return 1;
		}
		else if(DrvUartFormat.flag.b.IsRX_ready)
		{
			DrvUartFormat.RxTimeOutCnt_ESP8266 = 0;
		}
	}
	else if(TypeRX == ESP8266_Rx_SendOK)
	{
		if(!DrvUartFormat.flag.b.IsRX_tcpsendIsOK)
		{
			if(DrvUartFormat.RxTimeOutCnt_ESP8266 == 1)
			{
				UART_SendData(data,cnt);
			}
			if(DrvUartFormat.RxTimeOutCnt_ESP8266 == SetRxTimeOutCnt1_ESP8266)
			{
				DrvUartFormat.RxTimeOutCnt_ESP8266 = 2;
				UART_SendData(data,cnt);
			}
			return 1;
		}
		else if(DrvUartFormat.flag.b.IsRX_tcpsendIsOK)
		{
			DrvUartFormat.RxTimeOutCnt_ESP8266 = 0;
		}
	}
	else if(TypeRX == ESP8266_Rx_tcpOK)
	{
		if(!DrvUartFormat.flag.b.IsRX_OK)
		{
			if(DrvUartFormat.RxTimeOutCnt_ESP8266 == 1)
			{
				UART_SendData(UART_SendWiFi_8CIPSTART, 	sizeof(UART_SendWiFi_8CIPSTART));
			}
			if(DrvUartFormat.RxTimeOutCnt_ESP8266 == SetRxTimeOutCnt1_ESP8266)
			{
				DrvUartFormat.RxTimeOutCnt_ESP8266 = 2;
				UART_SendData(UART_SendWiFi_8CIPSTART, 	sizeof(UART_SendWiFi_8CIPSTART)) ;
			}
			return 1;
		}
		else if(DrvUartFormat.flag.b.IsRX_OK)
		{
			DrvUartFormat.RxTimeOutCnt_ESP8266 = 0;
		}
		
	}
	DrvUartFormat.flag.b.IsRX_tcpsendIsOK = 0;
	DrvUartFormat.flag.b.IsRX_ready = 0;
	DrvUartFormat.flag.b.IsRX_OK = 0;
	return 0;
}

void UART_SendWiFiSet()
{
	while(UART_ESP8266_Wait(ESP8266_Rx_OK,UART_SendWiFi_1AT, 			sizeof(UART_SendWiFi_1AT)) );
	while(UART_ESP8266_Wait(ESP8266_Rx_OK,UART_SendWiFi_2CWAUTOCONN, 	sizeof(UART_SendWiFi_2CWAUTOCONN)) );
	while(UART_ESP8266_Wait(ESP8266_Rx_OK,UART_SendWiFi_3CIPMODE, 		sizeof(UART_SendWiFi_3CIPMODE)) );
	while(UART_ESP8266_Wait(ESP8266_Rx_ready,UART_SendWiFi_4RST, 		sizeof(UART_SendWiFi_4RST)) );
	while(UART_ESP8266_Wait(ESP8266_Rx_LinkOK,UART_SendWiFi_5CWJAP, 		sizeof(UART_SendWiFi_5CWJAP)) );
	while(UART_ESP8266_Wait(ESP8266_Rx_OK,UART_SendWiFi_6CIPMUX, 		sizeof(UART_SendWiFi_6CIPMUX)) );
	while(UART_ESP8266_Wait(ESP8266_Rx_OK,UART_SendWiFi_7CIPMODE, 		sizeof(UART_SendWiFi_7CIPMODE)) );
	//while(UART_ESP8266_Wait(ESP8266_Rx_None,UART_SendWiFi_8CIPSTART1, 	sizeof(UART_SendWiFi_8CIPSTART1)) );
	//while(UART_ESP8266_Wait(ESP8266_Rx_tcpOK,UART_SendWiFi_8CIPSTART2, 	sizeof(UART_SendWiFi_8CIPSTART2)) );
	while(UART_ESP8266_Wait(ESP8266_Rx_tcpOK,0,0));
	while(UART_ESP8266_Wait(ESP8266_Rx_SendOK,UART_SendWiFi_9CIPSEND, 		sizeof(UART_SendWiFi_9CIPSEND)) );
}

volatile bit gbv_UARTSendAT_Is_10s;
volatile unsigned char AT_State;
volatile unsigned char AT_State_Before;

void V_fun_UART_SendAT()
{
	if(
		   gbv_UARTSendAT_Is_10s
		|| (AT_State != AT_State_Before)
		|| DrvUartFormat.flag.b.IsRX_OK
		//|| DrvUartFormat.flag.b.IsRX_ready
		//|| DrvUartFormat.flag.b.IsRX_tcpsendIsOK
		)
	{
		GCC_DELAY(60000);
		gbv_UARTSendAT_Is_10s = 0;
		AT_State_Before = AT_State;
		//GCC_DELAY(65500);//12MHz:20ms
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
					UART_SendData(UART_SendWiFi_1AT,sizeof(UART_SendWiFi_1AT));
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
					UART_SendData(UART_SendWiFi_2CWAUTOCONN,sizeof(UART_SendWiFi_2CWAUTOCONN));
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
					UART_SendData(UART_SendWiFi_3CIPMODE,sizeof(UART_SendWiFi_3CIPMODE));
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
					UART_SendData(UART_SendWiFi_4RST,sizeof(UART_SendWiFi_4RST));
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
					UART_SendData(UART_SendWiFi_5CWJAP,sizeof(UART_SendWiFi_5CWJAP));
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
					UART_SendData(UART_SendWiFi_6CIPMUX,sizeof(UART_SendWiFi_6CIPMUX));
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
					UART_SendData(UART_SendWiFi_7CIPMODE,sizeof(UART_SendWiFi_7CIPMODE));
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
					UART_SendData(UART_SendWiFi_8CIPSTART,sizeof(UART_SendWiFi_8CIPSTART));
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
					UART_SendData(UART_SendWiFi_9CIPSEND,sizeof(UART_SendWiFi_9CIPSEND));
				}
				break;
			case Send_10Outsend:
					UART_SendData(UART_SendWiFi_10Outsend,sizeof(UART_SendWiFi_10Outsend)); //+++
					
					if(DrvUartFormat.flag.b.IsRX_OK)
					{
						DrvUartFormat.flag.b.IsRX_OK = 0;
						AT_State = Send_Stop;
					}
					else
					{
						UART_SendData(UART_SendWiFi_1AT,sizeof(UART_SendWiFi_1AT));
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

void V_UART_RX_ESP8266_Data(unsigned char value)
{
	//'>'
	if(value == '>')
	{
		DrvUartFormat.flag.b.IsRX_tcpsendIsOK = 1;
	}
	//OK
	if(value == 'O')
	{
		DrvUartFormat.RXState_ESP8266 = O_RXState_ESP8266;
	}
	else
	{
		switch(DrvUartFormat.RXState_ESP8266)
		{
			case O_RXState_ESP8266 : 
				if(value == 'K') 
				{
					DrvUartFormat.RXState_ESP8266 = OK_RXState_ESP8266;
					DrvUartFormat.flag.b.IsRX_OK = 1;
				}
				else
				{	
					DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
				}
				break;
			default :
				break;
		}
	}
	//ok
	if(value == 'o')
	{
		DrvUartFormat.RXState_ESP8266 = o_RXState_ESP8266;
	}
	else
	{
		switch(DrvUartFormat.RXState_ESP8266)
		{
			case o_RXState_ESP8266 : 
				if(value == 'k') 
				{
					DrvUartFormat.RXState_ESP8266 = ok_RXState_ESP8266;
					DrvUartFormat.flag.b.IsRX_Smallok = 1;
					bitDebug = 1;
				}
				else
				{	
					DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
				}
				break;
			default :
				break;
		}
	}
	//ready
	if(value == 'r')
	{
		DrvUartFormat.RXState_ESP8266 = r_RXState_ESP8266;
	}
	else
	{
		switch(DrvUartFormat.RXState_ESP8266)
		{
			case r_RXState_ESP8266 : 
				if(value == 'e') 	DrvUartFormat.RXState_ESP8266 = e_RXState_ESP8266;
				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
				break;
			case e_RXState_ESP8266 : 
				if(value == 'a') 	DrvUartFormat.RXState_ESP8266 = a_RXState_ESP8266;
				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
				break;
			case a_RXState_ESP8266 : 
				if(value == 'd') 	DrvUartFormat.RXState_ESP8266 = d_RXState_ESP8266;
				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
				break;
			case d_RXState_ESP8266 : 
				if(value == 'y'){ 	DrvUartFormat.RXState_ESP8266 = y_RXState_ESP8266;
									DrvUartFormat.flag.b.IsRX_ready = 1;
								}
				else 				DrvUartFormat.RXState_ESP8266 = None_RXState_ESP8266;
				break;
			default :
				break;
		}
	}
}