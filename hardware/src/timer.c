#include "timer.h"
#include "stdbool.h"

void timer_start(timer* timer,uint32_t duration)
{
    timer->duration = duration;
    timer->start_time = HAL_GetTick();
    timer->running = 1;

}
bool timer_is_expired (timer* timer)
{
    if(timer->running == 1 && (HAL_GetTick()-timer->start_time)>=timer->duration)
    {
        timer->running = 0;
        return true;
    }
    return false;
}





