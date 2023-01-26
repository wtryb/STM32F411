/**************************************
&File Name: LCD_ST7735s.c
&Author:    李泽枫
&date:      2023.1.10

+++++++
+NOTE+
+++++++

**************************************/
#include "LCD_ST7735s.h"
#include "SYSTEM.h"
#include "MODEL.h"


#if USE_SIM_SPI
void LCD_SIM_SPI_GPIO_Init(void)
{
      GPIO_InitTypeDef GPIO_InitStruct = {0};
    
      __HAL_RCC_GPIOB_CLK_ENABLE();
    
      /*Configure GPIO pins : PBPin PBPin PBPin */
  GPIO_InitStruct.Pin = SPI_SIM_SDA_PIN|SPI_SIM_SCL_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void LCD_Writ_Bus(unsigned char dat)
{
    unsigned char i;
	LCD_CS_0();
	for(i=0;i<8;i++)
	{			  
		LCD_SCLK_0();
		if(dat&0x80)
		{
		   LCD_MOSI_1();
		}
		else
		{
		   LCD_MOSI_0();
		}
		LCD_SCLK_1();
		dat<<=1;
	}	
  LCD_CS_1();	
}

void LCD_WR_DATA(unsigned char dat)
{
    LCD_Writ_Bus(dat>>8);
	LCD_Writ_Bus(dat);
}

void LCD_WR_DATA8(unsigned char dat)
{
    LCD_Writ_Bus(dat);
}

void LCD_WR_REG(unsigned char dat)
{
    LCD_DC_0();//写命令
	LCD_Writ_Bus(dat);
	LCD_DC_1();//写数据
}

void LCD_SPI_Send_Cmd(unsigned char CMD)
{
    LCD_WR_REG(CMD);
}

void LCD_SPI_Send_Data_8(unsigned char data)
{
    LCD_WR_DATA8(data);
}

void LCD_SPI_Send_Data_16(unsigned int data)
{
    LCD_WR_DATA(data);
}
#else
/********************************************
@Function name;             void LCD_SPI_Send_Cmd(unsigned char CMD)
@Function description;      LCD发送指令
@Function input;
@Function output;
@Date;
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void LCD_SPI_Send_Cmd(unsigned char CMD)
{   
    LCD_CS_0();
    LCD_DC_0();  
    HAL_SPI_Transmit(&hspi2, &CMD, 1, 0xffff);
    LCD_CS_1();  
   // HAL_Delay(1);
}

/********************************************
@Function name;		    void LCD_SPI_Send_Data_8(unsigned char data)
@Function description;	发送八位数据
@Function input;		
@Function output;		
@Date;			
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void LCD_SPI_Send_Data_8(unsigned char data)
{
    LCD_CS_0();
    LCD_DC_1();
    HAL_SPI_Transmit(&hspi2, &data, 1, 0xffff);
    LCD_CS_1();
   // HAL_Delay(1);
}

/********************************************
@Function name;		   void LCD_SPI_Send_Data_16(unsigned int data) 
@Function description;	发送十六位数据
@Function input;		
@Function output;		
@Date;			
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void LCD_SPI_Send_Data_16(unsigned int data)
{
    LCD_SPI_Send_Data_8(data >> 8);
    LCD_SPI_Send_Data_8(data);
}
#endif

/********************************************
@Function name;		    void LCD_Address_Set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
@Function description;	设置LCD窗口坐标
@Function input;		
@Function output;		
@Date;			
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void LCD_Address_Set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	LCD_SPI_Send_Cmd(0x2a);//列地址设置
    LCD_SPI_Send_Data_8(0x00);
	LCD_SPI_Send_Data_8(x1);
    LCD_SPI_Send_Data_8(0x00);
	LCD_SPI_Send_Data_8(x2);
    
	LCD_SPI_Send_Cmd(0x2b);//行地址设置
    LCD_SPI_Send_Data_8(0x00);
	LCD_SPI_Send_Data_8(y1);
    LCD_SPI_Send_Data_8(0x00);
	LCD_SPI_Send_Data_8(y2);
    
	LCD_SPI_Send_Cmd(0x2c);//储存器写
}

/********************************************
@Function name;		    void LCD_Init()
@Function description;	LCD的硬件初始化
@Function input;		
@Function output;		
@Date;			
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void LCD_Init(void)
{
#if USE_SIM_SPI
    LCD_SIM_SPI_GPIO_Init();
#endif
	LCD_RES_0();//复位
	HAL_Delay(100);
	LCD_RES_1();
	HAL_Delay(100);
	
	LCD_BLK_1();//打开背光
    HAL_Delay(100);
	
	//************* Start Initial Sequence **********//
	LCD_SPI_Send_Cmd(0x11); //Sleep out 
	HAL_Delay(120);              //Delay 120ms 
	//------------------------------------ST7735S 帧率设置-----------------------------------------// 
	LCD_SPI_Send_Cmd(0xB1); 
	LCD_SPI_Send_Data_8(0x01); 
	LCD_SPI_Send_Data_8(0x2C); 
	LCD_SPI_Send_Data_8(0x2D); 
	LCD_SPI_Send_Cmd(0xB2); 
	LCD_SPI_Send_Data_8(0x01);
	LCD_SPI_Send_Data_8(0x2C); 
	LCD_SPI_Send_Data_8(0x2D); 
	LCD_SPI_Send_Cmd(0xB3); 
	LCD_SPI_Send_Data_8(0x01); 
	LCD_SPI_Send_Data_8(0x2C); 
	LCD_SPI_Send_Data_8(0x2D); 
	LCD_SPI_Send_Data_8(0x01); 
	LCD_SPI_Send_Data_8(0x2C); 
	LCD_SPI_Send_Data_8(0x2D); 
	//------------------------------------End ST7735S Frame Rate---------------------------------// 
	LCD_SPI_Send_Cmd(0xB4); //Dot inversion 
	LCD_SPI_Send_Data_8(0x07); 
	//------------------------------------ST7735S 功率设置---------------------------------// 
	LCD_SPI_Send_Cmd(0xC0); 
	LCD_SPI_Send_Data_8(0xA2); 
	LCD_SPI_Send_Data_8(0x02); 
	LCD_SPI_Send_Data_8(0x84); 
	LCD_SPI_Send_Cmd(0xC1); 
	LCD_SPI_Send_Data_8(0xC5); 
	LCD_SPI_Send_Cmd(0xC2); 
	LCD_SPI_Send_Data_8(0x0A); 
	LCD_SPI_Send_Data_8(0x00); 
	LCD_SPI_Send_Cmd(0xC3); 
	LCD_SPI_Send_Data_8(0x8A); 
	LCD_SPI_Send_Data_8(0x2A); 
	LCD_SPI_Send_Cmd(0xC4); 
	LCD_SPI_Send_Data_8(0x8A); 
	LCD_SPI_Send_Data_8(0xEE); 
	//---------------------------------End ST7735S Power Sequence-------------------------------------// 
	LCD_SPI_Send_Cmd(0xC5); //VCOM 
	LCD_SPI_Send_Data_8(0x0E); 
	LCD_SPI_Send_Cmd(0x36);//0x00 0x80 0x40 0xc0 0x20 0xA0 0x60 0xE0; 
	LCD_SPI_Send_Data_8(0xc0);

	//------------------------------------ST7735S Gamma Sequence---------------------------------// 
    LCD_SPI_Send_Cmd(0xE0); 
	LCD_SPI_Send_Data_8(0x04); 
	LCD_SPI_Send_Data_8(0x22); 
	LCD_SPI_Send_Data_8(0x07); 
	LCD_SPI_Send_Data_8(0x0A); 
	LCD_SPI_Send_Data_8(0x2E); 
	LCD_SPI_Send_Data_8(0x30); 
	LCD_SPI_Send_Data_8(0x25); 
	LCD_SPI_Send_Data_8(0x2A); 
	LCD_SPI_Send_Data_8(0x28); 
	LCD_SPI_Send_Data_8(0x26); 
	LCD_SPI_Send_Data_8(0x2E); 
	LCD_SPI_Send_Data_8(0x3A); 
	LCD_SPI_Send_Data_8(0x00); 
	LCD_SPI_Send_Data_8(0x01); 
	LCD_SPI_Send_Data_8(0x03); 
	LCD_SPI_Send_Data_8(0x13); 
	LCD_SPI_Send_Cmd(0xE1); 
	LCD_SPI_Send_Data_8(0x04); 
	LCD_SPI_Send_Data_8(0x16); 
	LCD_SPI_Send_Data_8(0x06); 
	LCD_SPI_Send_Data_8(0x0D); 
	LCD_SPI_Send_Data_8(0x2D); 
	LCD_SPI_Send_Data_8(0x26); 
	LCD_SPI_Send_Data_8(0x23); 
	LCD_SPI_Send_Data_8(0x27); 
	LCD_SPI_Send_Data_8(0x27); 
	LCD_SPI_Send_Data_8(0x25); 
	LCD_SPI_Send_Data_8(0x2D); 
	LCD_SPI_Send_Data_8(0x3B); 
	LCD_SPI_Send_Data_8(0x00); 
	LCD_SPI_Send_Data_8(0x01); 
	LCD_SPI_Send_Data_8(0x04); 
	LCD_SPI_Send_Data_8(0x13); 
	//------------------------------------End ST7735S Gamma Sequence-----------------------------// 
	LCD_SPI_Send_Cmd(0x3A); //65k mode 
	LCD_SPI_Send_Data_8(0x05); 
	LCD_SPI_Send_Cmd(0x29); //Display on 
}


/********************************************
@Function name;		void LCD_Fill(unsigned int  xsta,unsigned int  ysta,unsigned int  xend,unsigned int  yend,unsigned int  color)    
@Function description;	指定颜色填充某块区域
@Function input;		
@Function output;		
@Date;			
*********************************************/
/**********FUNTCTION NOTICE********

**************************/
void LCD_Fill(unsigned int  xsta,unsigned int  ysta,unsigned int  xend,unsigned int  yend,unsigned int  color)
{          
	unsigned int i,j; 
	LCD_Address_Set(xsta,ysta,xend,yend);//设置显示范围
	for(i=xsta;i<xend;i++)
	{			
		for(j=ysta;j<yend;j++)
		{
            //printf("j:%d\r\n", j);
			LCD_SPI_Send_Data_16(color);
		}
	} 					  	    
}

void LCD_DrawPoint(unsigned int x,unsigned int y,unsigned int color)
{
	LCD_Address_Set(x,y,x,y);//设置光标位置 
	LCD_SPI_Send_Data_16(color);
} 
