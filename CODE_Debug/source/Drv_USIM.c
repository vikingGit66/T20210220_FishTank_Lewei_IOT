
#include "common.h"

struct DrvUartFormat_t DrvUartFormat;


void Drv_UART_Init()
{
	SET_UART_Format_D8_NONE_S1(); // 數據傳輸格式設定
	SET_UART_BAUDRATE_9600();	// 波特率設定
	SET_UART_ADDRESS_DISABLE();
	SET_UART_RECEIVER_IE_ENABLE();
	SET_UART_TRANSMITTER_IE_DISABLE();
	SET_UART_TRANSMITTER_EMPTY_DISABLE();
	SET_UART_ENABLE();
	_emi = 1;
	// UART IO
	SET_PD1_RX();
	SET_PD2_TX();
}

void V_UARTTxByte(unsigned char value)
{
	_acc = _usr;//串口发送函数
	_txr_rxr = value;
	while(!_tidle);
}
void V_UARTTxData(unsigned char *data, unsigned char len)
{
	len -= 1;
	while(len--)
	{
		V_UARTTxByte(*data);
		data ++;
	}
}
void V_const_UARTTxData(const unsigned char *data, unsigned char len)
{
	len -= 1;
	while(len--)
	{
		V_UARTTxByte(*data);
		data ++;
	}
}
DEFINE_ISR(UART_ISR, 0x02C)
{
	// 奇偶校验出错
	/*if (_perr)
	{
		_acc = _usr;
		_acc = _txr_rxr;
	}*/
	//錯誤處理
	if (_nf | _ferr | _oerr)	//  噪声干扰错误 | 帧错误 | 溢出错误
	{
		_acc = _usr;
		_acc = _txr_rxr;
		
	}
	
	// 接收数据
	
	if (_rxif)
	{
		unsigned char data_temp;
		data_temp = _txr_rxr;
		V_UARTReceiveInput(data_temp);
		V_UART_RX_ESP8266_Data(data_temp);
		//Debug
		//V_UARTTxByte(DataTempDebug);
		//unsigned char data[2]={0x55,0xaa};
		//V_UARTTxData(data,2);
	}
}
