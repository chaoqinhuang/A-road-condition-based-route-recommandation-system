#include "sys.h"
#include "math.h"            	
float Pitch,Roll,Yaw;
int tmp;
u8 rank_v,rank_h;
short aacX,aacY,aacZ;
short Xi,Yi,Zi;
void para_init(void);
void sys_init(void);
void task_10ms(void);

int main(void)
{	 
	sys_init();
	MPU_Get_Accelerometer(&aacX,&aacY,&aacZ);
	Zi = aacZ;
 	while(1)
	{
		if(TIME_100MS >= 100){
			TIME_100MS=0;
			mpu_dmp_get_data(&Pitch,&Roll,&Yaw);
			MPU_Get_Accelerometer(&aacX,&aacY,&aacZ);
			
			tmp = abs(aacZ-Zi)/1000;
			if(tmp > 9) rank_v = 9;
			else if(tmp > 8) rank_v = 8;
			else if(tmp > 7) rank_v = 7;
			else if(tmp > 6) rank_v = 6;
			else if(tmp > 5) rank_v = 5;
			else if(tmp > 4) rank_v = 4;
			else if(tmp > 3) rank_v = 3;
			else if(tmp > 2) rank_v = 2;
			else if(tmp > 1) rank_v = 1;
			else rank_v = 0;
			tmp = abs(aacX-Xi)/1000;
			if(tmp > 9) rank_h = 9;
			else if(tmp > 8) rank_h = 8;
			else if(tmp > 7) rank_h = 7;
			else if(tmp > 6) rank_h = 6;
			else if(tmp > 5) rank_h = 5;
			else if(tmp > 4) rank_h = 4;
			else if(tmp > 3) rank_h = 3;
			else if(tmp > 2) rank_h = 2;
			else if(tmp > 1) rank_h = 1;
			else rank_h = 0;
			
					
			rank_v = '0' + rank_v;
			rank_h = '0' + rank_h;
			while((USART2->SR&0X40)==0);  
			USART2->DR = rank_v; 
			while((USART2->SR&0X40)==0);  
			USART2->DR = rank_h; 
			//NRF_TX();
		}
	} 
}

void task_10ms()
{
	mpu_dmp_get_data(&Pitch,&Roll,&Yaw);
}


void para_init()
{
	Pitch = Roll = Yaw = 0.0;
}

void sys_init()
{
	para_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();										//��ʱ��ʼ�� 
	LED_Init();                    						 //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	KEY_Init();                    						 //=====������ʼ��
	uart_init(128000);           						//=====��ʼ������1
	uart2_init(36,9600);            					//=====����2��ʼ��	
	MPU_Init();											//��ʼ��MPU6050
	while(mpu_dmp_init()) delay_ms(400);				//�ȴ�MPU��ʼ��
	TIM2_Int_Init(999,71);								//1ms�жϿ���
	//NRF24L01_Init();                					//=====NRF24L01ģ���ʼ��
	//NRF24L01_FindMyself();          					//=====NRF24L01�Լ���� ûͨ��(û�н�����ģ��)��������������
	//TX_Mode();											//��Ϊ����ģʽ
}


