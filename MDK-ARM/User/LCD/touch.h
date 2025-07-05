#ifndef __TOUCH_H
#define __TOUCH_H		

#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "math.h"
#include "stdlib.h"

/* 电阻触摸驱动芯片 数据采集 滤波用参数 */
#define TP_READ_TIMES   5       /* 读取次数 */
#define TP_LOST_VAL     1       /* 丢弃值 */

#define TOUCH_X_LEFT_ADC  3750
#define TOUCH_X_RIGHT_ADC  380 
#define TOUCH_Y_UP_ADC  3850
#define TOUCH_Y_DOWN_ADC  480

#define touch_x_k  (float)(240 - 10)/(TOUCH_X_RIGHT_ADC - TOUCH_X_LEFT_ADC)
#define touch_x_b  (5*TOUCH_X_RIGHT_ADC - 235*TOUCH_X_LEFT_ADC)/(TOUCH_X_RIGHT_ADC - TOUCH_X_LEFT_ADC)
#define touch_y_k  (float)(320 - 10)/(TOUCH_Y_DOWN_ADC - TOUCH_Y_UP_ADC)
#define touch_y_b  (5*TOUCH_Y_DOWN_ADC - 315*TOUCH_Y_UP_ADC)/(TOUCH_Y_DOWN_ADC - TOUCH_Y_UP_ADC)

uint16_t XPT2046_Read(SPI_HandleTypeDef *hspi, uint16_t cmd);//注意格式化显示数据的%4d
uint16_t XPT2046_Read_Filter(SPI_HandleTypeDef *hspi, uint16_t cmd);//带滤波的读取函数


uint32_t XPT2046_Get_Point(SPI_HandleTypeDef *hspi);
#endif

