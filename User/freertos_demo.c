#include "freertos_demo.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./BSP/DHT11/driver_dht11.h"
#include "dev_uart.h"

#include "FreeRTOS.h"
#include "task.h"

#define START_TASK_PRIO 1                   /* �������ȼ� */
#define START_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            StartTask_Handler;  /* ������ */
void start_task(void *pvParameters);        /* ������ */


#define TASK1_PRIO      2                   /* �������ȼ� */
#define TASK1_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task1Task_Handler;  /* ������ */
void task1(void *pvParameters);             /* ������ */


#define TASK2_PRIO      3                   /* �������ȼ� */
#define TASK2_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task2Task_Handler;  /* ������ */
void task2(void *pvParameters);             /* ������ */

#define TASK3_PRIO      4                   /* �������ȼ� */
#define TASK3_STK_SIZE  128                 /* �����ջ��С */
TaskHandle_t            Task3Task_Handler;  /* ������ */
void task3_lcd(void *pvParameters);             /* ������ */

#define UART_TASK_PRIO      5
#define UART_TASK_STK_SIZE  256
TaskHandle_t UartTask_Handler;
void uart_loop_task(void *pvParameters);

void freertos_demo(void)
{
    
    xTaskCreate((TaskFunction_t )start_task,            /* ������ */
                (const char*    )"start_task",          /* �������� */
                (uint16_t       )START_STK_SIZE,        /* �����ջ��С */
                (void*          )NULL,                  /* ������������Ĳ��� */
                (UBaseType_t    )START_TASK_PRIO,       /* �������ȼ� */
                (TaskHandle_t*  )&StartTask_Handler);   /* ������ */
    vTaskStartScheduler();
}

void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           /* �����ٽ��� */

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

				
    vTaskDelete(StartTask_Handler); /* ɾ����ʼ���� */
    taskEXIT_CRITICAL();            /* �˳��ٽ��� */
}

void task1(void *pvParameters)
{
  
    while(1)
    {

        LED0_TOGGLE();                                                  /* LED0��˸ */
        vTaskDelay(1000);                                               /* ��ʱ1000ticks */
    }
}

void task2(void *pvParameters)
{
	
    while(1)
    {
		LED1_TOGGLE();                                                  /* LED1��˸ */
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
        // UART1 ����
        size = uart_read(DEV_UART1, buf, sizeof(buf));//STM32��DMA+FIFO�ж�ȡ��SSCOM���͵�����
        if (size > 0)
            uart_write(DEV_UART1, buf, size);//��ʱSTM32�Ƿ����ߣ�ͨ�����ָ��������·����ڿ������ڻ���
        // ���� DMA ���ͣ����ڽ� FIFO ������ˢ�µ����ڣ�
        uart_poll_dma_tx(DEV_UART1);
        // ������ʱ���ɵ������� CPU ռ�ù���
        vTaskDelay(10);  // ÿ1ms����һ�Σ��ɸ������ܵ���
    }
}

