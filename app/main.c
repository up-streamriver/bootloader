
/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015-2017, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: windows demo.
 * Created on: 2015-07-30
 */

#define LOG_TAG    "main"

#include <elog.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "ringbuffer.h"

#define bl_uart_recv_buffer_size 256

static ringbuffer8_t serial_rb;
static uint8_t bl_uart_recv_buffer[bl_uart_recv_buffer_size];

static void test_elog(void);

void process_receive_data (uint8_t data)
{
    while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
    esp_usart_write_data(&data,1);
}

void process_ringbuffer_data (uint8_t data)
{
    while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) != SET);
    rb8_puts(serial_rb,&data,1);

}

// void dma_receive_callback_func(uint8_t* data, uint16_t length)
// {
//     usart_printf("\r\n[DMA Callback] Received %d bytes: ", length);
//     for(uint16_t i = 0; i < length; i++)
//     {
//         esp_usart_write_data(&data[i], 1);
//     }
//     usart_printf("\r\n");
// }


int main(void)
{
    board_lowlevel_init();
    serial_rb = rb8_new(bl_uart_recv_buffer,bl_uart_recv_buffer_size);
    usart_receive_callback_register (process_ringbuffer_data);
    bl_uart_init();
	usart_printf("Counter");
    


		while(1)
		{
            uint8_t rdata;
            if(rb8_get(serial_rb,&rdata))
                esp_usart_write_data(&rdata,1);
		}

}

/**
 * EasyLogger demo
 */
void test_elog(void) {
    while(true) {
        /* test log output for all level */
        log_a("Hello EasyLogger!");
        log_e("Hello EasyLogger!");
        log_w("Hello EasyLogger!");
        log_i("Hello EasyLogger!");
        log_d("Hello EasyLogger!");
        log_v("Hello EasyLogger!");
//        elog_raw("Hello EasyLogger!");

    }
}
