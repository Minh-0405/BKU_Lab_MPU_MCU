
#ifndef INC_EX_H_
#define INC_EX_H_

void run_ex1(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,
	  GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,
	  GPIO_PIN_RESET);
	  HAL_Delay(2000);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,
	  GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,
	  GPIO_PIN_SET);
	  HAL_Delay(2000);
}

void run_ex2() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,
	GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,
	GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,
	GPIO_PIN_SET);
	HAL_Delay(5000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,
	GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,
	GPIO_PIN_RESET);
	HAL_Delay(3000);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,
		GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,
		GPIO_PIN_RESET);
	HAL_Delay(2000) ;
}

void run_ex3() {
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_10, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);

	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

	    HAL_Delay(3000);

	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

	    HAL_Delay(2000);

	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_10, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_9, GPIO_PIN_RESET);

	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_15, GPIO_PIN_RESET);

	    HAL_Delay(3000);

	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_9, GPIO_PIN_SET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_8, GPIO_PIN_RESET);

	    HAL_Delay(2000);
}

void display7SEG(int num){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
	                             GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
	    switch (num) {
	        case 0:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                                     GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_SET);
	            break;
	        case 1:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_SET);
	            break;
	        case 2:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 |
	                                     GPIO_PIN_4 | GPIO_PIN_6, GPIO_PIN_SET);
	            break;
	        case 3:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                                     GPIO_PIN_3 | GPIO_PIN_6, GPIO_PIN_SET);
	            break;
	        case 4:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_5 |
	                                     GPIO_PIN_6, GPIO_PIN_SET);
	            break;
	        case 5:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
	            break;
	        case 6:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
	            break;
	        case 7:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_SET);
	            break;
	        case 8:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
	            break;
	        case 9:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                                     GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
	            break;
	        default:
	            break;
	    }
}

void run_ex4(){
	int counter = 0;
		while (1){
			if(counter >= 10) counter = 0;
			display7SEG(counter++) ;
			HAL_Delay(1000);
		}
}

void run_ex5() {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_10, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_SET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);

	display7SEG(5) ;
	HAL_Delay(1000);
	display7SEG(4) ;
	HAL_Delay(1000);
	display7SEG(3) ;
	HAL_Delay(1000);


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);

	display7SEG(2) ;
	HAL_Delay(1000);
	display7SEG(1) ;
	HAL_Delay(1000);
	display7SEG(0) ;


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_9, GPIO_PIN_RESET);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_15, GPIO_PIN_RESET);

	display7SEG(3) ;
	HAL_Delay(1000);
	display7SEG(2) ;
	HAL_Delay(1000);
	display7SEG(1) ;
	HAL_Delay(1000);
	display7SEG(0) ;


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7 | GPIO_PIN_9, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6 | GPIO_PIN_8, GPIO_PIN_RESET);

	display7SEG(2) ;
	HAL_Delay(1000);
	display7SEG(1) ;
	HAL_Delay(1000);
	display7SEG(0) ;
}

void clearAllClockLEDs(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 |
                             GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11, GPIO_PIN_SET);
}

void setNumberOnClock(int num) {
    switch(num) {
    	case 1:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET); break;
		case 2:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  GPIO_PIN_RESET); break;
		case 3:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  GPIO_PIN_RESET); break;
		case 4:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); break;
		case 5:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET); break;
		case 6:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET); break;
		case 7:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET); break;
		case 8:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,  GPIO_PIN_RESET); break;
		case 9:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,  GPIO_PIN_RESET); break;
		case 10:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,  GPIO_PIN_RESET); break;
		case 11: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); break;
		case 0: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); break;
		default: break;
    }
}

void clearNumberOnClock(int num){
	switch(num) {
		case 1:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET); break;
		case 2:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9,  GPIO_PIN_SET); break;
		case 3:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,  GPIO_PIN_SET); break;
		case 4:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET); break;
		case 5:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET); break;
		case 6:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); break;
		case 7:  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET); break;
		case 8:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5,  GPIO_PIN_SET); break;
		case 9:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6,  GPIO_PIN_SET); break;
		case 10:  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7,  GPIO_PIN_SET); break;
		case 11: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET); break;
		case 0: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET); break;
		default: break;
	}
}

void run_ex6(){
	int num = 0 ;
	clearAllClockLEDs() ;
	while (1)
	{
		  setNumberOnClock(num);
			HAL_Delay(1000);
			clearNumberOnClock(num);
			num++;
			if (num > 11) {
				num = 0;
			}
	}
}

void run_ex10(){
	int sec = 0 ;
	int min = 0 ;
	int hour = 0 ;
	clearAllClockLEDs() ;

	while(1){
		setNumberOnClock(sec) ;
		HAL_Delay(200) ;
		if(sec != min && sec != hour) clearNumberOnClock(sec) ;
		sec++ ;

		if(sec > 11){
			sec = 0 ;
			if(min != hour) clearNumberOnClock(min) ;
			min++ ;
			if(min > 11){
				min = 0 ;
				if(hour != min) clearNumberOnClock(hour) ;
				hour++ ;
				if(hour > 11) hour = 0 ;
				setNumberOnClock(hour) ;
			}
			setNumberOnClock(min) ;
		}



	}
}

#endif /* INC_EX_H_ */
