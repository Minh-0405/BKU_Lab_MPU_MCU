#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"
#include "timer.h"
#define NO_OF_BUTTONS 3U
#define BUTTON_SAMPLE_MS 10U
#define BUTTON_SAMPLE_TICKS ((BUTTON_SAMPLE_MS + TIMER_CYCLE - 1U) / TIMER_CYCLE)
#define BUTTON_SAMPLE_PERIOD_MS (BUTTON_SAMPLE_TICKS * TIMER_CYCLE)

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} ButtonConfig;

void button_init(void);
void button_reading(void);
unsigned char is_button_pressed(uint8_t index);
unsigned char is_button_pressed_1s(uint8_t index);
#endif
