/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdio.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mt10t8.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */

    const uint8_t       char_array1[MT10T8_DIMENTION] = "0123456789";                                           					// Char string data.
    const uint8_t       char_array2[MT10T8_DIMENTION] = "AbcdEFJGhL";                                           					// Char string data.
    const uint8_t       char_array3[2 * MT10T8_DIMENTION] = "u-*_!^..A..\0";                                    					// Char string data.
    uint8_t             char_array4[2 * MT10T8_DIMENTION];                                         									// Char string data.

    const mt10t8_bus_t	mt10t8_bus = {(uint8_t*)(PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD4_Pos * 4), \
    								  (uint8_t*)(PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD0_Pos * 4), \
    				                  (uint8_t*)(PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD1_Pos * 4), \
									  (uint8_t*)(PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD2_Pos * 4), \
									  (uint8_t*)(PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD3_Pos * 4), \
    								  (uint8_t*)(PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD5_Pos * 4)}; // Inicialization pt_A0, pt_D0, pt_D1, pt_D2, pt_D3, pt_WR1.

    const mt10t8_t		mt10t8_1 = {&mt10t8_bus, PERIPH_BB_BASE + (((uint32_t)&(GPIOA->ODR)) & 0x000FFFFF) * 32 + GPIO_ODR_OD6_Pos * 4};	// LCI description structure (pt_bus, pt_WR2).

    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

    mt10t8_init(&mt10t8_1);                                                                                         // Initialization LCI. Result: unlock and clear LCI.
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

    mt10t8_out_char_string(&mt10t8_1, &char_array1[0]);
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

    mt10t8_out_char_string(&mt10t8_1, &char_array2[0]);
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

    mt10t8_out_char_string(&mt10t8_1, &char_array3[0]);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
	HAL_Delay(1000);

	sprintf(&char_array4[0], "%d", 0);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);
  	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

	sprintf(&char_array4[0], "%d", -1);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);
  	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

	sprintf(&char_array4[0], "%d", -1000000001);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);
  	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

	sprintf(&char_array4[0], "%o", 15);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);
  	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

	sprintf(&char_array4[0], "%x", 0xFFFFFFFF);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);
  	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

	sprintf(&char_array4[0], "%u", -1);
	mt10t8_out_char_string(&mt10t8_1, &char_array4[0]);
  	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);
    HAL_Delay(1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_7;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, MT10T8_DB0_Pin|MT10T8_DB1_Pin|MT10T8_DB2_Pin|MT10T8_DB3_Pin
                          |MT10T8_A0_Pin|MT10T8_WR1_Pin|MT10T8_WR2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MT10T8_DB0_Pin MT10T8_DB1_Pin MT10T8_DB2_Pin MT10T8_DB3_Pin
                           MT10T8_A0_Pin MT10T8_WR1_Pin MT10T8_WR2_Pin */
  GPIO_InitStruct.Pin = MT10T8_DB0_Pin|MT10T8_DB1_Pin|MT10T8_DB2_Pin|MT10T8_DB3_Pin
                          |MT10T8_A0_Pin|MT10T8_WR1_Pin|MT10T8_WR2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

