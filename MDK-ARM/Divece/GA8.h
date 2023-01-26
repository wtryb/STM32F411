/**************************************
&File Name:   GA8.h
&Author:      �����
&date:        2023.1.8

+++++++
+NOTE+
+++++++
GA8 CAT1ģ���������򣬰���PDU���ŷ����Լ�TCP����
**************************************/
#ifndef __GA8_H_
#define __GA8_H_

#include "SYSTEM.h"
#include "MODEL.h"

  
#define DEBUG_UART		      &huart1		//���ڵ��Կ�
#define GA8_USART           &huart2   //GA8ͨ�Ŵ���
 
#define OK_CODE_TCP_CON     0x11      //TCP���ӳɹ�
#define OK_CODE_SEND_MSG    0x12      //���ŷ��ͳɹ�
#define OK_CODE_NONE        0x13      //δ����ɹ�����
 
#define ERRO_CODE_HARDWARE  0x01      //Ӳ������
#define ERRO_CODE_SIM       0x02      //SIM������
#define ERRO_CODE_CREG      0x03      //�������
#define ERRO_CODE_TCP       0x04      //TCP���ӳ���
#define ERRO_CODE_TCP_RES   0x05      //TCP�ظ�����
#define ERRO_CODE_PDU       0x06      //PDU��������
#define ERRO_CODE_MSG_SEND  0x07      //���ŷ��ͳ���
#define ERRO_CODE_NONE      0x08      //δ����������
#define ERRO_CODE_CGATT     0x09      //δ��������

#define TCP_CONNETC_AT           "AT+QIOPEN=1,0,\"TCP\",\"restapi.amap.com\",80,0,1\r\n" //Ϊ�˷����޸�
#define TCP_MAP_GET_URL_TEST     "GET https://restapi.amap.com/v3/geocode/regeo?output=json&location=116.310003,39.991957&key=257da8c8a2c0ebd13452f6c60718029f&radius=1000&extensions=base"

#define GA8_MAX_BUFFER_SIZE 1000

extern char GA8_BUFFER[GA8_MAX_BUFFER_SIZE];
extern unsigned int RE_counter;
extern unsigned char RE_temp;

typedef struct Tcp_Msg
{
    char *head;
    char *url;
    char *Send_URL;
    
    void *Block_Para;
} Tcp_Msg;

void Usart1Printf(const char *format,...);
char Find_Str_In_Buffer(char *Buffer, char *str);
void Clear_Buffer(void);
void DEBUG_UART_Send_MSG(char *msg);
void GA8_Send_Cmd(char *cmd);

char GA8_Test(void);
void GA8_PDP_Connect(void);
char GA8_TCP_Connect(char *tcp_ip);
char GA8_TCP_Send_Msg(char *msg);

#endif
