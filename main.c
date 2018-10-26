#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "tim13.h"
#include "tim14.h"
//ALIENTEK 探索者STM32F407开发板 实验8
//PWM输出实验-库函数版本
int main(void)
{ 
	uint16_t led0pwmval = 0;
	uint16_t led1pwmval = 0;
	uint8_t dir0 = 1;
	uint8_t dir1 = 1;	
/*  TIM14表示-通过LED0显示效果
		TIM13表示-通过LED1显示效果（查询数据手册TIM13_CH1通过PA6输出，通过杜邦线连接PF10,PF10是和LED1连接的）   */

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);
	//LED_Init();				//初始化LED端口
	TIM14_Init(500-1,84-1);//重载值499，分频值83
	TIM13_Init(500-1,84-1);//重载值499，分频值83
	while(1)
	{
		delay_ms(10);//延时200ms
		//TIM14的预重载值
		if(dir0 == 1)
		{
			led0pwmval++;		
		}
		else
		{
			led0pwmval--;		
		}
		if(led0pwmval > 300)
		{
			dir0 = 0;
		}			
		if (led0pwmval == 0)
		{
			dir0 = 1;
		}
		//TIM13的预重载值
		if(dir1 == 1)
		{
			led1pwmval++;			
		}
		else
		{
			led1pwmval--;			
		}

		if(led1pwmval > 100)
		{
			dir1 = 0;		
		}

		if(led1pwmval == 0)
		{
			dir1 = 1;		
		}
  		TIM_SetCompare1(TIM14, led0pwmval);//将预重载值led0pwmval写入TIM14_CCR1寄存器
			TIM_SetCompare1(TIM13, led1pwmval);//将预重载值led1pwmval写入TIM13_CCR1寄存器
	}
}
