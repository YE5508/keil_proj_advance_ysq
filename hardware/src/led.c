/**
 * @file    led.c
 * @brief   LED 驱动实现文件。
 */
#include "led.h"
#include "stdbool.h"


static LED_BlinkConfig led_blinkconfig = {0U, 250U, 125U};



static inline bool is_led_valid(uint8_t led_num)
{
    return (led_num < LED_COUNT);
}

/* 点亮 LED1 */
static void led_on(uint8_t led_num)
{
    if(!is_led_valid(led_num))
    {
        return;
    }    
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

/* 熄灭 LED led_num */
static void led_off(uint8_t led_num)
{
        if(!is_led_valid(led_num))
    {
        return;
    }    
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

static void blink_1(void)
{
    led_on(led_blinkconfig.led_num);
    HAL_Delay(led_blinkconfig.on_ms);
    led_off(led_blinkconfig.led_num);
    HAL_Delay(led_blinkconfig.off_ms);
}

static void blink_2(void)
{
    uint8_t led_num1 = led_blinkconfig.led_num;
    uint8_t led_num2 = (led_blinkconfig.led_num+1)%4;
    led_on(led_num1);
    led_on(led_num2);
    HAL_Delay(led_blinkconfig.on_ms);
    led_off(led_num1);
    led_off(led_num2);
    HAL_Delay(led_blinkconfig.off_ms);
}

static void blink_4(void)
{
    for (uint8_t i =0;i<LED_COUNT;i++)
    {
        led_on(i);
    }
    HAL_Delay(led_blinkconfig.on_ms);
    for (uint8_t i =0;i<LED_COUNT;i++)
    {
        led_off(i);
    }
    HAL_Delay(led_blinkconfig.off_ms);
}

static void led_flow_1(void)
{
    while(led_blinkconfig.led_num < LED_COUNT)
    {
        blink_1();
        led_blinkconfig.led_num ++;
    }

}

static void led_flow_2(void)
{
    while(led_blinkconfig.led_num < LED_COUNT)
    {
        blink_2();
        led_blinkconfig.led_num ++;
    }

}

static void led_flow_4(void)
{
    while(led_blinkconfig.led_num < LED_COUNT)
    {
        blink_4();
        led_blinkconfig.led_num ++;
    }

}


/* led.c 内部：唯一的底层写入口 */
static void led_write_mask(uint16_t pin_mask, GPIO_PinState state)
{
    HAL_GPIO_WritePin(LED_GPIO_PORT, pin_mask, state);
}

void led_set_mask(uint16_t pin_mask, GPIO_PinState state)
{
    led_write_mask(pin_mask, state);
}

void led_toggle_mask(uint16_t pin_mask)
{
    HAL_GPIO_TogglePin(LED_GPIO_PORT, pin_mask);
}

