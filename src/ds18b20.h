#ifndef _DS18B20_H_
#define _DS18B20_H_
#include <stc15.h>
#include <intrins.h>
#include "delay.h"
#include "e2prom.h"

/* ROM命令 */
#define readrom 0x33
#define matchrom 0x55
#define skiprom 0xcc
#define searchrom 0xf0
#define alarm search 0xec
/* Memory命令 */
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
//读写温度传感器总线IO
void Write_ds18b20IO(bit b);
bit Read_ds18b20IO();
//初始化温度传感器
bit Init_ds18b20();													//初始化传感器并返回标志
void Init__ds18b20();												//无返回初始化传感器
//写温度传感器
void ds18b20_WriteBit(bit b);
void ds18b20_WriteData(unsigned char datum);
//读温度传感器
bit ds18b20_ReadBit();
unsigned char ds18b20_Read2Bit();
unsigned char ds18b20_ReadData();
//配置温度传感器
void Set_ds18b20();
//忽略ROM读取温度数据
//unsigned char ds18b20_readtemperature();
//多传感器单总线相关
unsigned char ds18b20_SearchRom();
unsigned char ds18b20_Read_ID_Temperature(unsigned char seq,unsigned char NumOfDev);
#endif