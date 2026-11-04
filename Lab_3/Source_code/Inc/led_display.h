#ifndef INC_LED_DISPLAY_H_
#define INC_LED_DISPLAY_H_

#include "main.h"
typedef enum { LED_OFF, LED_RED, LED_AMBER, LED_GREEN } TrafficColor;

extern int led_buffer[4];
void led_display_init(void);
void clearAllLeds(void);
void display7SEG(int num);
void led_display_normal(uint8_t west, uint8_t north);
void led_display_edit(uint8_t mode, uint8_t value);
void led_display_refresh(void);
void traffic_display(TrafficColor north_south, TrafficColor west_east);
#endif
