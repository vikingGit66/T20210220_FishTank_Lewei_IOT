#include "common.h"


#define Name1 1

#define NoH 0
#define NoL 2
//#define UART_SendHead ""method": "//10,空格
#define DEF_method    	{'{','\"','m','e','t','h','o','d','\"',':',' '};//10,空格

#define DEF_updata      {'\"','u','p','d','a','t','a','\"',','};	//9
#define DEF_gatewayNo   {'\"','g','a','t','e','w','a','y','N','o','\"',':',' ','\"','0','2','\"',','};
#define DEF_userkey     {'\"',',','\"','V','a','l','u','e','\"',':',' ','\"'};
//a4695 0c875 da40b 2a8ab 5ca5b 0f584 09
#define DEF_userkeyNum  {'a','4','6','9','5','0','c','8','7','5','d','a','4','0','b','2','a','8','a','b','5','c','a','5','b','0','f','5','8','4','0','9'};
#define DEF_End         {'\"','}','&','^','!'};  

#define DEF_upload		{'\"','u','p','l','o','a','d','\"',','};	//9
#define DEF_data_Name	{'\"','d','a','t','e','\"',':','[','{','\"','N','a','m','e','\"',':','\"'};
#define DEF_Value		{'\"',',','\"','V','a','l','u','e','\"',':','\"'};
#define DEF_End2		{'\"','}',']','}','&','^','!'};

#define DEF_response	{'\"','r','e','s','p','o','n','s','e','\"',','};	//9


const unsigned char UART_Send_0method[]          = DEF_method;

const unsigned char UART_Send_1updata[]          = DEF_updata;
const unsigned char UART_Send_2gatewayNo[]       = DEF_gatewayNo;
const unsigned char UART_Send_3userkey[]         = DEF_userkey;
const unsigned char UART_Send_4userkeyNum[]      = DEF_userkeyNum;
const unsigned char UART_Send_5End[]             = DEF_End;

const unsigned char UART_Send_1upload[]          = DEF_upload;
const unsigned char UART_Send_2data_Name[]       = DEF_data_Name;
const unsigned char UART_Send_4Value[]           = DEF_Value;
const unsigned char UART_Send_6End2[]       	 = DEF_End2;

const unsigned char UART_Send_1response[]        = DEF_response;


void UART_SendData(const unsigned char *data, unsigned char cnt)
{
	static unsigned char i;//節省RAM
	for(i=0;i<cnt;i++)
	{
		DrvUartFormat.TxBuf[i] = data[i];
	}
	V_UARTTxData(DrvUartFormat.TxBuf, cnt);
		/*while(cnt--)
		{
			V_UARTTxByte(*data);
			data ++;
		}*/
}

void UART_Send_Num_UserKey()
{
	UART_SendData(UART_Send_0method, 			sizeof(UART_Send_0method));
	UART_SendData(UART_Send_1updata, 			sizeof(UART_Send_1updata));
	UART_SendData(UART_Send_2gatewayNo, 		sizeof(UART_Send_2gatewayNo));
	UART_SendData(UART_Send_3userkey, 			sizeof(UART_Send_3userkey));
	UART_SendData(UART_Send_4userkeyNum, 		sizeof(UART_Send_4userkeyNum));
	UART_SendData(UART_Send_5End, 				sizeof(UART_Send_5End));
}

void UART_Send_UploadData_Num(unsigned char Name, unsigned char value)
{
	UART_SendData(UART_Send_0method, 			sizeof(UART_Send_0method));
	UART_SendData(UART_Send_1upload, 			sizeof(UART_Send_1upload));
	UART_SendData(UART_Send_2data_Name, 		sizeof(UART_Send_2data_Name));
	//3
	switch(Name)
	{
		case Name1 :
			DrvUartFormat.TxBuf[0] = 'T';
			DrvUartFormat.TxBuf[1] = '1';
			V_UARTTxData(DrvUartFormat.TxBuf, 2);
			break;
		default :
			break;
	}
	UART_SendData(UART_Send_4Value, 			sizeof(UART_Send_4Value));
	//5
	DrvUartFormat.TxBuf[0] = value/10 + 0x30;
	DrvUartFormat.TxBuf[1] = value%10 + 0x30;
	V_UARTTxData(DrvUartFormat.TxBuf, 2);
	
	UART_SendData(UART_Send_6End2, 				sizeof(UART_Send_6End2));
}

#define RXState_None 	0
#define RXState_f0 		1
#define RXState_f1		2
#define RXState_f2 		3
#define RXState_f3 		4
#define RXState_ok 		5
#define RXState_Is_getAllSensors 		6
#define RXState_Is_updateSensor 		7

void V_UARTReceiveInput(unsigned char value)
{
	//提取f":"
	if(value == 'f')
	{
		DrvUartFormat.RXState = RXState_f0;
	}
	else
	{
		switch(DrvUartFormat.RXState)
		{
			case RXState_f0 : if(value == '"') DrvUartFormat.RXState = RXState_f1; else DrvUartFormat.RXState = RXState_None;
				break;
			case RXState_f1 : if(value == ':') DrvUartFormat.RXState = RXState_f2; else DrvUartFormat.RXState = RXState_None;
				break;
			case RXState_f2 : if(value == '"') DrvUartFormat.RXState = RXState_f3; else DrvUartFormat.RXState = RXState_None;
				break;
			case RXState_None:
			case RXState_ok:
			default :
				break;
		}
	}
	if(DrvUartFormat.RXState == RXState_f3)
	{
		DrvUartFormat.RxBuf[0] = DrvUartFormat.RxBuf[1];
	    DrvUartFormat.RxBuf[1] = DrvUartFormat.RxBuf[2];
		DrvUartFormat.RxBuf[2] = DrvUartFormat.RxBuf[3];
		DrvUartFormat.RxBuf[3] = DrvUartFormat.RxBuf[4];
		DrvUartFormat.RxBuf[4] = DrvUartFormat.RxBuf[5];
		DrvUartFormat.RxBuf[5] = DrvUartFormat.RxBuf[6];
		DrvUartFormat.RxBuf[6] = DrvUartFormat.RxBuf[7];
		DrvUartFormat.RxBuf[7] = DrvUartFormat.RxBuf[8];
		DrvUartFormat.RxBuf[8] = DrvUartFormat.RxBuf[9];
		DrvUartFormat.RxBuf[9] = DrvUartFormat.RxBuf[10];
		DrvUartFormat.RxBuf[10] = DrvUartFormat.RxBuf[11];
		DrvUartFormat.RxBuf[11] = DrvUartFormat.RxBuf[12];
		DrvUartFormat.RxBuf[12] = value;
		DrvUartFormat.RxCycle1 ++;
		if(DrvUartFormat.RxCycle1 == 14)
		{
			DrvUartFormat.RxCycle1 = 0;
			//getAllSensors
			if( (DrvUartFormat.RxBuf[0]=='g')&&
				(DrvUartFormat.RxBuf[1]=='e')&&
				(DrvUartFormat.RxBuf[2]=='t')&&
				(DrvUartFormat.RxBuf[3]=='A')&&
				(DrvUartFormat.RxBuf[4]=='l')&&
				(DrvUartFormat.RxBuf[5]=='l')&&
				(DrvUartFormat.RxBuf[6]=='S')&&
				(DrvUartFormat.RxBuf[7]=='e')&&
				(DrvUartFormat.RxBuf[8]=='n')&&
				(DrvUartFormat.RxBuf[9]=='s')&&
				(DrvUartFormat.RxBuf[10]=='o')&&
				(DrvUartFormat.RxBuf[11]=='r')&&
				(DrvUartFormat.RxBuf[12]=='s'))
			{
				DrvUartFormat.RXState = RXState_Is_getAllSensors;
			}
			else //updateSensor
			if( (DrvUartFormat.RxBuf[0]=='u')&&
				(DrvUartFormat.RxBuf[1]=='p')&&
				(DrvUartFormat.RxBuf[2]=='d')&&
				(DrvUartFormat.RxBuf[3]=='a')&&
				(DrvUartFormat.RxBuf[4]=='t')&&
				(DrvUartFormat.RxBuf[5]=='e')&&
				(DrvUartFormat.RxBuf[6]=='S')&&
				(DrvUartFormat.RxBuf[7]=='e')&&
				(DrvUartFormat.RxBuf[8]=='n')&&
				(DrvUartFormat.RxBuf[9]=='s')&&
				(DrvUartFormat.RxBuf[10]=='o')&&
				(DrvUartFormat.RxBuf[11]=='r'))
			{
				DrvUartFormat.RXState = RXState_Is_updateSensor;
				
			}
			else
			{
				DrvUartFormat.RXState = RXState_None;
			}
		}
	}
	switch(DrvUartFormat.RXState)
	{
		case RXState_Is_getAllSensors :
			DrvUartFormat.flag.b.IsRX_getAllSensors = 1;
			break;
		case RXState_Is_updateSensor :
			DrvUartFormat.RxCycle2 ++;
			if(DrvUartFormat.RxCycle2 == 9)
			{
				DrvUartFormat.RxBuf[13] = value;//標識C
			}
			else if(DrvUartFormat.RxCycle2 == 10)
			{
				DrvUartFormat.RxBuf[14] = value;//標識1
			}
			else if(DrvUartFormat.RxCycle2 == 19)
			{
				DrvUartFormat.RxBuf[15] = value;//數據
				DrvUartFormat.flag.b.IsRX_updateSensor = 1;
				DrvUartFormat.RXState = RXState_None;
			}
			
			break;
		default :
		break;
	}
	if(value == '!')
	{
		DrvUartFormat.RXState = RXState_None;
		DrvUartFormat.RxCycle1 = 0;
		DrvUartFormat.RxCycle2 = 0;
	}
	
	
}
