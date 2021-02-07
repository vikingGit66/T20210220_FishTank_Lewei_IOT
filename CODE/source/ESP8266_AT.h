#ifndef _ESP8266_AT_H_
#define _ESP8266_AT_H_

extern volatile unsigned char AT_State;


typedef enum 
{
	Send_Stop,
	Send_1AT,
	Send_2CWAUTOCONN,
	Send_3CIPMODE,
	Send_4RST,
	Send_5CWJAP,
	Send_6CIPMUX,
	Send_7CIPMODE,
	Send_8CIPSTART,
	Send_9CIPSEND,
	Send_10Outsend
} AT_State_Is;


void V_fun_UART_RxData();
void fun_ESP8266_StartAT();
void V_fun_UART_SendAT();


#endif

