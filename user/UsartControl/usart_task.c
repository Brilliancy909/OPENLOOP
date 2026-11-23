/*
 * @File Name: usart_task.c
 * @brief  串口收发任务与非阻塞 DMA 发送
 * @Author : Brilliancy
 * @Version : 1.1
 * @Creat Date : 2026-11-18
 * @note   发送数据先写入环形缓冲，由 DMA 分段搬出，调用方不阻塞；
 *         缓冲满时丢弃超出部分（400Hz 数据流下不会丢）。
 */
#include "global_control.h"

#define UART_TX_RING_SIZE 256U /* 环形缓冲大小，含 1 个保留空位 */

/* DMA 发送环形缓冲（必须在 DMA 可访问的 D2 SRAM） */
DMA_RAM static uint8_t s_uart_tx_ring[UART_TX_RING_SIZE];
static volatile uint16_t s_uart_tx_head = 0U;       /* 写入位置 */
static volatile uint16_t s_uart_tx_tail = 0U;       /* DMA 发送位置 */
static volatile uint16_t s_uart_tx_active_len = 0U; /* 当前 DMA 长度 */
static volatile uint8_t s_uart_tx_busy = 0U;        /* 1: DMA 发送中 */

/**
 * @brief  启动下一段 DMA 发送
 * @param  none
 * @retval none
 * @note   可在中断上下文调用，由 UART_Tx_Write 和发送完成回调触发
 */
static void UART_Tx_Kick(void)
{
    uint16_t len;
    uint32_t primask;

    primask = __get_PRIMASK();
    __disable_irq();

    if ((s_uart_tx_busy != 0U) || (s_uart_tx_head == s_uart_tx_tail))
    {
        __set_PRIMASK(primask);
        return;
    }

    if (s_uart_tx_tail < s_uart_tx_head)
    {
        len = (uint16_t)(s_uart_tx_head - s_uart_tx_tail);
    }
    else
    {
        len = (uint16_t)(UART_TX_RING_SIZE - s_uart_tx_tail);
    }

    s_uart_tx_active_len = len;
    s_uart_tx_busy = 1U;

    if (HAL_UART_Transmit_DMA(&huart3, &s_uart_tx_ring[s_uart_tx_tail], len)
        != HAL_OK)
    {
        s_uart_tx_active_len = 0U;
        s_uart_tx_busy = 0U;
    }

    __set_PRIMASK(primask);
}

/**
 * @brief  非阻塞写串口发送缓冲
 * @param  data: 待发送数据，不能为 NULL
 * @param  len: 数据长度，单位字节
 * @retval 实际写入缓冲的字节数，缓冲满时小于 len
 * @note   可在中断上下文调用，写入后由 DMA 自动发送
 */
uint16_t UART_Tx_Write(const uint8_t *data, uint16_t len)
{
    uint16_t written = 0U;
    uint16_t next;
    uint32_t primask;

    if ((data == NULL) || (len == 0U))
    {
        return 0U;
    }

    primask = __get_PRIMASK();
    __disable_irq();

    while (written < len)
    {
        next = (uint16_t)((s_uart_tx_head + 1U) % UART_TX_RING_SIZE);
        if (next == s_uart_tx_tail)
        {
            break; /* 缓冲已满，丢弃剩余数据 */
        }

        s_uart_tx_ring[s_uart_tx_head] = data[written];
        s_uart_tx_head = next;
        written++;
    }

    __set_PRIMASK(primask);

    UART_Tx_Kick();

    return written;
}

/**
 * @brief  DMA 发送完成回调
 * @param  huart: 串口句柄
 * @retval none
 * @note   推进环形缓冲读指针，并启动下一段发送
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART3)
    {
        s_uart_tx_tail = (uint16_t)((s_uart_tx_tail + s_uart_tx_active_len)
                                    % UART_TX_RING_SIZE);
        s_uart_tx_active_len = 0U;
        s_uart_tx_busy = 0U;
        UART_Tx_Kick();
    }
}

/**
 * @brief  printf 底层写函数，重定向到 DMA 发送
 * @param  file: 文件描述符，未使用
 * @param  ptr: 待发送数据
 * @param  len: 数据长度
 * @retval 返回 len，按发送成功处理
 * @note   覆盖 syscalls.c 中的弱定义；非阻塞，缓冲满时数据丢弃
 */
int _write(int file, char *ptr, int len)
{
    (void)file;

    if (len > 0)
    {
        (void)UART_Tx_Write((const uint8_t *)ptr, (uint16_t)len);
    }

    return len;
}

/**
 * @brief  单字节输出重定向
 * @param  ch: 待发送字符
 * @retval 返回发送的字符
 * @note   printf 走 _write；此函数仅供直接调用，非阻塞
 */
int __io_putchar(int ch)
{
    uint8_t byte = (uint8_t)ch;

    (void)UART_Tx_Write(&byte, 1U);

    return ch;
}

void Usart_Task(void)
{
}
