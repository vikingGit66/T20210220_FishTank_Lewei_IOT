
#ifndef _GPIO_H_
#define _GPIO_H_

#include "HT66F0185.h"

#define SET_PA0_ICPDA()		{}
#define SET_PA0_TP0()		{}
#define SET_PA0_OCDSDA()	{}

#define SET_PA1_LED8()		{ _pac1 = 0; _pa1 = 0; }
#define SET_PA1_SDO()		{}
#define SET_PA1_SSEG2()		{}
#define SET_PA1_SCOM2()		{}

#define SET_PA2_ICPCK()		{}
#define SET_PA2_OCDSCK()	{}

#define SET_PA3_SDI()		{}
#define SET_PA3_SDA()		{}
#define SET_PA3_CX()		{ _cos = 0;}
#define CLR_PA3_CX()		{ _cos = 1;}
#define SET_PA3_SSEG3()		{}
#define SET_PA3_SCOM3()		{}

#define SET_PA4_TCK1()		{}
#define SET_PA4_SSEG15()	{}
#define SET_PA4_AN3()		{}

#define SET_PA5_LED1_POWER(){ _pac5 = 0; _pa5 = 0;}
#define SET_PA5_SSEG10()	{}
#define SET_PA5_AN4()		{}
#define SET_PA5_VREFI()		{}

#define SET_PA6_TCK2()		{}
#define SET_PA6_AN5()		{}
#define SET_PA6_VREF_VDD()	{ _vrefps = 1; _savrs3 = 0; _savrs2 = 0; _savrs1 = 0; }
#define CLR_PA6_VREF_VDD()	{ _vrefps = 0; _savrs3 = 0; _savrs2 = 0; _savrs1 = 0; }
#define SET_PA6_VREF_VREFI(){}
#define SET_PA6_VREF_VBG()	{}
#define SET_PA6_SSEG9()		{}

#define SET_PA7_LED2_POWER(){ _pac7 = 0; _pa7 = 0; }
#define SET_PA7_SDA()		{}
#define SET_PA7_SSEG8()		{}
#define SET_PA7_AN6()		{}

#define SET_PB0_KEY0()		{ _pbc0 = 1; _pbpu0 = 1; }
#define SET_PB0_INT0_DOWN()	{ _int0s1 = 1 ; _int0s0 = 0 ; _int0f = 0; _int0e = 1;}
#define SET_PB0_SSEG18()	{}
#define SET_PB0_AN0()		{}
#define SET_PB0_XT1()		{}

#define SET_PB1_KEY1()		{ _pbc1 = 1; _pbpu1 = 1; }
#define SET_PB1_INT0_DOWN()	{ _int1s1 = 1 ; _int1s0 = 0 ; _int1f = 0; _int1e = 1;}
#define SET_PB1_SSEG17()	{}
#define SET_PB1_AN1()		{}
#define SET_PB1_XT2()		{}

#define SET_PB2_TCK0()		{}
#define SET_PB2_SSEG16()	{}
#define SET_PB2_AN2()		{ _ace2 = 1;}
#define CLR_PB2_AN2()		{ _ace2 = 0;}

#define SET_PB3_LED3_POWER(){ _pbc3 = 0; _pb3 = 0;}
#define SET_PB3_TX()		{}
#define SET_PB3_SSEG7()		{}
#define SET_PB3_AN7()		{}
#define CLR_PB3_TP2()		{}

#define SET_PB4_C_POWER()	{ _pbc4 = 0; _pb4 = 1;}
#define CLR_PB4_C_POWER()	{ _pbc4 = 0; _pb4 = 0;}
#define SET_PB4_RX()		{}
#define SET_PB4_SSEG6()		{}
#define SET_PB4_CLO()		{}

#define SET_PB5_SCS()		{}
#define SET_PB5_C_N()		{ _csel = 1; }
#define CLR_PB5_C_N()		{ _csel = 0; }
#define SET_PB5_SSEG5()		{}
#define SET_PB5_SCOM5()		{}

#define SET_PB6_SCK()		{}
#define SET_PB6_SCL()		{}
#define SET_PB6_C_P()		{ _csel = 1;}
#define CLR_PB6_C_P()		{ _csel = 0;}
#define SET_PB6_SSEG4()		{}
#define SET_PB6_SCOM4()		{}

#define SET_PC0_LED1() 		{ _pcc0 = 0; _pc0 = 0; }
#define SET_PC0_SSEG19() 	{}
#define SET_PC0_OSC1() 		{}

#define SET_PC1_LED2()		{ _pcc1 = 0; _pc1 = 0; }
#define SET_PC1_SSEG20() 	{}
#define SET_PC1_OSC2() 		{}

#define SET_PC2_LED3()		{ _pcc2 = 0; _pc2 = 0; }
#define SET_PC2_SDO()		{}
#define SET_PC2_SSEG0()		{}
#define SET_PC2_SCOM0()		{}

#define SET_PC3_LED4()		{ _pcc3 = 0; _pc3 = 0; }
#define SET_PC3_SDO()		{}
#define SET_PC3_SSEG21()	{}

#define SET_PC4_LED5()		{ _pcc4 = 0; _pc4 = 0; }
#define SET_PC4_SDI()		{}
#define SET_PC4_SDA()		{}
#define SET_PC4_SSEG22()	{}

#define SET_PC5_LED6()		{ _pcc5 = 0; _pc5 = 0; }
#define SET_PC5_SCK()		{}
#define SET_PC5_SCL()		{}
#define SET_PC2_SSEG1()		{}
#define SET_PC2_SCOM1()		{}

#define SET_PC6_LED7()		{ _pcc5 = 0; _pc5 = 0; }
#define SET_PC6_SCS()		{}
#define SET_PC6_SSEG23()	{}

#define SET_PD0_SSEG11()	{}

#define SET_PD1_RX()		{ _pdc1 = 1;}
#define SET_PD1_SSEG12()	{}

#define SET_PD2_TX()		{ _pdc1 = 0;}
#define SET_PD2_SSEG13()	{}

#define SET_PD3_SSEG14()	{}

void V_GPIOPowerOnInit();
void V_GPIOPowerDownInit();

#endif
