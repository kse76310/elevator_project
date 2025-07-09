#include "main.h"
#include <stdlib.h>

#define HIGH 1
#define LOW  0

uint8_t us_count = 0;
enum state_define
	{OK,
	TIMEOUT,
	VALUE_ERROR,
	TRANS_ERROR};

enum state_define state = OK;

#define DHT_PIN_NUM	0

void init_dht11(void);
int dht11_main(uint8_t* data);
void signal_us_check(int duration, int binary_choice);
int dht11_get_bit(void);



//#define DHT_DDR		DDRG
//#define DHT_PORT		GPIOA->ODR
//#define DHT_PIN		GPIOA->IDR
