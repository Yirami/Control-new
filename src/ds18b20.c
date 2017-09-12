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
	while(Read_ds18b20IO())						// ��ʱ����
	{
		Delay2us();
		i++;
		if(i>150)
		{
			return(0);										// ����0�������豸����
		}
	}
	Delay600us();
	return(1);												// ����1�������豸����
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
/* ��ȡ2bit���� */
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
void Set_ds18b20()
{
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(writescratchpad);
	ds18b20_WriteData(0x55);					// ���ø��±�����ֵ		
	ds18b20_WriteData(0xf5);					// ���õ��±�����ֵ
	ds18b20_WriteData(0x1f);					// �����¶ȴ�����������9λģʽ���¶�ת��ʱ�䲻����100ms
	Init__ds18b20();
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(copyscratchpad);
}
///* ��ȡ�¶����� */
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
/* �����豸ROM */
unsigned char ds18b20_SearchRom()
{ 
	unsigned char k,m,n;																	//K������λ�����m��64λROM�ֽںţ�n��64λROM��λ��
	unsigned char conflict;																//��ͻλ
	unsigned char stack[(MaxNumOfds18b20)];								//�洢��ͻλ�ڵ����У�ջ��
	unsigned char f=0;																		//ջ��
	unsigned char ss[64];																	//ROM����
	unsigned char num=0;																	//����������������
	unsigned int 	IAP_ADDRESS=0x0000;
	IapEraseSector(IAP_ADDRESS);													//����EEPROM��Ӧ����
	
	do
	{
		Init__ds18b20();
		ds18b20_WriteData(searchrom);	
		for(m=0;m<8;m++)
		{
			unsigned char s=0;																//ROM�ֽ��ݴ�
			for(n=0;n<8;n++)
			{
				k=ds18b20_Read2Bit();														//����λ����
				k=k&0x03;
				s>>=1;
				if(k==0x01)																			//01����������Ϊ0 д0 ��λΪ0��������Ӧ
				{   		
					ds18b20_WriteBit(0);
	    		ss[(m*8+n)]=0;
				}
				else if(k==0x02)																//10����������Ϊ1 д1 ��λΪ1��������Ӧ
				{
					s=s|0x80;
					ds18b20_WriteBit(1);
					ss[(m*8+n)]=1;
				}
				else if(k==0x00)																//����������Ϊ00 �г�ͻλ �жϳ�ͻλ
				{	
					conflict=m*8+n+1;					
					if(conflict>stack[f])													//�����ͻλ����ջ��д0
					{						
						ds18b20_WriteBit(0);
						ss[(m*8+n)]=0;												
						stack[++f]=conflict;						
					}
					else if(conflict<stack[f])										//С��ջ��д��ǰ������
					{
						s=s|((ss[(m*8+n)]&0x01)<<7);
						ds18b20_WriteBit(ss[(m*8+n)]);
					}
					else																					//����ջ��д1
					{
						s=s|0x80;
						ds18b20_WriteBit(1);
						ss[(m*8+n)]=1;
						f=f-1;
					}
				}
				else
				{
					return(0xff);																//���ش����豸����
				}
			}
			IapProgramByte(IAP_ADDRESS,s);
			IAP_ADDRESS++;
		}
		num=num+1;
	}
	while(stack[f]!=0&&(num<MaxNumOfds18b20));	
	return(num);																					//�����������ĸ���
}
/* ��ȡָ�������¶� */
unsigned char ds18b20_Read_ID_Temperature(unsigned char seq,unsigned char NumOfDev)
{
	unsigned char th, tl, num, tem;
	unsigned char curID[8];
	unsigned int 	IAP_ADDRESS=0x0000+8*seq;							//��ʼEEPROM���׵�ַ
	
	if((seq>(NumOfDev-1))|(seq<0))	
	{
		return 0xfe;																			//���ش����������в��Ϸ�
	}
	
	for(num = 0;num < 8;num ++)													//ӳ�䴫����˳��ȡ����ӦID
	{
		curID[num]=IapReadByte(IAP_ADDRESS+num);
	}
	
	if(Init_ds18b20()==0)	
	{
		return 0xff;																			//����ʧȥ��Ӧ
	}
	ds18b20_WriteData(skiprom);
	ds18b20_WriteData(convertt);
	Delay_Nms(100);
	Init__ds18b20();
	ds18b20_WriteData(matchrom);
	for(num = 0;num < 8;num ++)													//����8byte���к�
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