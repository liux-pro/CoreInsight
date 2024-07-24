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
#ifdef LOONG
	P2_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_0 | GPIO_Pin_1);
	P2_SPEED_HIGH(GPIO_Pin_3 | GPIO_Pin_5); // ��ƽת���ٶȿ죨���IO�ڷ�ת�ٶȣ�
#else
	P1_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
	P4_MODE_IO_PU(GPIO_Pin_7);
	P1_SPEED_HIGH(GPIO_Pin_3 | GPIO_Pin_5); // ��ƽת���ٶȿ죨���IO�ڷ�ת�ٶȣ�
#endif
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
void configBlackLightPWM(u8 brightness)
{
	const u16 period = (u32)MAIN_Fosc / (u32)(20 * 1000);
	PWMx_InitDefine PWMx_InitStructure;

	// PWM1P_3 P6.0
	P6_MODE_IO_PU(GPIO_Pin_0);

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1;							// ģʽ,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = (u32)brightness * (u32)period / (u32)255; // PWMռ�ձ�ʱ��, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO1P;								// ���ͨ��ѡ��,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM1, &PWMx_InitStructure);							// ��ʼ��PWM1

	PWMx_InitStructure.PWM_Period = period;		   // ����ʱ��,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;		   // ��������������, 0~255
	PWMx_InitStructure.PWM_MainOutEnable = ENABLE; // �����ʹ��, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;	   // ʹ�ܼ�����, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);  // ��ʼ��PWMͨ�üĴ���,  PWMA,PWMB

	PWM1_USE_P60P61();
	NVIC_PWM_Init(PWMA, DISABLE, Priority_0);
}

void main(void)
{
	u8 i;
	BYTE *p_UsbBuffer;
	WTST = 0;  // ���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXFR = 1; // ��չ�Ĵ���(XFR)����ʹ��
	CKCON = 0; // ��߷���XRAM�ٶ�

	uart_init();
	usb_init();
	EA = 1;

	SPI_config1();

	LCD_Init();			// ��ʼ��LCD
	LCD_Display_Dir(2); // ��Ļ����

	LCD_Clear(BLACK);
	configBlackLightPWM(255);
	LCD_Set_Window(0, 0, 320, 240);
	LCD_WriteRAM_Prepare();
	SPI_DC = 1;

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
					}
					break;
					case CMD_SET_BRIGHTNESS:
					{
						configBlackLightPWM(*(u8 *)(RxBuffer + 4));
					}
					break;
					default:
						break;
					}
				}
			}

			if (RxCount == 64)
			{
				for (i = 0; i < 8; i++)
				{
					SoftSPI_WriteByte(*(p_UsbBuffer++));
					SoftSPI_WriteByte(*(p_UsbBuffer++));
					SoftSPI_WriteByte(*(p_UsbBuffer++));
					SoftSPI_WriteByte(*(p_UsbBuffer++));
					SoftSPI_WriteByte(*(p_UsbBuffer++));
					SoftSPI_WriteByte(*(p_UsbBuffer++));
					SoftSPI_WriteByte(*(p_UsbBuffer++));
					SoftSPI_WriteByte(*(p_UsbBuffer++));
				}
			}
			else
			{
				for (i = 0; i < RxCount; i++)
				{
					SoftSPI_WriteByte(*(p_UsbBuffer++));
				}
			}

			uart_recv_done(); // �Խ��յ����ݴ�����ɺ�,һ��Ҫ����һ���������,�Ա�CDC������һ�ʴ�������
		}
	}
}