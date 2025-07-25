/**
 ****************************************************************************************************
 * @file        main.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       跑马灯 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/LED/led.h"
#include "./BSP/KEY/key.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/DHT11/driver_dht11.h"
#include "FreeRTOS.h"
#include "task.h"
#include "freertos_demo.h"
#include "dev_uart.h"

int main(void)
{
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(336, 8, 2, 7);         /* 设置时钟,168Mhz */
    delay_init(168);                            /* 延时初始化 */
	//usart_init(115200);                     /* 串口初始化为115200 */
    led_init();                                 /* 初始化LED */
	beep_init();                            /* 初始化蜂鸣器 */
    extix_init();                           /* 初始化外部中断输入 */
	lcd_init();
	key_init();
	uart_device_init(DEV_UART1);
	
	freertos_demo();                    /* 运行FreeRTOS例程 */
	
}

