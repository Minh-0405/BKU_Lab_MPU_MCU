
#ifndef INC_EX_H_
#define INC_EX_H_

void display7SEG(int num){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
	                             GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_SET);
		switch (num) {
	        case 0:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_4 | GPIO_PIN_5, GPIO_PIN_RESET);
	            break;
	        case 1:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_RESET);
	            break;
	        case 2:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 |
	                                     GPIO_PIN_4 | GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 3:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
	                                     GPIO_PIN_3 | GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 4:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_5 |
	                                     GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 5:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 6:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 7:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_PIN_RESET);
	            break;
	        case 8:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        case 9:
	            HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |
	                                     GPIO_PIN_5 | GPIO_PIN_6, GPIO_PIN_RESET);
	            break;
	        default:
	            break;
	    }
}

int ex1 = 1 ;
void run_ex1() {
		  display7SEG(ex1) ;
		if(ex1 == 1) ex1 = 2 ;
		else if(ex1 == 2) ex1 = 1 ;

		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
		  if(ex1 == 2) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		  else HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
}

int ex2 = 1 ;
void run_ex2() {

	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
	if(ex2 == 1) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	else if(ex2 == 2) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	else if(ex2 == 3) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
	else if(ex2 == 4) HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);

		  display7SEG(ex2) ;
		  if(ex2 == 4) HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);

		ex2++ ;
		if(ex2 == 5) ex2 = 1 ;
}

int led_buffer [4] = {4 , 3 , 2 , 1};
void update7SEG(int index) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    switch (index) {
        case 0:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
            display7SEG(led_buffer[0]);
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
            display7SEG(led_buffer[1]);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
            display7SEG(led_buffer[2]);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
            display7SEG(led_buffer[3]);
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
            break;
        default:
            break;
    }
}

void updateClockBuffer(int current_hour, int current_minute) {
    // Calculate the tens and ones digits for the hour
    led_buffer[0] = current_hour / 10;
    led_buffer[1] = current_hour % 10;

    // Calculate the tens and ones digits for the minute
    led_buffer[2] = current_minute / 10;
    led_buffer[3] = current_minute % 10;
}


int hour = 15 ; int minute = 20 ; int second = 36 ;
void run_ex5() {

	second++;
	if (second >= 60) {
		second = 0;
		minute++;
	}
	if (minute >= 60) {
		minute = 0;
		hour++;
	}
	if (hour >= 24) {
		hour = 0;
	}

	updateClockBuffer(hour, minute);
}


void displayRow(uint8_t row_data){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,  (row_data & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,  (row_data & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (row_data & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (row_data & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, (row_data & 0x10) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, (row_data & 0x20) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, (row_data & 0x40) ? GPIO_PIN_RESET : GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, (row_data & 0x80) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

uint8_t matrix_row [8] = {0x00 , 0xFC , 0x22 , 0x21 , 0x21 , 0x22 , 0xFC , 0x00 };
void updateLEDMatrix(int index) {
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_SET);
    switch (index) {
        case 0:
        	shiftMatrixLeft() ;
        	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
            displayRow(matrix_row[index]) ;
            break;
        case 1:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
            displayRow(matrix_row[index]) ;
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
            displayRow(matrix_row[index]) ;
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
            displayRow(matrix_row[index]) ;
            break;
        case 4:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
			displayRow(matrix_row[index]) ;
			break;
        case 5:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET);
			displayRow(matrix_row[index]) ;
			break;
        case 6:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET);
			displayRow(matrix_row[index]) ;
			break;
        case 7:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
			displayRow(matrix_row[index]) ;
			break;
        default:
            break;
    }
}

void shiftMatrixLeft() {
	uint8_t tmp = matrix_row[0] ;
    for (int i = 0; i < 7; i++) {
    	matrix_row[i] = matrix_row[i+1] ;
    }
    matrix_row[7] = tmp ;
}


#endif /* INC_EX_H_ */
