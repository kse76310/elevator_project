#include <string.h>


#include "uart.h"
#include "extern.h"



/**
  * @brief  Rx Transfer completed callbacks.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */

//comportmaster로 부터 1char을 수신하면 HAl_UART_RXCpltcallback으로 진입
//9600bps인 경우 HAL_UART_RxCpltCallback를 수행후 1ms이내에는 빠져나가야한다
//115200bps인 경우에는 86us이내에 빠져나가야한다
__weak void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	volatile static int i=0;

	if(huart == &huart2)
	{
			if (rx_data == '\n')
		{
			rx_buff[rear++][i] = '\0';
			rear %=COMMAND_NUMBER;
			i=0;
		}
		else
		{
			rx_buff[rear][i++] = rx_data;
			//command_length를 check하는 logic 추가
		}
		HAL_UART_Receive_IT(&huart2, &rx_data,1);  //주의: 반드시 집어넣어야 다음 int 발생
	}
}




void pc_command_processing(void) {
	if (front != rear)
	{
		printf("%s\n", rx_buff[front]);

			if (strncmp((const char*)rx_buff[front],(const char*)"led_all_on", strlen("led_all_on"))==0)
			{
				*(unsigned int*)0x40020414=0xff;
			}

			else if (strncmp((const char*)rx_buff[front],(const char*)"led_all_off", strlen("led_all_off"))==0)
			{
				*(unsigned int*)0x40020414=0x00;
			}
			else if (strncmp((const char*)rx_buff[front],(const char*)"setrtc", strlen("setrtc"))==0)
			{
				set_rtc(&rx_buff[front][6]);
			}
			else if (strncmp((const char*)rx_buff[front],(const char*)"help", strlen("help"))==0)
			{
				show_command();
			}
			else if (strncmp((const char*)rx_buff[front],(const char*)"print_rtc", strlen("print_rtc"))==0)
			{
				o_prt.p_rtc=1;
				printf("print_rtc: %d \n", o_prt.p_rtc);
			}
			else if (strncmp((const char*)rx_buff[front],(const char*)"printoff_rtc", strlen("printoff_rtc"))==0)
			{
				o_prt.p_rtc=0;
				printf("print_rtc: %d \n", o_prt.p_rtc);
			}

		front++;
		front %= COMMAND_NUMBER;
		//rx_buff에 data가 존재
	}
}


t_print o_prt;

void show_command(void)
{
	char *cmd[]={
			"setrtc",
			"print_rtc",
			"printoff_rtc",
			"help"
	};

	for (int i=0; i<4;i++)
		printf("%s, ",cmd[i]);

	printf("\n");
}









