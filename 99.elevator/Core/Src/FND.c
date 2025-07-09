#include "FND.h"
void shift_register_init(void) {
//    // GPIO 클럭 활성화
//    __HAL_RCC_GPIOB_CLK_ENABLE();
//    __HAL_RCC_GPIOC_CLK_ENABLE();
//
//    // Shift 레지스터 핀 설정
//    GPIO_InitTypeDef GPIO_InitStruct = {0};
//    GPIO_InitStruct.Pin = SHIFT_DATA_PIN | SHIFT_CLOCK_PIN | SHIFT_LATCH_PIN;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(SHIFT_GPIO_PORT, &GPIO_InitStruct);
//
//    // 디스플레이 선택 핀 설정
   //GPIO_InitStruct.Pin = DISPLAY1_PIN | DISPLAY2_PIN | DISPLAY3_PIN | DISPLAY4_PIN;
    //HAL_GPIO_Init(DISPLAY_GPIO_PORT, &GPIO_InitStruct);

    // 초기 상태 설정
    HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_DATA_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_CLOCK_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_LATCH_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY1_PIN | DISPLAY2_PIN | DISPLAY3_PIN | DISPLAY4_PIN, GPIO_PIN_RESET);
}

// Shift 레지스터에 데이터 전송
void shift_register_write(uint8_t data) {
    for (int i = 0; i < 8; i++) {
        HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_DATA_PIN, (data & (0x80 >> i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_CLOCK_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_CLOCK_PIN, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_LATCH_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(SHIFT_GPIO_PORT, SHIFT_LATCH_PIN, GPIO_PIN_RESET);
}

// 7세그먼트 데이터 (공통 캐소드 기준)
const uint8_t segment_map[10] = {
    0b10100000, // 0
    0b11111001, // 1
    0b11000100, // 2
    0b11010000, // 3
    0b10011001, // 4
    0b10010010, // 5
    0b10000010, // 6
    0b11111000, // 7
    0b10000000, // 8
    0b10001110  // 9
};

// 특정 디스플레이에 숫자 표시
void fnd_display_digit(uint8_t digit, uint8_t display_index) {
    // 모든 디스플레이 끄기
	shift_register_init();
    HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY1_PIN | DISPLAY2_PIN | DISPLAY3_PIN | DISPLAY4_PIN, 0);

    // 데이터 전송
    shift_register_write(segment_map[digit]);
    osDelay(2);
    // 선택된 디스플레이 켜기
    switch (display_index) {
        case 0: HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY1_PIN, GPIO_PIN_SET); break;
        case 1: HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY2_PIN, GPIO_PIN_SET); break;
        case 2: HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY3_PIN, GPIO_PIN_SET); break;
        case 3: HAL_GPIO_WritePin(DISPLAY_GPIO_PORT, DISPLAY4_PIN, GPIO_PIN_SET); break;




    }
}

// 4자리 숫자 표시
void fnd_display_number(uint16_t number) {
    uint8_t digits[4] = {
        (number / 1000) % 10, // 천의 자리
        (number / 100) % 10,  // 백의 자리
        (number / 10) % 10,   // 십의 자리
        number % 10           // 일의 자리
    };

    for (int i = 0; i < 4; i++) {
        fnd_display_digit(digits[i], 4);
        HAL_Delay(3); // 디스플레이 스캐닝 딜레이
    }
}

// 메인 함수
void fnd_main(uint8_t number) {
    // Shift 레지스터 초기화
    fnd_display_digit(number, 2);
    osDelay(2);
    fnd_display_digit(9, 3);
    osDelay(2);




}
