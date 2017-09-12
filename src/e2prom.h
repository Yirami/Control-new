/*
STC15W408AS-SOP28@11.0592MHz
*/
#ifndef _E2PROM_H_
#define _E2PROM_H_
#include <stc15.h>
#include <intrins.h>

#define CMD_IDLE			0			//¿ÕÏĞÄ£Ê½
#define CMD_READ			1			//IAP×Ö½Ú¶ÁÃüÁî
#define CMD_PROGRAM		2			//IAP×Ö½Ú±à³ÌÃüÁî
#define CMD_ERASE			3			//IAP×Ö½Ú²Á³ıÃüÁî

#define ENABLE_IAP 		0X82

void IapIdle();
unsigned char IapReadByte(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);
void IapEraseSector(unsigned int addr);
#endif