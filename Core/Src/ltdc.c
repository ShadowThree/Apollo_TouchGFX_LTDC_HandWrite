/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ltdc.c
  * @brief   This file provides code for the configuration
  *          of the LTDC instances.
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
#include "ltdc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

LTDC_HandleTypeDef hltdc;

/* LTDC init function */
void MX_LTDC_Init(void)
{

  /* USER CODE BEGIN LTDC_Init 0 */

  /* USER CODE END LTDC_Init 0 */

  LTDC_LayerCfgTypeDef pLayerCfg = {0};
  LTDC_LayerCfgTypeDef pLayerCfg1 = {0};

  /* USER CODE BEGIN LTDC_Init 1 */

  /* USER CODE END LTDC_Init 1 */
  hltdc.Instance = LTDC;
  hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
  hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
  hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
  hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
  hltdc.Init.HorizontalSync = 19;
  hltdc.Init.VerticalSync = 2;
  hltdc.Init.AccumulatedHBP = 159;
  hltdc.Init.AccumulatedVBP = 22;
  hltdc.Init.AccumulatedActiveW = 1183;
  hltdc.Init.AccumulatedActiveH = 622;
  hltdc.Init.TotalWidth = 1343;
  hltdc.Init.TotalHeigh = 634;
  hltdc.Init.Backcolor.Blue = 0;
  hltdc.Init.Backcolor.Green = 0;
  hltdc.Init.Backcolor.Red = 0;
  if (HAL_LTDC_Init(&hltdc) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg.WindowX0 = 0;
  pLayerCfg.WindowX1 = LTDC_L0_WIDTH;
  pLayerCfg.WindowY0 = 0;
  pLayerCfg.WindowY1 = LTDC_L0_HEIGHT;
  pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg.Alpha = 255;
  pLayerCfg.Alpha0 = 0;
  pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_CA;
  pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_CA;
  pLayerCfg.FBStartAdress = LTDC_L0_ADDR;
  pLayerCfg.ImageWidth = LTDC_L0_WIDTH;
  pLayerCfg.ImageHeight = LTDC_L0_HEIGHT;
  pLayerCfg.Backcolor.Blue = 0;
  pLayerCfg.Backcolor.Green = 0;
  pLayerCfg.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
  {
    Error_Handler();
  }
  pLayerCfg1.WindowX0 = LTDC_L1_START_X;
  pLayerCfg1.WindowX1 = (LTDC_L1_START_X + LTDC_L1_WIDTH);
  pLayerCfg1.WindowY0 = LTDC_L1_START_Y;
  pLayerCfg1.WindowY1 = (LTDC_L1_START_Y + LTDC_L1_HEIGHT);
  pLayerCfg1.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
  pLayerCfg1.Alpha = 255;
  pLayerCfg1.Alpha0 = 0;
  pLayerCfg1.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
  pLayerCfg1.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
  pLayerCfg1.FBStartAdress = LTDC_L1_ADDR;
  pLayerCfg1.ImageWidth = LTDC_L1_WIDTH;
  pLayerCfg1.ImageHeight = LTDC_L1_HEIGHT;
  pLayerCfg1.Backcolor.Blue = 0;
  pLayerCfg1.Backcolor.Green = 0;
  pLayerCfg1.Backcolor.Red = 0;
  if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg1, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN LTDC_Init 2 */

  /* USER CODE END LTDC_Init 2 */

}

void HAL_LTDC_MspInit(LTDC_HandleTypeDef* ltdcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLL3.PLL3M = 5;
    PeriphClkInitStruct.PLL3.PLL3N = 40;
    PeriphClkInitStruct.PLL3.PLL3P = 2;
    PeriphClkInitStruct.PLL3.PLL3Q = 2;
    PeriphClkInitStruct.PLL3.PLL3R = 4;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_2;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* LTDC clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOI_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 13, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* ltdcHandle)
{

  if(ltdcHandle->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PI9     ------> LTDC_VSYNC
    PI10     ------> LTDC_HSYNC
    PF10     ------> LTDC_DE
    PH9     ------> LTDC_R3
    PH10     ------> LTDC_R4
    PH11     ------> LTDC_R5
    PH12     ------> LTDC_R6
    PG6     ------> LTDC_R7
    PG7     ------> LTDC_CLK
    PH13     ------> LTDC_G2
    PH14     ------> LTDC_G3
    PH15     ------> LTDC_G4
    PI0     ------> LTDC_G5
    PI1     ------> LTDC_G6
    PI2     ------> LTDC_G7
    PG11     ------> LTDC_B3
    PI4     ------> LTDC_B4
    PI5     ------> LTDC_B5
    PI6     ------> LTDC_B6
    PI7     ------> LTDC_B7
    */
    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_0|GPIO_PIN_1
                          |GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7);

    HAL_GPIO_DeInit(GPIOF, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOH, GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);

    HAL_GPIO_DeInit(GPIOG, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11);

    /* LTDC interrupt Deinit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
#include <stdlib.h>
#include "atk_ncr.h"

#define LTDC_DBG_EN	0
#if LTDC_DBG_EN
#include "dbger.h"
#define LTDC_DBG(fmt, ...)	LOG_DBG(fmt, ##__VA_ARGS__)
#else
#define LTDC_DBG(fmt, ...)
#endif
void LTDC_draw_line(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t width)
{
	#define DELAY_TIME	20
	//#define DRAW_LINE_DELAY(ms)		osDelay(ms)
	#define DRAW_LINE_DELAY(ms)
	uint32_t addr;
	int16_t val;
	if(abs(x1-x2) > abs(y1-y2)) {
		val = (int16_t)(100.0f * abs(y2-y1) / abs(x2-x1));
		if(x1 < x2) {
			if(y1 < y2) {		// abs(x1-x2) > abs(y1-y2)		// x1 < x2		// y1 < y2
				for(int16_t i = x1; i <= x2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1+val*(i-x1)/100;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1+val*(i-x1)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1+val*(i-x1)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) > abs(y1-y2)		// x1 < x2		// y1 >= y2
				for(int16_t i = x1; i <= x2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1-val*(i-x1)/100;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1-val*(i-x1)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1-val*(i-x1)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		} else {
			if(y1 < y2) {		// abs(x1-x2) > abs(y1-y2)		// x1 >= x2		// y1 < y2
				for(int16_t i = x1; i >= x2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1+val*(x1-i)/100;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1+val*(x1-i)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1+val*(x1-i)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) > abs(y1-y2)		// x1 >= x2		// y1 >= y2
				for(int16_t i = x1; i >= x2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = i;
						draw_coor[point_num++].y = y1-val*(x1-i)/100;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (i - LTDC_L1_START_X) * 2 + (( y1-val*(x1-i)/100+j ) - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", i, y1-val*(x1-i)/100+j, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		}
	} else {
		val = (int16_t)(100.0f * abs(x2-x1) / abs(y2-y1));
		if(x1 < x2) {
			if(y1 < y2) {		// abs(x1-x2) <= abs(y1-y2)		// x1 < x2		// y1 < y2
				for(int16_t i = y1; i <= y2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = x1+val*(i-y1)/100;
						draw_coor[point_num++].y = i;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1+val*(i-y1)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1+val*(i-y1)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) <= abs(y1-y2)		// x1 < x2		// y1 >= y2
				for(int16_t i = y1; i >= y2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = x1+val*(y1-i)/100;
						draw_coor[point_num++].y = i;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1+val*(y1-i)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1+val*(y1-i)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		} else {
			if(y1 < y2) {		// abs(x1-x2) <= abs(y1-y2)		// x1 >= x2		// y1 < y2
				for(int16_t i = y1; i <= y2; i++) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = x1-val*(i-y1)/100;
						draw_coor[point_num++].y = i;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1-val*(i-y1)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1-val*(i-y1)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			} else {		// abs(x1-x2) <= abs(y1-y2)		// x1 >= x2		// y1 >= y2
				for(int16_t i = y1; i >= y2; i--) {
					DRAW_LINE_DELAY(DELAY_TIME);
					if(point_num < MAX_POINT) {
						draw_coor[point_num].x = x1-val*(y1-i)/100;
						draw_coor[point_num++].y = i;
					}
					for(int8_t j = -width; j <= width; j++) {
						addr = (LTDC_L1_ADDR + (( x1-val*(y1-i)/100+j ) - LTDC_L1_START_X) * 2 + (i - LTDC_L1_START_Y) * LTDC_L1_WIDTH * 2);
						LTDC_DBG("\tp(%d,%d) addr:0x%08x\n", x1-val*(y1-i)/100+j, i, addr);
						*(uint16_t*)addr = 0;
					}
				}
			}
		}
	}
}
/* USER CODE END 1 */
