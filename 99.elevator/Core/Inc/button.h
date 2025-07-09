#include "main.h"

#define BTN0 0  //pc0
#define BTN1  1  //pc1
#define BTN2  2  //pc2
#define BTN3  3  //pc3
#define BTN4  4  //pc13 demo bd

#define BUTTON_NUMBER 5

#define BUTTON_PRESS 0 //active low
#define BUTTON_RELEASE 1// button을 뗀 상태이다

#define GPIOC_ODR 0x40020810

int get_button(GPIO_TypeDef *GPIO,int GPIO_Pin,int button_num);
void button_led_toggle_test(void);
