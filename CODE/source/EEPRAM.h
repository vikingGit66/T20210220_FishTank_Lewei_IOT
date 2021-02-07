#ifndef _EEPRAM_H_
#define _EEPRAM_H_

#define EEPRAM_Addr_TipsLEDFlag 	0x00
#define EEPRAM_Addr_TipsLED 		0x01
#define EEPRAM_Addr_LEDPowerFlag 	0x02
#define EEPRAM_Addr_LEDPower 		0x03

#define EEPRAM_TipsLEDFlag 		0xaa
#define EEPRAM_LEDPowerFlag 	0x55

void V_EEPRAM_Start();
unsigned char V_EEPRAM_Write_Byte(unsigned char addr, unsigned char data);
unsigned char V_EEPRAM_Read_Byte(unsigned char addr);

#endif



