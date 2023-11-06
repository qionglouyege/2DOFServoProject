/*This file is used for control servo*/

#include "main.h"

#ifndef _SREVO_H_
#define _SERVO_H_

#define COE_P 0.1;
#define COE_I 0.1;
#define COE_D 0.1;

void initServoLoct(void);
void writeServoLoct(void);

float adjustServoViaError(int8_t error);

#endif