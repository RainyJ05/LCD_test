#ifndef __TOUCH_H
#define __TOUCH_H		

#include "stm32f4xx.h"                  // Device header
#include "main.h"
#include "math.h"
#include "stdlib.h"

/* 电阻触摸驱动芯片 数据采集 滤波用参数 */
#define TP_READ_TIMES   5       /* 读取次数 */
#define TP_LOST_VAL     1       /* 丢弃值 */

uint16_t XPT2046_Read(SPI_HandleTypeDef *hspi, uint16_t cmd);//注意格式化显示数据的%4d
uint16_t XPT2046_Read_Filter(SPI_HandleTypeDef *hspi, uint16_t cmd);//带滤波的读取函数
#endif
