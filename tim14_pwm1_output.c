#include "sys.h"
#include "tim14.h"
#include "led.h"
#include "usart.h"


void TIM14_Init(uint32_t arr,uint32_t psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);//¿ªÆôTIM14Ê±ÖÓ
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);//¿ªÆôGPIOÊ±ÖÓ

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);//ÅäÖÃPF9¸´ÓÃ¹¦ÄÜAF9(TIM14)	
																													//PF9Êä³öÁ¬½ÓLED0
//	GPIO_PinAFConfig(GPIOF, GPIO_PinSource10, GPIO_AF_TIM14);	
	//	GPIO_PinAFConfig(GPIOF, GPIO_Pin_9, GPIO_AF_TIM14);	//º¯ÊýµÚ¶þ¸öÊµ²Îµ÷ÓÃ´íÎó¡£
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;//Ñ¡ÔñÒª¿ØÖÆµÄÒý½ÅPF9
//		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;//Ä£Ê½ÉèÖÃÎª¸´ÓÃÄ£Ê½

	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;//ÉèÖÃÒý½ÅËÙÂÊÎª100MZ
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;//ÉèÖÃÒý½ÅÄ£Ê½ÎªÍ¨ÓÃÍÆÍìÊä³ö
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;//ÉÏÀ­µç×è

	GPIO_Init(GPIOF, &GPIO_InitStruct);//µ÷ÓÃ¿âº¯Êý£¬³õÊ¼»¯GPIO²ÎÊý

	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;	//Ê±ÖÓÔ¤·ÖÆµÖµ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//¶¨Ê±Æ÷ÏòÉÏ¼ÆÊý
	TIM_TimeBaseInitStruct.TIM_Period = arr;//×Ô¶¯ÖØ×°ÔØ¼Ä´æÆ÷ÖÜÆÚµÄÖµ£¨¼ÆÊýÖµ£©


	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//Ê±ÖÓ·ÖÆµÒò×Ó
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);//µ÷ÓÃ¿âº¯Êý£¬³õÊ¼»¯TIM²ÎÊý

	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;//ÉèÖÃTIM14_CCMR1Ä£Ê½ÎªTIM_OCMode_PWM1
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//ÉèÖÃTIM14_CCER×îµÍÎ»ÖÃ1£¬Ê¹ÄÜÊä³ö
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;//¶¨Ê±Æ÷TIM14_CNT<TIM14_CCR1ÖµÊ±£¬Êä³öµÍµçÆ½
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);//Ê¹ÄÜÍ¨µÀCH1
	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);//Ê¹ÄÜÔ¤×°ÔØ
	TIM_ARRPreloadConfig(TIM14, ENABLE);//Ê¹ÄÜTIM14ÖØ×°ÔØ¼Ä´æÆ÷ARR

	TIM_Cmd(TIM14, ENABLE);//Ê¹ÄÜ¶¨Ê±Æ÷ÍâÉè

}



