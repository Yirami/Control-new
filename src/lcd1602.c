#include "lcd1602.h"
unsigned char num;
unsigned char code table1[]="Cpu SB Gpu A  W";
unsigned char code table2[]="All are offline!";
unsigned char code table3[]="Device online!";
/*******************************************************************
* дָ���������8λ���䣩
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
* д���ݺ���������8λ���䣩
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
* д���¶����ݺ�����������λʮ��������
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
* ָ��λ��д��ȫ���¶����ݺ���������������λʮ��������
*******************************************************************/
void lcd_Disp(unsigned char cpu,unsigned char sb,unsigned char gpu,unsigned char air,unsigned char water)
{
	en=0;
	lcd_WriteCom(0x38);			//00111000B��������ʾģʽ��
	lcd_WriteCom(0x0e);			//00001110B������ʾ����ʾ��꣬��겻��˸��
	lcd_WriteCom(0x06);			//00000110B������һ���ַ��� ָ��+1��дһ���ַ������������ƣ�
	lcd_WriteCom(0x01);			//00000001B����ʾ������
	lcd_WriteCom(0x80);			//����������ָ�룩
	for(num=0;num<strlen(table1);num++)
	{
		lcd_WriteData(table1[num]);
	}
	lcd_WriteCom(0x80+0x40);	//����������ָ�룩
	lcd_WriteTem(cpu);
	lcd_WriteCom(0x80+0x44);	//����������ָ�룩
	lcd_WriteTem(sb);
	lcd_WriteCom(0x80+0x47);	//����������ָ�룩
	lcd_WriteTem(gpu);
	lcd_WriteCom(0x80+0x4b);	//����������ָ�룩
	lcd_WriteTem(air);
	lcd_WriteCom(0x80+0x4e);	//����������ָ�룩
	lcd_WriteTem(water);
}
/*******************************************************************
* DS18B20��ʼ��״̬��ʾ
*******************************************************************/
void lcd_DispMessage(bit state)
{
	en=0;
	lcd_WriteCom(0x38);			//00111000B��������ʾģʽ��
	lcd_WriteCom(0x0e);			//00001110B������ʾ����ʾ��꣬��겻��˸��
	lcd_WriteCom(0x06);			//00000110B������һ���ַ��� ָ��+1��дһ���ַ������������ƣ�
	lcd_WriteCom(0x01);			//00000001B����ʾ������
	lcd_WriteCom(0x80);			//����������ָ�룩
	for(num=0;num<strlen(table1);num++)
	{
		lcd_WriteData(table1[num]);
	}
	lcd_WriteCom(0x80+0x40);	//����������ָ�룩
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