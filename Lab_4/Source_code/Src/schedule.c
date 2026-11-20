/*
 * schedule.c
 *
 *  Created on: Nov 13, 2026
 *      Author: ducmi
 */
#include "schedule.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint8_t Error_code_G = 0;

const led_config leds[5] = {
    {GPIOA, GPIO_PIN_4},
    {GPIOA, GPIO_PIN_5},
    {GPIOA, GPIO_PIN_6},
    {GPIOA, GPIO_PIN_7},
    {GPIOA, GPIO_PIN_8}
};

void SCH_Init(void) {
    unsigned char i;
    for (i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_Delete_Task(i);
    }
    Error_code_G = 0;
}

void SCH_Update(sTask *dut) {
    if (dut->pTask) {
        if (dut->Delay == 0) {
            dut->RunMe += 1;
            if (dut->Period) {
                dut->Delay = dut->Period;
            }
        } else {
            dut->Delay -= 1;
        }
    }
}

unsigned char SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD) {
    unsigned char Index = 0;
    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)) {
        Index++;
    }
    if (Index == SCH_MAX_TASKS) {
        Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        return SCH_MAX_TASKS;
    }
    SCH_tasks_G[Index].pTask = pFunction;
    SCH_tasks_G[Index].Delay = DELAY;
    SCH_tasks_G[Index].Period = PERIOD;
    SCH_tasks_G[Index].RunMe = 0;
    return Index;
}

void SCH_Dispatch_Tasks(void) {
    unsigned char Index;
    for (Index = 0; Index < SCH_MAX_TASKS; Index++) {
        if (SCH_tasks_G[Index].RunMe > 0) {
            (*SCH_tasks_G[Index].pTask)();
            SCH_tasks_G[Index].RunMe -= 1;
            if (SCH_tasks_G[Index].Period == 0) {
                SCH_Delete_Task(Index);
            }
        }
    }
}

unsigned char SCH_Delete_Task(const tByte TASK_INDEX) {
    unsigned char Return_code;
    if (SCH_tasks_G[TASK_INDEX].pTask == 0) {
        Error_code_G = ERROR_SCH_CANNOT_DELETE_TASK;
        Return_code = RETURN_ERROR;
    } else {
        Return_code = RETURN_NORMAL;
    }
    SCH_tasks_G[TASK_INDEX].pTask = 0x0000;
    SCH_tasks_G[TASK_INDEX].Delay = 0;
    SCH_tasks_G[TASK_INDEX].Period = 0;
    SCH_tasks_G[TASK_INDEX].RunMe = 0;
    return Return_code;
}

void Task_Toggle_LED(led_config dut, int time) {
    HAL_GPIO_TogglePin(dut.port, dut.pin);
    UART_Print_Timestamp("LED", time);
}

void func_a(void) { Task_Toggle_LED(leds[0], 500);  }
void func_b(void) { Task_Toggle_LED(leds[1], 1000); }
void func_c(void) { Task_Toggle_LED(leds[2], 1500); }
void func_d(void) { Task_Toggle_LED(leds[3], 2000); }
void func_e(void) { Task_Toggle_LED(leds[4], 2500); }

void Task_10ms(void) {
    UART_Print_Timestamp("Task_10ms", 10);
}























