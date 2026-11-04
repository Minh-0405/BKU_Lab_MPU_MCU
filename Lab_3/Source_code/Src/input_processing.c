#include "input_processing.h"
#include "input_reading.h"
#include "led_display.h"
#include "timer.h"

#define MAX_DURATION 9U  /* Each value has one physical seven-segment digit. */

enum ButtonState {
    BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND
};
enum Mode { NORMAL = 1, MODIFY_RED, MODIFY_AMBER, MODIFY_GREEN };
enum DurationIndex { RED_TIME, AMBER_TIME, GREEN_TIME };
enum TrafficPhase { NS_RED_WE_GREEN, NS_RED_WE_AMBER, NS_GREEN_WE_RED, NS_AMBER_WE_RED };

static enum ButtonState buttonState[NO_OF_BUTTONS];
static enum Mode mode;
static enum TrafficPhase phase;
static uint8_t value_buffer[3]; /* red, amber, green; saved in RAM */
static uint8_t edit_value, phase_remaining, invalid_value, suppress_increment;
static uint8_t blink_on;

static void start_normal(void)
{
    phase = NS_RED_WE_GREEN;
    phase_remaining = value_buffer[GREEN_TIME];
    setTimer0(1000);
}

void input_processing_init(void)
{
    for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i) buttonState[i] = BUTTON_RELEASED;
    value_buffer[RED_TIME] = 5;
    value_buffer[AMBER_TIME] = 2;
    value_buffer[GREEN_TIME] = 3;
    mode = NORMAL;
    edit_value = invalid_value = suppress_increment = 0;
    blink_on = 1;
    start_normal();
}

static void switch_mode(uint8_t increment_held)
{
    mode = mode == MODIFY_GREEN ? NORMAL : (enum Mode)(mode + 1);
    blink_on = 1;
    invalid_value = 0;
    /* A held increment button must be released before editing a new mode. */
    suppress_increment = increment_held;
    if (mode == NORMAL) start_normal();
    else {
        edit_value = value_buffer[mode - MODIFY_RED];
        setTimer1(250);
    }
}

static void increment_value(void)
{
    if (mode == NORMAL) return;
    edit_value = edit_value >= MAX_DURATION ? 1U : edit_value + 1U;
    invalid_value = 0;
}

static void save_value(void)
{
    if (mode == NORMAL) return;
    if (edit_value < 1U || edit_value > MAX_DURATION) {
        invalid_value = 1;
        return;
    }

    /* Keep both roads consistent: red = green + amber.
     * A red edit adjusts green; a green/amber edit adjusts red.
     * Reject impossible combinations without changing any saved values. */
    if (mode == MODIFY_RED) {
        if (edit_value <= value_buffer[AMBER_TIME]) {
            invalid_value = 1;
            return;
        }
        value_buffer[RED_TIME] = edit_value;
        value_buffer[GREEN_TIME] = edit_value - value_buffer[AMBER_TIME];
    } else {
        uint8_t index = mode - MODIFY_RED;
        uint8_t other = index == AMBER_TIME ? GREEN_TIME : AMBER_TIME;
        uint16_t red_time = (uint16_t)edit_value + value_buffer[other];
        if (red_time > MAX_DURATION) {
            invalid_value = 1;
            return;
        }
        value_buffer[index] = edit_value;
        value_buffer[RED_TIME] = (uint8_t)red_time;
    }
    invalid_value = 0;
}

static void run_normal(void)
{
    /* Timer 0 expires once per second; its setter also clears the flag. */
    if (timer0_flag) {
        setTimer0(1000);
        if (--phase_remaining == 0U) {
            phase = (enum TrafficPhase)((phase + 1U) % 4U);
            phase_remaining = (phase == NS_RED_WE_AMBER || phase == NS_AMBER_WE_RED)
                              ? value_buffer[AMBER_TIME] : value_buffer[GREEN_TIME];
        }
    }
    switch (phase) {
    case NS_RED_WE_GREEN:
        traffic_display(LED_RED, LED_GREEN);
        led_display_normal(phase_remaining, phase_remaining + value_buffer[AMBER_TIME]);
        break;
    case NS_RED_WE_AMBER:
        traffic_display(LED_RED, LED_AMBER);
        led_display_normal(phase_remaining, phase_remaining);
        break;
    case NS_GREEN_WE_RED:
        traffic_display(LED_GREEN, LED_RED);
        led_display_normal(phase_remaining + value_buffer[AMBER_TIME], phase_remaining);
        break;
    case NS_AMBER_WE_RED:
        traffic_display(LED_AMBER, LED_RED);
        led_display_normal(phase_remaining, phase_remaining);
        break;
    }
}

void fsm_for_input_processing(void)
{
    uint8_t pressed[NO_OF_BUTTONS], held[NO_OF_BUTTONS];
    uint8_t press_event[NO_OF_BUTTONS] = {0};
    uint8_t repeat_event = 0;
    uint32_t irq_state = __get_PRIMASK();
    /* Read one coherent snapshot of the interrupt-owned input buffers. */
    __disable_irq();
    for (uint8_t i = 0; i < NO_OF_BUTTONS; ++i) {
        pressed[i] = is_button_pressed(i);
        held[i] = is_button_pressed_1s(i);
    }
    __set_PRIMASK(irq_state);

    if (!pressed[1]) suppress_increment = 0;
    for (int i = 0; i < (int)NO_OF_BUTTONS; i++) {
        switch (buttonState[i]) {
        case BUTTON_RELEASED:
            if (pressed[i]) {
                buttonState[i] = BUTTON_PRESSED;
                press_event[i] = 1;
            }
            break;
        case BUTTON_PRESSED:
            if (!pressed[i]) buttonState[i] = BUTTON_RELEASED;
            else if (held[i]) {
                buttonState[i] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
                if (i == 1U) {
                    repeat_event = 1;
                    setTimer2(500);
                }
            }
            break;
        case BUTTON_PRESSED_MORE_THAN_1_SECOND:
            if (!pressed[i]) buttonState[i] = BUTTON_RELEASED;
            else if (i == 1U && timer2_flag) {
                setTimer2(500);
                repeat_event = 1;
            }
            break;
        }
    }

    /* Mode has priority if several buttons are pressed together. */
    if (press_event[0]) switch_mode(pressed[1]);
    else {
        if (!suppress_increment && (press_event[1] || repeat_event)) increment_value();
        if (press_event[2]) save_value();
    }

    if (mode == NORMAL) run_normal();
    else {
        /* 2 Hz = 500 ms per complete cycle = toggle every 250 ms. */
        if (timer1_flag) {
            setTimer1(250);
            blink_on = !blink_on;
        }
        TrafficColor color = (TrafficColor)(mode - MODIFY_RED + LED_RED);
        traffic_display(blink_on ? color : LED_OFF, blink_on ? color : LED_OFF);
        led_display_edit(mode, edit_value);
        /* Rejected save: blink EN3; the mode on EN2 stays visible. */
        if (invalid_value && !blink_on) led_buffer[3] = -1;
    }
}
