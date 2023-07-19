/*This file is used for control servo*/

#include "main.h"

#ifndef _SREVO_H_
#define _SERVO_H_

void initServoLoct(void);
void writeServoLoct(uint16_t*);

extern uint16_t servoLoct[2];

#endif