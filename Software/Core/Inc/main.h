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
#include "stm32c0xx_hal.h"
#include "stm32c0xx_ll_rcc.h"
#include "stm32c0xx_ll_bus.h"
#include "stm32c0xx_ll_system.h"
#include "stm32c0xx_ll_exti.h"
#include "stm32c0xx_ll_cortex.h"
#include "stm32c0xx_ll_utils.h"
#include "stm32c0xx_ll_pwr.h"
#include "stm32c0xx_ll_dma.h"
#include "stm32c0xx_ll_gpio.h"

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
#define PLL_LED_1_Pin LL_GPIO_PIN_2
#define PLL_LED_1_GPIO_Port GPIOA
#define PLL_LED_2_Pin LL_GPIO_PIN_3
#define PLL_LED_2_GPIO_Port GPIOA
#define PLL_CE_2_Pin LL_GPIO_PIN_7
#define PLL_CE_2_GPIO_Port GPIOA
#define PLL_LE_2_Pin LL_GPIO_PIN_0
#define PLL_LE_2_GPIO_Port GPIOB
#define PLL_DATA_2_Pin LL_GPIO_PIN_1
#define PLL_DATA_2_GPIO_Port GPIOB
#define PLL_CLK_2_Pin LL_GPIO_PIN_2
#define PLL_CLK_2_GPIO_Port GPIOB
#define PLL_MUXout_2_Pin LL_GPIO_PIN_10
#define PLL_MUXout_2_GPIO_Port GPIOB
#define PLL_RF_EN_2_Pin LL_GPIO_PIN_11
#define PLL_RF_EN_2_GPIO_Port GPIOB
#define PLL_CE_1_Pin LL_GPIO_PIN_14
#define PLL_CE_1_GPIO_Port GPIOB
#define PLL_LE_1_Pin LL_GPIO_PIN_15
#define PLL_LE_1_GPIO_Port GPIOB
#define PLL_DATA_1_Pin LL_GPIO_PIN_8
#define PLL_DATA_1_GPIO_Port GPIOA
#define PLL_CLK_1_Pin LL_GPIO_PIN_9
#define PLL_CLK_1_GPIO_Port GPIOA
#define PLL_MUXout_1_Pin LL_GPIO_PIN_6
#define PLL_MUXout_1_GPIO_Port GPIOC
#define PLL_RF_EN_1_Pin LL_GPIO_PIN_7
#define PLL_RF_EN_1_GPIO_Port GPIOC
#define PLL_TOGGLE_2_Pin LL_GPIO_PIN_0
#define PLL_TOGGLE_2_GPIO_Port GPIOD
#define PLL_BTN_2_Pin LL_GPIO_PIN_3
#define PLL_BTN_2_GPIO_Port GPIOD
#define PLL_TOGGLE_1_Pin LL_GPIO_PIN_5
#define PLL_TOGGLE_1_GPIO_Port GPIOB
#define PLL_BTN_1_Pin LL_GPIO_PIN_8
#define PLL_BTN_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
