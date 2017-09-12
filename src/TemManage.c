#include "TemManage.h"
unsigned char init()
{
	unsigned char NumOfDev;
	lcd_Disp_Check_Status(Init_ds18b20());
	Delay_Nms(250);
	Delay_Nms(250);
	Delay_Nms(250);
	Delay_Nms(250);
	while(Init_ds18b20()==0)
	{
		lcd_Disp_Check_Status(Init_ds18b20());
		Delay_Nms(250);
		Delay_Nms(250);
	}
	NumOfDev=ds18b20_SearchRom();
	
	lcd_Disp_DevicesNum(NumOfDev);
	Set_ds18b20();
	Delay_Nms(250);
	Delay_Nms(250);
	return(NumOfDev);
}
void main()
{
	unsigned char NumOfDev;
	NumOfDev=init();
	while(1)
	{
		Delay_Nms(250);
		Delay_Nms(250);
		lcd_Disp(ds18b20_Read_ID_Temperature(0,NumOfDev),ds18b20_Read_ID_Temperature(1,NumOfDev),40,50,60);
	}
}