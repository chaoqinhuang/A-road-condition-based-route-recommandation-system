#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

extern u16 TIME_1MS;
extern u16 TIME_5MS;
extern u16 TIME_10MS;
extern u16 TIME_100MS;

void TIM4_Int_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 ch1,u16 ch2,u16 ch3,u16 ch4);
void TIM4_PWM_Set(u16 p1,u16 p2,u16 p3,u16 p4);
void Motor_Set(int p1,int p2,int p3,int p4);
void TIM2_Int_Init(u16 arr,u16 psc);
void TIM3_Int_Init(u16 arr,u16 psc);
#endif
