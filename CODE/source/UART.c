
#include "common.h"

volatile unsigned char UART_TXLength;
volatile unsigned char UART_TXOffset;
volatile unsigned char UART_RXOffset;
volatile bit UART_TXIsBusy;
struct DrvUartFormat_t DrvUartFormat;

void Drv_UART_Init()
{
	SET_UART_Format_D8_NONE_S1(); // 數據傳輸格式設定
	SET_UART_BAUDRATE_9600();	// 波特率設定
	SET_UART_ADDRESS_DISABLE();
	SET_UART_RECEIVER_IE_ENABLE();
	SET_UART_TRANSMITTER_IE_ENABLE();
	SET_UART_TRANSMITTER_EMPTY_ENABLE();
	SET_UART_ENABLE();
	_emi = 1;
	// UART IO
	SET_PD1_RX();
	SET_PD2_TX();
}

void fun_UARTSendData(unsigned char Length,unsigned char Offset)
{
	if(Length > UART_LENGTH_TX)
	{
		Length = 0;
	}
	if(Offset > UART_LENGTH_TX)
	{
		Offset = UART_LENGTH_TX;
	}
	UART_TXLength = Length-1;
	UART_TXOffset = Offset;
	// Start TX
	UART_TXIsBusy = 1;// uart 忙碌
	_acc = _usr;
	_txr_rxr = UART_TxBuf[Offset];
	//_dmbp0 = 0;
}

/***********************************
Function:  UART 數據發送和接收中斷子程序
INPUT	:
OUTPUT	:
NOTE	:
***********************************/
DEFINE_ISR(UART_ISR, 0x02C)
{
	// 奇偶校验出错
	/*if (_perr)
	{
		_acc = _usr;
		_acc = _txr_rxr;
	}*/
	//錯誤處理
	if(_nf | _ferr | _oerr)	//  噪声干扰错误 | 帧错误 | 溢出错误
	{
		_acc = _usr;
		_acc = _txr_rxr;
		
	}
	if (_txif && UART_TXIsBusy)// 发送数据
	{
		// 數據幀發送完成判斷
		UART_TXOffset++;
		if ( UART_TXOffset < UART_TXLength)
		{
			_txr_rxr = UART_TxBuf[UART_TXOffset];
		}
		else
		{
			if (_tidle)
			{
				UART_TXIsBusy = 0;
			}
		}
	}
	if(_rxif)// 接收数据
	{
		volatile unsigned char data;
		data = _txr_rxr;
		if(data == 'O')//OK\r\n
		{
			UART_RXOffset = 0;
		}
		if(data == 'o')//ok"
		{
			UART_RXOffset = 0;
		}
		UART_RxBuf[UART_RXOffset] = data;
		UART_RXOffset ++;
		if(UART_RXOffset >= UART_LENGTH_RX)
		{
			UART_RXOffset = 0;
		}
	}
}
