#include "tim.h"
#include "led.h"
#include "delay.h"
#include "bee.h"
void TIM3_Init(uint16_t arr, uint16_t psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; //定义一个结构体变量TIM_BaseInitStructure，用于配置定时器的基本参数。
	NVIC_InitTypeDef NVIC_InitStructure;   //定义一个结构体变量NVIC_InitStructure，用于配置中断。
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //使能TIM3定时器的时钟,将其挂载到APB1总线上
	
  TIM_TimeBaseInitStructure.TIM_Period = arr-1;  //设置定时器的周期,由中断时间与时钟周期还有重载数和预分频值得出
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc-1;  //设置预分频值,由中断时间与时钟周期还有重载数和预分频值得出
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //设置计数器模式为向上计数。
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 	//设置时钟分频因子。
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//使用上面设置的参数初始化TIM4定时器。
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //设置中断源为TIM3定时器。
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //设置抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //设置子优先级。
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //使能中断。
	NVIC_Init(&NVIC_InitStructure); //使用上面设置的参数初始化中断
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //使能TIM3定时器的更新中断。
	TIM_Cmd(TIM3,ENABLE);  //使能TIM3定时器。
	

}

int tm_sec=0;
void TIM3_IRQHandler(void)//每过一秒，标志位加1
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		tm_sec++;
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  
}

