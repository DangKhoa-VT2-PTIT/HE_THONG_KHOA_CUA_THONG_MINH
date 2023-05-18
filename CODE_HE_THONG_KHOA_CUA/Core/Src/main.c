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
#include "RC522.h" // Thư viện giao tiếp với module đ�?c/ghi thẻ từ RFID RC522
#include "KEYPAD.h" // Thư viện đ�?c phím nhấn bàn phím ma trận
#include "CLCD_I2C.h" // Thư viện màn hình LCD giao tiếp I2C
#include "String.h"
#include "stdbool.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define LCD_RFIDHOME      1u
#define LCD_PASSHOME      2u
#define LCD_CORRECTCARD   3u
#define LCD_WRONGCARD     4u
#define LCD_SHOWPASS      5u
#define LCD_CORRECTPASS   6u
#define LCD_WRONGPASS     7u
#define LCD_WARNING    8u

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
uint8_t Ar1_u8_RFID_InputCard[MFRC522_MAX_LEN];
const uint8_t Ar1_u8_RFID_MasterCard[MFRC522_MAX_LEN] = {0x49, 0xAE, 0XA3, 0XC2, 0X86}; // Thẻ master
const uint8_t Ar1_u8_RFID_Card1[MFRC522_MAX_LEN] = {0x1A, 0xE1, 0X80, 0X17, 0X61}; // Thẻ slave 1
uint8_t RC522_TagType;

// Mô ph�?ng thẻ từ
// char Ar1_c_SIM_InputCard[10];
// const char Ar1_c_SIM_MasterCard[10] = {'4', '9', 'A', 'E', 'A', '3', 'C', '2', '8', '6'}; // Thẻ mô ph�?ng master
// const char Ar1_c_SIM_Card1[10] = {'1', 'A', 'E', '1', '8', '0', '1', '7', '6', 'C'}; // Thẻ mô ph�?ng slave 1

// Khởi tạo Keypad và keymap
 KEYPAD_Name KeyPad;
 char KEYMAP[NUMROWS][NUMCOLS] = {
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}
 };

// Khởi tạo mật khẩu 
char c_KEYPAD_Key;
char c_KEYPAD_InputPassword[7];
const char c_KEYPAD_Password[7] = {'1','2','3','4','5','6'};
uint8_t Input_Index = 0; // Chỉ số của phím hiện tại
uint8_t Wrong_Count = 0; // Số lần sai mật khẩu
uint8_t Warning_Level = 0; // Mức cảnh báo
const char Warning_Level1[] = "Canh bao muc 1!";
const char Warning_Level2[] = "Canh bao muc 2!";
// Khai báo LCD
CLCD_I2C_Name LCD;
char LCD_str[20];

// Các biến trạng thái
bool RFID_Active = false;
bool Door_Status = false;

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
// Hàm kiểm tra thẻ từ
void RC522_RFID_Check(void)
{
  // ========================================= Mô ph�?ng trên Proteus ========================================= //
  // uint8_t status = HAL_UART_Receive(&huart2, Ar1_c_SIM_InputCard, 10, 0xffff);
  // while (status != HAL_OK)
  // {
  //   // Chờ chuỗi ghi vào buffer
  // }
  // HAL_UART_Transmit(&huart2, "\n\r", 2, 0xffff);
  // HAL_UART_Transmit(&huart2, Ar1_c_SIM_InputCard, 10, 0xffff);

  // if (strcmp(Ar1_c_SIM_MasterCard, Ar1_c_SIM_InputCard) == 0)
  // {
  //   RFID_Active = true;
  //   LCD_Show(LCD_CORRECTCARD);
  //   HAL_Delay(1000);
  //   LCD_Show(LCD_PASSHOME);
  // }
  // else if(strcmp(Ar1_c_SIM_InputCard, Ar1_c_SIM_Card1) == 0)
  // {
  //   RFID_Active = true;
  //   LCD_Show(LCD_CORRECTCARD);
  //   HAL_Delay(1000);
  //   LCD_Show(LCD_PASSHOME);
  // }
  // else
  // {
  //   RFID_Active = false;
  //   LCD_Show(LCD_WRONGCARD);
  //   HAL_Delay(1000);
  //   LCD_Show(LCD_RFIDHOME);
  // }


  // ========================================= Chạy trên phần cứng ========================================= //
  if(!MFRC522_Request(&mfrc522, PICC_REQIDL, &RC522_TagType))
    {
      if(!MFRC522_Anticoll(&mfrc522, Ar1_u8_RFID_InputCard))
      {
        // sprintf(LCD_str, "ID: 0x%02X%02X%02X%02X%02X", Ar1_u8_RFID_InputCard[0], Ar1_u8_RFID_InputCard[1], Ar1_u8_RFID_InputCard[2], Ar1_u8_RFID_InputCard[3], Ar1_u8_RFID_InputCard[4]);
        // CLCD_I2C_SetCursor(&LCD, 0, 1);
        // CLCD_I2C_WriteString(&LCD, LCD_str);
        // HAL_Delay(1000);
        // CLCD_I2C_Clear(&LCD);

        if( Ar1_u8_RFID_InputCard[0] == Ar1_u8_RFID_MasterCard[0]&&
            Ar1_u8_RFID_InputCard[1] == Ar1_u8_RFID_MasterCard[1]&&
            Ar1_u8_RFID_InputCard[2] == Ar1_u8_RFID_MasterCard[2]&&
            Ar1_u8_RFID_InputCard[3] == Ar1_u8_RFID_MasterCard[3]&&
            Ar1_u8_RFID_InputCard[4] == Ar1_u8_RFID_MasterCard[4])
        {
          RFID_Active = true;
          LCD_Show(LCD_CORRECTCARD);
          HAL_Delay(1000);
          LCD_Show(LCD_PASSHOME);
        }

        else if(  Ar1_u8_RFID_InputCard[0] == Ar1_u8_RFID_Card1[0]&&
                  Ar1_u8_RFID_InputCard[1] == Ar1_u8_RFID_Card1[1]&&
                  Ar1_u8_RFID_InputCard[2] == Ar1_u8_RFID_Card1[2]&&
                  Ar1_u8_RFID_InputCard[3] == Ar1_u8_RFID_Card1[3]&&
                  Ar1_u8_RFID_InputCard[4] == Ar1_u8_RFID_Card1[4])
        {
          RFID_Active = true;
          LCD_Show(LCD_CORRECTCARD);
          HAL_Delay(1000);
          LCD_Show(LCD_PASSHOME);
        }
        else
        {
          RFID_Active = false;
          LCD_Show(LCD_WRONGCARD);
          HAL_Delay(1000);
          LCD_Show(LCD_RFIDHOME);
        }
      }
    }
}

// Hàm kiểm tra mật khẩu
void KEYPAD_CheckPassword(void)
{
  c_KEYPAD_Key = KEYPAD4X4_Readkey(&KeyPad);
	HAL_Delay(10);
	if (RFID_Active == true && Door_Status == false) 
	{
    if(c_KEYPAD_Key != 0)
    {
      c_KEYPAD_InputPassword[Input_Index] = c_KEYPAD_Key;
	    Input_Index++;
      LCD_Show(LCD_SHOWPASS);

	    if (c_KEYPAD_Key == 'D')
	    {
	      Input_Index = 0;
        LCD_Show(LCD_PASSHOME);
	    }
	    if (Input_Index == 6) // Kiểm tra nếu đã nhập đủ 6 phím
	    {
	      if(strcmp(c_KEYPAD_InputPassword, c_KEYPAD_Password) == 0)
	      {
          Door_Status = true;
          Door_Control();

          Wrong_Count = 0;
          Warning_Level = 0;

          LCD_Show(LCD_CORRECTPASS);
          HAL_Delay(1000);
          LCD_Show(LCD_PASSHOME);

          HAL_Delay(2000);
          Door_Status = false;
          Door_Control();
	      }
	      else
	      {
          Wrong_Count++;

	        LCD_Show(LCD_WRONGPASS);
	        HAL_Delay(1000);
	  	    LCD_Show(LCD_PASSHOME);

          if(Wrong_Count == 3)
          {
            Wrong_Count = 0;
            Warning_Level++;

            LCD_Show(LCD_WARNING);
            HAL_Delay(5000);
            switch (Warning_Level) // Kiểm tra mức cảnh báo
            {
              case 1:
                Buzzer_On();
                HAL_Delay(3000);
                Buzzer_Off();
                LCD_Show(LCD_PASSHOME);
                break;
              case 2:
                HAL_UART_Transmit(&huart2, Warning_Level1, sizeof(Warning_Level1), 0xff);
                Buzzer_On();
                HAL_Delay(5000);
                Buzzer_Off();
                LCD_Show(LCD_PASSHOME);
                break;
              case 3:
                HAL_UART_Transmit(&huart2, Warning_Level2, sizeof(Warning_Level2), 0xff);
                Buzzer_On();
                HAL_Delay(7000);
                Buzzer_Off();
                LCD_Show(LCD_PASSHOME);
                Warning_Level = 0;
                break;
            }
          }
	      }
        Input_Index = 0;
	    }
    }
  }

  else
  {
    Door_Status = false;
  }
}

// Hàm hiển thị lên LCD
void LCD_Show(unsigned int Show_Type)
{
  switch (Show_Type)
  {
    case LCD_RFIDHOME:
      CLCD_I2C_Clear(&LCD);
      CLCD_I2C_SetCursor(&LCD, 0, 0);
	    CLCD_I2C_WriteString(&LCD,"Nhap the tu:");
      CLCD_I2C_SetCursor(&LCD, 0, 1);
      break;
    case LCD_PASSHOME:
      CLCD_I2C_Clear(&LCD);
      CLCD_I2C_SetCursor(&LCD, 0, 0);
	    CLCD_I2C_WriteString(&LCD,"Nhap mat khau:");
      CLCD_I2C_SetCursor(&LCD, 0, 1);
      break;
    case LCD_CORRECTCARD:
      CLCD_I2C_SetCursor(&LCD, 0, 1);
      CLCD_I2C_WriteString(&LCD, "The hop le!");
      break;
    case LCD_WRONGCARD:
      CLCD_I2C_SetCursor(&LCD, 0, 1);
      CLCD_I2C_WriteString(&LCD, "The sai!");
      break;
    case LCD_SHOWPASS:
      CLCD_I2C_SetCursor(&LCD, Input_Index, 1);
	    CLCD_I2C_WriteChar(&LCD, '*');
      break;
    case LCD_CORRECTPASS:
      CLCD_I2C_SetCursor(&LCD, 0, 1);
	    CLCD_I2C_WriteString(&LCD, "Mat khau dung!");
      break;
    case LCD_WRONGPASS:
      CLCD_I2C_SetCursor(&LCD, 0, 1);
	    CLCD_I2C_WriteString(&LCD, "Mat khau sai!");
      break;
    case LCD_WARNING:
      CLCD_I2C_Clear(&LCD);
      CLCD_I2C_SetCursor(&LCD, 0, 0);
	    CLCD_I2C_WriteString(&LCD,"Sai 3 lan!");
      CLCD_I2C_SetCursor(&LCD, 0, 1);
	    CLCD_I2C_WriteString(&LCD, "Khoa he thong!");
  }
}

void Buzzer_On(void)
{
  HAL_GPIO_WritePin(BUZZZER_GPIO_Port, BUZZZER_Pin, GPIO_PIN_SET);
}

void Buzzer_Off(void)
{
  HAL_GPIO_WritePin(BUZZZER_GPIO_Port, BUZZZER_Pin, GPIO_PIN_RESET);
}

void Door_Control(void)
{
  if(Door_Status == true)
  {
    HAL_GPIO_WritePin(DOOR_GPIO_Port, DOOR_Pin, GPIO_PIN_SET);
  }
  else
  {
    HAL_GPIO_WritePin(DOOR_GPIO_Port, DOOR_Pin, GPIO_PIN_RESET);
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
  // Với mô ph�?ng Proteus -> địa chỉ 0x40
  // Với phần cứng thực tế -> địa chỉ 0x4E
   CLCD_I2C_Init(&LCD,&hi2c1,0x4E,16,2);

  // Hiển thị lên LCD
  CLCD_I2C_SetCursor(&LCD, 0, 0);
  CLCD_I2C_WriteString(&LCD,"Nhap the tu:");
  CLCD_I2C_SetCursor(&LCD, 0, 1);
  //RFID_Active = true;
  //RC522_RFID_Check(); // Dùng cho mô ph�?ng
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    RC522_RFID_Check();
    KEYPAD_CheckPassword();
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
  HAL_GPIO_WritePin(GPIOB, DOOR_Pin|BUZZZER_Pin|COL3_Pin|COL1_Pin
                          |COL2_Pin|SPI1_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(COL4_GPIO_Port, COL4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DOOR_Pin BUZZZER_Pin COL3_Pin COL1_Pin
                           COL2_Pin SPI1_CS_Pin */
  GPIO_InitStruct.Pin = DOOR_Pin|BUZZZER_Pin|COL3_Pin|COL1_Pin
                          |COL2_Pin|SPI1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
