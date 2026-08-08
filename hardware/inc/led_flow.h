/**
 * @file    led_flow.h
 * @brief   LED_FLOW 驱动头文件。
 *          头文件放声明和宏，具体实现放在 led_flow.c。
 */
#ifndef LED_FLOW_H
#define LED_FLOW_H

#include "stm32h7xx_hal.h"
#include "led.h"
#include "stdbool.h"
#include "timer.h"

#ifdef __cplusplus
extern "C" {
#endif


void led_flow_statemachine(LED_FLOW_MODE new_mode,LED_FLOW_MODE* current_mode );


void flow_update(uint8_t* mode_step,uint8_t steps,timer* timer,uint8_t* current_step);

#ifdef __cplusplus
}
#endif

#endif /* LED_FLOW_H */
