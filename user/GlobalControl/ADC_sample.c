#include "global_control.h"
#include <stdio.h>

DMA_RAM uint16_t ADC_BUFF[3]; /* 气压和温度采集数组 */
uint16_t Air_value[2];        /* 气压值 */
float Temperature;            /* 温度值 */
/*
 * @brief  ADC采样电流
 * @param 
 * @return  
 * @note
 */
float ADC_Raw_To_Current(uint16_t raw)
{
    float voltage;
    voltage = (float)(raw * ADC_VREF / ADC_RESOLUTION - 1.65f) / (5.1f * 0.05f);

    return voltage;
}

/*
 * @brief  ADC采样气压
 * @param 
 * @return  
 * @note
 */
float ADC_Raw_To_Air(uint16_t raw)
{
    float Air;

    Air = (float)(raw * ADC_VREF / ADC_RESOLUTION / 0.6f - 0.2f) / 0.045f;

    return Air;
}

/*
 * @brief  ADC采样温度
 * @param 
 * @return  
 * @note
 */
float ADC_Raw_To_temperature(uint16_t raw)
{
    float value;
    
    uint16_t ts_cal1 = *(uint16_t *)TS_CAL1_ADDR;
    uint16_t ts_cal2 = *(uint16_t *)TS_CAL2_ADDR;
    // T = (110 - 30) / (CAL2 - CAL1) * (ADC_Data - CAL1) + 30
    value = (80.0f / (float)(ts_cal2 - ts_cal1)) * ((float)raw - (float)ts_cal1) + 30.0f;

    return value;
}