#include "main.h"
#include "servo.h"
#include "tim.h"

uint16_t servoLoct[2] = {1000, 1000};

void initServoLoct(void)
{
    for(int i = 0; i < 2; i++)
        *(servoLoct + i) = 1000;
}

void writeServoLoct(uint16_t* servoLoct)
{
    if((*(servoLoct + 0) >= 440) && (*(servoLoct + 0) <= 1500));
    else *(servoLoct + 0) = 1000;

    if((*(servoLoct + 1) >= 440) && (*(servoLoct + 1) <= 1500));
    else *(servoLoct + 1) = 1000;

    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, *(servoLoct + 0));
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, *(servoLoct + 1));
}