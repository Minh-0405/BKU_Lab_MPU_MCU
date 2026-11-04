#include "led_display.h"
#include "timer.h"

#define SEGMENT_PINS (GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
                      GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14)
#define ENABLE_PINS (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3)
#define TRAFFIC_PINS (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                      GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6)
int led_buffer[4];
static uint8_t scan_index;

void clearAllLeds(void)
{
    HAL_GPIO_WritePin(GPIOA, SEGMENT_PINS, GPIO_PIN_SET);
}

void display7SEG(int num)
{
    /* Bits 0..6 are a..g on PA8..PA14. Common anode: low = on. */
    static const uint8_t patterns[10] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
    };
    clearAllLeds();
    if (num >= 0 && num <= 9) {
        HAL_GPIO_WritePin(GPIOA, (uint16_t)(patterns[num] << 8), GPIO_PIN_RESET);
    }
}

void led_display_init(void)
{
    HAL_GPIO_WritePin(GPIOB, ENABLE_PINS, GPIO_PIN_SET);
    clearAllLeds();
    traffic_display(LED_OFF, LED_OFF);
    for (uint8_t i = 0; i < 4U; ++i) {
        led_buffer[i] = -1;
    }
    scan_index = 0;
    setTimerFreq(10);
}

void led_display_normal(uint8_t west, uint8_t north)
{
    /* Each enable controls an independent display in the schematic. */
    led_buffer[0] = west;   /* EN0 / PB0: west's currently lit color. */
    led_buffer[1] = north;  /* EN1 / PB1: north's currently lit color. */
    led_buffer[2] = -1;
    led_buffer[3] = -1;
}

void led_display_edit(uint8_t mode, uint8_t value)
{
    led_buffer[0] = -1;
    led_buffer[1] = -1;
    led_buffer[2] = mode;   /* EN2 / PB2: mode 2, 3, or 4. */
    led_buffer[3] = value;  /* EN3 / PB3: temporary, unsaved duration. */
}

void led_display_refresh(void)
{
    if (!freq_flag) return;
    setTimerFreq(10);
    HAL_GPIO_WritePin(GPIOB, ENABLE_PINS, GPIO_PIN_SET);
    /* Only two displays are used in each mode. Skip blank slots so each
     * active display refreshes every 20 ms with the default 10 ms tick. */
    for (uint8_t checked = 0; checked < 4U; ++checked) {
        if (led_buffer[scan_index] >= 0 && led_buffer[scan_index] <= 9) break;
        scan_index = (scan_index + 1U) % 4U;
    }
    int digit = led_buffer[scan_index];
    display7SEG(digit);
    if (digit >= 0 && digit <= 9) {
        HAL_GPIO_WritePin(GPIOB, (uint16_t)(GPIO_PIN_0 << scan_index), GPIO_PIN_RESET);
    }
    scan_index = (scan_index + 1U) % 4U;
}

void traffic_display(TrafficColor north_south, TrafficColor west_east)
{
    static const uint16_t ns_pins[] = {0, GPIO_PIN_1, GPIO_PIN_3, GPIO_PIN_2};
    static const uint16_t we_pins[] = {0, GPIO_PIN_4, GPIO_PIN_6, GPIO_PIN_5};
    uint16_t on_pins = ns_pins[north_south] | we_pins[west_east];
    /* One atomic port write avoids a transient wrong color. Active low. */
    GPIOA->BSRR = (uint32_t)(TRAFFIC_PINS & ~on_pins) | ((uint32_t)on_pins << 16U);
}
