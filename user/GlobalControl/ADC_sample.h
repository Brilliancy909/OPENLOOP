
#ifndef __ADC_SAMPELE_H
#define __ADC_SAMPELE_H

#include "global_control.h"

/* ADC温度校准值 */
#define TS_CAL1_ADDR 0x1FF1E820 // 30℃ 时的 ADC 校准值
#define TS_CAL2_ADDR 0X1FF1E840 // 110℃ 时的 ADC 校准值

extern uint16_t ADC_BUFF[3];
extern uint16_t Air_value[2];
extern float Temperature;

float ADC_Raw_To_Current(uint16_t raw);
float ADC_Raw_To_Air(uint16_t raw);
float ADC_Raw_To_temperature(uint16_t raw);

#endif
