#ifndef __MYIIC_H
#define __MYIIC_H
#include "main.h"

#define SDA_IN() 	{GPIOB->CRH&=(uint32_t)0XFFFF0FFF;GPIOB->CRH|=(uint32_t)8<<12;}
#define SDA_OUT()	 {GPIOB->CRH&=(uint32_t)0XFFFF0FFF;GPIOB->CRH|=(uint32_t)3<<12;}

#define IIC_SDA PBout(9)
#define IIC_SCL PBout(8)

#define IIC_SDA_1  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_SET)
#define IIC_SDA_0  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_11,GPIO_PIN_RESET)
#define IIC_SCL_1  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_SET)
#define IIC_SCL_0  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_10,GPIO_PIN_RESET)

#define READ_SDA   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)


void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);


uint8_t IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);

void IIC_Send_Byte(uint8_t txd);
uint8_t IIC_Read_Byte(unsigned char ack);


#endif
