/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gt911.h"
#include "dbger.h"
#include "atk_ncr.h"
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
/* USER CODE BEGIN Variables */
volatile uint8_t recognize_finish = 0;
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};
/* Definitions for TouchGFX */
osThreadId_t TouchGFXHandle;
const osThreadAttr_t TouchGFX_attributes = {
  .name = "TouchGFX",
  .stack_size = 2048 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for binSemRecognize */
osSemaphoreId_t binSemRecognizeHandle;
const osSemaphoreAttr_t binSemRecognize_attributes = {
  .name = "binSemRecognize"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void TouchGFX_Task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of binSemRecognize */
  binSemRecognizeHandle = osSemaphoreNew(1, 0, &binSemRecognize_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TouchGFX */
  TouchGFXHandle = osThreadNew(TouchGFX_Task, NULL, &TouchGFX_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
__weak void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	
	// GT911 init
	GT911_STA_t gt911_sta = GT911_STA_OK;
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
	gt911_sta = gt911_init();
	if(GT911_STA_OK != gt911_sta) {
		LOG_ERR("GT911 init err[%d]\n", gt911_sta);
	} else {
		LOG_DBG("GT911 init OK\n");
		HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	
//	extern void LTDC_draw_line_test(void);
//	LTDC_draw_line_test();
	
	// hand write lib init
	if(alientek_ncr_init()) {
		LOG_ERR("Hand Write Lib Init ERR\n");
	}
	
  /* Infinite loop */
  for(;;)
  {
    osSemaphoreAcquire(binSemRecognizeHandle, osWaitForever);
		//LOG_DBG("recognize...\n");
//		for(uint16_t i = 0; i < point_num; i+=2) {
//			LOG_DBG("P(%d,%d) P(%d,%d)\n", draw_coor[i].x, draw_coor[i].y, draw_coor[i+1].x, draw_coor[i+1].y);
//			osDelay(2);
//		}
		alientek_ncr(draw_coor, point_num, CHAR_NUM/2, RECOGNIZE_123, result);
		alientek_ncr(draw_coor, point_num, CHAR_NUM/2, RECOGNIZE_ABC, &result[3]);
		recognize_finish = 1;
		LOG_DBG("point_num[%d] result: %s\n", point_num, result);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_TouchGFX_Task */
/**
* @brief Function implementing the TouchGFX thread.
* @param argument: Not used
* @retval None
*/
#include "dbger.h"
/* USER CODE END Header_TouchGFX_Task */
__weak void TouchGFX_Task(void *argument)
{
  /* USER CODE BEGIN TouchGFX_Task */
	char* color[] = {"red", "green", "blue"};
	uint16_t color_code[] = {0xF800, 0x07E0, 0x001F};
	uint8_t cur_color = 0;
  /* Infinite loop */
  for(;;)
  {
    osDelay(3000);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		LOG_DBG("change color to %s\n", color[cur_color]);
		for(uint32_t i = 0; i < 1024*600*2; i += 2) {
			*(uint16_t*)(0xC0000000 + i) = color_code[cur_color];
			//*(uint16_t*)(0xC0000000 + i) = *(uint16_t*)(0xC1000000 + 1024*600*2 * cur_color + i);
		}
		if(++cur_color >= 3) {
			cur_color = 0;
		}
  }
  /* USER CODE END TouchGFX_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

