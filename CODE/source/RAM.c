/*
 * @RAM清零
 * @創建時間：T20201028
 * @作者：Viking
 * @版本號：V2.0
 * @注：
 */
#include "common.h"


/**
 * @brief RAM初始化
 * @detail 將所有RAM初始為0
 *
 * @note 適用RAM大於256byte IP
 * @attention 注意
 * @warning 警告
 * @exception 异常
 */
#define RAM_BANK 2


void V_RamInit()
{
	_dmbp0 = 0;
	_mp1 = 0x80;
	for(_tblp = 0x00;_tblp < 128;_tblp++)
	{
		_iar1 = 0;
		_mp1++;
	}
	
	_dmbp0 = 1;	
	_mp1 = 0x80;
	for(_tblp = 0x00;_tblp < 128;_tblp++)
	{
		_iar1 = 0;
		_mp1++;
	}	
}

