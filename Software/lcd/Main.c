/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* 如果要在程序中使用此代码,请在程序中注明使用了STC的资料及程序            */
/*---------------------------------------------------------------------*/

#include	"Task.h"
#include	"System_init.h"
#include "LCD.h"  
#include "test code.h"
#include	"STC32G_SPI.h"
#include	"STC32G_Switch.h"
#include	"STC32G_NVIC.h"
#include  "STC32G_Clock.h"



/****************  SPI初始化函数 *****************/
void SPI_config1(void)
{
	SPI_InitTypeDef		SPI_InitStructure;
	SPI_InitStructure.SPI_Enable    = ENABLE;				//SPI启动    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG      = DISABLE;				//片选位     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;				//移位方向   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;		//主从选择   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;			//时钟相位   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;		//数据边沿   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed     = SPI_Speed_2;			//SPI速度    SPI_Speed_4, SPI_Speed_8, SPI_Speed_16, SPI_Speed_2
	SPI_Init(&SPI_InitStructure);
	//NVIC_SPI_Init(ENABLE,Priority_3);		//中断使能, ENABLE/DISABLE; 优先级(低到高) Priority_0,Priority_1,Priority_2,Priority_3
	
	SPI_SW(SPI_P54_P13_P14_P15);	//SPI_P54_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32
	
	P1_PULL_UP_ENABLE(GPIO_Pin_3 | GPIO_Pin_5);
	P1_SPEED_HIGH(GPIO_Pin_3 | GPIO_Pin_5); //电平转换速度快（提高IO口翻转速度）

	HSPllClkConfig(MCLKSEL_HIRC,PLL_96M,2);    //系统时钟选择,PLL时钟选择,时钟分频系数
	HSSPI_Enable();
}


void DispBand1(void);

#define LCD_WriteRAM2(RGB_Code)       \
    do {                             \
        SPI_DC = 1;                  \
        SPDAT = (u8)((RGB_Code) >> 8); \
        _nop_(); _nop_(); _nop_();   \
        _nop_(); _nop_(); _nop_();   \
        _nop_(); _nop_();            \
        SPDAT = (u8)((RGB_Code) & 0xff); \
        _nop_(); _nop_(); _nop_();   \
        _nop_(); _nop_(); _nop_();   \
        _nop_();                     \
    } while (0)
		
//========================================================================
// 函数: void	main(void)
// 描述: 主函数程序.
// 参数: None.
// 返回: None.
// 版本: V1.0, 2012-10-22
//========================================================================
void main(void)
{
  u16 line;
	u16 i,j;
	WTST = 0;		//设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
	EAXSFR();		//扩展SFR(XFR)访问使能 
	CKCON = 0;      //提高访问XRAM速度

	SYS_Init();
	

	Set_GPIO();                         //端口设置
	
	SPI_config1();
	
	LCD_Init();			                    //初始化LCD 	

  LCD_Display_Dir(USE_LCM_DIR);		 		//屏幕方向

	//LCD_Clear(WHITE);                   //清屏

	
	//Color_Test();								//纯色测试
	//Read_Test();								//读颜色测试
	//FillRec_Test();							//图形测试
	//English_Font_test();				//英文测试
	//Chinese_Font_test();				//中文测试
	P2=0;
	while(1){
		
		for(line=0;line<240;line++){
		P20 = !P20;
		
				
	LCD_Set_Window(0,0,240,240);
		P21 = !P21;

	LCD_WriteRAM_Prepare();     		//开始写入GRAM	
		P22 = !P22;

	for(i=0;i<240;i++)
	{
      if(i==line){
				for(j=0;j<240;j++)
			    LCD_WriteRAM(BLUE);
			}else{
					for(j=0;j<240/8;j++)
{
			    LCD_WriteRAM2(RED);LCD_WriteRAM2(RED);LCD_WriteRAM2(RED);LCD_WriteRAM2(RED);LCD_WriteRAM2(RED);LCD_WriteRAM2(RED);LCD_WriteRAM2(RED);LCD_WriteRAM(RED);
}	
}
	}

		
		
			P23 = !P23;

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		}

		
		
		
	}

	while (1)
	{
        Task_Pro_Handler_Callback();
	}
}



