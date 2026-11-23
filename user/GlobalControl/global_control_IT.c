/*
 * @File Name: global_control_IT.c
 * @brief  处理全局中断回调函数
 * @Author : Brilliancy
 * @Version : 1.0
 * @Creat Date : 2026-11-18
 * 
 */
#include "ADC_sample.h"
#include "global_control.h"
#include "motor_publicdata.h"
#include "stm32h750xx.h"
#include <stdint.h>

extern uint8_t Uart_RX[100]; /* 串口接收数组 */
extern uint8_t Uart_TX[100]; /* 串口发送数组 */

/* 三相电流采样结果：中断里更新，主循环打印（避免在中断里阻塞发送串口） */
volatile float g_Iu = 0.0f;
volatile float g_Iv = 0.0f;
volatile float g_Iw = 0.0f;
volatile uint8_t g_print_req = 0U;

#define ADC_PRINT_DIV 50U /* 20kHz / 50 = 400Hz 串口输出 */
static uint32_t s_print_div = 0U;
/*
 * @brief  串口回调函数
 * @param 
 * @return  
 * @note
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART3)
    {
        /* 收到的数据回显：走统一的非阻塞 DMA 发送环形缓冲 */
        (void)UART_Tx_Write((const uint8_t *)Uart_RX, Size);
        HAL_UARTEx_ReceiveToIdle_DMA(&huart3, Uart_RX, sizeof(Uart_RX));
        __HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT);
    }
}

/*
 * @brief  ADC注入结束回调函数
 * @param 
 * @return  
 * @note
 */
void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    uint16_t temp[2];

    if (hadc->Instance == ADC1)
    {
        /* 中心对齐模式下每个 PWM 周期上溢(峰点)和下溢(谷点)各触发一次：
           峰点时三相输出全高、下桥臂全关，分流电阻上无电流，采到的无效；
           只处理谷点(CNT≈0，零矢量中心)的样本，等效采样率 20kHz。
           注意：若后续把 TIM1 的 RepetitionCounter 改为 1，需确认 UEV
           落在谷点，不要再叠加此软件过滤。 */
        if (htim1.Instance->CNT > (htim1.Instance->ARR >> 1))
        {
            return;
        }

        temp[0] = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_1);
        temp[1] = HAL_ADCEx_InjectedGetValue(hadc, ADC_INJECTED_RANK_2);
        Current_UVW.Iu = ADC_Raw_To_Current(temp[0]);
        Current_UVW.Iw = ADC_Raw_To_Current(temp[1]);
        Current_UVW.Iv = -Current_UVW.Iu - Current_UVW.Iw;

        /* 快照给主循环打印，保证三个值来自同一次采样 */
        g_Iu = Current_UVW.Iu;
        g_Iv = Current_UVW.Iv;
        g_Iw = Current_UVW.Iw;

        Air_value[0] = ADC_Raw_To_Air(ADC_BUFF[0]);
        Air_value[1] = ADC_Raw_To_Air(ADC_BUFF[1]);
        Temperature = ADC_Raw_To_temperature(ADC_BUFF[2]);

        MOTOR_RUN();

        if (++s_print_div >= ADC_PRINT_DIV)
        {
            s_print_div = 0U;
            g_print_req = 1U;
        }
    }

    if (hadc->Instance == ADC2)
    {
    }
    if (hadc->Instance == ADC3)
    {
        //
    }


}

/*
 * @brief  定时器更新中断回调函数
 * @param 
 * @return  
 * @note
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1)
    {
    }
    if (htim->Instance == TIM8)
    {
    }
}
