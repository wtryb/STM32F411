#ifndef __W25Q64_H_
#define __W25Q64_H_

/***************************PIN DEFINE************************/
#define W25Q64_CS_PORT                  GPIO_Pin_4
#define W25Q64_CS_Gpio_Pin              GPIOA

#define W25Q64_SCK_PORT                 GPIO_Pin_5
#define W25Q64_SCK_Gpio_Pin             GPIOA

#define W25Q64_MOSI_PORT                GPIO_Pin_7
#define W25Q64_MOSI_Gpio_Pin            GPIOA

#define W25Q64_MISO_PORT                GPIO_Pin_6
#define W25Q64_MISO_Gpio_Pin            GPIOA
/************************CMD DEFINE***************************/

#define W25Q64_CMD_WRITE_ENABLE         0x06        //Ð´Ê¹ÄÜ
#define W25Q64_CMD_WRITE_DIABLE         0x04        //Ð´½ûÖ¹

#define W25Q64_CMD_READ_STATUS          0x05        //¶Á×´Ì¬¼Ä´æÆ÷
#define W25Q64_CMD_WRITE_STATUS         0x01        //Ð´×´Ì¬¼Ä´æÆ÷

#define W25Q64_CMD_READ_DATA            0x03        //¶ÁÊý¾Ý
#define W25Q64_CMD_READ_FDATA           0x0B        //¿ì¶ÁÊý¾Ý
#define W25Q64_CMD_READ_FDDATA          0x3B        //¿ì¶ÁË«Êä³öÊý¾Ý

#define W25Q64_CMD_WRITE_DATA           0x02        //Ò³±à³Ì

#define W25Q64_CMD_ERASE_BLOCK          0xD8        //¿é²Á³ý
#define W25Q64_CMD_ERASE_SECTOR         0x20        //ÉÈÇø²Á³ý
#define W25Q64_CMD_ERASE_CHIP           0xC7        //Ð¾Æ¬²Á³ý
#define W25Q64_CMD_POWRER_OFF           0xB9        //µôµç

#define W25Q64_CMD_READ_ID1             0xAB        //ÊÍ·Åµôµç/Æ÷¼þID
#define W25Q64_CMD_READ_ID2             0x90        //ÖÆÔì/Æ÷¼þ ID
#define W25Q64_CMD_READ_ID3             0x9F        //JEDEC ID

/***************************************************/


typedef struct
{
	unsigned int FLASH_ID;
	unsigned int FLASH_SIZE;
	unsigned int SECTOR_COUNT;
	unsigned int SECTOR_SIZE;
	unsigned int SUBSECTOR_COUNT;
	unsigned int SUBSECTOR_SIZE;
	unsigned int PAGE_SIZE;
}W25Qx_Parameter;





#endif 
