/**
 * @file    led_flow.c
 * @brief   LED_FLOW 驱动实现文件。
 */
#include "led_flow.h"

static const uint8_t mode1_steps[] =
{
    LED1_PIN,
    LED1_PIN,
    LED2_PIN,
    LED2_PIN,
    LED3_PIN,
    LED3_PIN,
    LED4_PIN,
    LED4_PIN
};
#define MODE1_STEPS sizeof(mode1_steps)/sizeof(mode1_steps[0])


static const uint8_t mode2_steps[] =
{
    LED_LEFT,
    LED_LEFT,
    LED_RIGHT,
    LED_RIGHT
};
#define MODE2_STEPS sizeof(mode2_steps)/sizeof(mode2_steps[0])

static const uint8_t mode4_steps[] =
{
    LED_ALL
};
#define MODE4_STEPS sizeof(mode4_steps)/sizeof(mode4_steps[0])

BuzzerBlink buzzerblink_mode2 = {200U,800U};
BuzzerBlink buzzerblink_mode4 = {50U,100U};



void led_flow_statemachine(LED_FLOW_MODE new_mode,LED_FLOW_MODE* current_mode )
{   static timer timer_led = {0,0,0};
    static timer timer_buzzer = {0,0,0};
    static uint8_t current_step = 0;
    if(new_mode != *current_mode)
    {
        *current_mode = new_mode;
        switch (*current_mode)
        {   
            case MODE_0:
            led_set_mask(LED_ALL,GPIO_PIN_RESET);
            buzzer_off();

                break;        
            case MODE_1:
            timer_start(&timer_led);
            led_set_mask(mode1_steps[0],GPIO_PIN_SET);
            buzzer_off();
                break;
            case MODE_2:
            timer_start(&timer_led);
            led_set_mask(mode2_steps[0],GPIO_PIN_SET);
            buzzer_off();
            timer_start(&timer_buzzer);
                break;
            case MODE_4:
            timer_start(&timer_led);
            led_set_mask(mode4_steps[0],GPIO_PIN_SET);
            buzzer_off();
            timer_start(&timer_buzzer);
                break;
        }       
        return ;
    }
        switch (*current_mode)
    {   
        case MODE_0:
            led_set_mask(LED_ALL,GPIO_PIN_RESET);
            break;        
        case MODE_1:
            flow_update(mode1_steps,MODE1_STEPS,&timer_led,&current_step);
            break;
        case MODE_2:
            flow_update(mode2_steps,MODE2_STEPS,&timer_led,&current_step);
            buzzer_blink(&timer_buzzer,buzzerblink_mode2);
            break;
        case MODE_4:
            flow_update(mode4_steps,MODE4_STEPS,&timer_led,&current_step);
            buzzer_blink(&timer_buzzer,buzzerblink_mode4);
            break;
    } 
    return;     
}

void flow_update(uint8_t* mode_step,uint8_t steps,timer* timer,uint8_t* current_step)
{
    if(timer_is_expired(timer,500))
    {
        led_toggle_mask(mode_step[(++(*current_step))%steps]);
        timer_start(timer);
    }


}


