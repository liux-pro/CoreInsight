#ifndef __PIC_H
#define __PIC_H 

//16λBMP 40X40 ͼ��ȡģ����
//Image2LCDȡģѡ������
//ˮƽɨ��
//16λ
//40X40
//������ͼ��ͷ����
//��������
//�Զ�����
//��λ��ǰ
unsigned char code gImage_1[3200] = { /* 0X00,0X10,0X28,0X00,0X28,0X00,0X01,0X1B, */
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0X7D,0XF7,0XAF,0XDB,0XFF,0XF7,0XFF,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0X39,0XEE,0X00,0XD0,0XB3,0XE4,0XFF,0XFF,
0XDE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0XAB,0XE2,0X00,0XD8,0X88,0XD9,
0XFF,0XFF,0XDF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0X1C,0XEF,0XDF,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0X9A,0XEE,0X00,0XE0,0X00,0XE0,
0X05,0XD9,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X63,0XC8,0XFF,0XFF,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0XFF,0XF7,0X00,0XD8,0X02,0XE0,
0X00,0XE0,0X4E,0XE3,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0XDF,0XF7,0X00,0XD0,0XD8,0XED,
0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0X7D,0XF7,0X00,0XD8,0X02,0XE0,
0X02,0XE0,0X00,0XD8,0XDE,0XF7,0XDF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0X72,0XE4,0X00,0XD8,0X8F,0XE3,
0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0XF4,0XEC,0X00,0XE0,0X02,0XE0,
0X02,0XE0,0X00,0XE0,0X92,0XE4,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X02,0XD8,0X00,0XE0,0XEC,0XDA,
0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X84,0XD8,0X01,0XE0,0X02,0XE0,
0X02,0XE0,0X01,0XD8,0XAC,0XE2,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X32,0XE4,0X00,0XE0,0X01,0XE0,0X6E,0XE3,
0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0XD3,0XE4,0X00,0XE0,0X02,0XE0,0X02,0XE0,
0X02,0XE0,0X01,0XE0,0X2A,0XE2,0XFF,0XFF,0XBE,0XF7,0XDF,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0XFF,0XF7,0X00,0XD0,0X02,0XE0,0X00,0XD8,0X93,0XE4,
0XFF,0XF7,0XBE,0XF7,0XFF,0XF7,0X9E,0XF7,0X00,0XD8,0X02,0XE0,0X02,0XE0,0X02,0XE0,
0X02,0XE0,0X01,0XE0,0XAC,0XE2,0XFF,0XFF,0X7D,0XF7,0XDB,0XEE,0XFF,0XFF,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0XAC,0XE2,0X01,0XE0,0X02,0XE0,0X00,0XD8,0X59,0XEE,
0XFF,0XF7,0XBE,0XF7,0XFF,0XF7,0X63,0XD8,0X01,0XE0,0X02,0XE0,0X02,0XE0,0X02,0XE0,
0X02,0XE0,0X00,0XE0,0XF0,0XE3,0XFF,0XFF,0XFF,0XFF,0XE5,0XD0,0X52,0XE4,0XFF,0XFF,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XDF,0XF7,0X9E,0XF7,0X00,0XD8,0X02,0XE0,0X02,0XE0,0X00,0XD8,0XFF,0XF7,
0XDF,0XF7,0XFF,0XFF,0XE9,0XD9,0X00,0XE0,0X02,0XE0,0X02,0XE0,0X02,0XD8,0X02,0XE0,
0X02,0XE0,0X00,0XE0,0XF7,0XE5,0XFF,0XF7,0XFF,0XF7,0XF4,0XE4,0X00,0XD8,0X8B,0XDA,
0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XFF,0XFF,0XD0,0XE3,0X00,0XE0,0X02,0XE0,0X02,0XE0,0X01,0XD0,0XFF,0XFF,
0XFF,0XF7,0XD4,0XE4,0X00,0XD8,0X02,0XE0,0X02,0XE0,0X42,0XD8,0X42,0XE2,0X02,0XE0,
0X02,0XE0,0X00,0XD0,0XFF,0XFF,0XDE,0XF7,0XFF,0XF7,0X99,0XEE,0X00,0XD8,0X00,0XE0,
0XCC,0XDA,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XFF,0XFF,0X67,0XD9,0X01,0XE0,0X02,0XE0,0X02,0XE0,0X43,0XD8,0XFF,0XFF,
0XFF,0XF7,0X00,0XD0,0X02,0XE0,0X02,0XE0,0X02,0XD8,0X61,0XF5,0X01,0XE2,0X02,0XE0,
0X01,0XE0,0X26,0XD9,0XFF,0XF7,0XBE,0XF7,0XFF,0XF7,0X18,0XEE,0X00,0XE0,0X02,0XE0,
0X00,0XE0,0X96,0XED,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XFF,0XFF,0X43,0XD8,0X01,0XE0,0X02,0XE0,0X02,0XE0,0X00,0XD0,0XFF,0XFF,
0X97,0XED,0X00,0XE0,0X02,0XE0,0X02,0XE0,0X62,0XE2,0X60,0XFE,0XE1,0XEA,0X02,0XD8,
0X01,0XE0,0X8E,0XE3,0XFF,0XFF,0XBE,0XF7,0XFF,0XFF,0X2E,0XE3,0X01,0XE0,0X02,0XE0,
0X02,0XE0,0X01,0XD0,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XFF,0XFF,0X02,0XD8,0X02,0XE0,0X02,0XD9,0X02,0XD8,0X00,0XE0,0XF8,0XED,
0X76,0XED,0X00,0XE0,0X02,0XE0,0X02,0XD8,0XC1,0XFD,0XC0,0XFD,0XE1,0XF4,0X02,0XD8,
0X00,0XE0,0X92,0XE4,0XFF,0XF7,0XFF,0XFF,0X3C,0XF7,0X00,0XD8,0X02,0XE0,0X02,0XE0,
0X02,0XE0,0X00,0XE0,0XF7,0XED,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,
0XBE,0XF7,0XFF,0XFF,0X23,0XD8,0X02,0XE0,0X02,0XE1,0X42,0XEB,0X02,0XE0,0X01,0XD8,
0XFB,0XEE,0X00,0XE0,0X02,0XE0,0XC2,0XE1,0X00,0XFE,0X80,0XFD,0X20,0XFE,0X22,0XD8,
0X01,0XD8,0X8B,0XE2,0XFF,0XFF,0X18,0XEE,0X00,0XD8,0X02,0XE0,0X02,0XE0,0X02,0XE0,
0X02,0XE0,0X00,0XE0,0XD0,0XE3,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0XCC,0XD2,
0XFF,0XFF,0XFF,0XFF,0X06,0XD9,0X01,0XE0,0X02,0XD8,0XC0,0XFE,0XA2,0XD8,0X02,0XE0,
0X23,0XD8,0X63,0XE0,0X02,0XD8,0X81,0XEB,0XC0,0XFD,0X80,0XFD,0XE0,0XFD,0XE2,0XE2,
0X02,0XE0,0X00,0XD8,0XA7,0XD9,0X00,0XD8,0X02,0XE0,0X02,0XE0,0XE2,0XD8,0X02,0XE0,
0X02,0XE0,0X01,0XE0,0X0D,0XE3,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0X9E,0XF7,0X00,0XD0,
0XFF,0XFF,0XFF,0XFF,0XCC,0XE2,0X01,0XE0,0X02,0XD8,0X00,0XFE,0XC0,0XF5,0X02,0XD8,
0X02,0XE0,0X02,0XE0,0X02,0XD8,0X01,0XEC,0XC0,0XFD,0X80,0XFD,0XA0,0XFD,0XA0,0XFD,
0X02,0XD8,0X02,0XE0,0X01,0XE0,0X02,0XE0,0X02,0XD8,0X42,0XD9,0X02,0XEB,0X02,0XE0,
0X02,0XE0,0X00,0XE0,0XD0,0XE3,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0XB3,0XE4,0X00,0XE0,
0X14,0XED,0XFF,0XFF,0X76,0XED,0X00,0XD8,0X02,0XD8,0X61,0XF5,0XC0,0XFD,0X81,0XF5,
0X62,0XD8,0X02,0XD8,0X02,0XD8,0X41,0XEB,0XE0,0XFD,0X80,0XF5,0X80,0XFD,0X20,0XFE,
0X62,0XE1,0X02,0XE0,0X02,0XE0,0X02,0XD8,0XE2,0XD8,0X80,0XFE,0X82,0XE1,0X02,0XE0,
0X02,0XE0,0X00,0XD8,0X18,0XEE,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X4E,0XE3,0X00,0XE0,
0X22,0XD8,0XFF,0XF7,0XFF,0XFF,0X01,0XD0,0X02,0XE0,0X81,0XEC,0XA0,0XFD,0XA0,0XFD,
0X20,0XFE,0XA1,0XEB,0X02,0XD9,0XA2,0XD0,0XE0,0XFD,0XAE,0XF6,0X49,0XF6,0XA0,0XFD,
0X01,0XEC,0X02,0XE0,0X02,0XD8,0XA2,0XE2,0X20,0XFE,0X40,0XFE,0XA2,0XD8,0X02,0XE0,
0X02,0XE0,0X02,0XD0,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X2D,0XE3,0X01,0XE0,
0X01,0XE0,0X25,0XD9,0XFF,0XF7,0XB6,0XED,0X00,0XD8,0X61,0XEA,0X00,0XFE,0X80,0XFD,
0X80,0XFD,0XC0,0XFD,0X00,0XFE,0XE0,0XFD,0X60,0XF5,0X4A,0XF6,0XDD,0XF7,0X60,0XFD,
0X80,0XF5,0XA1,0XE2,0X81,0XF5,0XE0,0XFD,0X80,0XFD,0X21,0XFE,0X02,0XD8,0X02,0XE0,
0X00,0XD8,0X96,0XE5,0XFF,0XF7,0XFF,0XF7,0XDF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,0X72,0XE4,0X00,0XE0,
0X02,0XE0,0X01,0XE0,0X00,0XD8,0X51,0XE4,0XC9,0XD9,0X01,0XD8,0XE1,0XFD,0XA0,0XFD,
0X80,0XFD,0X4A,0XF6,0XC3,0XF5,0X60,0XFD,0X60,0XFD,0X8D,0XF6,0XFF,0XFF,0X40,0XF5,
0X60,0XFD,0XE0,0XF5,0XA0,0XFD,0X80,0XFD,0XA0,0XFD,0X01,0XF5,0X02,0XD8,0X00,0XE0,
0X8B,0XDA,0XFF,0XFF,0XFF,0XFF,0X15,0XED,0X18,0XEE,0XDF,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0X3C,0XF7,0X00,0XD8,
0X02,0XE0,0X02,0XE0,0X02,0XD8,0X01,0XE0,0X01,0XE0,0X02,0XE0,0X02,0XE1,0X40,0XFE,
0XA0,0XFD,0X40,0XF5,0X35,0XF7,0X57,0XF7,0X00,0XF5,0X58,0XF7,0X9A,0XFF,0X00,0XF5,
0XAF,0XF6,0X28,0XF6,0X80,0XFD,0X80,0XFD,0X20,0XFE,0X42,0XE2,0X01,0XE0,0X6A,0XDA,
0XFF,0XFF,0XF8,0XED,0XC4,0XD8,0X00,0XD0,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X88,0XD9,
0X01,0XE0,0X02,0XD8,0X42,0XEC,0X42,0XE2,0X02,0XD8,0X02,0XD8,0X02,0XD8,0X82,0XD8,
0X60,0XFD,0X80,0XFD,0X40,0XF5,0X36,0XF7,0XDC,0XF7,0XFF,0XFF,0X57,0XF7,0X79,0XFF,
0XFF,0XFF,0X40,0XF5,0X80,0XFD,0X00,0XFE,0X61,0XF4,0X02,0XD8,0X02,0XD8,0XC9,0XE1,
0X01,0XD8,0X00,0XE0,0X00,0XD8,0XDB,0XEE,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XF7,0X7D,0XF7,
0X00,0XD8,0X02,0XE0,0X62,0XD8,0XA0,0XFE,0X20,0XFE,0XE0,0XF4,0XE1,0XEB,0X81,0XEB,
0XA0,0XF4,0XA0,0XFD,0X80,0XFD,0X40,0XF5,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X08,0XF6,0X80,0XFD,0XC0,0XFD,0X42,0XE3,0X02,0XD0,0X02,0XD8,0X42,0XD8,0X62,0XE1,
0X02,0XD8,0X00,0XD8,0XF4,0XEC,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XF7,
0X76,0XED,0X00,0XD8,0X02,0XE0,0XC2,0XE1,0X40,0XFE,0XC0,0XFD,0XC0,0XFD,0XE2,0XF5,
0XA0,0XF5,0X60,0XFD,0X40,0XFD,0XC5,0XF5,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X36,0XF7,
0X20,0XF5,0X80,0XFD,0X80,0XF5,0XC0,0XFD,0XE0,0XFD,0X40,0XFE,0XA0,0XFE,0XA1,0XE1,
0X00,0XD8,0X35,0XED,0XFF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XFF,
0XFF,0XFF,0X59,0XF6,0X01,0XE0,0X02,0XE0,0X82,0XE1,0X20,0XFE,0XE0,0XFD,0XA0,0XF5,
0XD0,0XF6,0XDD,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X35,0XF7,
0X4A,0XF6,0XA2,0XF5,0XA0,0XFD,0XE0,0XFD,0X40,0XFE,0X01,0XEC,0X01,0XE0,0X65,0XE0,
0X3C,0XF7,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFA,0XEE,
0X4F,0XBC,0X44,0X92,0X61,0X91,0X42,0XD0,0X02,0XE8,0X02,0XE0,0X41,0XEB,0XE0,0XFD,
0X20,0XF6,0XA0,0XF5,0X02,0XF6,0XAA,0XF6,0XCE,0XFE,0XEE,0XFE,0XAB,0XFE,0X44,0XF6,
0XE0,0XFD,0X40,0XFE,0X41,0XF5,0X01,0XEB,0X42,0XE0,0X02,0XE0,0X81,0XA8,0X4E,0XB4,
0X99,0XDE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X3C,0XEF,0X6F,0XBC,0XC3,0X89,0XE0,0X80,
0X40,0X89,0X81,0X91,0XA2,0X91,0XC2,0X89,0X42,0X99,0X82,0XC0,0X02,0XE0,0X02,0XE0,
0XC2,0XE0,0X41,0XEA,0X00,0XEB,0X80,0XF3,0X80,0XEB,0X80,0XF3,0X20,0XEB,0X61,0XEA,
0X81,0XE9,0X02,0XE8,0X02,0XD8,0X02,0XC8,0X02,0XA9,0XA2,0X89,0XA2,0X89,0X61,0X89,
0X00,0X89,0X40,0X89,0XED,0XB3,0X98,0XDE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,
0XFF,0XFF,0X17,0XDE,0X4F,0XBC,0XA3,0X91,0XA0,0X80,0X20,0X89,0X81,0X91,0XA2,0X91,
0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XC2,0X89,0XC2,0X89,0X21,0X99,
0X03,0XB1,0X62,0XC0,0X02,0XC8,0X02,0XC8,0X02,0XD0,0X02,0XC8,0X22,0XC0,0X01,0XB8,
0XA1,0XA8,0X42,0X99,0XA2,0X89,0XC2,0X89,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,
0XA2,0X91,0X82,0X91,0X40,0X89,0XE0,0X88,0X41,0X89,0XCC,0XBB,0XD7,0XD5,0XFF,0XFF,
0X08,0XBB,0X60,0XE4,0X00,0XED,0X01,0XF5,0X63,0XCB,0XA3,0X99,0X81,0X89,0XA2,0X91,
0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0X00,0X89,0XC7,0X9A,
0XD4,0XCD,0X40,0X81,0XA2,0X89,0XC2,0X89,0XC2,0X89,0XC2,0X89,0X60,0X81,0XF0,0XBC,
0X49,0XA3,0X00,0X81,0XA1,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,
0XA2,0X91,0X82,0X91,0XE4,0XA1,0XE3,0XD3,0X41,0XF5,0XE0,0XEC,0XA0,0XEC,0XCA,0XC3,
0X41,0XF5,0X22,0XC3,0X23,0XC3,0X42,0XC3,0XA1,0XE4,0XE2,0XEC,0X04,0XA2,0X82,0X91,
0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0X61,0X89,0XE0,0X80,0X32,0XCD,0XFF,0XFF,
0X20,0X81,0X82,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,0X61,0X89,0XE8,0XA2,
0XFF,0XFF,0XB5,0XD5,0X00,0X81,0X40,0X89,0XA2,0X91,0XA2,0X91,0XA2,0X91,0XA2,0X91,
0XA2,0X91,0X44,0XAA,0X41,0XF5,0X41,0XD4,0X63,0XC3,0XA3,0XCB,0X02,0XBB,0XC4,0XF5,
0XD2,0XF6,0XC0,0XD3,0X01,0XED,0X02,0XD4,0X21,0XED,0X61,0XDC,0X22,0XED,0XE3,0XA1,
0X82,0X91,0XA2,0X91,0X61,0X89,0XE0,0X80,0XA7,0X9A,0X9D,0XF7,0XFF,0XFF,0X29,0XA3,
0X40,0X89,0XA2,0X91,0X82,0X91,0X82,0X91,0X82,0X91,0XA2,0X91,0XA2,0X91,0X00,0X81,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X4A,0XAB,0XC0,0X80,0X61,0X89,0XA2,0X91,0X81,0X91,
0X24,0XAA,0X61,0XF5,0X02,0XD4,0X41,0XF5,0XA2,0XC3,0X21,0XED,0XA0,0XD3,0X14,0XFF,
0XFF,0XFF,0X6D,0XC4,0X00,0XDC,0XE0,0XEC,0X41,0XDC,0X62,0XC3,0X60,0XF5,0X22,0XC3,
0XE0,0X80,0XC0,0X80,0X08,0XA3,0X99,0XE6,0XFF,0XFF,0XFF,0XFF,0XDA,0XE6,0XC0,0X80,
0X61,0X89,0X62,0X91,0XA2,0X91,0XC2,0X99,0XA3,0X99,0X83,0X91,0X62,0X89,0XE0,0X88,
0X58,0XDE,0XFF,0XFF,0XDF,0XF7,0XFF,0XFF,0X3C,0XEF,0X8B,0XAB,0XE0,0X80,0X20,0X91,
0X63,0XCB,0X61,0XF5,0XC3,0XCB,0X81,0XE4,0X40,0XF5,0XA0,0XD3,0X6E,0XC4,0XFF,0XFF,
0XBE,0XF7,0XFF,0XFF,0X59,0XE6,0X89,0XBB,0X42,0XC3,0XE0,0XD3,0X85,0XDC,0XEC,0XBB,
0X53,0XCD,0XDE,0XFF,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XFF,0XFF,0X2D,0XB4,0X61,0X91,
0XA3,0XCB,0X22,0XED,0X21,0XF5,0XE1,0XEC,0X21,0XED,0X81,0XFD,0X22,0XDC,0XA2,0X99,
0X4E,0XBC,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0X37,0XDE,
0X06,0XB3,0XE0,0XC2,0X60,0XCB,0X80,0XBA,0X85,0XAA,0XF7,0XDD,0XFF,0XFF,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XDF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0X0E,0XC4,0X60,0XE4,
0X82,0XE4,0XA2,0XCB,0XC1,0XEC,0XE1,0XEC,0XE3,0XD3,0XA5,0X99,0X41,0XF5,0X82,0XCB,
0X8A,0XBB,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,
0XFF,0XFF,0X7E,0XF7,0XDB,0XE6,0X7D,0XF7,0XFF,0XFF,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XDF,0XFF,0X9A,0XDE,0X40,0XF5,
0XC2,0XA1,0XA0,0XFD,0XE0,0XEC,0XA1,0XE4,0X40,0XF5,0X20,0XF5,0X80,0XE4,0XA0,0XA9,
0X11,0XD5,0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XDF,0XF7,0XDF,0XF7,0XDF,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XFF,0XFF,0XDC,0XFF,
0X4E,0XDD,0X09,0XB3,0XA5,0XB2,0X84,0XB2,0XA5,0XAA,0X29,0XBB,0X6F,0XC4,0XDA,0XEE,
0XFF,0XFF,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBF,0XF7,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XFF,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,0XBE,0XF7,
};
#endif