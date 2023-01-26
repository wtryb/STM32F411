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

#define W25Q64_CMD_WRITE_ENABLE         0x06        //дʹ��
#define W25Q64_CMD_WRITE_DIABLE         0x04        //д��ֹ

#define W25Q64_CMD_READ_STATUS          0x05        //��״̬�Ĵ���
#define W25Q64_CMD_WRITE_STATUS         0x01        //д״̬�Ĵ���

#define W25Q64_CMD_READ_DATA            0x03        //������
#define W25Q64_CMD_READ_FDATA           0x0B        //�������
#define W25Q64_CMD_READ_FDDATA          0x3B        //���˫�������

#define W25Q64_CMD_WRITE_DATA           0x02        //ҳ���

#define W25Q64_CMD_ERASE_BLOCK          0xD8        //�����
#define W25Q64_CMD_ERASE_SECTOR         0x20        //��������
#define W25Q64_CMD_ERASE_CHIP           0xC7        //оƬ����
#define W25Q64_CMD_POWRER_OFF           0xB9        //����

#define W25Q64_CMD_READ_ID1             0xAB        //�ͷŵ���/����ID
#define W25Q64_CMD_READ_ID2             0x90        //����/���� ID
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
