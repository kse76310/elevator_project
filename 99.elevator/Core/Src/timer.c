#include "timer.h"
#include "extern.h"
//1MHZ의 주파수가 TIM2에 공급
//T=1/f  0.000001 sec
//1us *1000 ==> 1ms
void delay_us(int us)
{

	//timer 2번의 counter reset

	__HAL_TIM_SET_COUNTER(&htim2,0);

	//사용자가 지정한 시간만큼 wait
	while(__HAL_TIM_GET_COUNTER(&htim2)<us)
		; //no operation


}
