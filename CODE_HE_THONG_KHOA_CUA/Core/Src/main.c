/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  * 
  * Code style:
  * https://khuenguyencreator.com/cach-viet-clean-code-trong-lap-trinh-c/
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
#include "RC522.h" // Thư viện giao tiếp với module đọc/ghi thẻ từ RFID RC522
#include "KEYPAD.h" // Thư viện đọc phím nhấn bàn phím ma trận
#include "CLCD_I2C.h" // Thư viện màn hình LCD giao tiếp I2C
#include "String.h"
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

SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USER CODE BEGIN PV */
// Khởi tạo thẻ từ
MFRC522_Name mfrc522;
uint8_t str[MFRC522_MAX_LEN];
uint8_t RC522_TagType;
unsigned char Ar1_uc_UID_Buffer[8] = {'1', '2', '3', '3', '4', 'A', '5', 'F'};
unsigned char Ar1_uc_UID_InputBuffer[8];

// Khởi tạo biến lưu Keypad và keymap
 KEYPAD_Name KeyPad;
 char KEYMAP[NUMROWS][NUMCOLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
 };
// Biến lưu key đọc được
unsigned char u8_KEYPAD_key;
// Khai báo LCD
CLCD_I2C_Name LCD1;

// 
unsigned char password[6] = {'1','2','3','A','B','C'};
unsigned char input_pass[6];
uint8_t inputIndex = 0; // Chỉ số của phím hiện tại
uint8_t status;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void RC522_UID_Check(void)
{
  // ========================================= Mô phỏng trên Proteus ========================================= //
  status = HAL_UART_Receive(&huart2, Ar1_uc_UID_InputBuffer, 8, 0xffff);
  while (status != HAL_OK)
  {
    // Chờ chuỗi ghi vào buffer
  }
  HAL_UART_Transmit(&huart2, "\n\r", 2, 0xffff);
  HAL_UART_Transmit(&huart2, Ar1_uc_UID_InputBuffer, 8, 0xffff);
  if (strcmp(Ar1_uc_UID_Buffer, Ar1_uc_UID_InputBuffer) == 0)
  {
    CLCD_I2C_SetCursor(&LCD1, 0, 1);
		CLCD_I2C_WriteString(&LCD1,"The tu Oke!");
  }
  else
  {
    CLCD_I2C_SetCursor(&LCD1, 0, 1);
		CLCD_I2C_WriteString(&LCD1,"The tu sai!");
  }

  // ========================================= Chạy trên phần cứng ========================================= //

}
void KEYPAD_CheckPassword(void)
{
  u8_KEYPAD_key = KEYPAD4X4_Readkey(&KeyPad);
	  	  HAL_Delay(20);
	      //RC522_UID_Check();
	      if (u8_KEYPAD_key != 0)
	      {
	        CLCD_I2C_SetCursor(&LCD1, inputIndex, 1);
	      	CLCD_I2C_WriteChar(&LCD1, u8_KEYPAD_key);
	        if (u8_KEYPAD_key == 'D')
	        {
	      	inputIndex = 0;
	        	CLCD_I2C_Clear(&LCD1);
	        	CLCD_I2C_SetCursor(&LCD1, 0, 0);
	        	CLCD_I2C_WriteString(&LCD1,"Nhap mat khau:");
	        	CLCD_I2C_SetCursor(&LCD1, 0, 1);
	        }
	        else if (u8_KEYPAD_key == '*')
	        {
	      	  inputIndex = 0;
	      	  if(strcmp(input_pass, password) == 0)
	      	  {
	      		 CLCD_I2C_SetCursor(&LCD1, 0, 1);
	      		 CLCD_I2C_WriteString(&LCD1, "Mat khau dung!");
	      		 HAL_Delay(2000);
	  		     CLCD_I2C_Clear(&LCD1);
	  		     CLCD_I2C_SetCursor(&LCD1, 0, 0);
	  		     CLCD_I2C_WriteString(&LCD1,"Nhap mat khau:");
	  		     CLCD_I2C_SetCursor(&LCD1, 0, 1);
	      	  }
	      	  else
	      	  {
	      		 CLCD_I2C_SetCursor(&LCD1, 0, 1);
	      		 CLCD_I2C_WriteString(&LCD1, "Mat khau sai!");
	      		 HAL_Delay(2000);
	  		     CLCD_I2C_Clear(&LCD1);
	  		     CLCD_I2C_SetCursor(&LCD1, 0, 0);
	  		     CLCD_I2C_WriteString(&LCD1,"Nhap mat khau:");
	  		     CLCD_I2C_SetCursor(&LCD1, 0, 1);
	      	  }
	        }
	        else
	        {
	      	  input_pass[inputIndex] = u8_KEYPAD_key;
	      	  inputIndex++;
	        }
	        //CLCD_I2C_WriteString(&LCD1, input_pass);
	      }


	      //HAL_UART_Transmit(&huart2, &u8_KEYPAD_key, sizeof(u8_KEYPAD_key), 100);
	  	  HAL_Delay(50);
}
void LCD_Show(void)
{

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
  MX_USART6_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  // Khởi tạo thẻ từ
  MFRC522_Init(&mfrc522, &hspi1, SPI1_CS_GPIO_Port, SPI1_CS_Pin);

  // Khởi tạo Keypad 4x4
   KEYPAD4X4_Init(&KeyPad, KEYMAP,
                           COL1_GPIO_Port, COL1_Pin,
                           COL2_GPIO_Port, COL2_Pin,
                           COL3_GPIO_Port, COL3_Pin,
                           COL4_GPIO_Port, COL4_Pin,
                           ROW1_GPIO_Port, ROW1_Pin,
                           ROW2_GPIO_Port, ROW2_Pin,
                           ROW3_GPIO_Port, ROW3_Pin,
                           ROW4_GPIO_Port, ROW4_Pin);
  // Khởi tạo LCD
  // Với mô phỏng Proteus -> địa chỉ 0x40
  // Với phần cứng thực tế -> địa chỉ 0x4E
   CLCD_I2C_Init(&LCD1,&hi2c1,0x4E,16,2);

  // Test hiển thị
  CLCD_I2C_SetCursor(&LCD1, 0, 0);
  CLCD_I2C_WriteString(&LCD1,"Nhap mat khau:");
  CLCD_I2C_SetCursor(&LCD1, 0, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    if(!MFRC522_Request(&mfrc522, PICC_REQIDL, &RC522_TagType))
    {
      if(!MFRC522_Anticoll(&mfrc522, str))
      {
        CLCD_I2C_WriteString(&LCD1, RC522_TagType);
      }
    }
	  
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

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
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

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
  * @brief USART6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART6_UART_Init(void)
{

  /* USER CODE BEGIN USART6_Init 0 */

  /* USER CODE END USART6_Init 0 */

  /* USER CODE BEGIN USART6_Init 1 */

  /* USER CODE END USART6_Init 1 */
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART6_Init 2 */

  /* USER CODE END USART6_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, COL3_Pin|COL1_Pin|COL2_Pin|SPI1_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ROW4_Pin */
  GPIO_InitStruct.Pin = ROW4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ROW4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ROW1_Pin */
  GPIO_InitStruct.Pin = ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(ROW1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ROW3_Pin ROW2_Pin */
  GPIO_InitStruct.Pin = ROW3_Pin|ROW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : COL4_Pin */
  GPIO_InitStruct.Pin = COL4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(COL4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : COL3_Pin COL1_Pin COL2_Pin SPI1_CS_Pin */
  GPIO_InitStruct.Pin = COL3_Pin|COL1_Pin|COL2_Pin|SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
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
