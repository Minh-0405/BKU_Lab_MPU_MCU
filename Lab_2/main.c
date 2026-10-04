/* USER CODE BEGIN Includes */
#include "Source_code.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
const int MAX_LED = 4;
int index = 0;
const int MAX_LED_MATRIX = 8 ;
int index_matrix = 1 ;
/* USER CODE END PV */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;
void setTimer0 ( int duration ) {
	timer0_counter = duration / TIMER_CYCLE ;
	timer0_flag = 0;
}

int timer1_counter = 0;
int timer1_flag = 0;
void setTimer1 ( int duration ) {
	timer1_counter = duration / TIMER_CYCLE ;
	timer1_flag = 0;
}

void timer_run () {
	if( timer0_counter > 0) {
		timer0_counter-- ;
		if( timer0_counter == 0) timer0_flag = 1;
	}
	if( timer1_counter > 0) {
		timer1_counter-- ;
		if( timer1_counter == 0) timer1_flag = 1;
	}
}
/* USER CODE END 0 */

int main(void)
{
    /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT (& htim2 ) ;
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  setTimer0 (100) ;
  setTimer1 (100) ;
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if( timer0_flag == 1) {
		  HAL_GPIO_TogglePin ( LED_RED_GPIO_Port , LED_RED_Pin ) ;
		  run_ex1() ;
		  run_ex2() ;
		  update7SEG(index++); if(index >= MAX_LED) index = 0 ; run_ex5() ;
		  setTimer0 (250) ;
	  }
	  if( timer1_flag == 1) {
		  if(index_matrix >= MAX_LED_MATRIX) index_matrix = 0 ; updateLEDMatrix(index_matrix++) ;
		  setTimer1 (10) ;
	  }
  }
  /* USER CODE END 3 */
}

/* USER CODE BEGIN 4 */
int clk = 0 ;
void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	clk++ ;
	timer_run() ; clk = 0 ;
	// if(clk == 51){ run_ex1() ; clk = 1 ;}
	if(clk == 26){ run_ex2() ; clk = 1 ;}
	// if(clk == 26){ update7SEG(index++); if(index >= MAX_LED) index = 0 ; clk = 1 ;} // for ex 3, 4
	// if(clk == 26){ run_ex5() ; update7SEG(index++); if(index >= MAX_LED) index = 0 ;  clk = 1 ;} // for ex 5
}
/* USER CODE END 4 */
