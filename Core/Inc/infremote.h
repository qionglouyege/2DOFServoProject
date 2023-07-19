/*This file is used for cope with infrared singal*/

#ifndef _INFREMOTE_H_
#define _INFREMOTE_H_
#include "main.h"

/*infrared remote control marco defination*/

#define INFRMT_WAIT_STATE       0
#define INFRMT_DATA_STATE       1

#define INFRMT_BUTTON_1         0xa2u
#define INFRMT_BUTTON_2         0x62u
#define INFRMT_BUTTON_3         0xe2u
#define INFRMT_BUTTON_4         0x22u
#define INFRMT_BUTTON_5         0x02u
#define INFRMT_BUTTON_6         0xc2u
#define INFRMT_BUTTON_7         0xe0u
#define INFRMT_BUTTON_8         0xa8u
#define INFRMT_BUTTON_9         0x90u
#define INFRMT_BUTTON_0         0x98u
#define INFRMT_BUTTON_ASTERISK  0x68u
#define INFRMT_BUTTON_POUND     0xb0u
#define INFRMT_BUTTON_UP        0x18u
#define INFRMT_BUTTON_DOWN      0x4au
#define INFRMT_BUTTON_RIGHT     0x5au
#define INFRMT_BUTTON_LEFT      0x10u
#define INFRMT_BUTTON_OK        0x38u

/*infrared remote control function declaration*/

void infStateInit(void);
void infImplement(uint8_t* , uint8_t*, uint16_t*);

/*infrared remote control variable declaration*/

extern uint8_t infraredState;       //datas tate or waiting state
extern uint8_t exitTimes;           //level changes times, judge if state end
extern uint8_t receivedData[4];     //storage received data, 32bit data, storaged in a 4 element array
extern uint8_t repeatTimes;         //storage repeat time
extern uint16_t levelPeriod;        //storage electric level period
extern uint8_t dataBit;             

#endif