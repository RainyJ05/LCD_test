#include "touch.h"

/*
读取XPT2046 x,y数据
hspi:spi外设句柄
cmd:读取控制字节，0xd0读x轴 0x90读y轴
*/
uint16_t XPT2046_Read(SPI_HandleTypeDef *hspi, uint16_t cmd)
{
    //用于延时和存储数据
    uint16_t num = 0;

    //以片选定义为条件控制编译，防止在没有定义下编译报错
#if defined( LCD_T_CS_GPIO_Port )
    uint8_t spi_r[2] , spi_t;

    //只有当触碰笔触时才读取，否则返回0
    if(HAL_GPIO_ReadPin(LCD_T_PEN_GPIO_Port, LCD_T_PEN_Pin) == GPIO_PIN_RESET)
    {
        //片选使能
			  
        HAL_GPIO_WritePin(LCD_T_CS_GPIO_Port, LCD_T_CS_Pin, GPIO_PIN_RESET);
        //写命令
        spi_t = cmd;
        HAL_SPI_TransmitReceive(hspi, &spi_t, spi_r, 1, 100);

        //延时等待转换
        num = 50;
        while(num--);
        spi_t = 0;

        //读取16位数据
        HAL_SPI_TransmitReceive(hspi, &spi_t, spi_r, 2, 100);

        //数据转换，保留中间12位
        num = (spi_r[0] << 8) | spi_r[1];
			  num &= ~(1<<15);
        num >>= 3;
        //片选失能
        HAL_GPIO_WritePin(LCD_T_CS_GPIO_Port, LCD_T_CS_Pin, GPIO_PIN_SET);
#endif
    }
    return num;
}

/*
带滤波读取XPT2046 x,y数据
hspi:spi外设句柄
cmd:读取控制字节，0xd0读x轴 0x90读y轴
*/
uint16_t XPT2046_Read_Filter(SPI_HandleTypeDef *hspi, uint16_t cmd)
{
    uint16_t i, j;
    uint16_t buf[TP_READ_TIMES];
    uint16_t sum = 0;
    uint16_t temp;

    for (i = 0; i < TP_READ_TIMES; i++)     /* 先读取TP_READ_TIMES次数据 */
    {
        buf[i] = XPT2046_Read(hspi,cmd);
    }

    for (i = 0; i < TP_READ_TIMES - 1; i++) /* 对数据进行排序 */
    {
        for (j = i + 1; j < TP_READ_TIMES; j++)
        {
            if (buf[i] > buf[j])   /* 升序排列 */
            {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    sum = 0;

    for (i = TP_LOST_VAL; i < TP_READ_TIMES - TP_LOST_VAL; i++)   /* 去掉两端的丢弃值 */
    {
        sum += buf[i];  /* 累加去掉丢弃值以后的数据. */
    }

    temp = sum / (TP_READ_TIMES - 2 * TP_LOST_VAL); /* 取平均值 */
    return temp;
}























