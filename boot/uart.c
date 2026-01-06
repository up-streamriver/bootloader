#include "uart.h"
#include <Stdarg.h>

static usart_receive_callback_t usart_receive_callback;

void bl_uart_init(void)
{
    GPIO_InitTypeDef GPIOStructure;
    NVIC_InitTypeDef NVICStructure;
    USART_InitTypeDef USARTStructure;

    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);

    GPIOStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIOStructure.GPIO_OType = GPIO_OType_PP;
    GPIOStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIOStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIOStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIOStructure);
    


    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVICStructure.NVIC_IRQChannel = USART2_IRQn;
    NVICStructure.NVIC_IRQChannelCmd = ENABLE;
    NVICStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVICStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVICStructure);

    USARTStructure.USART_BaudRate = 115200;
    USARTStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USARTStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USARTStructure.USART_Parity = USART_Parity_No;
    USARTStructure.USART_StopBits = USART_StopBits_1;
    USARTStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART2,&USARTStructure);

    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART2,ENABLE);

    esp_usart_write_string("USART2 Initialized!\r\n");
    
}

void usart_receive_callback_register (usart_receive_callback_t callback)
{
        usart_receive_callback = callback;
}

void esp_usart_write_data(uint8_t *data,uint16_t length)
{
    for(int i=0;i<length; i++)
    {
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);
        USART_SendData(USART2,data[i]);
    }
}

void esp_usart_write_string(const char * str)
{
    uint16_t length = strlen(str);
    esp_usart_write_data((uint8_t *)str,length);
}

void usart_printf(const char *format, ...)
{
    char buffer[128];
    va_list args;
    
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    
    esp_usart_write_string(buffer);
}


void USART2_IRQHandler(void)
{
   if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
   {
       uint8_t data = USART_ReceiveData(USART2);
       if(usart_receive_callback)
       {
           usart_receive_callback(data);
       }
       USART_ClearITPendingBit(USART2, USART_IT_RXNE);
   }
}