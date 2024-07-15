/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC 1T Series MCU Demo Programme -------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-0513-55012956,55012947,55012969 ------------------------*/
/* --- Tel: 86-0513-55012928,55012929,55012966 ------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* --- Web: www.STCMCUDATA.com  ---------------------------------------*/
/* --- QQ:  800003751 -------------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ����STC�����ϼ�����            */
/*---------------------------------------------------------------------*/

#include	"Task.h"
#include	"System_init.h"
#include "LCD.h"  
#include "test code.h"
#include	"STC32G_SPI.h"
#include	"STC32G_Switch.h"
#include	"STC32G_NVIC.h"
#include  "STC32G_Clock.h"



/****************  SPI��ʼ������ *****************/
void SPI_config1(void)
{
	SPI_InitTypeDef		SPI_InitStructure;
	SPI_InitStructure.SPI_Enable    = ENABLE;				//SPI����    ENABLE, DISABLE
	SPI_InitStructure.SPI_SSIG      = DISABLE;				//Ƭѡλ     ENABLE, DISABLE
	SPI_InitStructure.SPI_FirstBit  = SPI_MSB;				//��λ����   SPI_MSB, SPI_LSB
	SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;		//����ѡ��   SPI_Mode_Master, SPI_Mode_Slave
	SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;			//ʱ����λ   SPI_CPOL_High,   SPI_CPOL_Low
	SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;		//���ݱ���   SPI_CPHA_1Edge,  SPI_CPHA_2Edge
	SPI_InitStructure.SPI_Speed     = SPI_Speed_2;			//SPI�ٶ�    SPI_Speed_4, SPI_Speed_8, SPI_Speed_16, SPI_Speed_2
	SPI_Init(&SPI_InitStructure);
	//NVIC_SPI_Init(ENABLE,Priority_3);		//�ж�ʹ��, ENABLE/DISABLE; ���ȼ�(�͵���) Priority_0,Priority_1,Priority_2,Priority_3
	
	SPI_SW(SPI_P54_P13_P14_P15);	//SPI_P54_P13_P14_P15,SPI_P22_P23_P24_P25,SPI_P54_P40_P41_P43,SPI_P35_P34_P33_P32
	
	P1_PULL_UP_ENABLE(GPIO_Pin_3 | GPIO_Pin_5);
	P1_SPEED_HIGH(GPIO_Pin_3 | GPIO_Pin_5); //��ƽת���ٶȿ죨���IO�ڷ�ת�ٶȣ�

	HSPllClkConfig(MCLKSEL_HIRC,PLL_96M,2);    //ϵͳʱ��ѡ��,PLLʱ��ѡ��,ʱ�ӷ�Ƶϵ��
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
// ����: void	main(void)
// ����: ����������.
// ����: None.
// ����: None.
// �汾: V1.0, 2012-10-22
//========================================================================
void main(void)
{
  u16 line;
	u16 i,j;
	WTST = 0;		//���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXSFR();		//��չSFR(XFR)����ʹ�� 
	CKCON = 0;      //��߷���XRAM�ٶ�

	SYS_Init();
	

	Set_GPIO();                         //�˿�����
	
	SPI_config1();
	
	LCD_Init();			                    //��ʼ��LCD 	

  LCD_Display_Dir(USE_LCM_DIR);		 		//��Ļ����

	//LCD_Clear(WHITE);                   //����

	
	//Color_Test();								//��ɫ����
	//Read_Test();								//����ɫ����
	//FillRec_Test();							//ͼ�β���
	//English_Font_test();				//Ӣ�Ĳ���
	//Chinese_Font_test();				//���Ĳ���
	P2=0;
	while(1){
		
		for(line=0;line<240;line++){
		P20 = !P20;
		
				
	LCD_Set_Window(0,0,240,240);
		P21 = !P21;

	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM	
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



