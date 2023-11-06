# 描述

这个项目是2自由度舵机云台控制的项目，旨在做一个二自由度的稳瞄追踪控制，
这个项目作为一个demo，以便加深对二自由度控制的印象，更好的完成项目。

这个项目使用STM32F103C8T6作为控制板，

首先引出两路PWM信号作为舵机的控制信号。

## 20230702
- PWM和GIPO定时器不能公用，共用会出莫名其妙的问题

## 20230719
- 不能一直循环while1
- tim1 pwm波
- tim2 红外
- tim3 串口发送定时器
- tim4 函数执行定时器
- 注意串口优先级 usart2 为1 tim3 为2 gpio为0

## 20230814
### 引脚定义：
- PB7:`I2C1_SDA` I2C数据线
- PB6:`I2C1_SCL` I2C时钟线
- PA11:`PITCH_SERVO_PIN` 舵机俯仰PWM控制
- PA10:`YAW_SERVO_PIN` 舵机偏航PWM控制
- PA9:`INFRARED_PIN` 红外接收信号
- PA8:`LED_PIN` LED小灯信号
- PA2:`USART2_TX` 串口发
- PA3:`USART2_RX` 串口收

## 20230904
### 串口与单片机的通信协议规定：
- 每次发送8字节，用一个字符串数组：`char usartBufffer[8]`存储收发的数据
- 再次复习一下stm32发送接收数据的模式：
  1.阻塞式串口发送`HAL_UART_Transmit`：发送未完成时函数阻塞
  2.非阻塞式串口发送`HAL_UART_Transmit_IT`：发送一半时或完毕后响应发送中断：
    中断函数为`HAL_UART_TxCpltCallback`和`HAL_UART_TxHalfCpltCallback`。
  3.阻塞式串口接收`HAL_UART_Receive`：接收未完成时函数阻塞
  4.非阻塞式串口接收`HAL_UART_Receive_IT`：接收一半时或完毕后响应发送中断：
    中断函数为`HAL_UART_RxCpltCallback`和`HAL_UART_RxHalfCpltCallback`。
### 关于PID控制，其公式为
  $$ $$
  PID系数作为宏写在了servo.h里。


## 20230906
- 自己写的打印浮点数的函数不能用，用了就会占用

## 20231106
- 串口发送和接收字节可以设置为1 这样一次收发一个，可以精确控制,(而且bug会少。之前各种莫名奇妙的bug都是来源于此，设置8个字节一起发送)
- 收串口发送的数据时是无符号数，在进行计算时要解释成有符号数才可以