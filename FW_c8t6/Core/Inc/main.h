/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

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
#define SD_DET_Pin GPIO_PIN_1
#define SD_DET_GPIO_Port GPIOA
#define SYS_BEEP_Pin GPIO_PIN_2
#define SYS_BEEP_GPIO_Port GPIOA
#define LED_RUN_Pin GPIO_PIN_3
#define LED_RUN_GPIO_Port GPIOA
#define ONBRD_NTC_Pin GPIO_PIN_4
#define ONBRD_NTC_GPIO_Port GPIOA
#define EXT_NTC_Pin GPIO_PIN_5
#define EXT_NTC_GPIO_Port GPIOA
#define DET_INPUT_Pin GPIO_PIN_6
#define DET_INPUT_GPIO_Port GPIOA
#define THRESHOLD_IRQ_Pin GPIO_PIN_7
#define THRESHOLD_IRQ_GPIO_Port GPIOA
#define THRESHOLD_IRQ_EXTI_IRQn EXTI9_5_IRQn
#define PEAK_DET_RST_Pin GPIO_PIN_0
#define PEAK_DET_RST_GPIO_Port GPIOB
#define DET_CON_Pin GPIO_PIN_2
#define DET_CON_GPIO_Port GPIOB
#define V_DET_TOOGLE_Pin GPIO_PIN_12
#define V_DET_TOOGLE_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_15
#define SD_CS_GPIO_Port GPIOA
#define START_BTN_Pin GPIO_PIN_6
#define START_BTN_GPIO_Port GPIOB
#define START_BTN_EXTI_IRQn EXTI9_5_IRQn
#define LED_COM_Pin GPIO_PIN_7
#define LED_COM_GPIO_Port GPIOB
#define LED_CON_Pin GPIO_PIN_8
#define LED_CON_GPIO_Port GPIOB
#define LED_SD_Pin GPIO_PIN_9
#define LED_SD_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
