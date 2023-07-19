#include "infremote.h"
#include "main.h"
#include "tim.h"

static uint8_t infraredState = INFRMT_WAIT_STATE;
static uint8_t exitTimes = 0;
static uint8_t receivedData[4] = {0b00000000u, 0b00000000u, 0b00000000u, 0b00000000u};
static uint8_t repeatTimes = 0;
static uint16_t levelPeriod = 0;
static uint8_t dataBit = 0;

extern uint16_t servoLoct[2];

/*initialize infrared remote control variable
  if get wrong data, program return here*/
void infStateInit(void)
{
    infraredState = INFRMT_WAIT_STATE;
    __HAL_TIM_SetCounter(&htim2, 0x0);
    exitTimes = 0;
    repeatTimes = 0;
    levelPeriod = 0;
    dataBit = 0;
}

/*when receive data, tigger infrared exit function*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (infraredState)
    {
    /*when in data state*/
    case INFRMT_DATA_STATE:

        if(HAL_GPIO_ReadPin(INFRARED_PIN_GPIO_Port, INFRARED_PIN_Pin) == 1)
        {
            HAL_TIM_Base_Start(&htim2);
            exitTimes ++;
        }
        else if(HAL_GPIO_ReadPin(INFRARED_PIN_GPIO_Port, INFRARED_PIN_Pin) == 0)
        {
            HAL_TIM_Base_Stop(&htim2);
            levelPeriod = __HAL_TIM_GET_COUNTER(&htim2);
            __HAL_TIM_SET_COUNTER(&htim2, 0);
            exitTimes ++;

            if(levelPeriod > 1550 && levelPeriod < 1750)
                dataBit = 1;
            else if(levelPeriod > 460 && levelPeriod < 660)
                dataBit = 0;
            else infStateInit();

            if(exitTimes <= 64)
            {
                *(receivedData + (exitTimes - 1) / 16) = *(receivedData + (exitTimes - 1) / 16) << 1;
                *(receivedData + (exitTimes - 1) / 16) = *(receivedData + (exitTimes - 1) / 16) + dataBit;
            }
        }

        if(exitTimes == 65)
        {
            infraredState = INFRMT_WAIT_STATE;
            repeatTimes ++;
            exitTimes = 0;
        }   
        break;

    /*when in wait state*/
    case INFRMT_WAIT_STATE:

        switch (exitTimes)
        {
        case 0:
          if(HAL_GPIO_ReadPin(INFRARED_PIN_GPIO_Port, INFRARED_PIN_Pin) == 0)
          {
            __HAL_TIM_SetCounter(&htim2, 0);
            HAL_TIM_Base_Start(&htim2);
            exitTimes ++;
          }
          else exitTimes = 0;

            break;
        
        case 1:
            HAL_TIM_Base_Stop(&htim2);
            levelPeriod = __HAL_TIM_GetCounter(&htim2);
             if(levelPeriod > 8000 && levelPeriod <10000)
            {
                __HAL_TIM_SetCounter(&htim2, 0);
                HAL_TIM_Base_Start(&htim2);
                exitTimes ++;
            }
            else infStateInit();
            break;

        case 2:
            HAL_TIM_Base_Stop(&htim2);
            levelPeriod = __HAL_TIM_GetCounter(&htim2);
            if(levelPeriod > 3500 && levelPeriod <5500)     //enter DATA_STATE here
            {
                __HAL_TIM_SetCounter(&htim2, 0);
                HAL_TIM_Base_Stop(&htim2);
                infraredState = INFRMT_DATA_STATE;
                exitTimes = 0;
                repeatTimes = 0;
            }
            else if(levelPeriod > 1500 && levelPeriod < 3500)
            {
                __HAL_TIM_SetCounter(&htim2, 0);
                HAL_TIM_Base_Start(&htim2);
                exitTimes ++;
            }
            else infStateInit();
            break;

        case 3:
            HAL_TIM_Base_Stop(&htim2);
            levelPeriod = __HAL_TIM_GetCounter(&htim2);
            if(levelPeriod > 460 && levelPeriod <660)       //increase repeat_Time here
            {
                __HAL_TIM_SetCounter(&htim2, 0);
                repeatTimes ++;
                exitTimes = 0;
            }
            else infStateInit();

        default:
            break;
        }
        break;

    default:
        break;
    }
}

/*act different operation*/
void infImplement()
{
    switch (*(receivedData + 2))
    {
      case INFRMT_BUTTON_1:
      for(; repeatTimes > 0;)
      {
        (repeatTimes) --;
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, RESET);
        HAL_Delay(100);
      }
        break;

      case INFRMT_BUTTON_2:
      for(; repeatTimes > 0;)
      {
        (repeatTimes) --;
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, SET);
        HAL_Delay(200);
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, RESET);
        HAL_Delay(200);
      }
        break;   

      case INFRMT_BUTTON_3:
      for(; repeatTimes > 0;)
      {
        (repeatTimes) --;
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, SET);
        HAL_Delay(300);
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, RESET);
        HAL_Delay(300);
      }
        break; 

      case INFRMT_BUTTON_4:
      for(; repeatTimes > 0;)
      {
        (repeatTimes) --;
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, SET);
        HAL_Delay(400);
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, RESET);
        HAL_Delay(400);
      }
        break; 

      case INFRMT_BUTTON_5:
      for(; repeatTimes > 0;)
      {
        (repeatTimes) --;
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, SET);
        HAL_Delay(500);
        HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, RESET);
        HAL_Delay(500);
      }
        break; 

      case INFRMT_BUTTON_UP:
      for(;repeatTimes > 0; )
      {
        (repeatTimes) --;
        *(servoLoct + 1) += 100;
      }
        break;

      case INFRMT_BUTTON_DOWN:
      for(; repeatTimes > 0; )
      {
        (repeatTimes) --;
        *(servoLoct + 1) -= 100;
      }
        break;

      case INFRMT_BUTTON_LEFT:
      for(; repeatTimes > 0; )
      {
        (repeatTimes) --;
        *(servoLoct + 0) -= 100;
      }
        break;            

      case INFRMT_BUTTON_RIGHT:
      for(; repeatTimes > 0;)
      {
        (repeatTimes) --;
        *(servoLoct + 0) += 100;
      }
        break;  

    default:
      break;
    }
}