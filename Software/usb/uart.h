#ifndef __UART_H__
#define __UART_H__

//��RxFlagΪ1ʱ,��ʾ�ѽ��յ�CDC��������
//���յ����ݴ�С������RxCount����,ÿ����������64�ֽ�
//���ݱ�����RxBuffer������

void uart_init();
void uart_recv_done();
void uart_send(int size);


extern BOOL RxFlag;
extern BYTE RxCount;
extern BYTE xdata RxBuffer[64];
extern BYTE xdata TxBuffer[1024];


#endif
