/**************************************
&File Name:   GA8.c
&Author:      �����
&date:        2023.1.8
              2023.1.23(�ع�)
        
+++++++
+NOTE+
+++++++
GA8 CAT1ģ���������򣬰���PDU���ŷ����Լ�TCP����
**************************************/
#include "GA8.h"
#include "SYSTEM.h"
#include "MODEL.h"

#include <string.h>
#include <stdio.h>
#include <stdarg.h>                        

//���ռ���
unsigned int RE_counter = 0;
//GA8�Ľ��ջ���
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
@Function description;  �ڽ��ջ�������Ŀ���ַ���
@Function input;        char *Buffer: ����
                        char *str     Ŀ���ַ���
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
@Function description;    DEBUG��������ַ���    
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
@Function description;      ������ջ���
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
@Function description;        GA8����ָ��
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
@Function description;        ����GA8ģ���Ƿ�����
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
    //AT����
    case 0:
          Clear_Buffer();
          GA8_Send_Cmd("AT");
          HAL_Delay(100);
          if(Find_Str_In_Buffer(GA8_BUFFER, "OK") == 0)
          {
            flag = ERRO_CODE_HARDWARE;
            break;
          }
    //SIM�����
    case 1:
          Clear_Buffer();
          GA8_Send_Cmd("AT*ICCID?");
          HAL_Delay(100);
          if(Find_Str_In_Buffer(GA8_BUFFER, "*ICCID") == 0)
          {
            flag =  ERRO_CODE_SIM;
            break;
          }
    //����ע����      
    case 2:
          Clear_Buffer();
          GA8_Send_Cmd("AT+CREG?");
          HAL_Delay(100);
          if(Find_Str_In_Buffer(GA8_BUFFER, "+CREG: 0,1") == 0)
          {
            flag = ERRO_CODE_CREG;
            break;
          }
    //���總�ż��      
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
@Function description;        ����PDP����
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
  strcat((char *)temp, ",0,1");    //�����ַ���
  //����
  //Usart1Printf("temp:%s\r\n", temp);
  GA8_Send_Cmd(temp);
  HAL_Delay(5000); //�ȴ�����
  if(Find_Str_In_Buffer(GA8_BUFFER, "0,0") == 1)
    return OK_CODE_TCP_CON;
  else
    return ERRO_CODE_TCP;
}
  
/********************************************
@Function name;                char GA8_TCP_Send_Msg(char *msg)
@Function description;        ����TCP��Ϣ
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
     printf("%s", msg); //����TCP��Ϣ
     printf("\x1A");    //���ͽ�ֹ��
     HAL_Delay(5000);
     return OK_CODE_NONE;
   }
   else
     return ERRO_CODE_TCP_RES;
}