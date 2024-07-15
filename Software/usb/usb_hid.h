#ifndef __USB_HID_H__
#define __USB_HID_H__

#include "stc.h"
#include "usb.h"

void usbInit();
void usbCheckUpdate();
void usbSend2PC(BYTE *buffer);
void usbOutDone();

extern BYTE xdata UsbBuffer[];
extern BYTE bUsbOutReady;
extern BYTE bUsbInBusy;

#endif
