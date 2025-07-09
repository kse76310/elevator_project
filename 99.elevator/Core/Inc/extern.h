#include "button.h"


extern uint8_t rx_data;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim2;
extern volatile TIM11_1ms_counter;
extern volatile int buzzer_timer;
extern volatile int led_time;
extern t_print o_prt;


extern void led_main(void);
extern void button_led_toggle_test(void);
extern void ds1302_main(void);

extern void pc_command_processing(void);
extern void delay_us(int us);


extern void dht_test(void);
extern void flash_main();
extern void flash_set_time(void);
extern int flash_check();
extern void buzzer_main();
extern servo_motor_main(void);
extern void i2c_lcd_main(void);
extern void dotmatrix_main_test();
extern int dotmatrix_main_func(void);
extern int dotmatrix_main(void);

extern int queue_empty(void);
extern int queue_full(void);
extern void insert_queue(unsigned char value);
extern unsigned char read_queue();
extern uint8_t keypadScan();
extern void keypadInit();
extern int calculator(uint8_t first_num, uint8_t second_num,uint8_t calc);
extern void simple_calc();
extern void stepmotor_main(void);
extern void fnd_main(uint8_t number);
extern void buzzer_dingdong(void);

extern volatile int motor_state;
extern volatile uint8_t current_floor;
