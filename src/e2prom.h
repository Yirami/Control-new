/*
STC15W408AS-SOP28@11.0592MHz
*/
#ifndef _E2PROM_H_
#define _E2PROM_H_
#include <stc15.h>
#include <intrins.h>

#define CMD_IDLE			0			//����ģʽ
#define CMD_READ			1			//IAP�ֽڶ�����
#define CMD_PROGRAM		2			//IAP�ֽڱ������
#define CMD_ERASE			3			//IAP�ֽڲ�������

#define ENABLE_IAP 		0X82

void IapIdle();
unsigned char IapReadByte(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);
void IapEraseSector(unsigned int addr);
#endif