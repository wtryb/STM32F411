/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "fatfs.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "MODEL.h"
#include "SYSTEM.h"
#include "APP.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_examples.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */ 
char *test_str;
char *test_add;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  char flag;
  char *test_json = "{\"status\":\"1\",\"regeocode\":{\"addressComponent\":{\"city\":[],\"province\":\"??????\",\"adcode\":\"110108\",\"district\":\"??????\",\"towncode\":\"110108015000\",\"streetNumber\":{\"number\":\"5??\",\"location\":\"116.310454,39.992734\",\"direction\":\"????\",\"distance\":\"94.5489\",\"street\":\"????????\"},\"country\":\"????\",\"township\":\"????????\",\"businessAreas\":[{\"location\":\"116.303364,39.976410\",\"name\":\"??????\",\"id\":\"110108\"},{\"location\":\"116.314222,39.982490\",\"name\":\"??????\",\"id\":\"110108\"},{\"location\":\"116.294214,39.996850\",\"name\":\"????\",\"id\":\"110108\"}],\"building\":{\"name\":\"????????\",\"type\":\"????????????;????;????????\"},\"neighborhood\":{\"name\":\"????????\",\"type\":\"????????????;????;????????\"},\"citycode\":\"010\"},\"formatted_address\":\"????????????????????????????\"},\"info\":\"OK\",\"infocode\":\"10000\"}";
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
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_SPI2_Init();
  MX_SPI1_Init();
  MX_TIM5_Init();
  MX_FATFS_Init();
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN 2 */
    
  DEBUG_UART_Send_MSG("<-----------????????--------->\n\r");

  //????TIM5??????????????????????LVGL????????????????lv_task
  __HAL_TIM_CLEAR_IT(&htim5,TIM_IT_UPDATE ); //????IT??????
  HAL_TIM_Base_Start_IT(&htim5);

  //????????2??????????????GA8??????????
  __HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE);
  HAL_UART_Receive_IT(GA8_USART, (uint8_t *)&RE_temp, 1);

  //SPI Flash??????
  W25Qx_Init();
   
//  flag = GA8_Test();
//  Usart1Printf("flag1:%x\r\n", flag);
//  GA8_PDP_Connect();

//  flag = GA8_TCP_Connect("\"restapi.amap.com\",80");
//  Usart1Printf("flag2:%x\r\n", flag);
//  Usart1Printf("%s", GA8_BUFFER);

//  flag = GA8_TCP_Send_Msg("GET https://restapi.amap.com/v3/geocode/regeo?output=json&location=116.310003,39.991957&key=257da8c8a2c0ebd13452f6c60718029f&radius=1000&extensions=base\r\n");
//  Usart1Printf("flag3:%x\r\n", flag);
//  Usart1Printf("%s", GA8_BUFFER);

//  test_str = Find_JSON_From_Buffer(GA8_BUFFER);

//  test_add = Gett_Address_cJSON(test_str);
//  Usart1Printf("test_add:%s\r\n", test_add);
    
//   //LVGL??????
//   lv_init();
//   //LVGL??????????????
//   lv_port_disp_init();  
   
  DEBUG_UART_Send_MSG("<-----------????????--------->\n\r");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {       
     HAL_GPIO_TogglePin(LED_pin_GPIO_Port, LED_pin_Pin);
    
     HAL_Delay(500);
    
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 15;
  RCC_OscInitStruct.PLL.PLLN = 144;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
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
