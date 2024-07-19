#include "STC32G.H"
#include "stc.h"
#include "usb.h"
#include "uart.h"
#include "stdio.h"
#include "intrins.h"
#include "STC32G_GPIO.h"
#include "LCD.h"
#include "test code.h"
#include "STC32G_SPI.h"
#include "STC32G_Switch.h"
#include "STC32G_NVIC.h"
#include "STC32G_Clock.h"
#include <string.h>
#include "communicate.h"
#include "STC32G_PWM.h"
#include "STC32G_Timer.h"
/*
IRCƵ�ʱ����� 35.000MHz
*/

void Delay1000ms(void) //@24.000MHz
{
	unsigned long edata i;

	_nop_();
	_nop_();
	i = 5999998UL;
	while (i)
		i--;
}

/****************  SPI��ʼ������ *****************/
void SPI_config1(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Enable = ENABLE;		  // SPI����    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG = DISABLE;		  // Ƭѡλ     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit = SPI_MSB;	  // ��λ����   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // ����ѡ��   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	  // ʱ����λ   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;  // ���ݱ���   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed = SPI_Speed_2;	  // SPI�ٶ�    SPI_Speed_4, SPI_Speed_8, SPI_Speed_16, SPI_Speed_2
	SPI_Init(&SPI_InitStructure);
	// NVIC_SPI_Init(ENABLE,Priority_3);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3

	SPI_SW(SPI_P54_P13_P14_P15); // SPI_P54_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32

	P1_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
	P4_MODE_IO_PU(GPIO_Pin_7);
	P1_PULL_UP_ENABLE(GPIO_Pin_3 | GPIO_Pin_5);
	P1_SPEED_HIGH(GPIO_Pin_3 | GPIO_Pin_5); // ��ƽת���ٶȿ죨���IO�ڷ�ת�ٶȣ�
	{
		/*
			����������������󣬸Ŀ⺯����̫�õ�ԭ����������ĺ����帴�Ƴ�������һ�ġ�
			HSPllClkConfig(MCLKSEL_HIRC, PLL_96M, 2); ϵͳʱ��ѡ��,PLLʱ��ѡ��,ʱ�ӷ�Ƶϵ��
		*/
		MainClockSel(MCLKSEL_HIRC); // ϵͳʱ��ѡ��, MCLKSEL_HIRC/MCLKSEL_XIRC/MCLKSEL_X32K/MCLKSEL_I32K/MCLKSEL_PLL/MCLKSEL_PLL2/MCLKSEL_I48M

		// HIRC ������ʱ��Ϊ35M���ķ�Ƶ��8M��һ�㣬������������Ƶ��12M����35%��������
		USBCLK &= ~PCKI_MSK;
		USBCLK |= PCKI_D4; // PLL����ʱ��4��Ƶ

		PLLClockSel(PLL_96M);	// PLLʱ��ѡ��, PLL_96M/PLL_144M
		PLLEnable(ENABLE);		// PLL��Ƶʹ��, ENABLE/DISABLE
		delay_ms(2);			// �ȴ�PLL��Ƶ
		HSIOClockSel(HSCK_PLL); // ����IOʱ��ѡ��, HSCK_MCLK/HSCK_PLL
		HSClockDiv(2);			// ����IOʱ�ӷ�Ƶϵ��
	}

	HSSPI_Enable();
	// SPI��HSPI����Ƶ�� = HIRC 35M �ķ�Ƶ ���� PLL ������� 96M ����Ƶ 48M ���� HSPI���� SPI�Լ�Ҳ��2��Ƶ ����24M
	// ����stc32g12k128 ������IO�ٶ�ԭ��5v�������33M��3.3v�������20M�������24M����΢���޵ġ�
}

/**
 * ����Ƿ���յ��ض���ISP�̼���������
 */
void checkISP()
{
	// �±������Ż�̫ɵ�������Ż�strlen,ֱ��д8
	if (memcmp("@STCISP#", RxBuffer, 8) == 0)
	{
		usb_write_reg(OUTCSR1, 0);

		USBCON = 0x00;
		USBCLK = 0x00;
		IRC48MCR = 0x00;

		delay_ms(10);
		// ��λ��bootloader
		IAP_CONTR = 0x60;
		while (1)
			;
	}
}

u8 xdata b[1024 * 6] = {0};
void configBlackLightPWM()
{
	PWMx_InitDefine PWMx_InitStructure;

	// PWM1P_3 P6.0
	P6_MODE_IO_PU(GPIO_Pin_0);

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1; // ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = 1000;			   // PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO1P;	   // ���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM1, &PWMx_InitStructure);  // ��ʼ��PWM1

	PWMx_InitStructure.PWM_Period = 1750;		   // ����ʱ��,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;		   // ��������������, 0~255
	PWMx_InitStructure.PWM_MainOutEnable = ENABLE; // �����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;	   // ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);  // ��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

	PWM1_USE_P60P61();
	NVIC_PWM_Init(PWMA, DISABLE, Priority_0);
}

void main(void)
{
	u16 line;
	u32 i, j;
	u16 color;
	BYTE *p_UsbBuffer;
	WTST = 0;  // ���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXFR = 1; // ��չ�Ĵ���(XFR)����ʹ��
	CKCON = 0; // ��߷���XRAM�ٶ�
	P2_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);

	uart_init();
	usb_init();
	EA = 1;

	SPI_config1();

	LCD_Init();			// ��ʼ��LCD
	LCD_Display_Dir(2); // ��Ļ����

	LCD_Clear(BLACK);
	LCD_Set_Window(0, 0, 320, 240);
	LCD_WriteRAM_Prepare();
	SPI_DC = 1;

	configBlackLightPWM();

	while (1)
	{
		if (RxFlag)
		{
			p_UsbBuffer = RxBuffer;

			// ����ͼƬ����ʱ��һ�㶼�Ǵ����ݰ�����ռ��64�ֽڵĻ���
			// С��64�ļ�������������
			if (RxCount < 64)
			{
				checkISP();

				// Ϲ����ĸ�ʽ������31������������������ɫ�����ظ��ĸ���
				// ����@��ͷ������λ������
				if (
					RxCount == 31 &&
					*(RxBuffer + 0) == '@' &&
					*(RxBuffer + 1) == '@' &&
					*(RxBuffer + 2) == '@')
				{
					RxCount = 0;

					switch (*(RxBuffer + 3))
					{
					case CMD_SET_WINDOW:
					{
						LCD_Set_Window(*(u16 *)(RxBuffer + 4), *(u16 *)(RxBuffer + 4 + 2), *(u16 *)(RxBuffer + 4 + 4), *(u16 *)(RxBuffer + 4 + 6));
						LCD_WriteRAM_Prepare(); // ��ʼд��GRAM
						SPI_DC = 1;
						P23 = ~P23;
					}
					break;
					default:
						break;
					}
				}
			}

			for (i = 0; i < RxCount; i++)
			{
				SPDAT = *(p_UsbBuffer++);
				NOP(16);
			}
			uart_recv_done(); // �Խ��յ����ݴ�����ɺ�,һ��Ҫ����һ���������,�Ա�CDC������һ�ʴ�������
		}
	}
}