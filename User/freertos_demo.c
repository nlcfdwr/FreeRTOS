#include "freertos_demo.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/DHT11/driver_dht11.h"
#include "dev_uart.h"

#include "FreeRTOS.h"
#include "task.h"

#define START_TASK_PRIO 1                   /* 任务优先级 */
#define START_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            StartTask_Handler;  /* 任务句柄 */
void start_task(void *pvParameters);        /* 任务函数 */


#define TASK1_PRIO      2                   /* 任务优先级 */
#define TASK1_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task1Task_Handler;  /* 任务句柄 */
void task1(void *pvParameters);             /* 任务函数 */


#define TASK2_PRIO      3                   /* 任务优先级 */
#define TASK2_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task2Task_Handler;  /* 任务句柄 */
void task2(void *pvParameters);             /* 任务函数 */

#define TASK3_PRIO      4                   /* 任务优先级 */
#define TASK3_STK_SIZE  128                 /* 任务堆栈大小 */
TaskHandle_t            Task3Task_Handler;  /* 任务句柄 */
void task3_lcd(void *pvParameters);             /* 任务函数 */

#define UART_TASK_PRIO      5
#define UART_TASK_STK_SIZE  256
TaskHandle_t UartTask_Handler;
void uart_loop_task(void *pvParameters);

void freertos_demo(void)
{
    
    xTaskCreate((TaskFunction_t )start_task,            /* 任务函数 */
                (const char*    )"start_task",          /* 任务名称 */
                (uint16_t       )START_STK_SIZE,        /* 任务堆栈大小 */
                (void*          )NULL,                  /* 传入给任务函数的参数 */
                (UBaseType_t    )START_TASK_PRIO,       /* 任务优先级 */
                (TaskHandle_t*  )&StartTask_Handler);   /* 任务句柄 */
    vTaskStartScheduler();
}

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* 进入临界区 */

    xTaskCreate((TaskFunction_t )task1,
                (const char*    )"task1",
                (uint16_t       )TASK1_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK1_PRIO,
                (TaskHandle_t*  )&Task1Task_Handler);

    xTaskCreate((TaskFunction_t )task2,
                (const char*    )"task2",
                (uint16_t       )TASK2_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK2_PRIO,
                (TaskHandle_t*  )&Task2Task_Handler);
				
	xTaskCreate((TaskFunction_t )task3_lcd,
                (const char*    )"task3",
                (uint16_t       )TASK3_STK_SIZE,
                (void*          )NULL,
                (UBaseType_t    )TASK3_PRIO,
                (TaskHandle_t*  )&Task3Task_Handler);
				
	xTaskCreate((TaskFunction_t )uart_loop_task,
            (const char*    )"uart_loop",
            (uint16_t       )UART_TASK_STK_SIZE,
            (void*          )NULL,
            (UBaseType_t    )UART_TASK_PRIO,
            (TaskHandle_t*  )&UartTask_Handler);

				
    vTaskDelete(StartTask_Handler); /* 删除开始任务 */
    taskEXIT_CRITICAL();            /* 退出临界区 */
}

void task1(void *pvParameters)
{
  
    while(1)
    {

        LED0_TOGGLE();                                                  /* LED0闪烁 */
        vTaskDelay(1000);                                               /* 延时1000ticks */
    }
}

void task2(void *pvParameters)
{
	
    while(1)
    {
		LED1_TOGGLE();                                                  /* LED1闪烁 */
        vTaskDelay(1000);  
    }
}

void task3_lcd(void *pvParameters)
{
	extern uint8_t Data[5];
	char str[32];
    while(1)
    {
		if(DHT_Read()){
			uint8_t Humi = Data[0];
			uint8_t Temp = Data[2];
			sprintf(str, "Temp: %d C", Temp);
            lcd_show_string(40, 10, 220, 24, 24, str, BLUE);
            sprintf(str, "Humi: %d %%", Humi);
            lcd_show_string(40, 40, 220, 24, 24, str, RED);
		}
        vTaskDelay(1000);  
    }
}

void uart_loop_task(void *pvParameters)
{
    uint8_t buf[256];
    uint16_t size;

    while (1)
    {
        // UART1 环回
        size = uart_read(DEV_UART1, buf, sizeof(buf));//STM32从DMA+FIFO中读取从SSCOM发送的数据
        if (size > 0)
            uart_write(DEV_UART1, buf, size);//此时STM32是发送者，通过这句指令可以在下方窗口看到串口回显
        // 启动 DMA 发送（用于将 FIFO 中数据刷新到串口）
        uart_poll_dma_tx(DEV_UART1);
        // 任务延时（可调）避免 CPU 占用过高
        vTaskDelay(10);  // 每1ms调度一次，可根据性能调整
    }
}

