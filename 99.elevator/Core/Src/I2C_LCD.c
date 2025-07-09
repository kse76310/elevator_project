#include "main.h"
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>
#include "i2c_lcd.h"

extern I2C_HandleTypeDef hi2c1;

void i2c_lcd_main(void);
void i2c_lcd_init(void);

#define I2C_LCD_ADDRESS (0x27 << 1)
unsigned char lcd_test[4] = { '4','3', 0 };

// I2C 시작 조건 생성
void I2C_Start(void) {
    I2C1->CR1 |= I2C_CR1_START; // Start 조건 생성
    while (!(I2C1->SR1 & I2C_SR1_SB)); // Start 비트가 설정될 때까지 대기
}

// I2C 주소 전송
void I2C_Address(uint8_t address) {
    I2C1->DR = address; // 슬레이브 주소 전송
    while (!(I2C1->SR1 & I2C_SR1_ADDR)); // 주소 전송 완료 대기
    (void)I2C1->SR2; // SR2 읽기 (클리어)
}

// I2C 데이터 전송
void I2C_Write(uint8_t data) {
    I2C1->DR = data; // 데이터 전송
    while (!(I2C1->SR1 & I2C_SR1_TXE)); // 데이터 전송 완료 대기
}

// I2C 정지 조건 생성
void I2C_Stop(void) {
    I2C1->CR1 |= I2C_CR1_STOP; // Stop 조건 생성
}

// LCD 명령 전송
void lcd_command(uint8_t command) {
    uint8_t high_nibble, low_nibble;
    high_nibble = command & 0xF0;
    low_nibble = (command << 4) & 0xF0;

    I2C_Start();
    I2C_Address(I2C_LCD_ADDRESS);
    I2C_Write(high_nibble | 0x04 | 0x08); // en=1, rs=0, rw=0, backlight=1
    I2C_Write(high_nibble | 0x00 | 0x08); // en=0, rs=0, rw=0, backlight=1
    I2C_Write(low_nibble | 0x04 | 0x08); // en=1, rs=0, rw=0, backlight=1
    I2C_Write(low_nibble | 0x00 | 0x08); // en=0, rs=0, rw=0, backlight=1
    I2C_Stop();
    osDelay(2); // 명령 실행 시간
}

// LCD 데이터 전송
void lcd_data(uint8_t data) {
    uint8_t high_nibble, low_nibble;
    high_nibble = data & 0xF0;
    low_nibble = (data << 4) & 0xF0;

    I2C_Start();
    I2C_Address(I2C_LCD_ADDRESS);
    I2C_Write(high_nibble | 0x05 | 0x08); // en=1, rs=1, rw=0, backlight=1
    I2C_Write(high_nibble | 0x01 | 0x08); // en=0, rs=1, rw=0, backlight=1
    I2C_Write(low_nibble | 0x05 | 0x08); // en=1, rs=1, rw=0, backlight=1
    I2C_Write(low_nibble | 0x01 | 0x08); // en=0, rs=1, rw=0, backlight=1
    I2C_Stop();
    osDelay(2); // 데이터 전송 시간
}

// LCD 초기화
void i2c_lcd_init(void) {
    lcd_command(0x33);
    lcd_command(0x32);
    lcd_command(0x28); // Function Set 4-bit mode
    lcd_command(DISPLAY_ON);
    lcd_command(0x06); // Entry mode set
    lcd_command(CLEAR_DISPLAY);
    osDelay(2);
}

// 문자열 출력
void lcd_string(uint8_t* str) {
    while (*str) {
        lcd_data(*str++);
    }
}

// 커서 이동
void move_cursor(uint8_t row, uint8_t column) {
    lcd_command(0x80 | (row << 6) | column);
}

// 메인 함수
void i2c_lcd_main(void) {
    static uint8_t value = 0;



        move_cursor(0, 0);
        lcd_string((uint8_t*)"Hello World!!!");
        move_cursor(1, 0);
        lcd_data(value + '0');
        value++;
        if (value > 9) value = 0;

}
