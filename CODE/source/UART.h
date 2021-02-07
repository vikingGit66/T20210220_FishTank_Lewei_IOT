#ifndef _UART_H_
#define _UART_H_


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用變量 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define  UART_LENGTH_TX	110	// 協議中最大的長度 40
#define  UART_LENGTH_RX	18	// 協議中最大的長度
struct DrvUartFormat_t
{
    union {
		struct
		{
			unsigned char IsRX_getAllSensors    : 1;  
			unsigned char IsRX_updateSensor     : 1;  
			
			unsigned char IsRX_OK				: 1;
			unsigned char IsRX_ready			: 1;
			unsigned char IsRX_tcpsendIsOK		: 1;
			unsigned char IsRX_ok   		: 1;
		} b;
		unsigned char byte;
	} flag;
};
static volatile unsigned char UART_TxBuf[UART_LENGTH_TX] __attribute__ ((at(0x180)));    // RW
static volatile unsigned char UART_RxBuf[UART_LENGTH_RX] __attribute__ ((at(0x1ee)));    // RW

extern struct DrvUartFormat_t DrvUartFormat;
extern volatile unsigned char UART_RXOffset;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 共用函數 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void Drv_UART_Init();     // 初始化
void fun_UARTSendData(unsigned char Length,unsigned char Offset);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 預定義@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#define SET_UART_ENABLE()	{  _uarten = 1;_rxen = 1;_txen = 1;_txif = 0;_urf = 0;_ure = 1;}
#define SET_UART_DISABLE()	{  _uarten = 0;_rxen = 0;_txen = 0;}


#define SET_UART_Format_D8_NONE_S1()		{ _ucr1 = 0x00; }// 傳輸8bit = (8bit-Data  None-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D7_EVEN_S1()		{ _ucr1 = 0x20; }// 傳輸8bit = (7bit-Data  Even-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D7_ODD_S1()			{ _ucr1 = 0x30; }// 傳輸8bit = (7bit-Data  Odd -Parity  None-Add)1bit-Stop
#define SET_UART_Format_D9_NONE_S1()		{ _ucr1 = 0x40; }// 傳輸9bit = (9bit-Data  None-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D8_EVEN_S1()		{ _ucr1 = 0x60; }// 傳輸9bit = (8bit-Data  Even-Parity  None-Add)1bit-Stop
#define SET_UART_Format_D8_ODD_S1()			{ _ucr1 = 0x70; }// 傳輸9bit = (8bit-Data  Odd-Parity   None-Add)1bit-Stop
#define SET_UART_Format_D8_NONE_S2()		{ _ucr1 = 0x00; }// 傳輸8bit = (8bit-Data  None-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D7_EVEN_S2()		{ _ucr1 = 0x20; }// 傳輸8bit = (7bit-Data  Even-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D7_ODD_S2()			{ _ucr1 = 0x30; }// 傳輸8bit = (7bit-Data  Odd -Parity  None-Add)2bit-Stop
#define SET_UART_Format_D9_NONE_S2()		{ _ucr1 = 0x40; }// 傳輸9bit = (9bit-Data  None-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D8_EVEN_S2()		{ _ucr1 = 0x60; }// 傳輸9bit = (8bit-Data  Even-Parity  None-Add)2bit-Stop
#define SET_UART_Format_D8_ODD_S2()			{ _ucr1 = 0x70; }// 傳輸9bit = (8bit-Data  Odd-Parity   None-Add)2bit-Stop

#define SET_UART_WAKEUP_ENABLE()				{ _wake  = 1;}
#define SET_UART_WAKEUP_DISABLE()				{ _wake  = 0;}
#define SET_UART_ADDRESS_ENABLE()				{ _adden = 1;}
#define SET_UART_ADDRESS_DISABLE()				{ _adden = 0;}
#define SET_UART_RECEIVER_IE_ENABLE()			{ _rie   = 1;} // OERR(溢出)/RXIF(有有效數據)置位時可置中斷標誌位
#define SET_UART_RECEIVER_IE_DISABLE()			{ _rie   = 0;}
#define SET_UART_TRANSMITTER_IE_ENABLE()	    { _tiie = 1;} // TIDLE(無數據傳輸)置位，可置中斷標誌位
#define SET_UART_TRANSMITTER_IE_DISABLE()		{ _tiie = 0;}
#define SET_UART_TRANSMITTER_EMPTY_ENABLE()		{ _teie = 1;} // TXIF(數據已加載到移位暫存器，TXR為空)置位時，可置中斷標誌位
#define SET_UART_TRANSMITTER_EMPTY_DISABLE()	{ _teie = 0;}

//#if SYS_CLOCK_FREQ == 4000000
//    #define SET_UART_BAUDRATE_300()				{ _brgh = 0; _brg = 207;}
//    #define SET_UART_BAUDRATE_1200()			{ _brgh = 1; _brg = 207;}
//    #define SET_UART_BAUDRATE_2400()			{ _brgh = 1; _brg = 103;}
//    #define SET_UART_BAUDRATE_4800()			{ _brgh = 1; _brg =  51;}
//    #define SET_UART_BAUDRATE_9600()			{ _brgh = 1; _brg =  25;}
//    #define SET_UART_BAUDRATE_19200()		    { _brgh = 1; _brg =  12;}
//    #define SET_UART_BAUDRATE_250000()			{ _brgh = 1; _brg =   0;}
//#endif
#if SYS_CLOCK_FREQ == 8000000
//    #define SET_UART_BAUDRATE_1200()			{ _brgh = 0; _brg = 103;}
    #define SET_UART_BAUDRATE_2400()			{ _brgh = 0; _brg = 77;}
//    #define SET_UART_BAUDRATE_4800()			{ _brgh = 1; _brg = 103;}
     #define SET_UART_BAUDRATE_9600()			{ _brgh = 1; _brg =  77;}
     #define SET_UART_BAUDRATE_19200()		    { _brgh = 1; _brg =  38;}
     #define SET_UART_BAUDRATE_57600()		    { _brgh = 1; _brg =  12;}
     #define SET_UART_BAUDRATE_250000()			{ _brgh = 1; _brg =   2;}
#endif
//#if SYS_CLOCK_FREQ == 12000000
//    #define SET_UART_BAUDRATE_1200()			{ _brgh = 0; _brg = 155;}
//    #define SET_UART_BAUDRATE_2400()			{ _brgh = 0; _brg =  77;}
//    #define SET_UART_BAUDRATE_4800()			{ _brgh = 1; _brg = 155;}
//    #define SET_UART_BAUDRATE_9600()			{ _brgh = 1; _brg =  77;}
//    #define SET_UART_BAUDRATE_19200()		    { _brgh = 1; _brg =  38;}
//    #define SET_UART_BAUDRATE_57600()		    { _brgh = 1; _brg =  12;}
//    #define SET_UART_BAUDRATE_250000()			{ _brgh = 1; _brg =   2;}
//#endif

#endif