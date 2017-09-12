#include "TemManage.h"
void init()
{
	lcd_DispMessage(Init_ds18b20());
	set_ds18b20();
}
void main()
{
	init();
	while(1)
	{
		Delay_Nms(250);
		Delay_Nms(250);
		lcd_Disp(ds18b20_readtemperature(),30,40,50,60);
	}
}