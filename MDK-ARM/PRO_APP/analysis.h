#ifndef __analysis_H_
#define __analysis_H_

char *Find_JSON_From_Buffer(const char *srcStr);

char *Gett_Address_cJSON(char *srcStr);

/*�ߵ�API�·���������utf-8����
 *sscom��ʾ����ΪGBK����
 *lvgl֧��utg-8����
 *��������Ҫunicode���롣������
 ����ļ�Ӧ����utf-8����������Ҫת��Ϊunicode���룬��Ҫ��sscom��������Ҫת��ΪGBK
*/
int UnicodeToUtf8(char* pInput, char *pOutput);
int Utf8ToUnicode(char* pInput, char* pOutput);


#endif 
