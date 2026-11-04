#include "input_reading.h"

static const ButtonConfig button[NO_OF_BUTTONS] = {
    {BUTTON_0_GPIO_Port, BUTTON_0_Pin},
    {BUTTON_1_GPIO_Port, BUTTON_1_Pin},
    {BUTTON_2_GPIO_Port, BUTTON_2_Pin}
};

/* Active-low inputs must start RELEASED, not at C's default zero. */
static volatile GPIO_PinState buttonBuffer[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static volatile uint8_t flagForButtonPress1s[NO_OF_BUTTONS];
static uint16_t counterForButtonPress1s[NO_OF_BUTTONS];

/* 100 samples at the default 10 ms period, as in your original code. */
#define DURATION_FOR_AUTO_INCREASING \
    ((1000U + BUTTON_SAMPLE_PERIOD_MS - 1U) / BUTTON_SAMPLE_PERIOD_MS)

void button_init(void)
{
    for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i) {
        buttonBuffer[i] = GPIO_PIN_SET;
        debounceButtonBuffer1[i] = GPIO_PIN_SET;
        debounceButtonBuffer2[i] = GPIO_PIN_SET;
        flagForButtonPress1s[i] = 0;
        counterForButtonPress1s[i] = 0;
    }
}
/* Called once per sample from TIM2, never again from the main loop. */
void button_reading(void)
{
    for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i) {
        GPIO_PinState old_state = buttonBuffer[i];
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button[i].port, button[i].pin);

        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            buttonBuffer[i] = debounceButtonBuffer1[i];
        }

        if (buttonBuffer[i] == GPIO_PIN_RESET) {
            /* Start at zero on the accepted press; then count full intervals. */
            if (old_state == GPIO_PIN_SET) {
                counterForButtonPress1s[i] = 0;
            } else if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                counterForButtonPress1s[i]++;
            }
            flagForButtonPress1s[i] =
                counterForButtonPress1s[i] >= DURATION_FOR_AUTO_INCREASING;
        } else {
            counterForButtonPress1s[i] = 0;
            flagForButtonPress1s[i] = 0;
        }
    }
}

unsigned char is_button_pressed(uint8_t index)
{
    return index < NO_OF_BUTTONS && buttonBuffer[index] == GPIO_PIN_RESET;
}

unsigned char is_button_pressed_1s(uint8_t index)
{
    return index < NO_OF_BUTTONS && flagForButtonPress1s[index];
}
