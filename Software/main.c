#include "STC32G.H"
#include "stc.h"
#include "usb.h"
#include "usb_hid.h"
#include "stdio.h"
#include "intrins.h"
#include "STC32G_GPIO.h"
#include "LCD.h"
#include "test code.h"
#include "STC32G_SPI.h"
#include "STC32G_Switch.h"
#include "STC32G_NVIC.h"
#include "STC32G_Clock.h"

/*
IRCƵ�ʱ����� 35.000MHz
*/

char *USER_STCISPCMD = "@STCISP#"; // �����Զ���λ��ISP�����û��ӿ�����

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

	P1_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7);
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

void main(void)
{
	u16 line;
	u16 i, j;
	WTST = 0;  // ���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXFR = 1; // ��չ�Ĵ���(XFR)����ʹ��
	CKCON = 0; // ��߷���XRAM�ٶ�
	P2_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);

	usb_init();
	EA = 1;

	SPI_config1();

	LCD_Init(); // ��ʼ��LCD

	LCD_Display_Dir(USE_LCM_DIR); // ��Ļ����

	P2_MODE_IO_PU(GPIO_Pin_0);

	while (1)
	{
		for (line = 0; line < 320; line++)
		{
			P20 = !P20;

			LCD_Set_Window(0, 0, 240, 320);
			P21 = !P21;

			LCD_WriteRAM_Prepare(); // ��ʼд��GRAM
			P22 = !P22;

			for (i = 0; i < 320; i++)
			{
				if (i == line)
				{
					for (j = 0; j < 240 / 8; j++)
					{
						LCD_WriteRAM_Inline(BLACK);
						LCD_WriteRAM_Inline(BLACK);
						LCD_WriteRAM_Inline(BLACK);
						LCD_WriteRAM_Inline(BLACK);
						LCD_WriteRAM_Inline(BLACK);
						LCD_WriteRAM_Inline(BLACK);
						LCD_WriteRAM_Inline(BLACK);
						LCD_WriteRAM_Inline(BLACK);
					}
				}
				else
				{
					for (j = 0; j < 240 / 8; j++)
					{
						LCD_WriteRAM_Inline(RED);
						LCD_WriteRAM_Inline(RED);
						LCD_WriteRAM_Inline(RED);
						LCD_WriteRAM_Inline(RED);
						LCD_WriteRAM_Inline(RED);
						LCD_WriteRAM_Inline(RED);
						LCD_WriteRAM_Inline(RED);
						LCD_WriteRAM_Inline(RED);
					}
				}
			}

			P23 = !P23;
			if (bUsbOutReady)
			{
				usbOutDone();
				usbCheckUpdate(); // ����Ƿ�Ϊ������Ϣ
			}
		}
	}
}