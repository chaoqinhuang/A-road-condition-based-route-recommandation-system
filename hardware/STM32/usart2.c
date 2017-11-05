
#include "usart2.h"


/**************************************************************************
函数功能：串口2初始化
入口参数：pclk2:PCLK2 时钟频率(Mhz)    bound:波特率
返回  值：无
**************************************************************************/
void uart2_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				                 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
	mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB1ENR|=1<<17;  //使能串口时钟 
	GPIOA->CRL&=0XFFFF00FF; 
	GPIOA->CRL|=0X00008B00;//IO状态设置
	GPIOA->ODR|=1<<2;	  
	RCC->APB1RSTR|=1<<17;   //复位串口1
	RCC->APB1RSTR&=~(1<<17);//停止复位	   	   
	//波特率设置
 	USART2->BRR=mantissa; // 波特率设置	 
	USART2->CR1|=0X200C;  //1位停止,无校验位.
	//使能接收中断
	USART2->CR1|=1<<8;    //PE中断使能
	USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(0,1,USART2_IRQn,2);//组2
}

/**************************************************************************
函数功能：串口2接收中断
入口参数：无
返回  值：无
**************************************************************************/
void USART2_IRQHandler(void)
{	
	if(USART2->SR&(1<<5))//接收到数据
	{	  
		int Usart3_Receive;//蓝牙接收相关变量
//		static u8 Flag_PID,i,j,Receive[50];
//		static float tg;
//		static float kp,ki,kd;
//		static u16 Data;
		Usart3_Receive=USART2->DR; 
		if(Usart3_Receive=='a') LED0 = ~LED0;
//		
////		if(Usart3_Receive=='A') {M1=M1+10;M2=M2+10;M3=M3+10;M4=M4+10;}
////		if(Usart3_Receive=='E') {M1=M1-10;M2=M2-10;M3=M3-10;M4=M4-10;}
////		if(Usart3_Receive=='G') OLED_ShowString(0,20,"L!");
////		if(Usart3_Receive=='C') OLED_ShowString(0,20,"R!");
//		
//		if(Usart3_Receive=='a') test_flag = 1;							//开始调试
//		if(Usart3_Receive=='b') {};										//保持联络
//		if(Usart3_Receive=='c') {test_flag = 0;Motor_Set(0,0,0,0);}		//停止调试
//		if(Usart3_Receive=='d') PID_Send=1; 							//获取参数
//		if(Usart3_Receive=='e') Flash_Send=1;							//保存参数
////		if(Usart3_Receive=='f') OLED_ShowString(0,20,"f!");
////		if(Usart3_Receive=='g') OLED_ShowString(0,20,"g!");
////		if(Usart3_Receive=='h') OLED_ShowString(0,20,"h!");
////		if(Usart3_Receive=='i') OLED_ShowString(0,20,"i!");
//		
//		if(Usart3_Receive==0x7B) Flag_PID=1;  //指令起始位
//		if(Usart3_Receive==0x7D) Flag_PID=2;  //指令停止位
//		
//		if(Flag_PID==1)                      //记录参数
//		{
//			Receive[i]=Usart3_Receive;
//			i++;
//		}
//		if(Flag_PID==2)   //执行
//		{
//			if(Receive[3]==0x50) 	       PID_Send=1;     //获取设备参数
//			else  if(Receive[3]==0x57) 	 Flash_Send=1;   //掉电保存参数
//			else  if(Receive[1]!=0x23)                    //更新PID参数
//			{								
//				for(j=i;j>=4;j--)
//				{
//					Data+=(Receive[j-1]-0x30)*pow(10,i-j);
//				}
//				switch(Receive[1])
//				{
//					case 0x30:  tg=(float)Data/10;break;
//					case 0x31:  kp=(float)Data/10;break;
//					case 0x32:  ki=(float)Data/10;break;
//					case 0x33:  kd=(float)Data/10;break;
//					case 0x34:  throttle=(int)Data;break;
//					case 0x35:  break;
//					case 0x36:  break;
//					case 0x37:  break;
//					case 0x38:  break;
//				}
//				//PID_X_SetPo(tg-50);
//				PID_X_Set(kp,ki,kd);
//			}				 
//			Flag_PID=0;   //相关标志位清零
//			i=0;
//			j=0;
//			Data=0;	
//			if(Flash_Send==1)          //写入PID参数到Flash,由app控制该指令
//			{
//				Flash_Write();	
//				Flash_Send=0;	
//			}
//		 } 
//		lose_control = 0;		
	}  											 
} 

