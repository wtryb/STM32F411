/**************************************
&File Name:   #include "analysis.h"
&Author:        �����
&date:           2023.1.24

+++++++
+NOTE+
+++++++
��Ŀ����������صĹ��ܺ���
**************************************/
#include "analysis.h"

#include "APP.h"
#include "SYSTEM.h"
#include "MODEL.h"
#include "cJSON.h"

#include <string.h>

/********************************************
@Function name;                char Find_JSON_From_Buffer(char *dirStr, char *srcStr)
@Function description;        ��Դ�ַ�����Ѱ��������JSON�ֶ�
                              
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
char *Find_JSON_From_Buffer(const char *srcStr)
{
  char *str_temp;
  char *str_temp1;
  char aaa[2000]; //��֤���鹻�󣬶���ֻ���������޷���ָ�룬utf-8����һ�����������ֽ�
  
  str_temp = strstr(srcStr, "{"); //Ѱ��JSON�ֶο�ͷ��{
  
  if(str_temp != NULL)
  {
    str_temp1 = str_temp;    //��ֵ��Ŀ���ַ���
    while(*str_temp1 != '\0')
    {
      str_temp1++;         //�ƶ�ָ�뵽Դ�ַ�������ĩβ
    }
    while(*str_temp1 != '}')
    {
      str_temp1--;         //��ĩβѰ��JSON���ݽ�β��}
    }
    
    if(str_temp1 == str_temp) //�Ƚ�����ָ�룬��ָ����ͬ����ΪJSON���ݲ�����
    {
      return NULL;
    }
    else
    {
      strncpy(aaa, (const char *)str_temp, str_temp1 - str_temp + 1);  
      return aaa;
    }
  }
  else 
    return 0;   //û���ҵ�JSON���ݿ�ͷ��{
}

/********************************************
@Function name;                void Gett_Address_cJSON(char *dirStr, char *srcStr)
@Function description;        ��Դ�ַ����л�ȡformatted_address����ֵ�����ص�Ŀ���ַ���
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
char *Gett_Address_cJSON(char *srcStr)
{
  cJSON *cJSON_OBJ;
  cJSON *cJSON_Address;
  cJSON *Address;
  char aaa[1000];   //��֤���鹻�󣬶���ֻ���������޷���ָ�룬utf-8����һ�����������ֽ�
  
  //Usart1Printf("srcStr JSON:%s\r\n", srcStr);
  //����һ����JSON����
  cJSON_OBJ = cJSON_Parse(srcStr);
  //����Ƕ��
  cJSON_Address = cJSON_GetObjectItem(cJSON_OBJ, "regeocode");
  //��ȡformatted_address����ֵ
  Address = cJSON_GetObjectItem(cJSON_Address, "formatted_address");
  //cJSON_Delete(cJSON_OBJ);  //�ͷŶ��ڴ�
  if(Address->valuestring != NULL)    //�ж��Ƿ񷵻���formatted_address��ֵ
  {  
    strncpy(aaa, (const char *)Address->valuestring, strlen(Address->valuestring));
    //Usart1Printf("aaa JSON:%s\r\n", aaa);
    return aaa; //���ص�Ŀ���ַ���
  }
  else
  {
    return NULL;
  }
}

/********************************************
@Function name;                int UnicodeToUtf8(char* pInput, char *pOutput) 
@Function description;        unicodeתutf-8
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********
Դ��
https://blog.csdn.net/bladeandmaster88/article/details/54837338
**************************/
int UnicodeToUtf8(char* pInput, char *pOutput)  
{  
	int len = 0; //��¼ת�����Utf8�ַ������ֽ���
	while (*pInput)
	{
		//����һ��unicode�ַ�
		char low = *pInput;//ȡ��unicode�ַ��ĵ�8λ
		pInput++;
		char high = *pInput;//ȡ��unicode�ַ��ĸ�8λ
		int w=high<<8;
		unsigned  wchar = (high<<8)+low;//��8λ�͵�8λ���һ��unicode�ַ�,�ӷ����㼶���
 
		if (wchar <= 0x7F ) //Ӣ���ַ�
		{   
			pOutput[len] = (char)wchar;  //ȡwchar�ĵ�8λ
			len++;
		}  
		else if (wchar >=0x80 && wchar <= 0x7FF)  //����ת����˫�ֽ�pOutput�ַ�
		{  
			pOutput[len] = 0xc0 |((wchar >> 6)&0x1f);  //ȡ��unicode�����6λ���5λ����䵽110yyyyy 10zzzzzz ��yyyyy��
			len++;
			pOutput[len] = 0x80 | (wchar & 0x3f);  //ȡ��unicode����ĵ�6λ����䵽110yyyyy 10zzzzzz ��zzzzzz��
			len++;
		}  
		else if (wchar >=0x800 && wchar < 0xFFFF)  //����ת����3���ֽڵ�pOutput�ַ�
		{  
			pOutput[len] = 0xe0 | ((wchar >> 12)&0x0f);  //����λ����1110xxxx 10yyyyyy 10zzzzzz�е�xxxx
			len++;
			pOutput[len] = 0x80 | ((wchar >> 6) & 0x3f);  //�м�6λ����1110xxxx 10yyyyyy 10zzzzzz�е�yyyyyy
			len++;
			pOutput[len] = 0x80 | (wchar & 0x3f);  //��6λ����1110xxxx 10yyyyyy 10zzzzzz�е�zzzzzz
			len++;
		}  
 
		else //���������ֽ�����unicode�ַ������д���
		{
			return -1;
		}
		pInput ++;//������һ��unicode�ַ�
	}
	//utf8�ַ������棬�и�\0
	pOutput [len]= 0;
	return len;  
}  
/********************************************
@Function name;                int Utf8ToUnicode(char* pInput, char* pOutput)
@Function description;        utf-8תunicode 
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********
* ��UTF8����ת����Unicode��UCS-2LE������  �͵�ַ���λ�ֽ�
* ������
*    char* pInput     �����ַ���
*    char*pOutput   ����ַ���
* ����ֵ��ת�����Unicode�ַ������ֽ�������������򷵻�-1
**************************/
//utf8תunicode
int Utf8ToUnicode(char* pInput, char* pOutput)
{
	int outputSize = 0; //��¼ת�����Unicode�ַ������ֽ���
 
	while (*pInput)
	{
		if (*pInput > 0x00 && *pInput <= 0x7F) //�����ֽ�UTF8�ַ���Ӣ����ĸ�����֣�
		{
			*pOutput = *pInput;
			 pOutput++;
			*pOutput = 0; //С�˷���ʾ���ڸߵ�ַ�0
		}
		else if (((*pInput) & 0xE0) == 0xC0) //����˫�ֽ�UTF8�ַ�
		{
			char high = *pInput;
			pInput++;
			char low = *pInput;
			if ((low & 0xC0) != 0x80)  //����Ƿ�Ϊ�Ϸ���UTF8�ַ���ʾ
			{
				return -1; //��������򱨴�
			}
 
			*pOutput = (high << 6) + (low & 0x3F);
			pOutput++;
			*pOutput = (high >> 2) & 0x07;
		}
		else if (((*pInput) & 0xF0) == 0xE0) //�������ֽ�UTF8�ַ�
		{
			char high = *pInput;
			pInput++;
			char middle = *pInput;
			pInput++;
			char low = *pInput;
			if (((middle & 0xC0) != 0x80) || ((low & 0xC0) != 0x80))
			{
				return -1;
			}
			*pOutput = (middle << 6) + (low & 0x3F);//ȡ��middle�ĵ���λ��low�ĵ�6λ����ϳ�unicode�ַ��ĵ�8λ
			pOutput++;
			*pOutput = (high << 4) + ((middle >> 2) & 0x0F); //ȡ��high�ĵ���λ��middle���м���λ����ϳ�unicode�ַ��ĸ�8λ
		}
		else //���������ֽ�����UTF8�ַ������д���
		{
			return -1;
		}
		pInput ++;//������һ��utf8�ַ�
		pOutput ++;
		outputSize += 2;
	}
	//unicode�ַ������棬������\0
	*pOutput = 0;
	 pOutput++;
	*pOutput = 0;
	return outputSize;
}

