#include "sys.h"
#include "tim13.h"
void TIM13_Init(uint32_t arr,uint32_t psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);
	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
//	GPIO_PinAFConfig(GPIOF, GPIO_PinSource8, GPIO_AF_TIM13);	
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_TIM13);
//	GPIO_PinAFConfig(GPIOF, GPIO_PinSource10, GPIO_AF_TIM14);	
	//	GPIO_PinAFConfig(GPIOF, GPIO_Pin_9, GPIO_AF_TIM14);	//º¯ÊýµÚ¶þ¸öÊµ²Îµ÷ÓÃ´íÎó¡£
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
//		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;

		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

//	GPIO_Init(GPIOF, &GPIO_InitStruct);
		GPIO_Init(GPIOA, &GPIO_InitStruct);

	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;	
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = arr;


	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseInitStruct);

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC1Init(TIM13, &TIM_OCInitStruct);
	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM13, ENABLE);

	TIM_Cmd(TIM13, ENABLE);


}

