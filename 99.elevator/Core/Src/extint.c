#include "extint.h"
#include "stepmotor.h"
#include "extern.h"



 void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	 switch(GPIO_Pin){
	        case GPIO_PIN_0: current_floor = 0; break;
	        case GPIO_PIN_1: current_floor = 1; break;
	        case GPIO_PIN_2: current_floor = 2;  break;
	        case GPIO_PIN_4: current_floor = 3; break;
	      }
}
