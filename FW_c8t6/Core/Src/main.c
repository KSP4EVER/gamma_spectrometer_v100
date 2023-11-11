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
#include "fatfs.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usbd_cdc_if.h"
#include "stm32f1xx_it.h"
#include "math.h"
#include <inttypes.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

//EEPROM I2C defines////////////////////////////////////////////////////////////
#define ONBRD_EEPROM_READ_ADDR  0xAD
#define ONBRD_EEPROM_WRITE_ADDR 0xAC

#define DET_EEPROM_READ_ADDR	0xAF
#define DET_EEPROM_WRITE_ADDR	0xAE

#define MAX_PAGE_SIZE 0x0F
#define MAX_PAGE_NUMBER 0x0F
////////////////////////////////////////////////////////////////////////////////

#define DET_TYPE_CONST_ADDR 	 0x00
#define SCI_TYPE_CONST_ADDR    0x10

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
FATFS fs;
FIL fil;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

I2C_HandleTypeDef hi2c2;

RTC_HandleTypeDef hrtc;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI1_Init(void);
static void MX_RTC_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
char vcp_command[32];
char vcp_data[32];

volatile struct Sensor_Data
{
	uint16_t channel_count;
	uint8_t  channel_count_ovf;

}sensor_data[2048];

volatile uint32_t DET_VALUE = 0;
volatile uint8_t meas_start = 0;
volatile uint8_t data_ready = 0;
volatile uint32_t sys_tick_ms = 0;
char file_name[64];


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//start/stop button pressed
    if(GPIO_Pin == START_BTN_Pin)
    {
    	//meas_start = 0 -> wait
    	//meas_start = 1 -> start measurment cycle
    	//meas_start = 2 -> stop measurment cycle
        meas_start++;
    }
    if((GPIO_Pin == THRESHOLD_IRQ_Pin)&&(meas_start == 1))
    {
    	//notify the main loop to measure detector signal
    	if(data_ready == 0)data_ready++;
    }
}
void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
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
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_I2C2_Init();
  MX_SPI1_Init();
  MX_FATFS_Init();
  MX_RTC_Init();
  MX_USB_DEVICE_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  char sd_buffer[40] = "0123456789ABCDEF0123456789ABCDEF\n";
  char meas_start_time[40];
  char meas_end_time[40];
  char file_name_buff[32] = "noname";

  HAL_ADCEx_Calibration_Start(&hadc1);
  HAL_ADCEx_Calibration_Start(&hadc2);


  //HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1);
  HAL_TIM_Base_Start(&htim1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while(1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  //blink status led
	  if(sys_tick_ms >= 100)
	  {
		  sys_tick_ms = 0;
		  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
		  //HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0xFFFF); // backup register

		  //check if the detector is connected/////////////////////////////////
/*
		  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1)
		  {
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
		  }
		  else
		  {
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
		  }
*/
		  ////////////////////////////////////////////////////////////////////
	  }
	  /////////////////////////////////////////////////////////////////////////////////

	  //command fetch from virtual com ports///////////////////////////////////////////

	  //start measurment///////////////////////////////////////////////////////////////
	  if(strcmp(vcp_command,"start") == 0)
	  {
		 if(meas_start == 0)
		 {
			 memcpy(file_name_buff,vcp_data,sizeof(vcp_data));


			 RTC_DateTypeDef gDate;
			 RTC_TimeTypeDef gTime;
			 HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
			 HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
			 sprintf(file_name,"%s_%2d-%02d-%02d-%02d-%02d-%02d.txt",file_name_buff,2000 + gDate.Year,gDate.Month,gDate.Date,gTime.Hours, gTime.Minutes, gTime.Seconds);
			 sprintf(meas_start_time,"%2d-%02d-%02d-%02d-%02d-%02d",2000 + gDate.Year,gDate.Month,gDate.Date,gTime.Hours, gTime.Minutes, gTime.Seconds);

			 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
			 meas_start = 1;
		 }
		 else; //valami hibaüzenetet visszaírni opcionálisan

	        memset(vcp_command,'0',sizeof(vcp_command));
	  }
	  ////////////////////////////////////////////////////////////////////////////////

	  //stop measurment////////////////////////////////////////////////////////////////
	  else if(strcmp(vcp_command,"stop") == 0)
	  {
		  if(meas_start == 1)meas_start = 2;
		  else; //valami hibaüzenetet visszaírni opcionálisan

	        memset(vcp_command,'0',sizeof(vcp_command));
	  }
	  ////////////////////////////////////////////////////////////////////////////////////

	  //write detector type to eeprom/////////////////////////////////////////////////////////////
	 /* else if(strcmp(vcp_command,"eeprom_write_det") == 0)
	  {
         HAL_I2C_Mem_Write(&hi2c2,DET_EEPROM_WRITE_ADDR,DET_TYPE_CONST_ADDR,I2C_MEMADD_SIZE_8BIT ,(uint8_t*)vcp_data,16,HAL_MAX_DELAY);
         HAL_Delay(50);

	     memset(vcp_command,'0',sizeof(vcp_command));
	  }
	 */ //////////////////////////////////////////////////////////////////////////////////////////

	  //write scintillator type to eeprom/////////////////////////////////////////////////////////////
	 /* else if(strcmp(vcp_command,"eeprom_write_sci") == 0)
	  {
         HAL_I2C_Mem_Write(&hi2c2,DET_EEPROM_WRITE_ADDR,SCI_TYPE_CONST_ADDR,I2C_MEMADD_SIZE_8BIT ,(uint8_t*)vcp_data,16,HAL_MAX_DELAY);
         HAL_Delay(50);

	     memset(vcp_command,'0',sizeof(vcp_command));
	  }
	  *///////////////////////////////////////////////////////////////////////////////////////////

	  //read data from eeprom
     /* else if(strcmp(vcp_command,"eeprom_read") == 0)
      {
    	 char buffer[32] = "";
    	 uint8_t det_type[15] ="";
         uint8_t sci_type[15] ="";

         HAL_I2C_Mem_Read(&hi2c2,DET_EEPROM_READ_ADDR,DET_TYPE_CONST_ADDR,I2C_MEMADD_SIZE_8BIT ,det_type,16,HAL_MAX_DELAY);
         HAL_Delay(50);
         HAL_I2C_Mem_Read(&hi2c2,DET_EEPROM_READ_ADDR,SCI_TYPE_CONST_ADDR,I2C_MEMADD_SIZE_8BIT ,sci_type,16,HAL_MAX_DELAY);

         sprintf(buffer,"%s %s\n",det_type,sci_type);

         CDC_Transmit_FS((char*)buffer,sizeof(buffer));
         memset(vcp_command,'0',sizeof(vcp_command));
      }*/
	  ////////////////////////////////////////////////////////////////////////////////////////

	  //read temperature data////////////////////////////////////////////////////////////
	  else if(strcmp(vcp_command,"temp") == 0)
	  {
		  volatile int16_t AD_RES = 0;
		  char buffer[5];
	       // Start ADC Conversion
	        HAL_ADC_Start(&hadc2);
	       // Poll ADC1 Perihperal & TimeOut = 1mSec
	        HAL_ADC_PollForConversion(&hadc2, 10);
	        AD_RES = HAL_ADC_GetValue(&hadc2);

	        sprintf(buffer,"%d\n",AD_RES);

	        CDC_Transmit_FS(buffer, sizeof(buffer));
	        HAL_Delay(1);

	        memset(vcp_command,'0',sizeof(vcp_command));

	  }

	  //set date time
	  else if(strcmp(vcp_command,"set_time") == 0)
	  {
		  RTC_TimeTypeDef sTime;
		  RTC_DateTypeDef sDate;

		  unsigned int hours,mins,sec,date,month,year;

		  sscanf(vcp_data,"%d-%d-%d-%d-%d-%d",&year,&month,&date,&hours, &mins,&sec);

		  sTime.Hours = (uint8_t)hours;
		  sTime.Minutes = (uint8_t)mins;
		  sTime.Seconds = (uint8_t)sec;
		  sDate.Date = (uint8_t)date;
		  sDate.Month = (uint8_t)month;
		  sDate.Year = (uint8_t)year;

		  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	        memset(vcp_command,'0',sizeof(vcp_command));
	  }
	  /////////////////////////////////////////////////////////////////////////

	  //set file_name
	  else if(strcmp(vcp_command,"set_file_name") == 0)
	  {

		  memset(file_name_buff,'\0',sizeof(file_name_buff));
		  memcpy(file_name_buff,vcp_data,sizeof(vcp_data));

	      memset(vcp_command,'0',sizeof(vcp_command));
	  }
	  ////////////////////////////////////////////////////////////////////////

	  //get date time
	  else if(strcmp(vcp_command,"get_time") == 0)
	  {
		  char time[19];
		  memset(time,'0',sizeof(time));

		  RTC_DateTypeDef gDate;
		  RTC_TimeTypeDef gTime;
		  HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
		  HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
		  sprintf(time,"%2d-%02d-%02d-%02d-%02d-%02d",2000 + gDate.Year,gDate.Month,gDate.Date,gTime.Hours, gTime.Minutes, gTime.Seconds);

	      CDC_Transmit_FS(time, sizeof(time));

	      memset(vcp_command,'0',sizeof(vcp_command));
	  }
	  ///////////////////////////////////////////////////////////////////////////


	 //start data logging////////////////////////////////////////////////////////
	 // if(meas_start == 1)
	 // {
	 //	 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);

	 // }
	 ////////////////////////////////////////////////////////////////////////////

	 //data logging stopped//////////////////////////////////////////////////////
	 if(meas_start == 2)
	 {
		 //memset(file_name,'\0',sizeof(file_name));


	     CDC_Transmit_FS(file_name, sizeof(file_name));

	     //mount sd card
		 f_mount(&fs, "", 0);
		 f_open(&fil, file_name, FA_OPEN_ALWAYS | FA_WRITE);
		 f_lseek(&fil, fil.fsize);

		 //write detector and scintillator type in the first row
    	/* uint8_t det_type[15] ="";
         uint8_t sci_type[15] ="";

         HAL_I2C_Mem_Read(&hi2c2,DET_EEPROM_READ_ADDR,DET_TYPE_CONST_ADDR,I2C_MEMADD_SIZE_8BIT ,det_type,15,HAL_MAX_DELAY);
         HAL_Delay(50);
         HAL_I2C_Mem_Read(&hi2c2,DET_EEPROM_READ_ADDR,SCI_TYPE_CONST_ADDR,I2C_MEMADD_SIZE_8BIT ,sci_type,15,HAL_MAX_DELAY);

         sprintf(sd_buffer,"%s;%s\n",det_type,sci_type);
         f_puts(sd_buffer, &fil);
        */ ////////////////////////////////////////////////////////////////

         //write start and stop time to the second row
         RTC_DateTypeDef gDate;
         RTC_TimeTypeDef gTime;
         HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
         HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
         sprintf(meas_end_time,"%2d-%02d-%02d-%02d-%02d-%02d",2000 + gDate.Year,gDate.Month,gDate.Date,gTime.Hours, gTime.Minutes, gTime.Seconds);

		 sprintf(sd_buffer,"%s;%s\n",meas_start_time,meas_end_time);
		 f_puts(sd_buffer, &fil);
		 ///////////////////////////////////////////////////////////////

		 //write measured data
		 for (int i = 0;i < 2048;i++)
		 {
			sprintf(sd_buffer,"%d;%d\n",sensor_data[i].channel_count,sensor_data[i].channel_count_ovf);
		    f_puts(sd_buffer, &fil);
		 }

		 f_close(&fil);

		 f_mount(NULL, "", 0);

		 meas_start = 0;
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	 }
	 //////////////////////////////////////////////////////////////////////////////

	 if(data_ready == 1)
	 {
		 //HAL_Delay(1);
		 delay_us(5);
		 DET_VALUE = 0;
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

		 HAL_ADC_Start(&hadc1);
		 HAL_ADC_PollForConversion(&hadc1,5);
		 DET_VALUE = HAL_ADC_GetValue(&hadc1);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);

		 DET_VALUE = DET_VALUE/2;

		 //short capacitor in the peak detector
		  //

		  if(sensor_data[DET_VALUE].channel_count == 65535)
		  {
		  	  sensor_data[DET_VALUE].channel_count = 0;
		  	  sensor_data[DET_VALUE].channel_count_ovf++;
		  }
		  else
		  {
		  	  sensor_data[DET_VALUE].channel_count++;
		  }

		  //rövidzár megszüntetése
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

		  delay_us(20);
		  //HAL_Delay(1);
		  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
		  data_ready = 0;
	 }

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC
                              |RCC_PERIPHCLK_USB;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_6;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief ADC2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC2_Init(void)
{

  /* USER CODE BEGIN ADC2_Init 0 */

  /* USER CODE END ADC2_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC2_Init 1 */

  /* USER CODE END ADC2_Init 1 */
  /** Common config
  */
  hadc2.Instance = ADC2;
  hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc2.Init.ContinuousConvMode = DISABLE;
  hadc2.Init.DiscontinuousConvMode = DISABLE;
  hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc2.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_5;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC2_Init 2 */

  /* USER CODE END ADC2_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef DateToUpdate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;

  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
  DateToUpdate.Month = RTC_MONTH_JANUARY;
  DateToUpdate.Date = 0x1;
  DateToUpdate.Year = 0x20;

  if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

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
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
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
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 48+1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SYS_BEEP_Pin|LED_RUN_Pin|SD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PEAK_DET_RST_Pin|LED_COM_Pin|LED_CON_Pin|LED_SD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(V_DET_TOOGLE_GPIO_Port, V_DET_TOOGLE_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : SD_DET_Pin */
  GPIO_InitStruct.Pin = SD_DET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SD_DET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SYS_BEEP_Pin SD_CS_Pin */
  GPIO_InitStruct.Pin = SYS_BEEP_Pin|SD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LED_RUN_Pin */
  GPIO_InitStruct.Pin = LED_RUN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_RUN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : THRESHOLD_IRQ_Pin */
  GPIO_InitStruct.Pin = THRESHOLD_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(THRESHOLD_IRQ_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PEAK_DET_RST_Pin LED_COM_Pin */
  GPIO_InitStruct.Pin = PEAK_DET_RST_Pin|LED_COM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : DET_CON_Pin */
  GPIO_InitStruct.Pin = DET_CON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(DET_CON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : V_DET_TOOGLE_Pin */
  GPIO_InitStruct.Pin = V_DET_TOOGLE_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(V_DET_TOOGLE_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : START_BTN_Pin */
  GPIO_InitStruct.Pin = START_BTN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(START_BTN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_CON_Pin LED_SD_Pin */
  GPIO_InitStruct.Pin = LED_CON_Pin|LED_SD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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

