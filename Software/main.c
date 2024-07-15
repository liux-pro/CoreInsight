#include "STC32G.H"
#include "stc.h"
#include "usb.h"
#include "usb_hid.h"
#include "stdio.h"
#include "intrins.h"
#include "STC32G_GPIO.h"


/*
����ʱ��IRCƵ�ʱ����� 24.000MHz
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

void main(void)
{

	WTST = 0;  // ���ó���ָ����ʱ��������ֵΪ0�ɽ�CPUִ��ָ����ٶ�����Ϊ���
	EAXFR = 1; // ��չ�Ĵ���(XFR)����ʹ��
	CKCON = 0; // ��߷���XRAM�ٶ�
	usb_init();
	EA = 1;

	P2_MODE_IO_PU(GPIO_Pin_0);

	while (1)
	{
        if(bUsbOutReady){
            usbOutDone();
            usbCheckUpdate();                           //����Ƿ�Ϊ������Ϣ            
        }   
	}
}