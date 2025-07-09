#include "main.h"
#include "ds1302.h"

#define COMMAND_NUMBER 20
#define COMMAND_LENGTH 40
volatile uint8_t rx_buff[COMMAND_NUMBER][COMMAND_LENGTH];   // uart0로 부터 들어온 문자를 저장 하는 버퍼(변수)
volatile int rear=0;
volatile int front=0;
void pc_command_processing(void);

