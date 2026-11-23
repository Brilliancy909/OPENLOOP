/*
 * @File Name: global_control.c
 * @brief  自定义循环
 * @Author : Brilliancy
 * @Version : 1.0
 * @Creat Date : 2026-11-18
 * 
 */
#include "global_control.h"
#include "main.h"
#include "motor_FOC.h"
#include "motor_foc.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_tim.h"
#include "stm32h7xx_hal_tim_ex.h"
#include "tim.h"
#include <stdint.h>
#include <stdio.h>

DMA_RAM uint8_t Uart_RX[100]; /* 串口接收数组 */
DMA_RAM uint8_t Uart_TX[100]; /* 串口发送数组 */

/*
 * @brief  全局初始化
 * @param
 * @return
 * @note
 */
void Global_Init(void)
{
    /* FOC参数初始化 */
    FOC_Init();

    /* 串口通信正常确认 */
    printf("Hello MOJE - DMA Printf Ready\r\n");

    /* 串口接收触发 */
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)Uart_RX, sizeof(Uart_RX));
    __HAL_DMA_DISABLE_IT(huart3.hdmarx, DMA_IT_HT);

    /* ADC校准 */
    HAL_ADCEx_Calibration_Start(&hadc1, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc2, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_Delay(3);

    /* ADC注入组开启 */
    HAL_ADCEx_InjectedStart_IT(&hadc1);
    HAL_ADCEx_InjectedStart_IT(&hadc2);

    /* 规则组采集开始 */
    HAL_ADC_Start_DMA(&hadc3, (uint32_t *)ADC_BUFF, 3);

    /* 开启TIM中断：更新中断没有用到（回调为空），去掉后少 2 路 40kHz 中断；
       计数器由下面的 HAL_TIM_PWM_Start 使能，TRGO 触发不依赖 UIE 位 */
    /* HAL_TIM_Base_Start_IT(&htim1); */
    /* HAL_TIM_Base_Start_IT(&htim8); */

    /* PWM输出通道打开 */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);

    /* PWM输出使能 */
    HAL_GPIO_WritePin(PWM_EN_0_GPIO_Port, PWM_EN_0_Pin, SET);
    HAL_GPIO_WritePin(PWM_EN_1_GPIO_Port, PWM_EN_1_Pin, SET);
}

/*
 * @brief  全局循环
 * @param 
 * @return  
 * @note
 */
void Global_Loop(void)
{
    /* 三相电流打印放到主循环：ADC 中断里只更新数据，400Hz 输出
       (400Hz × ~20 字节 ≈ 8kB/s，远低于 1152000bps 的 ~115kB/s) */
    // if (g_print_req != 0U)
    // {
    //     g_print_req = 0U;
    //     printf("%.2f,%.2f,%.2f\n", g_Iu, g_Iv, g_Iw);
    // }
    // printf("%f,%f,%f\n", rtY.Tcmp1, rtY.Tcmp2, rtY.Tcmp3);
         printf("%.2f,%.2f,%.2f\n", g_Iu, g_Iv, g_Iw);
}
