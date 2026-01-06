#include "board.h"



led_desc_t led0=
{
    .clock_source=RCC_AHB1Periph_GPIOE,
    .port=GPIOE,
    .pin=GPIO_Pin_5,
    .on_lvl=Bit_RESET,
    .off_lvl=Bit_SET,
};

led_desc_t led1=
{
    .clock_source=RCC_AHB1Periph_GPIOE,
    .port=GPIOE,
    .pin=GPIO_Pin_6,
    .on_lvl=Bit_RESET,
    .off_lvl=Bit_SET,
};

led_desc_t led2=
{
    .clock_source=RCC_AHB1Periph_GPIOC,
    .port=GPIOC,
    .pin=GPIO_Pin_13,
    .on_lvl=Bit_RESET,
    .off_lvl=Bit_SET,
};

void board_lowlevel_init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

}