#include "led.h"
#include "extern.h"

// GPIO 핀 제어 매크로

// Shift 레지스터에 데이터를 전송하는 함수
void shift_led_write(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        // 데이터 비트 전송
        if (data & (1 << (7 - i))) {
            GPIOC->ODR|= (1 << 4);
        } else {
        	GPIOC->ODR &= ~(1 << 4);
        }

        // 클럭 펄스 생성
        GPIOC->ODR |= (1 << 5);
        osDelay(1); // 클럭 신호 유지 시간
        GPIOC->ODR &= ~(1 << 5);
    }

    // 래치 신호로 출력 고정
    GPIOA->ODR |= (1 << 7);
    osDelay(1);
    GPIOA->ODR &= ~(1 << 7);
}

// 모든 LED를 켜는 함수
void led_all_on(void) {
    shift_led_write(0xFF); // 모든 비트를 1로 설정
}

// 모든 LED를 끄는 함수
void led_all_off(void) {
    shift_led_write(0x00); // 모든 비트를 0으로 설정
}

// LED를 왼쪽으로 이동하며 켜는 함수
void shift_left_ledon(void)
{
	static uint8_t i = 0;
    if(led_time>=100){
    i++;
    i%=8;
    led_time=0;
    }
        shift_led_write(1 << i);
}


// LED를 오른쪽으로 이동하며 켜는 함수
void shift_right_ledon(void)
{
	static uint8_t i = 0;
	  if(led_time>=100){
	    i++;
	    i%=8;
	    led_time=0;
	    }
	        shift_led_write(1 << (7-i));

}


// LED를 왼쪽으로 이동하며 켜고 유지하는 함수
void shift_left_keep_ledon(void) {
    uint8_t led = 0;
    for (int i = 0; i < 8; i++) {
        led |= (1 << i);
        shift_led_write(led);
        HAL_Delay(100);
    }
}

// LED를 오른쪽으로 이동하며 켜고 유지하는 함수
void shift_right_keep_ledon(void) {
    uint8_t led = 0;
    for (int i = 0; i < 8; i++) {
        led |= (1 << (7 - i));
        shift_led_write(led);
        HAL_Delay(100);
    }
}

// 꽃 모양으로 LED를 켜는 함수
void flower_on(void) {
    uint8_t led = 0;
    for (int i = 0; i < 5; i++) {
        led = (1 << (3 + i)) | (1 << (4 - i));
        shift_led_write(led);
        HAL_Delay(200);
    }
}

// 꽃 모양으로 LED를 끄는 함수
void flower_off(void) {
    uint8_t led = 0xFF;
    for (int i = 0; i < 4; i++) {
        led &= ~((1 << (7 - i)) | (1 << i));
        shift_led_write(led);
        HAL_Delay(200);
    }
}

void led_main(void){
	if(motor_state==0)
		led_all_on();
	else if(motor_state==1)
	shift_right_ledon();
	else if (motor_state==2)
	shift_left_ledon();




}
