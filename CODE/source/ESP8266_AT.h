#ifndef _ESP8266_AT_H_
#define _ESP8266_AT_H_

//#define KeyControl1 J1
//#define KeyControl2 J2
extern volatile bit KeyControl1Data;
extern volatile bit KeyControl1DataLast;
extern volatile bit KeyControl2Data;


extern volatile unsigned char AT_State;
extern char UpdateSensorName[2];
extern unsigned char UpdateSensorData;

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
	Send_Data,
	Send_10Outsend
} AT_State_Is;

void fun_IOT_StartData();
void fun_IOT_SendData(char *Name,unsigned char Value);
void fun_IOT_response(char *Name,unsigned char Value);
void V_fun_UART_RxData();
void fun_ESP8266_StartAT();
void V_fun_UART_SendAT();


#endif

