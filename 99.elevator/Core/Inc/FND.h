#include "main.h"


#include "stm32f4xx_hal.h"



// Shift 레지스터 핀 정의
#define SHIFT_DATA_PIN GPIO_PIN_11  // 데이터 입력 핀
#define SHIFT_CLOCK_PIN GPIO_PIN_12 // 클럭 핀
#define SHIFT_LATCH_PIN GPIO_PIN_10 // 래치 핀
#define SHIFT_GPIO_PORT GPIOC      // GPIO 포트

// 디스플레이 선택 핀 정의
#define DISPLAY1_PIN GPIO_PIN_4
#define DISPLAY2_PIN GPIO_PIN_5
#define DISPLAY3_PIN GPIO_PIN_6
#define DISPLAY4_PIN GPIO_PIN_7
#define DISPLAY_GPIO_PORT GPIOB

// 함수 프로토타입
void shift_register_init(void);
void shift_register_write(uint8_t data);
void fnd_display_digit(uint8_t digit, uint8_t display_index);
void fnd_display_number(uint16_t number);


