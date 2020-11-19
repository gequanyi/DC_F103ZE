#include "myiic.h"
#include "gpio.h"



void MPU_IIC_Delay(void)
{
	__nop();__nop();__nop();
	__nop();__nop();__nop();
}


void IIC_Init(void)
{
	MX_GPIO_Init();
}

void IIC_Start(void)      //������ʼ�ź�
{
	SDA_OUT();
	IIC_SDA_1;
	IIC_SCL_1;
	MPU_IIC_Delay();
	IIC_SDA_0;
	MPU_IIC_Delay();
	IIC_SCL_0;
}

void IIC_Stop(void)   //����ֹͣ�ź�
{
	SDA_OUT();
	IIC_SCL_0;
	IIC_SDA_0;
	MPU_IIC_Delay();
	IIC_SCL_1; IIC_SDA_1;
	MPU_IIC_Delay();
}

uint8_t IIC_Wait_Ack(void)   //�ȴ�Ӧ���źŵ�����1��Ӧ��ʧ�ܣ�0��Ӧ��ɹ�
{
	uint8_t time=0;
	SDA_IN();
	IIC_SDA_1; MPU_IIC_Delay();
	IIC_SCL_1; MPU_IIC_Delay();
	while(READ_SDA)
	{
		time++;
		if(time>250)
		{
			IIC_Stop();
			return 1;
		}
			
	}
	IIC_SCL_0;
	return 0;
		
}

void IIC_Ack(void)   //����ACKӦ��
{
	IIC_SCL_0;SDA_OUT();
	IIC_SDA_0;  MPU_IIC_Delay();
	IIC_SCL_1;  MPU_IIC_Delay();
	IIC_SCL_0;
}

void IIC_NAck(void)    //������ACKӦ��
{
	IIC_SCL_0;
	SDA_OUT();
	IIC_SDA_1; MPU_IIC_Delay();
	IIC_SCL_1; MPU_IIC_Delay();
	IIC_SCL_0;
}


void IIC_Send_Byte(uint8_t txd)  //����һ���ֽ�
{
	uint8_t t;
	SDA_OUT();
	IIC_SCL_0;  //����ʱ�ӿ�ʼ��������
	for(t=0;t<8;t++)
	{
		if(txd&0x80)
		{
			IIC_SDA_1;
		}
		else
		{
			IIC_SDA_0;
		}
		txd<<=1;
		MPU_IIC_Delay();    
		IIC_SCL_1;  MPU_IIC_Delay();
		IIC_SCL_0;  MPU_IIC_Delay();
	}
}


uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
	for(i=0;i<8;i++)
	{
		IIC_SCL_0;  MPU_IIC_Delay();
		IIC_SCL_1;
		receive<<=1;
		if(READ_SDA) 
		{
			receive++;
		}
		MPU_IIC_Delay();
	}
	if(!ack)   IIC_NAck();
	else IIC_Ack();
	return receive;
}
