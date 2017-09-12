#include "lcd1602.h"
unsigned char num;
unsigned char code table1[]="Cpu SB Gpu A  W";
unsigned char code table2[]="All are offline!";
unsigned char code table3[]="Device online!";
/*******************************************************************
* 写指令函数（并行8位传输）
*******************************************************************/
void lcd_WriteCom(unsigned char com)
{
	rs=0;
	rw=0;
	LB=com;
	Delay_Nms(2);
	en=1;
	Delay_Nms(2);
	en=0;
	Delay_Nms(5);
}
/*******************************************************************
* 写数据函数（并行8位传输）
*******************************************************************/
void lcd_WriteData(unsigned char datum)
{
	rs=1;
	rw=0;
	LB=datum;
	Delay_Nms(2);
	en=1;
	Delay_Nms(2);
	en=0;
	Delay_Nms(5);
}
/*******************************************************************
* 写入温度数据函数（输入两位十进制数）
*******************************************************************/
void lcd_WriteTem(unsigned char tem)
{
	unsigned char shi,ge;
	shi=tem/10;
	ge=tem%10;
	lcd_WriteData(shi+0x30);
	lcd_WriteData(ge+0x30);
}
/*******************************************************************
* 指定位置写入全部温度数据函数（输入五组两位十进制数）
*******************************************************************/
void lcd_Disp(unsigned char cpu,unsigned char sb,unsigned char gpu,unsigned char air,unsigned char water)
{
	en=0;
	lcd_WriteCom(0x38);			//00111000B（设置显示模式）
	lcd_WriteCom(0x0e);			//00001110B（开显示，显示光标，光标不闪烁）
	lcd_WriteCom(0x06);			//00000110B（操作一个字符后 指针+1，写一个字符后，整屏不左移）
	lcd_WriteCom(0x01);			//00000001B（显示清屏）
	lcd_WriteCom(0x80);			//（设置数据指针）
	for(num=0;num<strlen(table1);num++)
	{
		lcd_WriteData(table1[num]);
	}
	lcd_WriteCom(0x80+0x40);	//（设置数据指针）
	lcd_WriteTem(cpu);
	lcd_WriteCom(0x80+0x44);	//（设置数据指针）
	lcd_WriteTem(sb);
	lcd_WriteCom(0x80+0x47);	//（设置数据指针）
	lcd_WriteTem(gpu);
	lcd_WriteCom(0x80+0x4b);	//（设置数据指针）
	lcd_WriteTem(air);
	lcd_WriteCom(0x80+0x4e);	//（设置数据指针）
	lcd_WriteTem(water);
}
/*******************************************************************
* DS18B20初始化状态显示
*******************************************************************/
void lcd_DispMessage(bit state)
{
	en=0;
	lcd_WriteCom(0x38);			//00111000B（设置显示模式）
	lcd_WriteCom(0x0e);			//00001110B（开显示，显示光标，光标不闪烁）
	lcd_WriteCom(0x06);			//00000110B（操作一个字符后 指针+1，写一个字符后，整屏不左移）
	lcd_WriteCom(0x01);			//00000001B（显示清屏）
	lcd_WriteCom(0x80);			//（设置数据指针）
	for(num=0;num<strlen(table1);num++)
	{
		lcd_WriteData(table1[num]);
	}
	lcd_WriteCom(0x80+0x40);	//（设置数据指针）
	if(state)
	{
		for(num=0;num<strlen(table3);num++)
		{
			lcd_WriteData(table3[num]);
		}
	}
	else
	{
		for(num=0;num<strlen(table2);num++)
		{
			lcd_WriteData(table2[num]);
		}
	}
}