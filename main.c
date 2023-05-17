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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CLCD_I2C.h"
#include "stdio.h"
#include "KEYPAD.h"

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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t txt1[30] = " ";
uint8_t ack;
char txt = 'k';
// Khoi tao bien LCD
CLCD_I2C_Name LCD1;

KEYPAD_Name KeyPad;
char KEYMAP[NUMROWS][NUMCOLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};

char Key;
int i =0;
int pass = '6';
int sai =0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//Hien thi the tu
void LCD_Thetu(void)
{

	CLCD_I2C_SetCursor(&LCD1,0,0);
	CLCD_I2C_WriteString(&LCD1," Quet the tu: ");
	HAL_Delay(500);
	CLCD_I2C_SetCursor(&LCD1,0,1);
	CLCD_I2C_WriteString(&LCD1," Da xac nhan ");
	HAL_Delay(1000);

}

//Hien thi mat khau duoc nhap tu ban phim
void LCD_Nhapmatkhau(void)
{

	CLCD_I2C_SetCursor(&LCD1,0,1);
	CLCD_I2C_WriteChar(&LCD1,Key);
	CLCD_I2C_SetCursor(&LCD1,0,1);
	CLCD_I2C_WriteString(&LCD1,"*");
	HAL_Delay(500);

}

// Thuc hien khi mat khau duoc nhap dung
void LCD_Matkhaudung(void)
{
	CLCD_I2C_Clear(&LCD1);
	CLCD_I2C_SetCursor(&LCD1,0,0);
	CLCD_I2C_WriteString(&LCD1," Mat khau dung ");
	CLCD_I2C_SetCursor(&LCD1,0,1);
	CLCD_I2C_WriteString(&LCD1," - * - * - * -");
	HAL_Delay(1000);
	CLCD_I2C_Clear(&LCD1);
	CLCD_I2C_SetCursor(&LCD1,0,0);
	CLCD_I2C_WriteString(&LCD1," ** Cua mo ** ");
	HAL_Delay(3000);
	CLCD_I2C_Clear(&LCD1);
	CLCD_I2C_SetCursor(&LCD1,0,0);
	CLCD_I2C_WriteString(&LCD1," ** Cua dong **");
	HAL_Delay(3000);

}

//Thuc hien khi xac nhan mat khau duoc nhap sai
void LCD_Matkhausai(void)
{

	CLCD_I2C_Clear(&LCD1);
	CLCD_I2C_SetCursor(&LCD1,0,0);
	CLCD_I2C_WriteString(&LCD1,"  Mat khau sai  ");
	CLCD_I2C_SetCursor(&LCD1,0,1);
	CLCD_I2C_WriteString(&LCD1,"  - ! - ! - ! -   ");
	HAL_Delay(1000);
	++sai;
	switch(sai)
	{
		case 1:

			CLCD_I2C_Clear(&LCD1);
			CLCD_I2C_SetCursor(&LCD1,0,0);
			CLCD_I2C_WriteString(&LCD1,"  Canh bao 1!  ");
			CLCD_I2C_SetCursor(&LCD1,0,1);
			CLCD_I2C_WriteString(&LCD1,"Nhap lai sau 1s");
			HAL_Delay(1000);
			CLCD_I2C_Clear(&LCD1);
			CLCD_I2C_SetCursor(&LCD1,0,0);
			CLCD_I2C_WriteString(&LCD1," Nhap mat khau: ");
			break;

		case 2:

			CLCD_I2C_Clear(&LCD1);
			CLCD_I2C_SetCursor(&LCD1,0,0);
			CLCD_I2C_WriteString(&LCD1,"  Canh bao 2!  ");
			CLCD_I2C_SetCursor(&LCD1,0,1);
			CLCD_I2C_WriteString(&LCD1,"Nhap lai sau 10s");
			HAL_Delay(10000);
			CLCD_I2C_Clear(&LCD1);
			CLCD_I2C_SetCursor(&LCD1,0,0);
			CLCD_I2C_WriteString(&LCD1," Nhap mat khau: ");
			break;

		case 3:

			CLCD_I2C_Clear(&LCD1);
			CLCD_I2C_SetCursor(&LCD1,0,0);
			CLCD_I2C_WriteString(&LCD1,"  Canh bao 3!  ");
			CLCD_I2C_SetCursor(&LCD1,0,1);
			CLCD_I2C_WriteString(&LCD1,"Nhap lai sau 15s");
			HAL_Delay(15000);
			CLCD_I2C_Clear(&LCD1);
			CLCD_I2C_SetCursor(&LCD1,0,0);
			CLCD_I2C_WriteString(&LCD1," Nhap mat khau: ");
			break;

	}

}


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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  //  HAL_UART_Transmit(&huart2, &txt, sizeof(txt), 0xFFFF);
  //
  //    for(uint8_t address=0; address<128; address++)
  //    {
  //  	  ack = HAL_I2C_IsDeviceReady(&hi2c1, address<<1, 3, 6);
  //  	  HAL_UART_Transmit(&huart2, &ack, sizeof(ack), 0xFFFF);
  //  	  HAL_Delay(1);
  //  	  if(ack == HAL_OK)
  //  	  {
  //  		  sprintf((char*)txt1, "Dia chi I2C 0x%X\n\r", address<<1);
  //  		  HAL_UART_Transmit(&huart2, &txt1, sizeof(txt1), 0xffff);
  //  	  }
  //    }


  // Khoi tao LCD
  CLCD_I2C_Init(&LCD1,&hi2c1,0x70,16,2);

  //  CLCD_I2C_SetCursor(&LCD1, 0, 1);
  //  CLCD_I2C_WriteString(&LCD1,"Hello !");

 	///////////////////////////
   	KEYPAD3X4_Init(&KeyPad, KEYMAP,
   	   								COL1_GPIO_Port, COL1_Pin,
   									COL2_GPIO_Port, COL2_Pin,
   									COL3_GPIO_Port, COL3_Pin,
   									ROW1_GPIO_Port, ROW1_Pin,
   									ROW2_GPIO_Port, ROW2_Pin,
   									ROW3_GPIO_Port, ROW3_Pin,
   									ROW4_GPIO_Port, ROW4_Pin);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

   	LCD_Thetu();
   	CLCD_I2C_Clear(&LCD1);
   	CLCD_I2C_SetCursor(&LCD1,0,0);
   	CLCD_I2C_WriteString(&LCD1," Nhap mat khau: ");

  while (1)
  {
    /* USER CODE END WHILE */
	  Key = KEYPAD3X4_Readkey(&KeyPad);
	  if(Key)
	  {
		  HAL_UART_Transmit(&huart2, (uint8_t*)&Key, 1, 100);
	  }
	  HAL_Delay(50);


	  if(Key != 0)
	  {

		  LCD_Nhapmatkhau();

		  if(Key == pass )
		  {

			  LCD_Matkhaudung();

		  }

		  else
		  {

			  LCD_Matkhausai();

		  }
	  }
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|COL1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, COL2_Pin|COL3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin COL1_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|COL1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW1_Pin ROW4_Pin */
  GPIO_InitStruct.Pin = ROW1_Pin|ROW4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : COL2_Pin COL3_Pin */
  GPIO_InitStruct.Pin = COL2_Pin|COL3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : ROW3_Pin */
  GPIO_InitStruct.Pin = ROW3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ROW3_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ROW2_Pin */
  GPIO_InitStruct.Pin = ROW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ROW2_GPIO_Port, &GPIO_InitStruct);

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
