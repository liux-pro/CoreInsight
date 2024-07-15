#include "sys.h"	  
#include "lcd.h"   
#include "pic.h"
#include "test code.h"
#include "string.h"
#include <stdio.h>
 
 u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//������ɫ����
 u16 ColornTab[8]={RED,MAGENTA,GREEN,DARKBLUE,BLUE,BLACK,LIGHTGREEN};
 u16 ColornTab1[8]={MAGENTA,GREEN,DARKBLUE,BLUE,BLACK,LIGHTGREEN,RED};




//���̶���
void DrawTestPage(u8 *str)
{
	//���ƹ̶���up
	LCD_Clear(WHITE);
	LCD_Fill(0,0,lcddev.width,20,BLUE);
	POINT_COLOR=GREEN;
	LCD_DrawLine(0,20,lcddev.width,20);
	POINT_COLOR=BLUE;
	LCD_DrawLine(0,21,lcddev.width,21);
	POINT_COLOR=RED;
	LCD_DrawLine(0,22,lcddev.width,22);
	//���ƹ̶���down
	LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=GREEN;
	LCD_DrawLine(0,lcddev.height-20,lcddev.width,lcddev.height-20);
	POINT_COLOR=BLUE;
	LCD_DrawLine(0,lcddev.height-21,lcddev.width,lcddev.height-21);
	POINT_COLOR=RED;            
	LCD_DrawLine(0,lcddev.height-22,lcddev.width,lcddev.height-22);	
	POINT_COLOR=WHITE;
	Gui_StrCenter(0,2,str,16,1);//������ʾ
	Gui_StrCenter(0,lcddev.height-18,"�����к�Ѷ�������޹�˾",16,1);//������ʾ
}

//���Ĳ���
void Chinese_Font_test(void)
{	
	DrawTestPage("������ʾ����");
	
		POINT_COLOR=RED;	//������ɫ
		BACK_COLOR=BLACK;  //����ɫ 
	
		Show_Str(10,30,"16X16:��Ѷ����",16,1);
		Show_Str(10,50,"16X16:TFTҺ����ʾ��",16,1);
		Show_Str(10,70,"24X24:������ʾ",24,1);
		Show_Str(10,100,"32X32:���Գ���",32,1);
		delay_ms(1500);
}

//������ҳ
void main_test(u8 *id)
{
	DrawTestPage("��ʾ�����Գ���");
	POINT_COLOR=RED;
	Gui_StrCenter(0,100,"��ʾ��",32,1);
	POINT_COLOR=GREEN;
	Gui_StrCenter(0,135,"���Գ���",32,1);
	POINT_COLOR=BLUE;
	Gui_StrCenter(0,170,id,24,1);
	POINT_COLOR=BLACK;
	Gui_StrCenter(0,196,"240RGB*320",24,1);
	POINT_COLOR=BLACK;
	Gui_StrCenter(0,235,"TEL:13528896127",24,1);
	delay_ms(2000);				
}

//ͼ�β���
void FillRec_Test(void)
{
	u8 i=0;
	DrawTestPage("ͼ�β���");
	LCD_Fill(0,24,lcddev.width,lcddev.height-24,WHITE);
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_DrawRectangle(lcddev.width/2-25+(i*15),lcddev.height/2-25+(i*15),lcddev.width/2-25+(i*15)+60,lcddev.height/2-25+(i*15)+60); 
		delay_ms(100);
	}
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_Draw_Circle(50+(i*35),60,30);
		delay_ms(100);
	}
	delay_ms(1500);
	
	
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		LCD_Fill(lcddev.width/2-25+(i*15),lcddev.height/2-25+(i*15),lcddev.width/2-25+(i*15)+60,lcddev.height/2-25+(i*15)+60,POINT_COLOR); 
		delay_ms(100);
	}
	for (i=0; i<5; i++) 
	{
		POINT_COLOR=ColorTab[i];
		gui_fill_circle(50+(i*35),60,30,POINT_COLOR);
		delay_ms(100);
	}
	delay_ms(1500);
}

//Ӣ�Ĳ���
void English_Font_test(void)
{
	DrawTestPage("Ӣ����ʾ����");
	POINT_COLOR=RED;
	BACK_COLOR=WHITE;
	LCD_ShowString(10,30,200,12,12,"6X12:abcdefghijklmnopqrstuvwxyz");
	LCD_ShowString(10,45,200,12,12,"6X12:ABCDEFGHIJKLMNOP0123456789");
	POINT_COLOR=GREEN;
	LCD_ShowString(10,60,200,16,16,"8X16:abcdefghijklmnopqrstuvwxyz");
	LCD_ShowString(10,80,200,16,16,"8X16:ABCDEFGHIJKLMNOP0123456789");
	POINT_COLOR=BLUE;
	LCD_ShowString(10,100,200,24,24,"12X24:abcdefghijklmnopqrstuvwxyz");
	LCD_ShowString(10,128,200,24,24,"12X24:ABCDEFGHIJKLMNOP0123456789");
	delay_ms(1500);
}

//ͼƬ����
void Pic_test(void)
{
	DrawTestPage("ͼƬ��ʾ����");
	POINT_COLOR=BLUE;
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(60,100,gImage_1);
	Gui_Drawbmp16(130,100,gImage_1);
	delay_ms(1500);
}

//�ǶȲ���
void Rotate_Test(void)
{
	u8 num=0;
	u8 *Direction[4]={"Rotation:0","Rotation:180","Rotation:270","Rotation:90"};
	
		for(num=0;num<4;num++)
		{		
			LCD_Display_Dir(num);
			DrawTestPage("�ǶȲ���");
			POINT_COLOR=BLUE;
			Show_Str(20,30,Direction[num],16,1);
			Gui_Drawbmp16(30,50,gImage_1);
			delay_ms(1000);delay_ms(1000);
		}

	LCD_Display_Dir(USE_LCM_DIR);	

}



//������ɫ
void DispBand(void)	 
{
	unsigned int i,j,k;
	//unsigned int color[8]={RED,RED,GREEN,GREEN,BLUE,BLUE,WHITE,WHITE};
	//unsigned int color[8]={BLUE,GREEN,RED,GBLUE,BRED,YELLOW,BLACK,WHITE};

	LCD_Set_Window(0,0,lcddev.width,lcddev.height);

	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM	

	for(i=0;i<8;i++)
	{
		for(j=0;j<lcddev.height/8;j++)
		{
	        for(k=0;k<lcddev.width;k++)
			{
				
				LCD_WriteRAM(ColornTab[i]);				
				
			} 
		}
	}
	for(j=0;j<lcddev.height%8;j++)
	{
        for(k=0;k<lcddev.width;k++)
		{
			
				LCD_WriteRAM(ColornTab[7]);			
			
		} 
	}
	
	//delay_ms(1000);
}
//������ɫ
void DispBand1(void)	 
{
	unsigned int i,j,k;
	//unsigned int color[8]={RED,RED,GREEN,GREEN,BLUE,BLUE,WHITE,WHITE};
	//unsigned int color[8]={BLUE,GREEN,RED,GBLUE,BRED,YELLOW,BLACK,WHITE};

	LCD_Set_Window(0,0,lcddev.width,lcddev.height);

	LCD_WriteRAM_Prepare();     		//��ʼд��GRAM	

	for(i=0;i<8;i++)
	{
		for(j=0;j<lcddev.height/8;j++)
		{
	        for(k=0;k<lcddev.width;k++)
			{
				
				LCD_WriteRAM(ColornTab1[i]);				
				
			} 
		}
	}
	for(j=0;j<lcddev.height%8;j++)
	{
        for(k=0;k<lcddev.width;k++)
		{
			
				LCD_WriteRAM(ColornTab1[7]);			
			
		} 
	}
	
}

//��ɫ����
void Color_Test(void)
{

	DispBand();          
	
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;
	Show_Str(20,30,"WHITE",16,1);delay_ms(1000);
	POINT_COLOR=WHITE;
	LCD_Clear(RED);
	Show_Str(20,30,"RED ",16,1);delay_ms(1000);
	LCD_Clear(GREEN);
	Show_Str(20,30,"GREEN ",16,1);delay_ms(1000);
	LCD_Clear(BLUE);
	Show_Str(20,30,"BLUE ",16,1);delay_ms(1500);
	
}

//��ʾ���ز���
void Switch_test(void)
{
	u8 num=3;
	while(num--)
	{
	LCD_DisplayOff();
	delay_ms(400);
	LCD_DisplayOn();
	delay_ms(400);
	}
	
}

//��ID ��ɫ ����
void Read_Test(void)
{
	//u16 color;
	//u8 buf[10] = {0},i;
	//u8 cbuf[20] = {0};

//	DrawTestPage("����ɫֵ����");
//	LCD_Fill(0,23,lcddev.width,lcddev.height-23,WHITE);	

//	for (i=0; i<7; i++) 
//	{
//		POINT_COLOR=ColornTab[i];
//		LCD_Fill(40-10,55+i*25-10,40+10,55+i*25+10,POINT_COLOR);
//		color = LCD_ReadPoint(40,55+i*25);
//		sprintf((char *)cbuf,"read color:0x%04x",color);
//		Show_Str(40+20,55+i*25-8,cbuf,16,1);
//	}
//	delay_ms(1500);
}

