#include <head.inc>
//��ʱ��DELAY2US��DELAY10US��DELAY25US��DELAY60US��DELAY80US��DELAY600US��DELAY10MS��DELAY800MS��DELAY1000MS
ORG 0000H     							//��λ��ַ
AJMP MAIN     							//���Զ���ת��������
ORG 0003H	  							//���ж�0��ڵ�ַ
AJMP KEY_0     							//������ת�����ж�0�ӳ���
ORG 0100H     							//�������ַ����
								/************************
									������
								************************/
MAIN:	   	  
ACALL INIT  							//��ʼ��
M_LOOP:
MOV IE, #00H							//�ر������ж�
ACALL READ_T_DO
ACALL DRIVE_LED_C
MOV IE, #81H							//���������ж�0
MOV PCON, #02H							//�������ģʽ
NOP
NOP
JB LSE,$
AJMP M_LOOP
								/************************
									��ʼ���ӳ���
								************************/
INIT:
MOV SP,#7FH								//��ջָ������
CLR LSE									//�����²�����ģʽ��־
MOV IAP_ADDRH, #00H						//E2PROM��IAP������ַ��λ
MOV IAP_ADDRL, #00H						//E2PROM��IAP������ַ��λ
ACALL R_E2PROM							//װ��E2PROM���ϴ����õ��²���������A
MOV TPDF_COPY,A
SETB P3.2								//���̳�ʼ��
ACALL KCLR
SETB TCON.0								//�������ж�0���½��ز����ж�
MOV IE, #00H							//�ر������ж�
ACALL RS_18B20							//18B20��ʼ��
MOV A, #0CCH							//����ROM(ROMָ��)
ACALL W_18B20_BYTE
MOV A, #4EH								//д�ݴ���(����ָ��)
ACALL W_18B20_BYTE
MOV A, #55H								//���±�����
ACALL W_18B20_BYTE
MOV A, #0F5H							//���±�����
ACALL W_18B20_BYTE
MOV A, #1FH								//����9λ����
ACALL W_18B20_BYTE
ACALL RS_18B20							//18B20��ʼ��
MOV A, #0CCH							//����ROM(ROMָ��)
ACALL W_18B20_BYTE
MOV A, #48H								//�����ݴ���(����ָ��)
ACALL W_18B20_BYTE
MOV WKTCL, #0FFH						//������绽��ʱ�Ӽ����Ͱ�λ
MOV WKTCH, #9FH							//������绽��ʱ�Ӽ�������λ�����򿪵��绽��ʱ��
RET
								/*************************
									�ж��²ִ������
								*************************/
READ_T_DO:
MOV IE, #00H							//�رռ��̵��ⲿ�ж�
ACALL RS_18B20
MOV A, #0CCH							//����ROM
ACALL W_18B20_BYTE
MOV A, #44H								//�����¶�ת��
ACALL W_18B20_BYTE
ACALL DELAY1000MS
ACALL RS_18B20
ACALL MATCH_ROM1						//ƥ��ROM1
MOV A, #0BEH							//���ݴ���
ACALL W_18B20_BYTE
ACALL R_18B20_BYTE
MOV TPT1_L,A
ACALL R_18B20_BYTE
MOV TPT1_H,A
ACALL RS_18B20
ACALL MATCH_ROM2						//ƥ��ROM2
MOV A, #0BEH							//���ݴ���
ACALL W_18B20_BYTE
ACALL R_18B20_BYTE
MOV TPT2_L,A
ACALL R_18B20_BYTE
MOV TPT2_H,A
ACALL CCLAT
MOV A,TPDF_COPY
CJNE A,TPDF_C,J_DO
J_DO:
JC DO
DEC A
DEC A
CJNE A,TPDF_C,J_UNDO
J_UNDO:
JNC UNDO
MOV IE, #81H							//�²����²���֮�䣬�޶������أ����¿��������ж�
RET
DO:
SETB EXECT								//�²�����²����ޣ�����
MOV IE, #81H							//���������ж�
RET
UNDO:
CLR EXECT								//�²�����²����ޣ�ֹͣ����
MOV IE, #81H							//���������ж�
RET
CCLAT:									//�¶ȼ���ת������λBCD�룺TPDF_C_H��TPDF_C_L��
MOV A,TPT1_L
ACALL CCLAT_MOV_R
MOV TPT1_L,A
MOV A,TPT1_H
ACALL CCLAT_MOV_L
MOV TPT1_H,A
ORL A,TPT1_L
MOV TEMP1,A
MOV A,TPT2_L
ACALL CCLAT_MOV_R
MOV TPT2_L,A
MOV A,TPT2_H
ACALL CCLAT_MOV_L
MOV TPT2_H,A
ORL A,TPT2_L
MOV TEMP2,A
SUBB A,TEMP1							//Ӱ�������²���������ɵ����Ե���
RLC A
JC CCLAT_N
CLR CCLATNF
RRC A
MOV TPDF_C,A
MOV B, #64H
DIV AB
MOV A,B
MOV B, #0AH
DIV AB
MOV TPDF_C_H,A
MOV TPDF_C_L,B
RET
CCLAT_N:
SETB CCLATNF
CPL A
RRC A
ANL A, #7FH
INC A
MOV TPDF_C,A
MOV B, #64H
DIV AB
MOV A,B
MOV B, #0AH
DIV AB
MOV TPDF_C_H,A
MOV TPDF_C_L,B
RET
CCLAT_MOV_R:
ANL A, #0F0H
RR A
RR A
RR A
RR A
RET
CCLAT_MOV_L:
ANL A, #0FH
RL A
RL A
RL A
RL A
RET
								/*************************
								���ݼ����²���������
								*************************/
DRIVE_LED_C:
JB CCLATNF,DRV_N						//�����²�Ϊ����ת
MOV LEDN1, #0FFH						//��һ������ܲ���(�����²�Ϊ��ʱ)
MOV DPTR,#LEDNUM
MOV A,TPDF_C_H
MOVC A,@A+DPTR
MOV LEDN2,A
MOV A,TPDF_C_L
MOVC A,@A+DPTR
MOV LEDN3,A
ACALL W_Latch
RET
DRV_N:
MOV LEDN1, #7FH						//��һ���������ʾ����
MOV DPTR,#LEDNUM
MOV A,TPDF_C_H
MOVC A,@A+DPTR
MOV LEDN2,A
MOV A,TPDF_C_L
MOVC A,@A+DPTR
MOV LEDN3,A
ACALL W_Latch
RET
								/*************************
								���ݼ��̰��������������
								*************************/
DRIVE_LED_KEY:							//��0�Ű���(���ü�)���������ʾ
JNB LSE,USELESS
MOV LEDN1, #57H						//��һ���������ʾ���÷���
ACALL CCLAT_TPDF						//ת�������²�ΪBCD
MOV DPTR,#LEDNUM
MOV A,TPDF_COPY_H
MOVC A,@A+DPTR
MOV LEDN2,A
MOV A,TPDF_COPY_L
MOVC A,@A+DPTR
MOV LEDN3,A
ACALL W_Latch							//д��������
RET
USELESS:
ACALL DRIVE_LED_C						//�����������ʾ�����²�
RET
CCLAT_TPDF:								//תTPDF_COPYΪBCD��������TPDF_COPY_L,TPDF_COPY_H
MOV A, TPDF_COPY
MOV B, #64H
DIV AB
MOV A,B
MOV B, #0AH
DIV AB
MOV TPDF_COPY_H,A
MOV TPDF_COPY_L,B
RET
				/*д������(3Byte)*/
W_Latch:								//��LEDN1,LEDN2,LEDN3����˳���ɸ�λ����λ����д������������
CLR OE
CLR SCK
CLR LCK
MOV ACC,LEDN3
MOV W_LAT,#08H
ACALL W_L_LOOP
MOV ACC,LEDN2
MOV W_LAT,#08H
ACALL W_L_LOOP
MOV ACC,LEDN1
MOV W_LAT,#08H
ACALL W_L_LOOP
SETB SCK
CLR SCK
RET
W_L_LOOP:
RLC A
MOV SDI,C
SETB LCK
CLR LCK
DJNZ W_LAT,W_L_LOOP
RET
				/*��������ݱ�*/
LEDNUM:
DB 82H,0FAH,46H,52H,3AH,13H,03H,0DAH,02H,12H,57H,0AH,22H,7FH
//  0,  1,   2,  3,  4,  5, 6,  7,  8,  9, ����,����,ˮ��,����
								/*************************
									DS18B20
								*************************/
RS_18B20:		/*18B20��λʱ��*/				
ACALL DELAY600US
SETB DQ
NOP
NOP
CLR DQ
ACALL DELAY600US
SETB DQ
ACALL DELAY80US
JB DQ, RS_18B20
ACALL DELAY600US
RET
W_18B20_BYTE:	/*д18B20һ���ֽ�*/		
SETB DQ
MOV R5, #08H
W_18B20_BIT:
RRC A
CLR DQ
ACALL DELAY2US
MOV DQ, C
ACALL DELAY25US
SETB DQ
ACALL DELAY60US
DJNZ R5, W_18B20_BIT
RET
R_18B20_BYTE:	/*��18B20һ���ֽ�*/		
SETB DQ
MOV R5, #08H
R_18B20_BIT:
CLR DQ
ACALL DELAY2US
SETB DQ
ACALL DELAY10US
MOV C, DQ
ACALL DELAY60US
RRC A
DJNZ R5, R_18B20_BIT
RET
				/*18B20ROMһ��λд��C*/
SEARCH_LOOP:							//����һд
ACALL R_18B20_BIT
MOV ROMR1,C
ACALL R_18B20_BIT
MOV ROMR2,C
JG_ROMR:
JNB ROMR1,JG_0
JB ROMR1,JG_1
JG_0:
JNB ROMR2,S_R_00
JB ROMR2,S_R_01
JG_1:
JNB ROMR2,S_R_10
JB ROMR2,S_R_11
S_R_01:									//����Ϊ01���������ROM��һλ��Ϊ0
CLR C
ACALL W_18B20_BIT
RET
S_R_10:									//����Ϊ10���������ROM��һλ��Ϊ1
SETB C
ACALL W_18B20_BIT
RET
S_R_11:									//����Ϊ11�����û��ROM��Ӧ
MOV IAP_CONTR, #20H						//���������λ
S_R_00:									//����Ϊ00�����ROM�ڴ�λ���ݳ�ͻ
MOV ROMJ,ROMPTR
JB ROMJE,S_R_00_1
SETB ROMJF
CLR C
ACALL W_18B20_BIT
RET
S_R_00_1:
CLR ROMJE
CLR ROMJF
SETB C
ACALL W_18B20_BIT
RET
				/*18B20ROMд��RAMѭ��*/
S_W_LOOP:								//ѭ��д��64λROM��ROMPTRָ����ַ
ACALL SEARCH_LOOP
RRC A
DJNZ R5,S_W_LOOP
MOV R5, #08H
MOV R1,ROMPTR							//�˴����⣬R3����ͨ����(ԭ���Ĵ������Ѱַ����ʹ��R0,R1)
MOV @R1,A			
INC ROMPTR
DJNZ R4,S_W_LOOP
RET
				/*18B20ROM������д��RAM������*/
SEARCH_ROM:
MOV ROMPTR, #40H
ACALL RS_18B20							//18B20��λ
MOV A, #0F0H							//д������ROMָ��
ACALL W_18B20_BYTE
SETB DQ
MOV R4, #08H
ACALL S_W_LOOP							//д��ROM1
MOV C,ROMJF
MOV ROMJE,C
ACALL RS_18B20							//18B20��λ
MOV A, #0F0H							//�ڶ���д������ROMָ��
ACALL W_18B20_BYTE
SETB DQ
MOV R4, #08H
ACALL S_W_LOOP							//д��ROM2
RET
				/*18B20ROMƥ��������*/
MATCH_ROM1:								//ƥ��ROM1
ACALL RS_18B20							//��λ
MOV A, #55H								//ƥ��ROM
ACALL W_18B20_BYTE
SETB DQ
MOV ROMPTR, #40H						//ROM1�׵�ַ����ָ��
MOV R4, #08H
ACALL M_R_LOOP
RET
MATCH_ROM2:								//ƥ��ROM2
ACALL RS_18B20							//��λ
MOV A, #55H								//ƥ��ROM
ACALL W_18B20_BYTE
SETB DQ
MOV ROMPTR, #48H						//ROM2�׵�ַ����ָ��
MOV R4, #08H
ACALL M_R_LOOP
RET
M_R_LOOP:								//ƥ������д��ѭ��
MOV R1,ROMPTR
MOV A,@R1
ACALL W_18B20_BYTE
INC ROMPTR
DJNZ R4,M_R_LOOP
RET
								/************************
									�����ж�
								************************/
KEY_0:				/*0�Ű����ж�(�趨)*/
CLR K0
SETB K1
SETB K2
NOP
NOP
JB P3.2,KEY_1
ACALL DELAY10MS						//���ȥ����������ʱ�ӳ�����ʱ��Լ10ms
JNB P3.2,KEY0		    			//�ж�P3.2�͵�ƽ��ת��0��ȷʵ���£�
ACALL KCLR
RETI
KEY0:				
ACALL DELAY10MS						//����ȥ����������ʱ�ӳ�����ʱ��Լ10ms
JB P3.2,KEY00							//�ж�P3.2�ߵ�ƽ��ת��ȷʵ���֣�
AJMP KEY0		    				//�ж�P3.2�͵�ƽ��ת��ѭ��������ָߵ�ƽ��  
KEY00:
CPL LSE
ACALL DRIVE_LED_KEY
ACALL KCLR
RETI
KEY_1:	           	/*1�Ű����ж�(���ּ�)*/ 
SETB K0
CLR K1
SETB K2
NOP
NOP
JB P3.2,KEY_2
ACALL DELAY10MS						//���ȥ����������ʱ�ӳ�����ʱ��Լ10ms
JNB P3.2,KEY1		    			//�ж�P3.2�͵�ƽ��ת��1��ȷʵ���£�
ACALL KCLR
RETI
KEY1:
ACALL DELAY10MS						//����ȥ����������ʱ�ӳ�����ʱ��Լ10ms
JB P3.2,KEY10							//�ж�P3.2�ߵ�ƽ��ת��ȷʵ���֣�
AJMP KEY1							//�ж�P3.2�͵�ƽ��ת��ѭ��������ָߵ�ƽ��  
KEY10:
JB LSE,KEY100
ACALL KCLR
RETI
KEY100:
MOV A,TPDF_COPY
CJNE A, #63H,JUDGE_T						//��99���²�Ƚ�
ACALL KCLR
RETI
KEY_2:	           	/*2�Ű����ж�(���ּ�)*/ 
SETB K1
CLR K2
SETB K0
NOP
NOP
ACALL DELAY10MS						//���ȥ����������ʱ�ӳ�����ʱ��Լ10ms
JNB P3.2,KEY2		    			//�ж�P3.2�͵�ƽ��ת��2��ȷʵ���£�
ACALL KCLR
RETI
KEY2:	          	/*2�Ű����ж�(���ּ�)*/     					
ACALL DELAY10MS						//����ȥ����������ʱ�ӳ�����ʱ��Լ10ms
JB P3.2,KEY20							//�ж�P3.2�ߵ�ƽ��ת��ȷʵ���֣�
AJMP KEY2		    				//�ж�P3.2�͵�ƽ��ת��ѭ��������ָߵ�ƽ��  
KEY20:
JB LSE,KEY200
ACALL KCLR
RETI
KEY200:
MOV A,TPDF_COPY
CJNE A, #03H,JUDGE_B						//��3���²�Ƚ�
ACALL KCLR
RETI
JUDGE_T:
JNC JUDGE_99
INC A
AJMP COPY
JUDGE_B:
JC JUDGE_03
DEC A
AJMP COPY
JUDGE_99:
MOV A,#63H
AJMP COPY
JUDGE_03:
MOV A,#03H
COPY:
ACALL E_E2PROM
MOV TPDF_COPY,A
ACALL W_E2PROM
MOV A,TPDF_COPY
ACALL DRIVE_LED_KEY
ACALL KCLR
RETI
KCLR:
CLR K0
CLR K1
CLR K2
RET
								/*************************
								��ʱ��������
								*************************/
DELAY2US:			;@11.0592MHz
	NOP
	PUSH 30H
	MOV 30H,#1
NEXT2US:
	DJNZ 30H,NEXT2US
	POP 30H
	RET
DELAY10US:			;@11.0592MHz
	PUSH 30H
	MOV 30H,#19
NEXT10US:
	DJNZ 30H,NEXT10US
	POP 30H
	RET
DELAY25US:			;@11.0592MHz
	PUSH 30H
	MOV 30H,#52
NEXT25US:
	DJNZ 30H,NEXT25US
	POP 30H
	RET
DELAY60US:			;@11.0592MHz
	NOP
	NOP
	NOP
	PUSH 30H
	MOV 30H,#129
NEXT60US:
	DJNZ 30H,NEXT60US
	POP 30H
	RET
DELAY80US:			;@11.0592MHz
	NOP
	NOP
	NOP
	NOP
	PUSH 30H
	MOV 30H,#173
NEXT80US:
	DJNZ 30H,NEXT80US
	POP 30H
	RET
DELAY600US:			;@11.0592MHz
	NOP
	NOP
	PUSH 30H
	PUSH 31H
	MOV 30H,#6
	MOV 31H,#36
NEXT600US:
	DJNZ 31H,NEXT600US
	DJNZ 30H,NEXT600US
	POP 31H
	POP 30H
	RET
DELAY10MS:			;@11.0592MHz
	NOP
	NOP
	NOP
	PUSH 30H
	PUSH 31H
	MOV 30H,#87
	MOV 31H,#10
NEXT10MS:
	DJNZ 31H,NEXT10MS
	DJNZ 30H,NEXT10MS
	POP 31H
	POP 30H
	RET

DELAY800MS:			;@11.0592MHz
	NOP
	NOP
	NOP
	PUSH 30H
	PUSH 31H
	PUSH 32H
	MOV 30H,#27
	MOV 31H,#229
	MOV 32H,#249
NEXT800MS:
	DJNZ 32H,NEXT800MS
	DJNZ 31H,NEXT800MS
	DJNZ 30H,NEXT800MS
	POP 32H
	POP 31H
	POP 30H
	RET
DELAY1000MS:			;@11.0592MHz
	NOP
	NOP
	NOP
	PUSH 30H
	PUSH 31H
	PUSH 32H
	MOV 30H,#34
	MOV 31H,#159
	MOV 32H,#56
NEXT1000MS:
	DJNZ 32H,NEXT1000MS
	DJNZ 31H,NEXT1000MS
	DJNZ 30H,NEXT1000MS
	POP 32H
	POP 31H
	POP 30H
	RET
								/************************
									EEPROM��д(1BYTE)
								************************/
R_E2PROM:								//��ȡE2PROM���ݵ�A
MOV IAP_ADDRH, #00H
MOV IAP_ADDRL, #00H
MOV IAP_CONTR, #10000011B
MOV IAP_CMD, #01H
MOV IAP_TRIG, #5AH
MOV IAP_TRIG, #0A5H
NOP
MOV A,IAP_DATA
RET
E_E2PROM:								//����E2PROMһ����������
MOV IAP_ADDRH, #00H
MOV IAP_ADDRL, #00H
MOV IAP_CONTR, #10000011B
MOV IAP_CMD, #03H
MOV IAP_TRIG, #5AH
MOV IAP_TRIG, #0A5H
NOP
RET
W_E2PROM:								//д��A�����ݵ�E2PROM
MOV IAP_DATA, A
MOV IAP_ADDRH, #00H
MOV IAP_ADDRL, #00H
MOV IAP_CONTR, #10000011B
MOV IAP_CMD, #02H
MOV IAP_TRIG, #5AH
MOV IAP_TRIG, #0A5H
NOP
RET
END
