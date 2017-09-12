#ifndef _DS18B20_H_
#define _DS18B20_H_
#include <stc15.h>
#include <intrins.h>
#include "delay.h"
#include "e2prom.h"

/* ROM���� */
#define readrom 0x33
#define matchrom 0x55
#define skiprom 0xcc
#define searchrom 0xf0
#define alarm search 0xec
/* Memory���� */
#define writescratchpad 0x4e
#define readscratchpad 0xbe
#define copyscratchpad 0x48
#define convertt 0x44
#define recalle2 0xb8
#define readpowersupply 0xb4

#define MaxNumOfds18b20 10

sbit tb0=P3^7;
sbit tb1=P3^6;
sbit tb2=P3^5;
sbit tb3=P3^4;
sbit tb4=P3^3;
sbit tb5=P3^2;
//��д�¶ȴ���������IO
void Write_ds18b20IO(bit b);
bit Read_ds18b20IO();
//��ʼ���¶ȴ�����
bit Init_ds18b20();													//��ʼ�������������ر�־
void Init__ds18b20();												//�޷��س�ʼ��������
//д�¶ȴ�����
void ds18b20_WriteBit(bit b);
void ds18b20_WriteData(unsigned char datum);
//���¶ȴ�����
bit ds18b20_ReadBit();
unsigned char ds18b20_Read2Bit();
unsigned char ds18b20_ReadData();
//�����¶ȴ�����
void Set_ds18b20();
//����ROM��ȡ�¶�����
//unsigned char ds18b20_readtemperature();
//�ഫ�������������
unsigned char ds18b20_SearchRom();
unsigned char ds18b20_Read_ID_Temperature(unsigned char seq,unsigned char NumOfDev);
#endif