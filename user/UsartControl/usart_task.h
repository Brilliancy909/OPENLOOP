#ifndef __USART_TASK_H
#define __USART_TASK_H

#include "global_control.h"

#define CH_COUNT 3
typedef struct
{
    float fdata[CH_COUNT];
    uint8_t tail[4];
} TXDATA;

void Usart_Task(void);
int __io_putchar(int ch);

/**
 * @brief  非阻塞写串口发送缓冲
 * @param  data: 待发送数据，不能为 NULL
 * @param  len: 数据长度，单位字节
 * @retval 实际写入缓冲的字节数，缓冲满时小于 len
 * @note   可在中断上下文调用，写入后由 DMA 自动发送
 */
uint16_t UART_Tx_Write(const uint8_t *data, uint16_t len);

#endif
