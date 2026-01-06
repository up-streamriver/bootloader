#ifndef __UART_H
#define __UART_H


#include <stdbool.h>
#include "stm32f4xx.h"

typedef void (*usart_receive_callback_t) (uint8_t data);
void bl_uart_init(void);
void usart_receive_callback_register (usart_receive_callback_t callback);
void esp_usart_write_string(const char * str);
void usart_printf(const char *format, ...);

#endif /* __UART_H */
