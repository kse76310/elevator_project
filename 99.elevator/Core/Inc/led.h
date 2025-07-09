#include "main.h"

void led_all_on(void);
void led_all_off(void);
void led_main(void);
void shift_left_ledon(void);
 void shift_right_ledon(void);
 void shift_left_keep_ledon(void);
 void shift_right_keep_ledon(void);
void flower_on(void);
void flower_off(void);


#define GPIOB_ODR 0x40020414
#define LATCH_HIGH() (GPIOA->ODR |= (1 << 7))
#define LATCH_LOW()  (GPIOA->ODR &= ~(1 << 7))
#define CLOCK_HIGH() (GPIOC->ODR |= (1 << 5))
#define CLOCK_LOW()  (GPIOC->ODR &= ~(1 << 5))
#define DATA_HIGH()  (GPIOC->ODR |= (1 << 4))
#define DATA_LOW()   (GPIOC->ODR &= ~(1 << 4))



