/*
STC15W408AS-SOP28@11.0592MHz
*/
#ifndef _LCD1602_H_
#define _LCD1602_H_
#include <stc15.h>
#include <string.h>
#include "delay.h"
#define LB P1
sbit en=P2^0;
sbit rw=P2^1;
sbit rs=P2^2;
sbit bg=P2^7;
void lcd_WriteCom(unsigned char com);
void lcd_WriteData(unsigned char date);
void lcd_WriteTem(unsigned char tem);
void lcd_Disp(unsigned char cpu,unsigned char gpu,unsigned char sb,unsigned char air,unsigned char water);
void lcd_DispMessage(bit state);
#endif