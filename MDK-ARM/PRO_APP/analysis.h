#ifndef __analysis_H_
#define __analysis_H_

char *Find_JSON_From_Buffer(const char *srcStr);

char *Gett_Address_cJSON(char *srcStr);

/*高德API下发的数据是utf-8编码
 *sscom显示中文为GBK编码
 *lvgl支持utg-8编码
 *发短信需要unicode编码。。。。
 因此文件应采用utf-8，短信则需要转换为unicode编码，需要用sscom调试则需要转换为GBK
*/
int UnicodeToUtf8(char* pInput, char *pOutput);
int Utf8ToUnicode(char* pInput, char* pOutput);


#endif 
