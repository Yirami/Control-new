/*
STC15W408AS-SOP28@11.0592MHz
PWM@SYSclk/12,8
*/
#include <stc15.h>
#include <intrins.h>
#include "delay.h"
#include "ds18b20.h"
#include "lcd1602.h"
#define uchar unsigned char
#define uint unsigned int
sbit fan=P2^3;
sbit pwm=P2^6;
unsigned char init();
