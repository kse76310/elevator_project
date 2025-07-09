       #include "stepmotor.h"
#include "button.h"
#include "buzzer.h"
//#include "extern.h"

volatile uint8_t current_floor = 0;
volatile uint8_t target_floor = 0xFF;
volatile uint8_t motor_state = IDLE;
volatile uint8_t stepmotor_state = 0;
volatile uint8_t floor_request[4] = {0, 0, 0, 0};

int stepmotor_drive(int step);
void set_rpm(int rpm);
void stepmotor_main(void);
void check_floor_buttons(void);
/*
 * RPM(Revolutions Per Minute : 분당 회전수
 * 1분 60sec : 1sec(1,000,000us) * 60sec : 60,000,000us
 * 1초 : 1000ms --> 1ms(1,000us) * 1000ms : 1,000,000us
 * 1바퀴 회전: 4096 step 필요
 * 4096/8 ==> 512 sequence  :  360도 회전
 * 1 sequence (8step) : 0.70312도
 * 0.70312 x 512 sequence : 360도 회전
 * ----- RPM 조절 -----
 * 예) 1분에 13회전이 최대 속도
 * 13회전 : 60,000,000us(1분) / 4096 / 13 ==> step과 step간의 간격 time: 1126us
 * 1126us X 4096(1회전 하는데 필요 스탭) = 4,615,384us
 *                            = 4615ms(4.6초)
 * 60초 / 4.6초(1회전 하는데 소요시간 : 13회전
 */
void set_rpm(int rpm)   //rpm : 1~13
{
   osDelay(1);
   // 최대speed기준(13) : delay_us(1126);
}


void stepmotor_main(void)
{

	static uint8_t temp=1;

    // 버튼 입력 → 요청 저장
    if(get_button(GPIOC, BTN_0_Pin, BTN0) == BUTTON_PRESS) floor_request[0] = !floor_request[0];
    if(get_button(GPIOC, BTN_1_Pin, BTN1) == BUTTON_PRESS) floor_request[1] = !floor_request[1];
    if(get_button(GPIOC, BTN_2_Pin, BTN2) == BUTTON_PRESS) floor_request[2] = !floor_request[2];
    if(get_button(GPIOC, BTN_3_Pin, BTN3) == BUTTON_PRESS) floor_request[3] = !floor_request[3];

    //타겟층이 정해지지 않았고 정지되어있는 상태이면 다음 타겟층을 정한다.
    if (target_floor == 0xFF && motor_state == IDLE)
    {
    	if(temp==1)//이전에 상승중이였다면 현재 층보다 더 높은층을 우선으로 함
    	{
    		check_up();
				if(target_floor==0xff)
				{//현재 층보다 더 높은 층의 요청이 없다면 아래층을 확인한다
					check_down();
				}
    	}

    	if(temp==2)//이전에 하강중이였다면 현재 층보다 더 낮은층을 우선으로 함
    	{
    		check_down();
    		if(target_floor==0xff)
    		{//현재 층보다 더 낮은 층의 요청이 없다면 위층을 확인한다
    			check_up();
    		}
    	}
    }






        if (target_floor != 0xFF)
        { //타겟층이 정해졌다면 현재 위치와 비교한다.
        	target_floor%=4;
            if (target_floor > current_floor)
                motor_state = FORWARD;
            else if (target_floor < current_floor)
                motor_state = BACKWARD;
            else
            {
                floor_request[target_floor] = 0;
                target_floor = 0xFF;
            }
        }


    // 모터 동작
    if (motor_state != IDLE)
    {
        stepmotor_drive(motor_state);
        set_rpm(13);

        if (current_floor == target_floor)
        {
            floor_request[target_floor] = 0;
            temp=motor_state;
            motor_state = IDLE;
            target_floor = 0xFF;
            buzzer_dingdong();

        }else if(motor_state==FORWARD)
    	check_up();
        else if(motor_state==BACKWARD)
    	check_down();

    }
}


void check_up(void)
{
	for (int f = current_floor+1; f < 4; f++)
	{
			if (floor_request[f])
			{
				target_floor = f;
				break;
			}
	}
}
void check_down(void)
{
	for (int f = current_floor-1; f>= 0; f--)
	{
		if (floor_request[f])
		{
			target_floor = f;
			break;
		}
	}
}


void check_floor_buttons(void) {
    if (get_button(GPIOC, BTN_0_Pin, BTN0) == BUTTON_PRESS)
        target_floor = 0;
    if (get_button(GPIOC, BTN_1_Pin, BTN1) == BUTTON_PRESS)
        target_floor = 1;
    if (get_button(GPIOC, BTN_2_Pin, BTN2) == BUTTON_PRESS)
        target_floor = 2;
    if (get_button(GPIOC, BTN_3_Pin, BTN3) == BUTTON_PRESS)
        target_floor = 3;
}


int stepmotor_drive(int direction)
{
   static int step=0;

   switch(step)
   {
   case 0:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);

      break;
   case 1:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
      break;
   case 2:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
      break;
   case 3:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
      break;
   case 4:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
      break;
   case 5:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 1);
      break;
   case 6:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 1);
      break;
   case 7:
      HAL_GPIO_WritePin(GPIOC, IN1_Pin, 1);
      HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
      HAL_GPIO_WritePin(GPIOC, IN4_Pin, 1);
      break;
   default:
	  HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
	  HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
	  HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
	  HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
	  break;

   }
   if(direction == FORWARD)
   {
      step++;
      step %= 8;   // 다음 진행할 step for(i=0; i<8; i++)
   } //BACKWARD
   else if (direction==BACKWARD)
   {
      step--;
      if(step < 0)   //for(j=7; j< 0; j--)
         step=7;
   }
   else if (direction==IDLE)
   {
	   HAL_GPIO_WritePin(GPIOC, IN1_Pin, 0);
	   HAL_GPIO_WritePin(GPIOC, IN2_Pin, 0);
	   HAL_GPIO_WritePin(GPIOC, IN3_Pin, 0);
	   HAL_GPIO_WritePin(GPIOC, IN4_Pin, 0);
	   step=9;
   }

}

