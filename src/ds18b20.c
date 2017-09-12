#include "ds18b20.h"
/* 对DS18B20数据总线IO写入操作 */
void Write_ds18b20IO(bit b)
{
	tb0=b;
}
/* 对DS18B20数据总线IO读取操作 */
bit Read_ds18b20IO()
{
	bit b;
	b=tb0;
	return(b);
}
/* 初始化DS18B20 */
bit Init_ds18b20()
{
	unsigned char i=0;
	Write_ds18b20IO(1);
	Delay2us();
	Write_ds18b20IO(0);
	Delay600us();
	Write_ds18b20IO(1);
	Delay60us();
	while(Read_ds18b20IO())						// 超时控制
	{
		Delay2us();
		i++;
		if(i>150)
		{
			return(0);										// 返回0，所有设备离线
		}
	}
	Delay600us();
	return(1);												// 返回1，存在设备在线
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
/* 写入一位数据 */
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
/* 写入一字节数据 */
void ds18b20_WriteData(unsigned char datum)
{
	unsigned char i=8;
	while(i--)
	{
		ds18b20_WriteBit(datum&0x01);
		datum>>=1;
	}
}
/* 读取一位数据 */
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
/* 读取2bit数据 */
unsigned char ds18b20_Read2Bit()
{
	
	unsigned char datum=0;
	unsigned char i=2;
	while(i--)
	{
		datum<<=1;
		if(ds18b20_ReadBit())
		{
			datum|=1;
		}
	}
	return(datum);
}
/* 读取一字节数据 */
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
/* 配置总线上的DS18B20 */
void Set_ds18b20()
{
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(writescratchpad);
	ds18b20_WriteData(0x55);					// 设置高温报警阈值		
	ds18b20_WriteData(0xf5);					// 设置低温报警阈值
	ds18b20_WriteData(0x1f);					// 设置温度传感器工作于9位模式，温度转换时间不超过100ms
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(copyscratchpad);
}
///* 读取温度数据 */
//unsigned char ds18b20_ReadTemperature()
//{
//	unsigned char th,tl,temp;
//	Init__ds18b20();
//	ds18b20_WriteData(skiprom);
//	ds18b20_WriteData(convertt);
//	Delay_Nms(100);
//	Init__ds18b20();
//	ds18b20_WriteData(skiprom);
//	ds18b20_WriteData(readscratchpad);
//	tl=ds18b20_ReadData();
//	th=ds18b20_ReadData();
//	tl&=0xf0;
//	tl>>=4;
//	th&=0x0f;
//	th<<=4;
//	temp=tl|th;
//	return(temp);
//}
/* 搜索设备ROM */
unsigned char ds18b20_SearchRom()
{ 
	unsigned char k,m,n;																	//K：读两位结果；m：64位ROM字节号，n：64位ROM字位号
	unsigned char conflict;																//冲突位
	unsigned char stack[(MaxNumOfds18b20)];								//存储冲突位节点序列（栈）
	unsigned char f=0;																		//栈顶
	unsigned char ss[64];																	//ROM缓存
	unsigned char num=0;																	//搜索到的器件计数
	unsigned int 	IAP_ADDRESS=0x0000;
	IapEraseSector(IAP_ADDRESS);													//擦除EEPROM相应扇区
	
	do
	{
		Init__ds18b20();
		ds18b20_WriteData(searchrom);	
		for(m=0;m<8;m++)
		{
			unsigned char s=0;																//ROM字节暂存
			for(n=0;n<8;n++)
			{
				k=ds18b20_Read2Bit();														//读两位数据
				k=k&0x03;
				s>>=1;
				if(k==0x01)																			//01读到的数据为0 写0 此位为0的器件响应
				{   		
					ds18b20_WriteBit(0);
	    		ss[(m*8+n)]=0;
				}
				else if(k==0x02)																//10读到的数据为1 写1 此位为1的器件响应
				{
					s=s|0x80;
					ds18b20_WriteBit(1);
					ss[(m*8+n)]=1;
				}
				else if(k==0x00)																//读到的数据为00 有冲突位 判断冲突位
				{	
					conflict=m*8+n+1;					
					if(conflict>stack[f])													//如果冲突位大于栈顶写0
					{						
						ds18b20_WriteBit(0);
						ss[(m*8+n)]=0;												
						stack[++f]=conflict;						
					}
					else if(conflict<stack[f])										//小于栈顶写以前的数据
					{
						s=s|((ss[(m*8+n)]&0x01)<<7);
						ds18b20_WriteBit(ss[(m*8+n)]);
					}
					else																					//等于栈顶写1
					{
						s=s|0x80;
						ds18b20_WriteBit(1);
						ss[(m*8+n)]=1;
						f=f-1;
					}
				}
				else
				{
					return(0xff);																//返回错误，设备离线
				}
			}
			IapProgramByte(IAP_ADDRESS,s);
			IAP_ADDRESS++;
		}
		num=num+1;
	}
	while(stack[f]!=0&&(num<MaxNumOfds18b20));	
	return(num);																					//返回搜索到的个数
}
/* 读取指定器件温度 */
unsigned char ds18b20_Read_ID_Temperature(unsigned char seq,unsigned char NumOfDev)
{
	unsigned char th, tl, num, tem;
	unsigned char curID[8];
	unsigned int 	IAP_ADDRESS=0x0000+8*seq;							//初始EEPROM读首地址
	
	if((seq>(NumOfDev-1))|(seq<0))	
	{
		return 0xfe;																			//返回错误，输入序列不合法
	}
	
	for(num = 0;num < 8;num ++)													//映射传感器顺序，取出对应ID
	{
		curID[num]=IapReadByte(IAP_ADDRESS+num);
	}
	
	if(Init_ds18b20()==0)	
	{
		return 0xff;																			//器件失去响应
	}
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(convertt);
	Delay_Nms(100);
	Init__ds18b20();
	ds18b20_WriteData(matchrom);
	for(num = 0;num < 8;num ++)													//发送8byte序列号
	{
	   ds18b20_WriteData(curID[num]);
	}
	Delay10us();
	ds18b20_WriteData(readscratchpad);
	tl = ds18b20_ReadData();
	th = ds18b20_ReadData();
	tl&=0xf0;
	tl>>=4;
	th&=0x0f;
	th<<=4;
	tem=tl|th;
	return(tem);
} 