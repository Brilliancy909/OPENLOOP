/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins
     PH0-OSC_IN (PH0)   ------> RCC_OSC_IN
     PA13 (JTMS/SWDIO)   ------> DEBUG_JTMS-SWDIO
     PA14 (JTCK/SWCLK)   ------> DEBUG_JTCK-SWCLK
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, Negative_Pressure_0_Pin|Negative_Pressure_1_Pin|Positive__Pressure_0_Pin|Positive__Pressure_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PWM_EN_0_Pin|LED_G_0_Pin|LED_R_0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LED_G_1_Pin|LED_R_1_Pin|FAN_ZK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PWM_EN_1_GPIO_Port, PWM_EN_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Negative_Pressure_0_Pin Negative_Pressure_1_Pin Positive__Pressure_0_Pin Positive__Pressure_1_Pin */
  GPIO_InitStruct.Pin = Negative_Pressure_0_Pin|Negative_Pressure_1_Pin|Positive__Pressure_0_Pin|Positive__Pressure_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : Sensor_Home_0_Pin */
  GPIO_InitStruct.Pin = Sensor_Home_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Sensor_Home_0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Sensor_Home_1_Pin Sensor_Home_2_Pin */
  GPIO_InitStruct.Pin = Sensor_Home_1_Pin|Sensor_Home_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : Sensor_Home_3_Pin Sensor_Home_4_Pin Sensor_Home_5_Pin Encoder_Z_1_Pin
                           Encoder_Z_0_Pin */
  GPIO_InitStruct.Pin = Sensor_Home_3_Pin|Sensor_Home_4_Pin|Sensor_Home_5_Pin|Encoder_Z_1_Pin
                          |Encoder_Z_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Sensor_Home_6_Pin Sensor_Home_7_Pin Sensor_Home_8_Pin Sensor_Home_9_Pin */
  GPIO_InitStruct.Pin = Sensor_Home_6_Pin|Sensor_Home_7_Pin|Sensor_Home_8_Pin|Sensor_Home_9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PWM_EN_0_Pin */
  GPIO_InitStruct.Pin = PWM_EN_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PWM_EN_0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_G_0_Pin LED_R_0_Pin */
  GPIO_InitStruct.Pin = LED_G_0_Pin|LED_R_0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_G_1_Pin LED_R_1_Pin */
  GPIO_InitStruct.Pin = LED_G_1_Pin|LED_R_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : FAN_ZK_Pin */
  GPIO_InitStruct.Pin = FAN_ZK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FAN_ZK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PWM_EN_1_Pin */
  GPIO_InitStruct.Pin = PWM_EN_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PWM_EN_1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CHIP_ID_0_Pin CHIP_ID_1_Pin CARD_ID_0_Pin CARD_ID_1_Pin
                           CARD_ID_2_Pin CARD_ID_3_Pin */
  GPIO_InitStruct.Pin = CHIP_ID_0_Pin|CHIP_ID_1_Pin|CARD_ID_0_Pin|CARD_ID_1_Pin
                          |CARD_ID_2_Pin|CARD_ID_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
