/*
 * @GPIO初始化
 * @創建時間：T20201028
 * @作者：Viking
 * @版本號：V2.0
 * @注：
 */
#include "common.h"

/* 
 * @ GPIO上電初始化
 * @ LED High Work
 */
void V_GPIOPowerOnInit()
{
	_acerl = 0x00; //clr AD
	_cos = 1;
	_csel = 0;//關閉比較器引腳
//PA0 ICPDA 	//PA1 LED8
//PA2 ICPCK		//PA3 CX
//PA4 NC		//PA5 LED1_POWER
//PA6 VREF 		//PA7 LED2_POWER
	_pa   = 0B00000000;
	_pac  = 0B01010101;//1 3 5 7
	_papu = 0B01010101;
	_pawu = 0B00000000;

//PB0 KEY1 		//PB1 KEY2
//PB2 NC		//PB3 LED3_POWER
//PB4 C_POWER	//PB5 C-
//PB6 C+		//PB7 NC	
	_pb   = 0B00000000;
	_pbc  = 0B10000111;//3 4 5 6
	_pbpu = 0B10000111;

//PC0 LED1 		//PC1 LED2
//PC2 LED3		//PC3 LED4
//PC4 LED5		//PC5 LED6 		
//PC6 LED7		//PC7 NC
	_pc   = 0B00000000;
	_pcc  = 0B10000000;//0-7
	_pcpu = 0B10000000;

//PD0-4 NC	
	_pd   = 0B00000000;
	_pdc  = 0B11111111;//NC
	_pdpu = 0B11111111;
}
/**
 * @brief 休眠GPIO配置，未使用 IO 輸入上拉
 */
void V_GPIOPowerDownInit()
{
//PA0 ICPDA 	//PA1 LED8
//PA2 ICPCK		//PA3 CX
//PA4 NC		//PA5 LED1_POWER
//PA6 VREF 		//PA7 LED2_POWER
	_pa   = 0B00000000;
	_pac  = 0B00000000;//1 5 7
	_papu = 0B00000000;
	_pawu = 0B00000000;

//PB0 KEY1 		//PB1 KEY2
//PB2 NC		//PB3 LED3_POWER
//PB4 C_POWER	//PB5 C-
//PB6 C+		//PB7 NC	
	_pb   = 0B00000000;
	_pbc  = 0B00000011;
	_pbpu = 0B00000011;

//PC0 LED1 		//PC1 LED2
//PC2 LED3		//PC3 LED4
//PC4 LED5		//PC5 LED6 		
//PC6 LED7		//PC7 NC
	_pc   = 0B00000000;
	_pcc  = 0B00000000;
	_pcpu = 0B11111111;

//PD0-4 NC	
	_pd   = 0B00000000;
	_pdc  = 0B00000000;
	_pdpu = 0B00000000;
}


