#include "main.h"
#include "servo.h"
#include "tim.h"

/*servoLoct[0] is yaw[A10], servoLoct[1] is pitch[A11].*/
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


/** 
 * @brief Adjust Servo position, delete position error via PID control.
 * @param error Get Picture capture position error.
 * @return Servo need to add or sub location.*/
float adjustServoViaError(int8_t error)
{
  static int8_t errorLast = 0;
  static float errorI = 0;
  errorI += error * COE_I;
  float errorP = error * COE_P;
  float errorD = (error - errorLast) * COE_D;

  return errorP + errorI + errorD;
}