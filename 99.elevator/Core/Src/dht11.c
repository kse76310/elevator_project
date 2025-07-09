
/*
 * dht11.c
 *
 * Created: 2025-03-18 오전 10:52:34
 *  Author: microsoft
 */

#include "dht11.h"
#include "extern.h"



char * error_log = " ";

void init_dht11(void)
{

	GPIOA->MODER|=0b01;  // output
	GPIOA->ODR |= 1 << DHT_PIN_NUM;

}

void signal_us_check(int duration, int binary_choice)
{
	us_count = 0;
	while((GPIOA->IDR & 1 ) == binary_choice)
	{
		delay_us(2);
		us_count += 2;
		if(us_count > duration)
		{
			state = TIMEOUT;
			return;
		}
	}
}

int dht11_get_bit(void)
{
	us_count = 0;
	while(GPIOA->IDR& 1 )
	{
		delay_us(2);
		us_count += 2;
		if(us_count > 90)
		{
			printf("여기다");
			state = TIMEOUT;
			return -1;
		}
	}

	if(us_count < 40) return 0;
	else if(us_count >= 40) return 1;
}


int dht11_main(uint8_t* data)
{

	init_dht11();

	memset(data, 0, 5); // data 초기화
	state = OK;

	// ================ step 1 : start signal ======================
	// idel상태인 HIGH를 100ms 유지 -> 이 후 LOW로 바꾸어 준다.


	HAL_Delay(100);

	GPIOA->ODR &= ~(1 << DHT_PIN_NUM);

	HAL_Delay(25); // LOW상태를 최소 18ms 유지해야함

	GPIOA->ODR |= 1 << DHT_PIN_NUM; // start signal을 보낸 다음에는 HIGH로 유지해야함
	GPIOA->MODER &= ~(1 << DHT_PIN_NUM);
	delay_us(1);

	// response signal check
	signal_us_check(50, HIGH); //high 50us 체크

	if (state != OK)
	{
		error_log = "response signal check failed";
		return;
	}
	// ============= step 2 : response signal check =============
	// step 2 실행 (정상적으로 DATA pin에 LOW가 감지된것)
	signal_us_check(100, LOW);  //low 100 us체크

	if (state != OK)
	{
		error_log = "step 2, response signal low check failed";
		return;
	}

	// response high 체크
	// LOW가 80us 정도 유지되고 (그니까 100us이내에) 잘 HIGH를 유지했는지 확인
	signal_us_check(100, HIGH); //high 100us 체크

	if (state != OK)
	{
		error_log = "step2, response signal high fail";
		return;
	}
	// 여기서 state가 OK면 hand shaking이 잘 마무리된것!!
	// == DTAT LINE은 지금 LOW 상태임


	// ============= step 3 : data bit receive from DHT11 =============
	// 40개의 pulse를 count 한다
	// -> 8비트식 한 바이트를 이루어 의미를 띄므로, 8비트씩 묶어야함
	// '0' : LOW 50us, HIGH 26~28us
	// '1' : LOW 50us, HIGH 70us

	for (int i = 0; i < 5; i++)
	{
		uint8_t pulse[8] = { 0, }; // 1개의 pulse를 저장할 변수 (8비트 저장)
		for (int j = 7; j >= 0; j--)
		{
			// LOW 50us 확인
			signal_us_check(70, LOW);
			if (state == TIMEOUT)
			{
				i = 5;
				j = -1;
				error_log = "get bit, 50us low check fail";
			}

			// state 확인 필수!
			// HIGH가 몇 us인지 확인
			int dht11_bit = dht11_get_bit();
			if (state == OK) pulse[j] = dht11_bit;
			else error_log = "get bit, high failed";
		}
		// pulse를 가지고 data로 넣어주기!
		if (state == OK)
		{
			data[i] = pulse[0] << 0 | pulse[1] << 1 | pulse[2] << 2 | pulse[3] << 3 |
			pulse[4] << 4 | pulse[5] << 5 | pulse[6] << 6 | pulse[7] << 7;
		}
		else {
			error_log = "get bit fail";
		}
	}

	// 5바이트 다 받아옴
	// check sum 확인!!
	if (state == OK)
	{
		if (data[4] != data[0] + data[1] + data[2] + data[3])
		{
			// check sum이 맞지 않는 상황
			state = VALUE_ERROR;
		}
	}
	else {
		error_log = "get bit failed 2";
	}

	delay_us(60); // 제일 마지막 단계!! 50us LOW상태 유지
	return state;
}



void dht_test(void){


		printf("linked\n");

				 uint8_t data[5] = { 0, };

				 while (1)
				 {
					 int state = dht11_main(data);

					 if (state == OK)
					 {
						 printf("temp = %d.%d, humidity = %d.%d\n", data[2], data[3], data[0], data[1]);
					 }
					 else
					 {
						 printf("ERROR : %s\n", error_log);

					 }

					 HAL_Delay(1000); // 2초 간격으로 데이터 갱신
		}
}




