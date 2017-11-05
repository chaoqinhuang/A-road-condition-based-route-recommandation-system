#include "pwm.h"

/*---------------------------------------------------------
函数说明：开启定时器TIM2，1MS中断一次
-----------------------------------------------------------*/
u16 TIME_1MS=0;
u16 TIME_5MS=0;
u16 TIME_10MS=0;
u16 TIME_100MS=0;

void TIM2_Int_Init(u16 arr,u16 psc)  //中断时间间隔：T = （arr+1）* （psc+1） / 72000000 s
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM2初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //从优先级2级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}
//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIME_1MS = (TIME_1MS > 100) ? 0 : TIME_1MS++;
		TIME_5MS = (TIME_5MS > 100) ? 0 : TIME_5MS++;
		TIME_10MS++;
		TIME_100MS++;
		//TIME_10MS =(TIME_10MS >100) ? 0 : TIME_10MS++;
		//TIME_100MS=(TIME_100MS>100) ? 0 : TIME_100MS++;
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
	}
}

/*---------------------------------------------------------
函数说明：开启定时器TIM3，用于计算超声波测距时间
-----------------------------------------------------------*/
u16 cnt=0;

void TIM3_Int_Init(u16 arr,u16 psc)  //中断时间间隔：T = （arr+1）* （psc+1） / 72000000 s
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx					 
}
//定时器3中断服务程序
void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志 
			
		}
}

/*---------------------------------------------------------
函数说明：开启定时器TIM4，硬件输出PWM波
-----------------------------------------------------------*/
void TIM4_PWM_Init(u16 arr,u16 ch1,u16 ch2,u16 ch3,u16 ch4)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器4时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟

	if(ch1)
		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_6; //PB4输出pwm
	if(ch2)
		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_7; //PB5输出pwm
	if(ch3)			
		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_8; //PB0输出pwm
	if(ch4)
		GPIO_InitStructure.GPIO_Pin |= GPIO_Pin_9; //PB1输出pwm

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO

   //初始化TIM4
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = 71; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	
	//初始化TIM4 Channel1 PWM模式
	if(ch1){
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC1
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	}
	//初始化TIM4 Channel2 PWM模式	
	if(ch2){
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC2
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	}
	//初始化TIM4 Channel3 PWM模式	 
	if(ch3){
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	}
	//初始化TIM4 Channel4 PWM模式	 
	if(ch4){
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC4
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
	}
	
	TIM_Cmd(TIM4, ENABLE);  //使能TIM4
	
	if(ch1) TIM_SetCompare1(TIM4,0);
	if(ch2) TIM_SetCompare2(TIM4,0);
	if(ch3) TIM_SetCompare3(TIM4,0);
	if(ch4) TIM_SetCompare4(TIM4,0);
}

void TIM4_PWM_Set(u16 p1,u16 p2,u16 p3,u16 p4)
{
	TIM_SetCompare1(TIM4,p1);
	TIM_SetCompare2(TIM4,p2);
	TIM_SetCompare3(TIM4,p3);
	TIM_SetCompare4(TIM4,p4);
}

void Motor_Set(int p1,int p2,int p3,int p4)
{
	if(p1<1)	p1 = 0;
	if(p2<1)	p2 = 0;
	if(p3<1)	p3 = 0;
	if(p4<1)	p4 = 0;
	if(p1>600)	p1 = 600;
	if(p2>600)	p2 = 600;
	if(p3>600)	p3 = 600;
	if(p4>600)	p4 = 600;
	
	TIM_SetCompare1(TIM4,p1+1000);
	TIM_SetCompare2(TIM4,p2+1000);
	TIM_SetCompare3(TIM4,p3+1000);
	TIM_SetCompare4(TIM4,p4+1000);
}

void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)  //检查TIM4更新中断发生与否
		{
			TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIM4更新中断标志 
		}
}
