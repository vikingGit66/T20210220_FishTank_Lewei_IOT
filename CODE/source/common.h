/*
 * @時鐘，小夜燈設置的時間，各個頭文件
 * @創建時間：T20201028-09：36
 * @作者：Viking
 * @版本號：V2.0
 * @注：未添加AD功能
 */
#ifndef _COMMON_H_
#define _COMMON_H_

extern volatile bit bitDebug;

#define u8 unsigned char
#define u16 unsigned int
#define uchar unsigned char
#define uint unsigned int

#define WDT_Disable_8ms() 	 { _wdtc = 0xa8;}
#define WDT_Disable_32ms()   { _wdtc = 0xa9;}
#define WDT_Disable_128ms()  { _wdtc = 0xaa;}
#define WDT_Disable_512ms()  { _wdtc = 0xab;}
#define WDT_Disable_1024ms() { _wdtc = 0xac;}
#define WDT_Disable_2048ms() { _wdtc = 0xad;}
#define WDT_Disable_4096ms() { _wdtc = 0xae;}
#define WDT_Disable_8192ms() { _wdtc = 0xaf;}
//@-------------LVD config--------------@
#define SET_LVD_DISABLE()       { _lvden = 0; _vbgen = 0;}
#define SET_LVD_LVDIN_EN()      { _lvdc = 0x18;}
#define SET_LVD_2V2_EN()        { _lvdc = 0x19;}
#define SET_LVD_2V4_EN()        { _lvdc = 0x1A;}
#define SET_LVD_2V7_EN()        { _lvdc = 0x1B;}
#define SET_LVD_3V0_EN()        { _lvdc = 0x1C;}
#define SET_LVD_3V3_EN()        { _lvdc = 0x1D;}
#define SET_LVD_3V6_EN()        { _lvdc = 0x1E;}
#define SET_LVD_4V0_EN()        { _lvdc = 0x1F;}

//#define DemoDebug
//#ifdef DemoDebug
//#endif

//時鐘
#define SYS_CLOCK_FREQ 8000000 //8000000
#define _LIRC_

#include "HT66F0185.h"
//#include "string.h"
#include "..\source\GPIO.h"
#include "..\source\SysClock.h"
#include "..\source\RAM.h"
#include "..\source\UART.h"
#include "..\source\Timer.h"
#include "..\source\ESP8266_AT.h"




#endif
