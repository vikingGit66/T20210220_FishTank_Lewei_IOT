/*
 * @時鐘初始化
 * @創建時間：T20201028
 * @作者：Viking
 * @版本號：V2.0
 * @注：
 */
#include "common.h"
/**
 * @brief 時鐘初始化32kHz
 * @return void
 */
void V_SysClock_32kHz_Init()
{
    // *********系統時鐘設定********//
    #ifdef _LIRC_
        _hlclk = 0;
        _cks2  = 0;
        _cks1  = 0;
        _cks0  = 0;
        
        // Enter Halt LIRC SLEEP
//		_idlen = 0;		
		
		// Enter Halt LIRC IDEL1
		_idlen = 1;
		_fsyson = 1;	//0:IDEL0

		while(!_lto);
    #endif // _LIRC_
}
/**
 * @brief 時鐘初始化HIRC
 * @return void
 */
void V_SysClock_8MHz_Init()
{
	_hlclk = 1;
//    _cks2  = 0;//8 / 8 = 1MHz
//    _cks1  = 0;
//    _cks0  = 0;
    while(!_hto);
}

