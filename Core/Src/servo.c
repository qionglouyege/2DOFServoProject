#include "main.h"
#include "servo.h"
#include "tim.h"

/*servoLoct[0] is yaw, servoLoct[1] is pitch.*/
float servoLoct[2] = {1000, 1000};

void initServoLoct(void)
{
    for(int i = 0; i < 2; i++)
        *(servoLoct + i) = 1000;
}

void writeServoLoct(void)
{
    if(((uint16_t)*(servoLoct + 0) >= 440) && ((uint16_t)*(servoLoct + 0) <= 1500));
    else *(servoLoct + 0) = 1000;

    if(((uint16_t)*(servoLoct + 1) >= 440) && ((uint16_t)*(servoLoct + 1) <= 1500));
    else *(servoLoct + 1) = 1000;

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, (uint16_t)*(servoLoct + 0));
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, (uint16_t)*(servoLoct + 1));
}