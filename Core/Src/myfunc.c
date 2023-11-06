#include "myfunc.h"
#include "main.h"
/**
 * @brief STM32 sprinf() cannot accept %f, so THIS is a substituted scheme.
 * @warning only can output pure float number. String array 8 enum at least.
*/
void my_sprintfloat(char* string, float data)
{
  if(data > 0)
  {
    uint16_t integralPart = ceil(data);
    uint16_t fractionalPart = ceil((data + 1 - integralPart) * 1000);
    sprintf(string, "+%d.%03d", integralPart - 1, fractionalPart);
  }
  else if(data < 0)
  {
    data = fabs(data);
    uint16_t integralPart = ceil(data);
    uint16_t fractionalPart = ceil((data + 1 - integralPart) * 1000);
    sprintf(string, "-%d.%03d", integralPart - 1, fractionalPart);
  }
  else
  {
    sprintf(string, "0.000");
  }
}

void bulingbuling()
{

  HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, SET);
  HAL_Delay(200);
  HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, RESET);
  HAL_Delay(200);
}