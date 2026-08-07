/**
 * @file    led.c
 * @brief   LED 驱动实现文件。
 */
#include "led.h"
#include "stdbool.h"





static inline bool is_led_valid(uint8_t led_num)
{
    return (led_num < LED_COUNT);
}

/* 点亮 LED1 */
static void led_on(uint8_t led_num)
{
    if(is_led_valid(led_num)==true)
    {
        switch (led_num)
            {
                case 0U:
                HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_PIN, GPIO_PIN_SET);
                break;
                case 1U:
                HAL_GPIO_WritePin(LED_GPIO_PORT, LED2_PIN, GPIO_PIN_SET);
                break;
                case 2U:
                HAL_GPIO_WritePin(LED_GPIO_PORT, LED3_PIN, GPIO_PIN_SET);
                break;
                case 3U:
                HAL_GPIO_WritePin(LED_GPIO_PORT, LED4_PIN, GPIO_PIN_SET);
                break;
            }
    }



}

/* 熄灭 LED led_num */
static void led_off(uint8_t led_num)
{
        if(is_led_valid(led_num)==true)
    {
        switch (led_num)
        {
            case 0U:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED1_PIN, GPIO_PIN_RESET);
            break;
            case 1U:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED2_PIN, GPIO_PIN_RESET);
            break;
            case 2U:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED3_PIN, GPIO_PIN_RESET);
            break;
            case 3U:
            HAL_GPIO_WritePin(LED_GPIO_PORT, LED4_PIN, GPIO_PIN_RESET);
            break;
        }
    }


}

void blink(LED_BlinkConfig led_blinkconfig)
{
    led_on(led_blinkconfig.led_num);
    HAL_Delay(led_blinkconfig.on_ms);
    led_off(led_blinkconfig.led_num);
    HAL_Delay(led_blinkconfig.off_ms);
}

void led_flow(LED_BlinkConfig led_blinkconfig)
{
    while(led_blinkconfig.led_num < LED_COUNT)
    {
        blink(led_blinkconfig);
        led_blinkconfig.led_num ++;
    }

}
