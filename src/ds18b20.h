#ifndef _DS18B20_H_
#define _DS18B20_H_
#include <stc15.h>
#include <intrins.h>
#include "delay.h"

/* ROMÃüÁî */
#define readrom 0x33
#define matchrom 0x55
#define skiprom 0xcc
#define searchrom 0xf0
#define alarm search 0xec
/* MemoryÃüÁî */
#define writescratchpad 0x4e
#define readscratchpad 0xbe
#define copyscratchpad 0x48
#define convertt 0x44
#define recalle2 0xb8
#define readpowersupply 0xb4

sbit tb0=P3^7;
sbit tb1=P3^6;
sbit tb2=P3^5;
sbit tb3=P3^4;
sbit tb4=P3^3;
sbit tb5=P3^2;

void Write_ds18b20IO(bit b);
bit Read_ds18b20IO();

bit Init_ds18b20();
void Init__ds18b20();

void ds18b20_WriteBit(bit b);
void ds18b20_WriteData(unsigned char datum);

bit ds18b20_ReadBit();
unsigned char ds18b20_ReadData();

void set_ds18b20();

unsigned char ds18b20_readtemperature();

#endif