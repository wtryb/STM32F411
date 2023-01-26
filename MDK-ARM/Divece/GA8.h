/**************************************
&File Name:   GA8.h
&Author:      李泽枫
&date:        2023.1.8

+++++++
+NOTE+
+++++++
GA8 CAT1模组驱动程序，包含PDU短信发送以及TCP连接
**************************************/
#ifndef __GA8_H_
#define __GA8_H_

#include "SYSTEM.h"
#include "MODEL.h"

  
#define DEBUG_UART		      &huart1		//串口调试口
#define GA8_USART           &huart2   //GA8通信串口
 
#define OK_CODE_TCP_CON     0x11      //TCP连接成功
#define OK_CODE_SEND_MSG    0x12      //短信发送成功
#define OK_CODE_NONE        0x13      //未定义成功代码
 
#define ERRO_CODE_HARDWARE  0x01      //硬件出错
#define ERRO_CODE_SIM       0x02      //SIM卡出错
#define ERRO_CODE_CREG      0x03      //网络出错
#define ERRO_CODE_TCP       0x04      //TCP连接出错
#define ERRO_CODE_TCP_RES   0x05      //TCP回复出错
#define ERRO_CODE_PDU       0x06      //PDU开启出错
#define ERRO_CODE_MSG_SEND  0x07      //短信发送出错
#define ERRO_CODE_NONE      0x08      //未定义错误代码
#define ERRO_CODE_CGATT     0x09      //未附着网络

#define TCP_CONNETC_AT           "AT+QIOPEN=1,0,\"TCP\",\"restapi.amap.com\",80,0,1\r\n" //为了方便修改
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
