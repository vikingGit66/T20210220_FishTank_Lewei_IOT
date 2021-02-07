#ifndef _ESP8266_AT_H_
#define _ESP8266_AT_H_

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

extern volatile bit gbv_UARTSendAT_Is_10s;
extern volatile unsigned char AT_State;
extern volatile unsigned char AT_State_Before;

void V_UART_RX_ESP8266_Data(unsigned char value);
void V_fun_UART_SendAT();
#endif

