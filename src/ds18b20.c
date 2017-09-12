#include "ds18b20.h"
/* ��DS18B20��������IOд����� */
void Write_ds18b20IO(bit b)
{
	tb0=b;
}
/* ��DS18B20��������IO��ȡ���� */
bit Read_ds18b20IO()
{
	bit b;
	b=tb0;
	return(b);
}
/* ��ʼ��DS18B20 */
bit Init_ds18b20()
{
	unsigned char i=0;
	Write_ds18b20IO(1);
	Delay2us();
	Write_ds18b20IO(0);
	Delay600us();
	Write_ds18b20IO(1);
	Delay60us();
	while(Read_ds18b20IO())
	{
		Delay2us();
		i++;
		if(i>150)
		{
			return(0);
		}
	}
	Delay600us();
	return(1);
}
void Init__ds18b20()
{
	Write_ds18b20IO(1);
	Delay2us();
	Write_ds18b20IO(0);
	Delay600us();
	Write_ds18b20IO(1);
	Delay600us();
}
/* д��һλ���� */
void ds18b20_WriteBit(bit b)
{
	Write_ds18b20IO(1);
	Delay2us();
	Write_ds18b20IO(0);
	Delay2us();
	Write_ds18b20IO(b);
	Delay60us();
	Write_ds18b20IO(1);
	Delay10us();
}
/* д��һ�ֽ����� */
void ds18b20_WriteData(unsigned char datum)
{
	unsigned char i=8;
	while(i--)
	{
		ds18b20_WriteBit(datum&0x01);
		datum>>=1;
	}
}
/* ��ȡһλ���� */
bit ds18b20_ReadBit()
{
	bit b;
	Write_ds18b20IO(1);
	Delay2us();
	Write_ds18b20IO(0);
	Delay2us();
	Write_ds18b20IO(1);
	Delay10us();
	b=Read_ds18b20IO();
	Delay60us();
	return(b);
}
/* ��ȡһ�ֽ����� */
unsigned char ds18b20_ReadData()
{
	
	unsigned char datum=0;
	unsigned char i=8;
	while(i--)
	{
		datum>>=1;
		if(ds18b20_ReadBit())
		{
			datum|=0x80;
		}
	}
	return(datum);
}
/* ���������ϵ�DS18B20 */
void set_ds18b20()
{
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(writescratchpad);
	ds18b20_WriteData(0x55);
	ds18b20_WriteData(0xf5);
	ds18b20_WriteData(0x1f);
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(copyscratchpad);
}
/* ��ȡ�¶����� */
unsigned char ds18b20_readtemperature()
{
	unsigned char th,tl,temp;
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(convertt);
	Delay_Nms(100);
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(readscratchpad);
	tl=ds18b20_ReadData();
	th=ds18b20_ReadData();
	tl&=0xf0;
	tl>>=4;
	th&=0x0f;
	th<<=4;
	temp=tl|th;
	return(temp);
}