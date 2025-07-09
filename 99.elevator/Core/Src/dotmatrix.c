

#include "main.h"
#include "button.h"
#include "extern.h"





#if 1
void dotmatrix_main_test();
void init_dotmatrix(uint8_t array[][8],int num);
int dotmatrix_main(void);
int dotmatrix_main_func(void);


uint8_t col[4]={0,0,0,0};
uint8_t hart[] = {		// hart
	0b00000000,    // hart
	0b01100110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100,
	0b00011000
};

uint8_t number_data[20][10] =
{
		{
		0b00011000,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00011000,
		0b00000001},
	{
		0b00010000,	//1
		0b00110000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00111000,
	    1   // 점 0b00000110
	},
	{
		0b0111000,	//2
		0b01000100,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00100000,
		0b01111100,
	    1
	},
	{
		0b01111100,	//3
	    0b00001000,
		0b00010000,
		0b00001000,
		0b00000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b00001000,	//4
		0b00011000,
		0b00101000,
		0b01001000,
		0b01111100,
		0b00001000,
		0b00001000,
	    1
	},
	{
		0b01111100,	//5
		0b01000000,
		0b01111000,
		0b00000100,
		0b00000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b00011000,	//6
		0b00100000,
		0b01000000,
		0b01111000,
		0b01000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b01111100,	//7
		0b01000100,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00010000,
		0b00010000,
	    1
	},
	{
		0b00111000,	//8
		0b01000100,
		0b01000100,
		0b00111000,
		0b01000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011100,
		0b00000100,
		0b00000100,
		0b00011000,
		0b00000001
	},
	{
		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
	}
};


uint8_t main_data[][8]=
	{
	{0x00,0x18,0x3c,0x7e,0x18,0x18,0x18,0x00}, //up
	{0x00,0x18,0x3c,0x7e,0x18,0x18,0x18,0x00}, //up
	{0x00,0x18,0x3c,0x7e,0x18,0x18,0x18,0x00}, //up
	{0x00,0x18,0x3c,0x7e,0x18,0x18,0x18,0x00}
	};
uint8_t number[][8]={
		{
				0b00010000,	//1
				0b00110000,
				0b00010000,
				0b00010000,
				0b00010000,
				0b00010000,
				0b00111000,
			    1   // 점 0b00000110
			},
			{
				0b0111000,	//2
				0b01000100,
				0b00000100,
				0b00001000,
				0b00010000,
				0b00100000,
				0b01111100,
			    1
			},
			{
				0b01111100,	//3
			    0b00001000,
				0b00010000,
				0b00001000,
				0b00000100,
				0b01000100,
				0b00111000,
			    1
			},
			{
				0b00001000,	//4
				0b00011000,
				0b00101000,
				0b01001000,
				0b01111100,
				0b00001000,
				0b00001000,
			    1
			}
};


unsigned char display_data[8];  // 최종 8x8 출력할 데이터
unsigned char scroll_buffer[50][8] = {0,};  // 스코롤할 데이타가 들어있는 버퍼
int number_of_character = 11;  // 출력할 문자 갯수


void init_dotmatrix(uint8_t array[][8],int num)
{
	for (int i=0; i < 8; i++)
	{
		display_data[i] = array[i];
	}
	for (int i=1; i < num+1; i++)
	{
		for (int j=0; j < 8; j++) // scroll_buffer[0] = blank
		{
			scroll_buffer[i][j] = array[i-1][j];
		}
	}
}



int dotmatrix_main_up(void)
{

	static int count;  // 컬럼 count
	static int index;  // scroll_buffer의 2차원 index값
	static uint32_t past_time;  // 이전 tick값 저장
	static int init=0;

	uint8_t temp;

	if(motor_state !=0&&init==0){
	int count=0;  // 컬럼 count
	int index=0;  // scroll_buffer의 2차원 index값
	uint32_t past_time=0;  // 이전 tick값 저장
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10 |GPIO_PIN_13 | GPIO_PIN_15, 0);
	osDelay(10);

	init_dotmatrix(main_data,4);
	init++;
	}



		uint32_t now = HAL_GetTick();  // 1ms




		// 1.처음시작시 past_time=0; now: 500 --> past_time=500
		if (now - past_time >= 200) // 500ms scroll
		{
			past_time = now;
		if(motor_state ==0)// up
		{
			init=0;
			for (int i=0; i < 8; i++)
			{

				display_data[i] = number[current_floor][i];


			}
		}

		else if(motor_state ==1)//올라감
		{
			for (int i=0; i < 8; i++)
				{

					display_data[i] = scroll_buffer[index%4][i+count];
					display_data[i] =scroll_buffer[(index+1)%4][i+count];

				}
		}
		else if (motor_state ==2)//내려감
		{
			for (int i=0; i < 8; i++)
					{

						display_data[7-i] = scroll_buffer[index%4][i+count];
						display_data[7-i] =scroll_buffer[(index+1)%4][i+count];

					}
		}
			if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
			{
				count =0;
				index++;

				// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
			}
		}
		for (int i=0; i < 8; i++)
		        {
					col[0] = ~(1 << i);  // 00000001  --> 11111110
					col[1] = display_data[i];
					//HAL_SPI_Transmit(&hspi2, col, 2, 1);

					for (int j=0; j <2; j++)
					{
						for(int k=0;k<8;k++)
						{
							temp = col[j];
						if (temp &(1<<k))
							HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 1);
						else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);

						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 1);
						HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, 0);
						}

					}
						GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
						GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
						osDelay(1);

		        }













}










#endif





































#if 0
void dotmatrix_main_test();
void init_dotmatrix(void);
int dotmatrix_main(void);
int dotmatrix_main_func(void);

uint8_t allon[] = {			// allon 문자 정의
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111,
	0b11111111
};


uint8_t smile[] = {			// 스마일 문자 정의
	0b00111100,
	0b01000010,
	0b10010101,
	0b10100001,
	0b10100001,
	0b10010101,
	0b01000010,
	0b00111100 };

uint8_t hart[] = {		// hart
	0b00000000,    // hart
	0b01100110,
	0b11111111,
	0b11111111,
	0b11111111,
	0b01111110,
	0b00111100,
	0b00011000
};

uint8_t one[] =
{0b00011000,
0b00111000,
0b00011000,
0b00011000,
0b00011000,
0b00011000,
0b01111110,
0b01111110};

uint8_t my_name[][3] =
{
	{0x08,0x3e,0x1c,0x08,0x7f,0x00,0x1c,0x1c}, //hong
	{0x02,0x22,0x56,0x8a,0x02,0x3a,0x08,0x08}, //seok
	{0x4a,0x7a,0x4e,0x7a,0x02,0x3a,0x28,0x38} //beom
};










uint8_t col[4]={0,0,0,0};

void dotmatrix_main_test()
{
  //dotmatrix_main();
	 int button0_state=0;
  while (1)
  {
	  if (get_button(GPIOC,GPIO_PIN_0,BTN0)==BUTTON_PRESS)
		  button0_state=!button0_state;


        for (int i=0; i < 8; i++)
        {
			col[0] = ~(1 << i);  // 00000001  --> 11111110
			if(button0_state)
				col[1] = hart[i];
			else
				col[1] = smile[i];

			HAL_SPI_Transmit(&hspi2, col, 2, 1);
			GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
			HAL_Delay(1);
        }

   if(button0_state)
	   buzzer_main();
   else
	   noTone();
  }
}

uint8_t number_data[20][10] =
{
		{
		0b00011000,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00100100,
		0b00011000,
		0b00000001},
	{
		0b00010000,	//1
		0b00110000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00010000,
		0b00111000,
	    1   // 점 0b00000110
	},
	{
		0b0111000,	//2
		0b01000100,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00100000,
		0b01111100,
	    1
	},
	{
		0b01111100,	//3
	    0b00001000,
		0b00010000,
		0b00001000,
		0b00000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b00001000,	//4
		0b00011000,
		0b00101000,
		0b01001000,
		0b01111100,
		0b00001000,
		0b00001000,
	    1
	},
	{
		0b01111100,	//5
		0b01000000,
		0b01111000,
		0b00000100,
		0b00000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b00011000,	//6
		0b00100000,
		0b01000000,
		0b01111000,
		0b01000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b01111100,	//7
		0b01000100,
		0b00000100,
		0b00001000,
		0b00010000,
		0b00010000,
		0b00010000,
	    1
	},
	{
		0b00111000,	//8
		0b01000100,
		0b01000100,
		0b00111000,
		0b01000100,
		0b01000100,
		0b00111000,
	    1
	},
	{
		0b00011000,
		0b00100100,
		0b00100100,
		0b00011100,
		0b00000100,
		0b00000100,
		0b00011000,
		0b00000001
	},
	{
		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
	}
};

unsigned char display_data[8];  // 최종 8x8 출력할 데이터
unsigned char scroll_buffer[50][8] = {0,};  // 스코롤할 데이타가 들어있는 버퍼
int number_of_character = 11;  // 출력할 문자 갯수

// 초기화 작업
// 1. display_data에 number_data[0]에 있는 내용 복사
// 2. number_data를 scroll_buffer에 복사
// 3. dotmatrix의 led를 off
void init_dotmatrix(void)
{
	for (int i=0; i < 8; i++)
	{
		display_data[i] = number_data[i];
	}
	for (int i=1; i < number_of_character+1; i++)
	{
		for (int j=0; j < 8; j++) // scroll_buffer[0] = blank
		{
			scroll_buffer[i][j] = number_data[i-1][j];
		}
	}
}

// scroll 문자 출력 프로그램
int dotmatrix_main(void)
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장


	uint32_t now = HAL_GetTick();  // 1ms
	// 1.처음시작시 past_time=0; now: 500 --> past_time=500
	if (now - past_time >= 500) // 500ms scroll
	{
		past_time = now;
		for (int i=0; i < 8; i++)
		{

			display_data[i] = (scroll_buffer[index][i] >> count) |
					(scroll_buffer[index+1][i] << 8 - count);
		}
		if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
		{
			count =0;
			index++;  // 다음 scroll_buffer로 이동
			if (index == number_of_character+1) index=0;
			// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
		}
	}
/*
 		0b00000000,    // hart
		0b01100110,
		0b11111111,
		0b11111111,
		0b11111111,
		0b01111110,
		0b00111100,
		0b00011000
 */
	for (int i=0; i < 8; i++)
	{
		// 공통 양극 방식
		// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
		col[0] = ~(1 << i);  // 00000001  --> 11111110
		col[1] = display_data[i];
		HAL_SPI_Transmit(&hspi2, col, 2, 1);
		GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
		GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
		HAL_Delay(1);
	}
}

// scroll 문자 출력 프로그램
int dotmatrix_main_func(void)
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장

	init_dotmatrix();

	while(1)
	{
		uint32_t now = HAL_GetTick();  // 1ms
		// 1.처음시작시 past_time=0; now: 500 --> past_time=500
		if (now - past_time >= 500) // 500ms scroll
		{
			past_time = now;
			for (int i=0; i < 8; i++)
			{

				display_data[i] = (scroll_buffer[index][i] >> count) |
						(scroll_buffer[index+1][i] << 8 - count);
			}
			if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
			{
				count =0;
				index++;  // 다음 scroll_buffer로 이동
				if (index == number_of_character+1) index=0;
				// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
			}
		}
		for (int i=0; i < 8; i++)
		{
			// 공통 양극 방식
			// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
			col[0] = ~(1 << i);  // 00000001  --> 11111110
			col[1] = display_data[i];
			HAL_SPI_Transmit(&hspi2, col, 2, 1);
			GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
			HAL_Delay(1);
		}
	}
	return 0;
}


int dotmatrix_main_up(void)
{
	static int count=0;  // 컬럼 count
	static int index=0;  // scroll_buffer의 2차원 index값
	static uint32_t past_time=0;  // 이전 tick값 저장

	init_dotmatrix();

	while(1)
	{
		uint32_t now = HAL_GetTick();  // 1ms
		// 1.처음시작시 past_time=0; now: 500 --> past_time=500
		if (now - past_time >= 200) // 500ms scroll
		{
			past_time = now;
			for (int i=0; i < 8; i++)
			{

				display_data[i] = scroll_buffer[index%11][i+count];
				display_data[i] =scroll_buffer[(index+1)%11][i+count];

			}
			if (++count == 8) // 8칼람을 다 처리 했으면 다음 scroll_buffer로 이동
			{
				count =0;
				index++;  // 다음 scroll_buffer로 이동

				// 11개의 문자를 다 처리 했으면 0번 scroll_buffer를 처리 하기위해 이동
			}
		}
		for (int i=0; i < 8; i++)
		{
			// 공통 양극 방식
			// column에는 0을 ROW에는 1을 출력해야 해당 LED가 on된다.
			col[0] = ~(1 << i);  // 00000001  --> 11111110
			col[1] = display_data[i];
			HAL_SPI_Transmit(&hspi2, col, 2, 1);
			GPIOB->ODR &= ~GPIO_PIN_13;   // latch핀을 pull-down
			GPIOB->ODR |= GPIO_PIN_13;   // latch핀을 pull-up
			HAL_Delay(1);
		}
	}
	return 0;
}

#endif

