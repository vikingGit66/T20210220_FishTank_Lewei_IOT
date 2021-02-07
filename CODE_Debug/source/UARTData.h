#ifndef _UARTDATA_H_
#define _UARTDATA_H_

void UART_SendData(const unsigned char *data, unsigned char cnt);
void UART_SendWiFiSet();
void UART_Send_Num_UserKey();
void V_UARTReceiveInput(unsigned char value);
void UART_Send_UploadData_Num(unsigned char Name, unsigned char value);
#endif


