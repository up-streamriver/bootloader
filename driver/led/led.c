#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include "board.h"
#include "led.h"

void led_init(const led_desc_t *desc)
{
   RCC_AHB1PeriphClockCmd(desc->clock_source,ENABLE);
   GPIO_InitTypeDef ginit;
   ginit.GPIO_Mode=GPIO_Mode_OUT;
   ginit.GPIO_OType=GPIO_OType_PP;
   ginit.GPIO_Speed=GPIO_Speed_25MHz;
   ginit.GPIO_Pin=desc->pin;
   GPIO_Init(desc->port,&ginit);
};

void led_deinit(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port,desc->pin,desc->off_lvl);
}

void led_off(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port,desc->pin,desc->off_lvl);
}

void led_on(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port,desc->pin,desc->on_lvl);
}

