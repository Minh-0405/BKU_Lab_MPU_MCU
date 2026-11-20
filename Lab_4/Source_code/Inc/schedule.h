/*
 * schedule.h
 *
 *  Created on: Nov 13, 2026
 *      Author: ducmi
 */

#ifndef INC_SCHEDULE_H_
#define INC_SCHEDULE_H_

#include "main.h"
#include <stdint.h>

#define SCH_MAX_TASKS 6
#define NO_TASK_ID 0

#define ERROR_SCH_TOO_MANY_TASKS 1
#define ERROR_SCH_CANNOT_DELETE_TASK 2
#define RETURN_ERROR 1
#define RETURN_NORMAL 0

typedef unsigned char tByte;

typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
} sTask;

typedef struct {
    GPIO_TypeDef *port;
    uint16_t pin;
} led_config;

extern sTask SCH_tasks_G[SCH_MAX_TASKS];
extern const led_config leds[5];

void SCH_Init(void);
void SCH_Update(sTask *dut);
unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);
void SCH_Dispatch_Tasks(void);
unsigned char SCH_Delete_Task(const tByte TASK_INDEX);

uint32_t get_time(void);
void UART_Print_Timestamp(const char *task_name, int period_ms);
void Task_Toggle_LED(led_config dut, int time);

void func_a(void);
void func_b(void);
void func_c(void);
void func_d(void);
void func_e(void);
void Task_10ms(void);

#endif /* INC_SCHEDULE_H_ */
