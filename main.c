#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "tim13.h"
#include "tim14.h"
//ALIENTEK ̽����STM32F407������ ʵ��8
//PWM���ʵ��-�⺯���汾
int main(void)
{ 
	uint16_t led0pwmval = 0;
	uint16_t led1pwmval = 0;
	uint8_t dir0 = 1;
	uint8_t dir1 = 1;	
/*  TIM14��ʾ-ͨ��LED0��ʾЧ��
		TIM13��ʾ-ͨ��LED1��ʾЧ������ѯ�����ֲ�TIM13_CH1ͨ��PA6�����ͨ���Ű�������PF10,PF10�Ǻ�LED1���ӵģ�   */

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);
	//LED_Init();				//��ʼ��LED�˿�
	TIM14_Init(500-1,84-1);//����ֵ499����Ƶֵ83
	TIM13_Init(500-1,84-1);//����ֵ499����Ƶֵ83
	while(1)
	{
		delay_ms(10);//��ʱ200ms
		//TIM14��Ԥ����ֵ
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
		//TIM13��Ԥ����ֵ
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
  		TIM_SetCompare1(TIM14, led0pwmval);//��Ԥ����ֵled0pwmvalд��TIM14_CCR1�Ĵ���
			TIM_SetCompare1(TIM13, led1pwmval);//��Ԥ����ֵled1pwmvalд��TIM13_CCR1�Ĵ���
	}
}
