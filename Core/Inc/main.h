/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Negative_Pressure_0_Pin GPIO_PIN_2
#define Negative_Pressure_0_GPIO_Port GPIOE
#define Negative_Pressure_1_Pin GPIO_PIN_3
#define Negative_Pressure_1_GPIO_Port GPIOE
#define Positive__Pressure_0_Pin GPIO_PIN_4
#define Positive__Pressure_0_GPIO_Port GPIOE
#define Positive__Pressure_1_Pin GPIO_PIN_5
#define Positive__Pressure_1_GPIO_Port GPIOE
#define Air_ADC_0_Pin GPIO_PIN_0
#define Air_ADC_0_GPIO_Port GPIOC
#define Air_ADC_1_Pin GPIO_PIN_1
#define Air_ADC_1_GPIO_Port GPIOC
#define Voltage_U_0_Pin GPIO_PIN_0
#define Voltage_U_0_GPIO_Port GPIOA
#define Voltage_W_0_Pin GPIO_PIN_1
#define Voltage_W_0_GPIO_Port GPIOA
#define Voltage_U_1_Pin GPIO_PIN_2
#define Voltage_U_1_GPIO_Port GPIOA
#define Voltage_W_1_Pin GPIO_PIN_3
#define Voltage_W_1_GPIO_Port GPIOA
#define Sensor_Home_0_Pin GPIO_PIN_4
#define Sensor_Home_0_GPIO_Port GPIOA
#define Encoder_A_1_Pin GPIO_PIN_5
#define Encoder_A_1_GPIO_Port GPIOA
#define Encoder_A_0_Pin GPIO_PIN_6
#define Encoder_A_0_GPIO_Port GPIOA
#define Encoder_B_0_Pin GPIO_PIN_7
#define Encoder_B_0_GPIO_Port GPIOA
#define Sensor_Home_1_Pin GPIO_PIN_4
#define Sensor_Home_1_GPIO_Port GPIOC
#define Sensor_Home_2_Pin GPIO_PIN_5
#define Sensor_Home_2_GPIO_Port GPIOC
#define Sensor_Home_3_Pin GPIO_PIN_0
#define Sensor_Home_3_GPIO_Port GPIOB
#define Sensor_Home_4_Pin GPIO_PIN_1
#define Sensor_Home_4_GPIO_Port GPIOB
#define Sensor_Home_5_Pin GPIO_PIN_2
#define Sensor_Home_5_GPIO_Port GPIOB
#define Sensor_Home_6_Pin GPIO_PIN_7
#define Sensor_Home_6_GPIO_Port GPIOE
#define Sensor_Home_7_Pin GPIO_PIN_8
#define Sensor_Home_7_GPIO_Port GPIOE
#define PWM_A_0_Pin GPIO_PIN_9
#define PWM_A_0_GPIO_Port GPIOE
#define Sensor_Home_8_Pin GPIO_PIN_10
#define Sensor_Home_8_GPIO_Port GPIOE
#define PWM_U_0_Pin GPIO_PIN_11
#define PWM_U_0_GPIO_Port GPIOE
#define Sensor_Home_9_Pin GPIO_PIN_12
#define Sensor_Home_9_GPIO_Port GPIOE
#define PWM_V_0_Pin GPIO_PIN_13
#define PWM_V_0_GPIO_Port GPIOE
#define PWM_W_0_Pin GPIO_PIN_14
#define PWM_W_0_GPIO_Port GPIOE
#define PWM_BK_0_Pin GPIO_PIN_15
#define PWM_BK_0_GPIO_Port GPIOE
#define Encoder_Z_1_Pin GPIO_PIN_10
#define Encoder_Z_1_GPIO_Port GPIOB
#define PWM_EN_0_Pin GPIO_PIN_12
#define PWM_EN_0_GPIO_Port GPIOB
#define LED_G_0_Pin GPIO_PIN_14
#define LED_G_0_GPIO_Port GPIOB
#define LED_R_0_Pin GPIO_PIN_15
#define LED_R_0_GPIO_Port GPIOB
#define LED_G_1_Pin GPIO_PIN_8
#define LED_G_1_GPIO_Port GPIOD
#define LED_R_1_Pin GPIO_PIN_9
#define LED_R_1_GPIO_Port GPIOD
#define FAN_ZK_Pin GPIO_PIN_11
#define FAN_ZK_GPIO_Port GPIOD
#define CAM0_ZK_Pin GPIO_PIN_12
#define CAM0_ZK_GPIO_Port GPIOD
#define CAM1_ZK_Pin GPIO_PIN_13
#define CAM1_ZK_GPIO_Port GPIOD
#define CAM2_ZK_Pin GPIO_PIN_14
#define CAM2_ZK_GPIO_Port GPIOD
#define Encoder_485_EN_1_Pin GPIO_PIN_15
#define Encoder_485_EN_1_GPIO_Port GPIOD
#define PWM_A_1_Pin GPIO_PIN_6
#define PWM_A_1_GPIO_Port GPIOC
#define PWM_U_1_Pin GPIO_PIN_7
#define PWM_U_1_GPIO_Port GPIOC
#define PWM_V_1_Pin GPIO_PIN_8
#define PWM_V_1_GPIO_Port GPIOC
#define PWM_W_1_Pin GPIO_PIN_9
#define PWM_W_1_GPIO_Port GPIOC
#define PWM_BK_1_Pin GPIO_PIN_8
#define PWM_BK_1_GPIO_Port GPIOA
#define PWM_EN_1_Pin GPIO_PIN_9
#define PWM_EN_1_GPIO_Port GPIOA
#define Encoder_485_RX_0_Pin GPIO_PIN_11
#define Encoder_485_RX_0_GPIO_Port GPIOA
#define Encoder_485_TX_0_Pin GPIO_PIN_12
#define Encoder_485_TX_0_GPIO_Port GPIOA
#define Encoder_485_EN_0_Pin GPIO_PIN_15
#define Encoder_485_EN_0_GPIO_Port GPIOA
#define R232_TX_Pin GPIO_PIN_10
#define R232_TX_GPIO_Port GPIOC
#define R232_RX_Pin GPIO_PIN_11
#define R232_RX_GPIO_Port GPIOC
#define CAN_RX_Pin GPIO_PIN_0
#define CAN_RX_GPIO_Port GPIOD
#define CAN_TX_Pin GPIO_PIN_1
#define CAN_TX_GPIO_Port GPIOD
#define CHIP_ID_0_Pin GPIO_PIN_2
#define CHIP_ID_0_GPIO_Port GPIOD
#define CHIP_ID_1_Pin GPIO_PIN_3
#define CHIP_ID_1_GPIO_Port GPIOD
#define CARD_ID_0_Pin GPIO_PIN_4
#define CARD_ID_0_GPIO_Port GPIOD
#define CARD_ID_1_Pin GPIO_PIN_5
#define CARD_ID_1_GPIO_Port GPIOD
#define CARD_ID_2_Pin GPIO_PIN_6
#define CARD_ID_2_GPIO_Port GPIOD
#define CARD_ID_3_Pin GPIO_PIN_7
#define CARD_ID_3_GPIO_Port GPIOD
#define Encoder_B_1_Pin GPIO_PIN_3
#define Encoder_B_1_GPIO_Port GPIOB
#define Encoder_Z_0_Pin GPIO_PIN_6
#define Encoder_Z_0_GPIO_Port GPIOB
#define Encoder_485_RX_1_Pin GPIO_PIN_0
#define Encoder_485_RX_1_GPIO_Port GPIOE
#define Encoder_485_TX_1_Pin GPIO_PIN_1
#define Encoder_485_TX_1_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
