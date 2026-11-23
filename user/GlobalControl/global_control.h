/*
 * @File Name: global_control.h
 * @brief  存放所有自定义的H文件
 * @Author : Brilliancy
 * @Version : 1.0
 * @Creat Date : 2026-11-18
 * 
 */
#ifndef __GLOBAL_CONTROL_H
#define __GLOBAL_CONTROL_H


/* 定义DMA地址 */
#define DMA_RAM __attribute__((section(".dma_buffer"), aligned(32)))


/* C标准库 */

#include "stdio.h"
#include "string.h"


/* 标准库 */
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "fdcan.h"
#include "gpio.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"

/* 自定义库 */
#include "usart_task.h"
#include "motor_FOC.h"
#include "motor_publicdata.h"
#include "ADC_sample.h"


/* 三相电流采样结果：ADC 中断更新，主循环打印 */
extern volatile float g_Iu;
extern volatile float g_Iv;
extern volatile float g_Iw;
extern volatile uint8_t g_print_req;

void Global_Init(void);
void Global_Loop(void);




#endif 


