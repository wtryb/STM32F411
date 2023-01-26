/**************************************
&File Name:     LCD_ST7735S
&Author:        李泽枫
&date:          2023.1.10

++++++
+NOTE+
++++++
1.8寸TFT-LCD ST7735s屏幕的驱动，包含软硬件两种SPI驱动方式。 
**************************************/

#ifndef __LCD_ST7735s_H_
#define __LCD_ST7735s_H_

#include "SYSTEM.h"
#include "MODEL.h"

/***********************USE_SIM_SPI****************************/
#define USE_SIM_SPI 0   //是否使用软件SPI

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
//画笔颜色
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
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色
#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

/***************************************************/

/**********************CMD DEFINE*****************************/
#define LCD_CMD_SLEEPIN     0x10    //睡眠开
#define LCD_CMD_SLEEPOUT    0x11    //睡眠关
#define LCD_CMD_PTLON       0x12    //部分显示模式开
#define LCD_CMD_NORON       0x13    //普通(全屏)显示模式开
#define LCD_CMD_INVOFF      0x20    //反色模式关
#define LCD_CMD_INVON       0x21    //反色模式开
#define LCD_CMD_GAMSET      0x26    //*伽马曲线设置，输出=输入/伽马，和像素值的输出有关
#define LCD_CMD_DISPOFF     0x28    //显示关，这个指令不会改变显示缓存内的内容，不会改变其他状态，刷白屏不是直接息屏
#define LCD_CMD_DISPON      0x29    //显示开
#define LCD_CMD_CASET       0x2A    //设置列地址，后面发送两字节数据，MV=0范围0-127，MV=1范围0-159
#define LCD_CMD_RASET       0x2B    //设置行地址，后面发送两字节数据，MV=0范围0-159，MV=1范围0-127
#define LCD_CMD_RAMWR       0x2C    //写RAM，将像素数据写进RAM后才可显示，上电之后RAM内数据为随机，软硬复位都不会清除RAM内的值
#define LCD_CMD_RGBSET      0x2D    //*设置颜色模式，4K、65K、262K
#define LCD_CMD_RAMHD       0x2E    //*读缓存数据，开始地址和MADCTL设置的不同
#define LCD_CMD_PTLAR       0x30    //设置部分显示的显示区域，后面发送四字节数据，1st2nd开始行3rd4th结束列，
                                    //-If End Row > Start Row, when MADCTL ML=’0’  If End Row > Start Row, when MADCTL ML=’1’
                                    //显示区域为PSL[0:7]到PEL[0:7]
                                    //-If End Row < Start Row, when MADCTL ML=’0’
                                    //显示区域为顶部到PEL[0:7]以及底部到PSL[0:7]，即不显示区域为PEL[0:7]到PSL[0:7]
#define LCD_CMD_SCRLAR      0x33    //设置显示垂直滚动区域，仅只是设置不执行垂直滚动，后面发送六字节数据，当MADCTR B4=0
                                    //1st和2nd数据设置顶部固定区域，从缓存和显示器顶部开始算，就是顶部到设定的值
                                    //3rd和4th数据设置滚动区域高度，计算为缓存的行数
                                    //5th和6th数据设置底部固定区域，从缓存和显示器顶部开始算，就是底部到设定的值
                                    //垂直滚动模式下，MADCTR的MV=0
#define LCD_CMD_MADCTL      0x36    //设置缓存的读写方向，后面发送一字节数据
                                    //D7            D6          D5          D4                  D3              D2    -    -
                                    //MY            MX          MV          ML                  RGB             MH
                                    //行地址顺序   列地址顺序  行/列交换   垂直刷新顺序       RGB-BGR顺序     水平刷新顺序
                                    //前三位设置MCU对缓存的读写方向        LCD垂直刷新方向                     
                                    //                                      0:上到下，1:下到上 0:RGB，1:BGR     0:左到右，1:右到左
#define LCD_CMD_VSCSAD      0x37    //这个命令与LCD_CMD_SCRLAR一起用，两者设置了垂直滚动区域和滚动模式，后面发送两字节数据，第一个字节为0x00，后面一字节为参数
                                    //该参数描述帧存储器中的哪一行将被写入显示器顶部固定区域最后一行之后的第一行，这个指令会开始滚动，部分显示模式下不可用
#define LCD_CMD_IDMOFF		0x38	//*IDLE模式关	
#define LCD_CMD_IDMON		0x39	//*IDLE模式开
#define LCD_CMD_COLMOD		0x3A	//设置RGB模式，后面发送一字节数据，D2/D1/D0 011-12bit 101-16bit 110-18bit 111-no

/***************************************************/

/*********************Screen Properties Define******************************/
#if LCD_PRO     //是否需要屏幕对象(类对象)对屏幕定义
#define LCD_PRO_V_ODER_U2N  0//上到下的垂直扫描顺序，也是寄存器写入顺序
#define LCD_PRO_V_ODER_D2P  1//下到上的垂直扫描顺序，也是寄存器写入顺序
#define LCD_PRO_H_ODER_L2R  0//左到右的水平扫描顺序，也是寄存器写入顺序
#define LCD_PRO_H_ODER_R2L  1//右到左的水平扫描顺序，也是寄存器写入顺序
#define LCD_PRO_RGB_MODE    0
#define LCD_PRO_BGR_MODE    1
/***************************************************/

/**************************PRV VAB*************************/
//屏幕属性，可以定义一个全局变量，方便获取屏幕属性。
typedef struct LCD_1In8_Screen
{
    unsigned char LCD_Width;    //屏幕宽
    unsigned char LCD_Height;   //屏幕高
    unsigned char RGB_Oder;     //颜色通道顺序，RGB还是BGR
    unsigned char Dis_Dir;      //显示方向，竖屏还是横屏
    unsigned char Inv_Mode;     //反色模式
    unsigned char Dis_Mode;     //局部还是全局显示
    unsigned char V_Oder;       //垂直方向刷新模式
    unsigned char H_Oder;       //水平方向刷新模式

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
void LCD_SPI_Send_Cmd(unsigned char data); //发送指令
void LCD_SPI_Send_Data_8(unsigned char data);//发送八位数据
void LCD_SPI_Send_Data_16(unsigned int data);//发送十六位数据
void LCD_Address_Set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);//设置寄存器窗口
void LCD_Init(void);  //LCD的硬件初始化

void LCD_Fill(unsigned int  xsta,unsigned int  ysta,unsigned int  xend,unsigned int  yend,unsigned int  color);//指定颜色填充一块区域
void LCD_DrawPoint(unsigned int x,unsigned int y,unsigned int color);
/***************************************************/


#endif                            
