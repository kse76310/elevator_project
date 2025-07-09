#include "button.h"


int get_button(GPIO_TypeDef *GPIO,int GPIO_Pin,int button_num)  //버튼 읽는 함수 (index 넘버, 버튼핀 번호)
{
	static unsigned char button_status[BUTTON_NUMBER] =
	{BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE,BUTTON_RELEASE};
	//지역변수에 static을 쓰면 전역변수처럼 함수를 빠져나갔다 들어와도 값이 유지된다
	int current_state;

	//current_state=HAL_GPIO_ReadPin(GPIO, GPIO_Pin);
				current_state=(*(unsigned int*)GPIOC_ODR>>button_num)&1;


	// 버튼을 읽는다
	if (current_state==BUTTON_PRESS&& button_status[button_num]==BUTTON_RELEASE)				//버튼이 처음 눌려진 상태
	{
		HAL_Delay(30);
		button_status[button_num]=BUTTON_PRESS;								// noise가 지나간 상태의 high 상태
		return BUTTON_RELEASE;															//아직은 완전히 눌렸다 떼어진 상태가 아니다
	}
	else if (current_state==BUTTON_RELEASE && button_status[button_num]==BUTTON_PRESS)
	{
		HAL_Delay(30);
		button_status[button_num]=BUTTON_RELEASE;
		return BUTTON_PRESS;

	}

	return BUTTON_RELEASE;  //버튼이 open 상태


}

void button_led_toggle_test(void)
{
	static int button_state0=0;
	static int button_state1=0;
	static int button_state2=0;
	static int button_state3=0;
	if (get_button(GPIOC,GPIO_PIN_0,BTN0)==BUTTON_PRESS)
		{
			button_state0=!button_state0;
			if(button_state0)
				*(unsigned int*)0x40020414|=0x01<<BTN0;
			else
				*(unsigned int*)0x40020414&=~(0x01<<BTN0);
		}

	if (get_button(GPIOC,GPIO_PIN_1,BTN1)==BUTTON_PRESS)
		{
			button_state1=!button_state1;
			if(button_state1)
				*(unsigned int*)0x40020414|=0x01<<BTN1;
			else
				*(unsigned int*)0x40020414&=~(0x01<<BTN1);
		}

	if (get_button(GPIOC,GPIO_PIN_2,BTN2)==BUTTON_PRESS)
		{
			button_state2=!button_state2;
			if(button_state2)
				*(unsigned int*)0x40020414|=0x01<<BTN2;
			else
				*(unsigned int*)0x40020414&=~(0x01<<BTN2);
		}

	if (get_button(GPIOC,GPIO_PIN_3,BTN3)==BUTTON_PRESS)
		{
			button_state3=!button_state3;
			if(button_state3)
				*(unsigned int*)0x40020414|=0x01<<BTN3;
			else
				*(unsigned int*)0x40020414&=~(0x01<<BTN3);
		}




}

