#include "delay.h"

/* ��ʱ������ms����*/
void Delay_Nms(unsigned char n)		//@11.0592MHz
{
	while (--n)
	{
		unsigned char i, j;

		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}
/* ��ʱ������us����*/
void Delay2us()		//@11.0592MHz
{
	unsigned char i;

	i = 3;
	while (--i);
}
/* ��ʱ������us����*/
void Delay10us()		//@11.0592MHz
{
	unsigned char i;

	_nop_();
	i = 25;
	while (--i);
}
/* ��ʱ������us����*/
void Delay60us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 1;
	j = 162;
	do
	{
		while (--j);
	} while (--i);
}
/* ��ʱ������us����*/
void Delay600us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 7;
	j = 113;
	do
	{
		while (--j);
	} while (--i);
}