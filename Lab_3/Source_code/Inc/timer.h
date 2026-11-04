#ifndef INC_TIMER_H_
#define INC_TIMER_H_

#include "main.h"
/* TIM2 uses a 1 kHz counter (8 MHz / 8000). Change only this period. */
#ifndef TIMER_CYCLE
#define TIMER_CYCLE 10U
#endif
#if TIMER_CYCLE < 1 || TIMER_CYCLE > 65536
#error "TIMER_CYCLE must be 1..65536 milliseconds"
#endif

extern volatile int timer0_flag, timer1_flag, timer2_flag, freq_flag;
void setTimer0(int duration_ms);
void setTimer1(int duration_ms);
void setTimer2(int duration_ms);
void setTimerFreq(int duration_ms);
void timer_run(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif
