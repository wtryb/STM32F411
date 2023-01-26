/**************************************
&File Name:     LCD_ST7735S
&Author:        �����
&date:          2023.1.10

++++++
+NOTE+
++++++
1.8��TFT-LCD ST7735s��Ļ��������������Ӳ������SPI������ʽ�� 
**************************************/

#ifndef __LCD_ST7735s_H_
#define __LCD_ST7735s_H_

#include "SYSTEM.h"
#include "MODEL.h"

/***********************USE_SIM_SPI****************************/
#define USE_SIM_SPI 0   //�Ƿ�ʹ�����SPI

#if USE_SIM_SPI

#define SPI_SIM_SCL_PORT    GPIOB
#define SPI_SIM_SCL_PIN     GPIO_PIN_10

#define SPI_SIM_SDA_PORT    GPIOB
#define SPI_SIM_SDA_PIN     GPIO_PIN_15

#define LCD_SCLK_0() HAL_GPIO_WritePin(SPI_SIM_SCL_PORT,SPI_SIM_SCL_PIN, GPIO_PIN_RESET)//SCL=SCLK
#define LCD_SCLK_1() HAL_GPIO_WritePin(SPI_SIM_SCL_PORT,SPI_SIM_SCL_PIN, GPIO_PIN_SET)

#define LCD_MOSI_0() HAL_GPIO_WritePin(SPI_SIM_SDA_PORT,SPI_SIM_SDA_PIN, GPIO_PIN_RESET)//SDA=MOSI
#define LCD_MOSI_1() HAL_GPIO_WritePin(SPI_SIM_SDA_PORT,SPI_SIM_SDA_PIN, GPIO_PIN_SET)

#endif
/***************************************************/

/***********************DC RES BL CS PIN DEFINE****************************/
#define LCD_BL_Pin          GPIO_PIN_0
#define LCD_BL_GPIO_Port    GPIOB

#define LCD_DC_Pin          GPIO_PIN_1
#define LCD_DC_GPIO_Port    GPIOB

#define LCD_RES_Pin         GPIO_PIN_2
#define LCD_RES_GPIO_Port   GPIOB

#define LCD_CS_Pin          GPIO_PIN_8
#define LCD_CS_GPIO_Port    GPIOA


#define LCD_DC_0()              HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET)
#define LCD_DC_1()              HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET)

#define LCD_CS_0()              HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define LCD_CS_1()              HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)

#define LCD_RES_0()             HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET)
#define LCD_RES_1()             HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET)

#define LCD_BLK_1()             HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET)
#define LCD_BLK_0()             HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_RESET)
/***************************************************/

#define USE_HORIZONTAL 1 
#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif              

/***********************COLOR DEFINE****************************/
//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

/***************************************************/

/**********************CMD DEFINE*****************************/
#define LCD_CMD_SLEEPIN     0x10    //˯�߿�
#define LCD_CMD_SLEEPOUT    0x11    //˯�߹�
#define LCD_CMD_PTLON       0x12    //������ʾģʽ��
#define LCD_CMD_NORON       0x13    //��ͨ(ȫ��)��ʾģʽ��
#define LCD_CMD_INVOFF      0x20    //��ɫģʽ��
#define LCD_CMD_INVON       0x21    //��ɫģʽ��
#define LCD_CMD_GAMSET      0x26    //*٤���������ã����=����/٤��������ֵ������й�
#define LCD_CMD_DISPOFF     0x28    //��ʾ�أ����ָ���ı���ʾ�����ڵ����ݣ�����ı�����״̬��ˢ��������ֱ��Ϣ��
#define LCD_CMD_DISPON      0x29    //��ʾ��
#define LCD_CMD_CASET       0x2A    //�����е�ַ�����淢�����ֽ����ݣ�MV=0��Χ0-127��MV=1��Χ0-159
#define LCD_CMD_RASET       0x2B    //�����е�ַ�����淢�����ֽ����ݣ�MV=0��Χ0-159��MV=1��Χ0-127
#define LCD_CMD_RAMWR       0x2C    //дRAM������������д��RAM��ſ���ʾ���ϵ�֮��RAM������Ϊ�������Ӳ��λ���������RAM�ڵ�ֵ
#define LCD_CMD_RGBSET      0x2D    //*������ɫģʽ��4K��65K��262K
#define LCD_CMD_RAMHD       0x2E    //*���������ݣ���ʼ��ַ��MADCTL���õĲ�ͬ
#define LCD_CMD_PTLAR       0x30    //���ò�����ʾ����ʾ���򣬺��淢�����ֽ����ݣ�1st2nd��ʼ��3rd4th�����У�
                                    //-If End Row > Start Row, when MADCTL ML=��0��  If End Row > Start Row, when MADCTL ML=��1��
                                    //��ʾ����ΪPSL[0:7]��PEL[0:7]
                                    //-If End Row < Start Row, when MADCTL ML=��0��
                                    //��ʾ����Ϊ������PEL[0:7]�Լ��ײ���PSL[0:7]��������ʾ����ΪPEL[0:7]��PSL[0:7]
#define LCD_CMD_SCRLAR      0x33    //������ʾ��ֱ�������򣬽�ֻ�����ò�ִ�д�ֱ���������淢�����ֽ����ݣ���MADCTR B4=0
                                    //1st��2nd�������ö����̶����򣬴ӻ������ʾ��������ʼ�㣬���Ƕ������趨��ֵ
                                    //3rd��4th�������ù�������߶ȣ�����Ϊ���������
                                    //5th��6th�������õײ��̶����򣬴ӻ������ʾ��������ʼ�㣬���ǵײ����趨��ֵ
                                    //��ֱ����ģʽ�£�MADCTR��MV=0
#define LCD_CMD_MADCTL      0x36    //���û���Ķ�д���򣬺��淢��һ�ֽ�����
                                    //D7            D6          D5          D4                  D3              D2    -    -
                                    //MY            MX          MV          ML                  RGB             MH
                                    //�е�ַ˳��   �е�ַ˳��  ��/�н���   ��ֱˢ��˳��       RGB-BGR˳��     ˮƽˢ��˳��
                                    //ǰ��λ����MCU�Ի���Ķ�д����        LCD��ֱˢ�·���                     
                                    //                                      0:�ϵ��£�1:�µ��� 0:RGB��1:BGR     0:���ң�1:�ҵ���
#define LCD_CMD_VSCSAD      0x37    //���������LCD_CMD_SCRLARһ���ã����������˴�ֱ��������͹���ģʽ�����淢�����ֽ����ݣ���һ���ֽ�Ϊ0x00������һ�ֽ�Ϊ����
                                    //�ò�������֡�洢���е���һ�н���д����ʾ�������̶��������һ��֮��ĵ�һ�У����ָ��Ὺʼ������������ʾģʽ�²�����
#define LCD_CMD_IDMOFF		0x38	//*IDLEģʽ��	
#define LCD_CMD_IDMON		0x39	//*IDLEģʽ��
#define LCD_CMD_COLMOD		0x3A	//����RGBģʽ�����淢��һ�ֽ����ݣ�D2/D1/D0 011-12bit 101-16bit 110-18bit 111-no

/***************************************************/

/*********************Screen Properties Define******************************/
#if LCD_PRO     //�Ƿ���Ҫ��Ļ����(�����)����Ļ����
#define LCD_PRO_V_ODER_U2N  0//�ϵ��µĴ�ֱɨ��˳��Ҳ�ǼĴ���д��˳��
#define LCD_PRO_V_ODER_D2P  1//�µ��ϵĴ�ֱɨ��˳��Ҳ�ǼĴ���д��˳��
#define LCD_PRO_H_ODER_L2R  0//���ҵ�ˮƽɨ��˳��Ҳ�ǼĴ���д��˳��
#define LCD_PRO_H_ODER_R2L  1//�ҵ����ˮƽɨ��˳��Ҳ�ǼĴ���д��˳��
#define LCD_PRO_RGB_MODE    0
#define LCD_PRO_BGR_MODE    1
/***************************************************/

/**************************PRV VAB*************************/
//��Ļ���ԣ����Զ���һ��ȫ�ֱ����������ȡ��Ļ���ԡ�
typedef struct LCD_1In8_Screen
{
    unsigned char LCD_Width;    //��Ļ��
    unsigned char LCD_Height;   //��Ļ��
    unsigned char RGB_Oder;     //��ɫͨ��˳��RGB����BGR
    unsigned char Dis_Dir;      //��ʾ�����������Ǻ���
    unsigned char Inv_Mode;     //��ɫģʽ
    unsigned char Dis_Mode;     //�ֲ�����ȫ����ʾ
    unsigned char V_Oder;       //��ֱ����ˢ��ģʽ
    unsigned char H_Oder;       //ˮƽ����ˢ��ģʽ

}   LCD_1In8_Screen;
#endif
/***************************************************/


/***********************FUN INFRE****************************/
#if USE_SIM_SPI 
void LCD_SIM_SPI_GPIO_Init(void);

void LCD_Writ_Bus(unsigned char dat);
void LCD_WR_DATA(unsigned char dat);
void LCD_WR_DATA8(unsigned char dat);
void LCD_WR_REG(unsigned char dat);
#endif
/***************************************************/
void LCD_SPI_Send_Cmd(unsigned char data); //����ָ��
void LCD_SPI_Send_Data_8(unsigned char data);//���Ͱ�λ����
void LCD_SPI_Send_Data_16(unsigned int data);//����ʮ��λ����
void LCD_Address_Set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);//���üĴ�������
void LCD_Init(void);  //LCD��Ӳ����ʼ��

void LCD_Fill(unsigned int  xsta,unsigned int  ysta,unsigned int  xend,unsigned int  yend,unsigned int  color);//ָ����ɫ���һ������
void LCD_DrawPoint(unsigned int x,unsigned int y,unsigned int color);
/***************************************************/


#endif                            
