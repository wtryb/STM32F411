/**************************************
&File Name:   GA8.c
&Author:      李泽枫
&date:        2023.1.8
              2023.1.23(重构)
        
+++++++
+NOTE+
+++++++
GA8 CAT1模组驱动程序，包含PDU短信发送以及TCP连接
**************************************/
#include "GA8.h"
#include "SYSTEM.h"
#include "MODEL.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>                        

//接收计数
unsigned int RE_counter = 0;
//GA8的接收缓冲
char GA8_BUFFER[GA8_MAX_BUFFER_SIZE];
unsigned char RE_temp;

char UartTxBuf[1000];
void Usart1Printf(const char *format,...)
{
	uint16_t len;
	va_list args;	
	va_start(args,format);
	len = vsnprintf((char*)UartTxBuf,sizeof(UartTxBuf)+1,(char*)format,args);
	va_end(args);
	HAL_UART_Transmit(&huart1, (uint8_t *)UartTxBuf, len, 0xff);
}


/********************************************
@Function name;         char Find_Str_In_Buffer(char *Buffer, char *str)
@Function description;  在接收缓存中找目标字符串
@Function input;        char *Buffer: 缓存
                        char *str     目标字符串
@Function output;
@Date;
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
char Find_Str_In_Buffer(char *Buffer, char *str)
{
  if(strstr(Buffer, str) == NULL)
    return 0;
  else
    return 1;
}

/********************************************
@Function name;           void UART1_Send_MSG(char *msg)          
@Function description;    DEBUG串口输出字符串    
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void DEBUG_UART_Send_MSG(char *msg)
{
  int AT_length = strlen(msg);

  HAL_UART_Transmit(DEBUG_UART, (const uint8_t *)msg, AT_length, 0xfffff);
}

/********************************************
@Function name;             void Clear_Buffer() 
@Function description;      清除接收缓冲
@Function input;
@Function output;         
@Date;
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void Clear_Buffer(void)
{
  int i;
  RE_counter = 0;
  for(i = 0;i < GA8_MAX_BUFFER_SIZE;i++)
    GA8_BUFFER[i] = 0;
}

/********************************************
@Function name;             void GA8_Send_Cmd(char *cmd)         
@Function description;        GA8发送指令
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void GA8_Send_Cmd(char *cmd)
{
  printf("%s\r\n",cmd);
}

/********************************************
@Function name;                char GA8_Test(void)
@Function description;        测试GA8模块是否正常
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
char GA8_Test(void)
{
  char i = 0;
  unsigned char flag = 0;
  switch(i)
  {
    //AT测试
    case 0:
          Clear_Buffer();
          GA8_Send_Cmd("AT");
          HAL_Delay(100);
          if(Find_Str_In_Buffer(GA8_BUFFER, "OK") == 0)
          {
            flag = ERRO_CODE_HARDWARE;
            break;
          }
    //SIM卡检查
    case 1:
          Clear_Buffer();
          GA8_Send_Cmd("AT*ICCID?");
          HAL_Delay(100);
          if(Find_Str_In_Buffer(GA8_BUFFER, "*ICCID") == 0)
          {
            flag =  ERRO_CODE_SIM;
            break;
          }
    //网络注册检查      
    case 2:
          Clear_Buffer();
          GA8_Send_Cmd("AT+CREG?");
          HAL_Delay(100);
          if(Find_Str_In_Buffer(GA8_BUFFER, "+CREG: 0,1") == 0)
          {
            flag = ERRO_CODE_CREG;
            break;
          }
    //网络附着检查      
    case 3:
           Clear_Buffer();
           GA8_Send_Cmd("AT+CGATT?");
          HAL_Delay(100);
          if(Find_Str_In_Buffer(GA8_BUFFER, "OK") == 0)
          {
            flag =  ERRO_CODE_CGATT;      
            break;
          }
  }
  return flag;
}

/********************************************
@Function name;                void GA8_PDP_Connect(void)
@Function description;        建立PDP连接
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void GA8_PDP_Connect(void)
{
    Clear_Buffer();
    GA8_Send_Cmd("AT+QIACT=1");
    HAL_Delay(100);
}


char GA8_TCP_Connect(char *tcp_ip)
{
  char temp[100] = "AT+QIOPEN=1,0,\"TCP\",";
  Clear_Buffer();
  
  strcat((char *)temp, tcp_ip);
  strcat((char *)temp, ",0,1");    //连接字符串
  //调试
  //Usart1Printf("temp:%s\r\n", temp);
  GA8_Send_Cmd(temp);
  HAL_Delay(5000); //等待五秒
  if(Find_Str_In_Buffer(GA8_BUFFER, "0,0") == 1)
    return OK_CODE_TCP_CON;
  else
    return ERRO_CODE_TCP;
}
  
/********************************************
@Function name;                char GA8_TCP_Send_Msg(char *msg)
@Function description;        发送TCP信息
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
char GA8_TCP_Send_Msg(char *msg)
{
   Clear_Buffer();
   GA8_Send_Cmd("AT+QISEND=0");
   HAL_Delay(100);
   if(Find_Str_In_Buffer(GA8_BUFFER, ">") == 1)
   {
     printf("%s", msg); //发送TCP消息
     printf("\x1A");    //发送截止符
     HAL_Delay(5000);
     return OK_CODE_NONE;
   }
   else
     return ERRO_CODE_TCP_RES;
}