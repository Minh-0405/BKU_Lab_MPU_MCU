#include "timer.h"
#include "input_reading.h"

static volatile uint32_t timer0_counter, timer1_counter, timer2_counter, freq_counter;
volatile int timer0_flag, timer1_flag, timer2_flag, freq_flag;

static void set_timer(volatile uint32_t *counter, volatile int *flag, int duration)
{
    uint32_t irq_state = __get_PRIMASK();
    __disable_irq();
    /* Positive durations round up; unarmed timers never raise a flag. */
    *counter = duration > 0 ? ((uint32_t)duration + TIMER_CYCLE - 1U) / TIMER_CYCLE : 0U;
    *flag = duration <= 0;
    __set_PRIMASK(irq_state);
}

void setTimer0(int duration) { set_timer(&timer0_counter, &timer0_flag, duration); }
void setTimer1(int duration) { set_timer(&timer1_counter, &timer1_flag, duration); }
void setTimer2(int duration) { set_timer(&timer2_counter, &timer2_flag, duration); }
void setTimerFreq(int duration) { set_timer(&freq_counter, &freq_flag, duration); }

static void tick_timer(volatile uint32_t *counter, volatile int *flag)
{
    if (*counter > 0U && --(*counter) == 0U) *flag = 1;
}

void timer_run(void)
{
    tick_timer(&timer0_counter, &timer0_flag);
    tick_timer(&timer1_counter, &timer1_flag);
    tick_timer(&timer2_counter, &timer2_flag);
    tick_timer(&freq_counter, &freq_flag);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t button_sample_counter;
    if (htim->Instance == TIM2) {
        /* At the default 10 ms period, read buttons on every interrupt.
         * If TIM2 is faster, count ticks to keep samples 10 ms apart. */
        if (++button_sample_counter >= BUTTON_SAMPLE_TICKS) {
            button_sample_counter = 0;
            button_reading();
        }
        timer_run();
    }
}
