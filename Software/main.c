#include "STC32G.H"
#include "stc.h"
#include "usb.h"
#include "usb_hid.h"
#include "stdio.h"
#include "intrins.h"
#include "STC32G_GPIO.h"


/*
下载时，IRC频率必须是 24.000MHz
*/

char *USER_STCISPCMD = "@STCISP#"; // 设置自动复位到ISP区的用户接口命令

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

	WTST = 0;  // 设置程序指令延时参数，赋值为0可将CPU执行指令的速度设置为最快
	EAXFR = 1; // 扩展寄存器(XFR)访问使能
	CKCON = 0; // 提高访问XRAM速度
	usb_init();
	EA = 1;

	P2_MODE_IO_PU(GPIO_Pin_0);

	while (1)
	{
        if(bUsbOutReady){
            usbOutDone();
            usbCheckUpdate();                           //检测是否为升级信息            
        }   
	}
}