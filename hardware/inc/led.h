/**
 * @file    led.h
 * @brief   LED 驱动头文件。
 *          头文件放声明和宏，具体实现放在 led.c。
 */
#ifndef LED_H
#define LED_H

#include "stm32h7xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 宏定义：给 LED 使用的端口和引脚起名字 */
#define LED_GPIO_PORT GPIOB
#define LED1_PIN      GPIO_PIN_3
#define LED2_PIN      GPIO_PIN_4
#define LED3_PIN      GPIO_PIN_5
#define LED4_PIN      GPIO_PIN_6
#define LED_COUNT 4

#define LED_LEFT  (LED1_PIN | LED2_PIN)
#define LED_RIGHT (LED3_PIN | LED4_PIN)
#define LED_ALL   (LED1_PIN | LED2_PIN | LED3_PIN | LED4_PIN)

/* 种子工程先提供无参数版本，只操作 LED1；题目 1 将其扩展为带编号参数版本 */

typedef struct 
{
    uint8_t led_num;
    uint32_t on_ms;
    uint32_t off_ms;
} LED_BlinkConfig;

typedef enum
{
    MODE_0 =0,
    MODE_1,
    MODE_2,
    MODE_4,
    
}LED_FLOW_MODE;

void led_set_mask(uint16_t pin_mask, GPIO_PinState state);
void led_toggle_mask(uint16_t pin_mask);


#ifdef __cplusplus
}
#endif

#endif /* LED_H */
