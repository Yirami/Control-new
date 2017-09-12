/*使用I/O资源：P1.0,P1.1,P1.2,P1.3,P1.4,P1.5,P3.0(RxD),P3.1(TxD),P3.2(INT0),P3.3,P3.6,P3.7
/*寄存器使用说明：第一组：R7(2us循环个数；10ms使用)R6(2us循环技计数；10ms使用)R5(8bit写入循环数)
/*<<<<<<<<<<<<<<<R4(8byte写入循环数)R1(间接存放地址)
/*单片机采用STC15W408AS(DIP16)
								/************************
									地址初始化
								************************/
WKTCL DATA 0AAH
WKTCH DATA 0ABH
IAP_DATA DATA 0C2H
IAP_ADDRH DATA 0C3H
IAP_ADDRL DATA 0C4H
IAP_CMD DATA 0C5H
IAP_TRIG DATA 0C6H
IAP_CONTR DATA 0C7H						//定义IAP控制寄存器
LEDN1 DATA 32H							//定义数码管1显示数据存放地址
LEDN2 DATA 33H							//定义数码管2显示数据存放地址
LEDN3 DATA 34H							//定义数码管3显示数据存放地址
TPT1_L DATA 35H							//定义温传1的温度数据低位存放地址
TPT1_H DATA 36H							//定义温传1的温度数据高位存放地址
TPT2_L DATA 37H							//定义温传2的温度数据低位存放地址
TPT2_H DATA 38H							//定义温传2的温度数据高位存放地址
TPDF_COPY DATA 39H						//定义温差数据镜像存放地址
TPDF_C DATA 3AH							//定义计算温差数据存放地址
W_LAT DATA 3BH							//写锁存器循环数存放地址
ROMPTR DATA 3CH							//18B20ROM存储地址指针寄存器
ROMJ DATA 3DH							//18B20ROM节点地址寄存器
TEMP1 DATA 3EH							//1号温度传感器温度八位补码表示
TEMP2 DATA 3FH							//2号温度传感器温度八位补码表示
ROM1_1 DATA 40H							//18B20ROM存储地址
ROM1_2 DATA 41H							//18B20ROM存储地址
ROM1_3 DATA 42H							//18B20ROM存储地址
ROM1_4 DATA 43H							//18B20ROM存储地址
ROM1_5 DATA 44H							//18B20ROM存储地址
ROM1_6 DATA 45H							//18B20ROM存储地址
ROM1_7 DATA 46H							//18B20ROM存储地址
ROM1_8 DATA 47H							//18B20ROM存储地址
ROM2_1 DATA 48H							//18B20ROM存储地址
ROM2_2 DATA 49H							//18B20ROM存储地址
ROM2_3 DATA 4AH							//18B20ROM存储地址
ROM2_4 DATA 4BH							//18B20ROM存储地址
ROM2_5 DATA 4CH							//18B20ROM存储地址
ROM2_6 DATA 4DH							//18B20ROM存储地址
ROM2_7 DATA 4EH							//18B20ROM存储地址
ROM2_8 DATA 4FH							//18B20ROM存储地址
TPDF_C_L DATA 50H						//定义计算温差个位存放地址
TPDF_C_H DATA 51H						//定义计算温差十位存放地址
LEDNUMPT DATA 52H						//定义LED数据表指针
TPDF_COPY_L DATA 53H					//定义设置温差个位存放地址
TPDF_COPY_H DATA 54H					//定义设置温差十位存放地址
LSE EQU 00H								//定义数码管设置使能位
ROMR1 EQU 01H							//定义ROM两读第1位
ROMR2 EQU 02H							//定义ROM两读第2位
ROMJE EQU 03H							//ROM节点选1使能
ROMJF EQU 04H							//ROM节点存在标志
CCLATNF EQU 05H							//作差结果为负标志
DQ EQU P1.0
EXECT EQU P1.1
SDI EQU P1.2
OE EQU P1.3
SCK EQU P1.4
LCK EQU P1.5
K0 EQU P3.3
K1 EQU P3.6
K2 EQU P3.7
