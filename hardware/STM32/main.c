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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();										//延时初始化 
	LED_Init();                    						 //=====初始化与 LED 连接的硬件接口
	KEY_Init();                    						 //=====按键初始化
	uart_init(128000);           						//=====初始化串口1
	uart2_init(36,9600);            					//=====串口2初始化	
	MPU_Init();											//初始化MPU6050
	while(mpu_dmp_init()) delay_ms(400);				//等待MPU初始化
	TIM2_Int_Init(999,71);								//1ms中断开启
	//NRF24L01_Init();                					//=====NRF24L01模块初始化
	//NRF24L01_FindMyself();          					//=====NRF24L01自检程序 没通过(没有接无线模块)就死在这是闪灯
	//TX_Mode();											//设为发送模式
}


