/**************************************
&File Name:   #include "analysis.h"
&Author:        李泽枫
&date:           2023.1.24

+++++++
+NOTE+
+++++++
项目解析数据相关的功能函数
**************************************/
#include "analysis.h"

#include "APP.h"
#include "SYSTEM.h"
#include "MODEL.h"
#include "cJSON.h"

#include <string.h>

/********************************************
@Function name;                char Find_JSON_From_Buffer(char *dirStr, char *srcStr)
@Function description;        从源字符串中寻找完整的JSON字段
                              
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
  char aaa[2000]; //保证数组够大，而且只能用数组无法用指针，utf-8编码一个汉字两个字节
  
  str_temp = strstr(srcStr, "{"); //寻找JSON字段开头的{
  
  if(str_temp != NULL)
  {
    str_temp1 = str_temp;    //赋值给目标字符串
    while(*str_temp1 != '\0')
    {
      str_temp1++;         //移动指针到源字符串的最末尾
    }
    while(*str_temp1 != '}')
    {
      str_temp1--;         //从末尾寻找JSON数据结尾的}
    }
    
    if(str_temp1 == str_temp) //比较两个指针，两指针相同则认为JSON数据不完整
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
    return 0;   //没有找到JSON数据开头的{
}

/********************************************
@Function name;                void Gett_Address_cJSON(char *dirStr, char *srcStr)
@Function description;        从源字符串中获取formatted_address键的值并返回到目标字符串
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
  char aaa[1000];   //保证数组够大，而且只能用数组无法用指针，utf-8编码一个汉字两个字节
  
  //Usart1Printf("srcStr JSON:%s\r\n", srcStr);
  //解析一整段JSON数据
  cJSON_OBJ = cJSON_Parse(srcStr);
  //解析嵌套
  cJSON_Address = cJSON_GetObjectItem(cJSON_OBJ, "regeocode");
  //获取formatted_address键的值
  Address = cJSON_GetObjectItem(cJSON_Address, "formatted_address");
  //cJSON_Delete(cJSON_OBJ);  //释放堆内存
  if(Address->valuestring != NULL)    //判断是否返回了formatted_address的值
  {  
    strncpy(aaa, (const char *)Address->valuestring, strlen(Address->valuestring));
    //Usart1Printf("aaa JSON:%s\r\n", aaa);
    return aaa; //返回到目标字符串
  }
  else
  {
    return NULL;
  }
}

/********************************************
@Function name;                int UnicodeToUtf8(char* pInput, char *pOutput) 
@Function description;        unicode转utf-8
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********
源自
https://blog.csdn.net/bladeandmaster88/article/details/54837338
**************************/
int UnicodeToUtf8(char* pInput, char *pOutput)  
{  
	int len = 0; //记录转换后的Utf8字符串的字节数
	while (*pInput)
	{
		//处理一个unicode字符
		char low = *pInput;//取出unicode字符的低8位
		pInput++;
		char high = *pInput;//取出unicode字符的高8位
		int w=high<<8;
		unsigned  wchar = (high<<8)+low;//高8位和低8位组成一个unicode字符,加法运算级别高
 
		if (wchar <= 0x7F ) //英文字符
		{   
			pOutput[len] = (char)wchar;  //取wchar的低8位
			len++;
		}  
		else if (wchar >=0x80 && wchar <= 0x7FF)  //可以转换成双字节pOutput字符
		{  
			pOutput[len] = 0xc0 |((wchar >> 6)&0x1f);  //取出unicode编码低6位后的5位，填充到110yyyyy 10zzzzzz 的yyyyy中
			len++;
			pOutput[len] = 0x80 | (wchar & 0x3f);  //取出unicode编码的低6位，填充到110yyyyy 10zzzzzz 的zzzzzz中
			len++;
		}  
		else if (wchar >=0x800 && wchar < 0xFFFF)  //可以转换成3个字节的pOutput字符
		{  
			pOutput[len] = 0xe0 | ((wchar >> 12)&0x0f);  //高四位填入1110xxxx 10yyyyyy 10zzzzzz中的xxxx
			len++;
			pOutput[len] = 0x80 | ((wchar >> 6) & 0x3f);  //中间6位填入1110xxxx 10yyyyyy 10zzzzzz中的yyyyyy
			len++;
			pOutput[len] = 0x80 | (wchar & 0x3f);  //低6位填入1110xxxx 10yyyyyy 10zzzzzz中的zzzzzz
			len++;
		}  
 
		else //对于其他字节数的unicode字符不进行处理
		{
			return -1;
		}
		pInput ++;//处理下一个unicode字符
	}
	//utf8字符串后面，有个\0
	pOutput [len]= 0;
	return len;  
}  
/********************************************
@Function name;                int Utf8ToUnicode(char* pInput, char* pOutput)
@Function description;        utf-8转unicode 
@Function input;	            
@Function output;	            
@Date;		
*********************************************/
/**********FUNTCTION NOTICE********
* 将UTF8编码转换成Unicode（UCS-2LE）编码  低地址存低位字节
* 参数：
*    char* pInput     输入字符串
*    char*pOutput   输出字符串
* 返回值：转换后的Unicode字符串的字节数，如果出错则返回-1
**************************/
//utf8转unicode
int Utf8ToUnicode(char* pInput, char* pOutput)
{
	int outputSize = 0; //记录转换后的Unicode字符串的字节数
 
	while (*pInput)
	{
		if (*pInput > 0x00 && *pInput <= 0x7F) //处理单字节UTF8字符（英文字母、数字）
		{
			*pOutput = *pInput;
			 pOutput++;
			*pOutput = 0; //小端法表示，在高地址填补0
		}
		else if (((*pInput) & 0xE0) == 0xC0) //处理双字节UTF8字符
		{
			char high = *pInput;
			pInput++;
			char low = *pInput;
			if ((low & 0xC0) != 0x80)  //检查是否为合法的UTF8字符表示
			{
				return -1; //如果不是则报错
			}
 
			*pOutput = (high << 6) + (low & 0x3F);
			pOutput++;
			*pOutput = (high >> 2) & 0x07;
		}
		else if (((*pInput) & 0xF0) == 0xE0) //处理三字节UTF8字符
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
			*pOutput = (middle << 6) + (low & 0x3F);//取出middle的低两位与low的低6位，组合成unicode字符的低8位
			pOutput++;
			*pOutput = (high << 4) + ((middle >> 2) & 0x0F); //取出high的低四位与middle的中间四位，组合成unicode字符的高8位
		}
		else //对于其他字节数的UTF8字符不进行处理
		{
			return -1;
		}
		pInput ++;//处理下一个utf8字符
		pOutput ++;
		outputSize += 2;
	}
	//unicode字符串后面，有两个\0
	*pOutput = 0;
	 pOutput++;
	*pOutput = 0;
	return outputSize;
}

