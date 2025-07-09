#include "keypad.h"

GPIO_TypeDef* keypadRowPort[4] = {GPIOC, GPIOC, GPIOC, GPIOC}; //R1~R4
GPIO_TypeDef* keypadColPort[4] = {GPIOC, GPIOC, GPIOC, GPIOC}; //C1~C4
uint16_t keypadRowPin[4] = {GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_6, GPIO_PIN_7}; //R1~R4 GPIO Input & Pull-up으로 설정을 해야 한다.
uint16_t keypadColPin[4] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11}; //C1~C4  GPIO Output으로만 설정 한다.


void keypadInit()
{
	for(uint8_t col = 0; col < 4; col++)
	{
		HAL_GPIO_WritePin(keypadColPort[col], keypadColPin[col], SET); //초기 값 1로 셋팅
	}
}

uint8_t getKeypadState(uint8_t col, uint8_t row)
{
#if 0
	uint8_t keypadChar[4][4] = {
			{'/', '3', '2', '1'},
			{'*', '6', '5', '4'},
			{'-', '9', '8', '7'},
			{'+', '=', '0', ' '},
	};

#else
	uint8_t keypadChar[4][4] = {
			{'1', '4', '7', ' '},
			{'2', '5', '8', '0'},
			{'3', '6', '9', '='},
			{'+', '-', '*', '/'},
	};
#endif
	static uint8_t prevState[4][4] = {
			{1, 1, 1, 1},
			{1, 1, 1, 1},
			{1, 1, 1, 1},
			{1, 1, 1, 1},
	};
	uint8_t curState = 1;

	HAL_GPIO_WritePin(keypadColPort[col], keypadColPin[col], RESET);
	curState = HAL_GPIO_ReadPin(keypadRowPort[row], keypadRowPin[row]);

	HAL_GPIO_WritePin(keypadColPort[col], keypadColPin[col], SET);

	if(curState == PUSHED && prevState[col][row] == RELEASED)
	{
		prevState[col][row] = curState;
		return 0;
	}
	else if (curState == RELEASED && prevState[col][row] == PUSHED)
	{
		prevState[col][row] = curState;
		return keypadChar[col][row];
	}
	return 0;
}

uint8_t keypadScan()
{
	uint8_t data;

	for(uint8_t col=0; col<4; col++)
	{
		for(uint8_t row=0; row<4; row++)
		{
			data = getKeypadState(col, row);
			if(data != 0)
			{
				return data;
			}
		}
	}
	return 0;
}





int calculator(uint8_t first_num, uint8_t second_num,uint8_t calc) {
    // 아스키 값을 정수로 변환
    int digit1 = first_num - '0';
    int digit2 = second_num - '0';
    int result;

    // 연산자에 따라 연산 수행
    switch (calc) {
        case '+':
            result = digit1 + digit2;
            break;
        case '-':
            result = digit1 - digit2;
            break;
        case '*':
            result = digit1 * digit2;
            break;
        case '/':
            if (digit2 == 0) {
                printf("Error: Division by zero\n");
                return -1; // 오류 코드 반환
            }
            result = digit1 / digit2;
            break;
        default:
            printf("Error: Invalid operator\n");
            return -1; // 오류 코드 반환
    }

    return result;
}

void simple_calc(){

	printf("connected\n");
	  while(1){
		  	  	  uint8_t first_num;
		  		  uint8_t second_num;
		  		  uint8_t calc;

		  static uint8_t calc_state=0;
		  if(!queue_empty())
		  	  {
		  		  if(calc_state==0){
		  			 first_num= read_queue();
		  			 printf("num1:%c\n",first_num);
		  		  }

		  		  else if(calc_state==1){
		  			 calc= read_queue();
		  			 printf("operator :%c\n",calc);
		  		  }

		  		  else if(calc_state==2)
		  		  {
		  			  second_num =read_queue();
		  			printf("num2 :%c\n",second_num);
		  		  }
		  		  else if(calc_state==3&&read_queue()=='=')
		  			printf("%c %c %c= %d\n",first_num,calc,second_num, calculator(first_num,second_num,calc));



		  		  calc_state++;
		  		  calc_state%=4;


		  	  }
	  }
}









