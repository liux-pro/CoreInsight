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
IRC频率必须是 35.000MHz
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

/****************  SPI初始化函数 *****************/
void SPI_config1(void)
{
	SPI_InitTypeDef SPI_InitStructure;
	SPI_InitStructure.SPI_Enable = ENABLE;		  // SPI启动    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG = DISABLE;		  // 片选位     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit = SPI_MSB;	  // 移位方向   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // 主从选择   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;	  // 时钟相位   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;  // 数据边沿   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed = SPI_Speed_2;	  // SPI速度    SPI_Speed_4, SPI_Speed_8, SPI_Speed_16, SPI_Speed_2
	SPI_Init(&SPI_InitStructure);
	// NVIC_SPI_Init(ENABLE,Priority_3);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3

	SPI_SW(SPI_P54_P13_P14_P15); // SPI_P54_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32

	P1_MODE_IO_PU(GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_6);
	P4_MODE_IO_PU(GPIO_Pin_7);
	P1_PULL_UP_ENABLE(GPIO_Pin_3 | GPIO_Pin_5);
	P1_SPEED_HIGH(GPIO_Pin_3 | GPIO_Pin_5); // 电平转换速度快（提高IO口翻转速度）
	{
		/*
			这个函数不满足需求，改库函数不太好的原则，这里把他的函数体复制出来，改一改。
			HSPllClkConfig(MCLKSEL_HIRC, PLL_96M, 2); 系统时钟选择,PLL时钟选择,时钟分频系数
		*/
		MainClockSel(MCLKSEL_HIRC); // 系统时钟选择, MCLKSEL_HIRC/MCLKSEL_XIRC/MCLKSEL_X32K/MCLKSEL_I32K/MCLKSEL_PLL/MCLKSEL_PLL2/MCLKSEL_I48M

		// HIRC 在下载时调为35M，四分频后8M多一点，将将满足输入频率12M（±35%）的需求
		USBCLK &= ~PCKI_MSK;
		USBCLK |= PCKI_D4; // PLL输入时钟4分频

		PLLClockSel(PLL_96M);	// PLL时钟选择, PLL_96M/PLL_144M
		PLLEnable(ENABLE);		// PLL倍频使能, ENABLE/DISABLE
		delay_ms(2);			// 等待PLL锁频
		HSIOClockSel(HSCK_PLL); // 高速IO时钟选择, HSCK_MCLK/HSCK_PLL
		HSClockDiv(2);			// 高速IO时钟分频系数
	}

	HSSPI_Enable();
	// SPI（HSPI）的频率 = HIRC 35M 四分频 输入 PLL 出来变成 96M 二分频 48M 进入 HSPI外设 SPI自己也有2分频 最终24M
	// 对于stc32g12k128 ，由于IO速度原因，5v环境最高33M，3.3v环境最高20M，这里的24M是略微超限的。
}

/**
 * 检查是否接收到特定的ISP固件升级请求。
 */
void checkISP()
{
	// 怕编译器优化太傻，不能优化strlen,直接写8
	if (memcmp("@STCISP#", RxBuffer, 8) == 0)
	{
		usb_write_reg(OUTCSR1, 0);

		USBCON = 0x00;
		USBCLK = 0x00;
		IRC48MCR = 0x00;

		delay_ms(10);
		// 复位到bootloader
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

	PWMx_InitStructure.PWM_Mode = CCMRn_PWM_MODE1; // 模式,		CCMRn_FREEZE,CCMRn_MATCH_VALID,CCMRn_MATCH_INVALID,CCMRn_ROLLOVER,CCMRn_FORCE_INVALID,CCMRn_FORCE_VALID,CCMRn_PWM_MODE1,CCMRn_PWM_MODE2
	PWMx_InitStructure.PWM_Duty = 1000;			   // PWM占空比时间, 0~Period
	PWMx_InitStructure.PWM_EnoSelect = ENO1P;	   // 输出通道选择,	ENO1P,ENO1N,ENO2P,ENO2N,ENO3P,ENO3N,ENO4P,ENO4N / ENO5P,ENO6P,ENO7P,ENO8P
	PWM_Configuration(PWM1, &PWMx_InitStructure);  // 初始化PWM1

	PWMx_InitStructure.PWM_Period = 1750;		   // 周期时间,   0~65535
	PWMx_InitStructure.PWM_DeadTime = 0;		   // 死区发生器设置, 0~255
	PWMx_InitStructure.PWM_MainOutEnable = ENABLE; // 主输出使能, ENABLE,DISABLE
	PWMx_InitStructure.PWM_CEN_Enable = ENABLE;	   // 使能计数器, ENABLE,DISABLE
	PWM_Configuration(PWMA, &PWMx_InitStructure);  // 初始化PWM通用寄存器,  PWMA,PWMB

	PWM1_USE_P60P61();
	NVIC_PWM_Init(PWMA, DISABLE, Priority_0);
}

void main(void)
{
	u16 line;
	u32 i, j;
	u16 color;
	BYTE *p_UsbBuffer;
	WTST = 0;  // 设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
	EAXFR = 1; // 扩展寄存器(XFR)访问使能
	CKCON = 0; // 提高访问XRAM速度
	P2_MODE_IO_PU(GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);

	uart_init();
	usb_init();
	EA = 1;

	SPI_config1();

	LCD_Init();			// 初始化LCD
	LCD_Display_Dir(2); // 屏幕方向

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

			// 发送图片数据时候一般都是大数据包，会占满64字节的缓冲
			// 小于64的极大概率是命令包
			if (RxCount < 64)
			{
				checkISP();

				// 瞎定义的格式，包长31，是奇数，减少与颜色数据重复的概率
				// 三个@开头，第四位是命令
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
						LCD_WriteRAM_Prepare(); // 开始写入GRAM
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
			uart_recv_done(); // 对接收的数据处理完成后,一定要调用一次这个函数,以便CDC接收下一笔串口数据
		}
	}
}