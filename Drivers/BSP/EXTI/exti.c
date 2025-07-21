
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/BEEP/beep.h"
#include "./BSP/KEY/key.h"
#include "./BSP/EXTI/exti.h"
#include "dev_uart.h"
#include "FreeRTOS.h"
#include "task.h"

void KEY0_INT_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY0�����ж��� ���жϱ�־λ */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY0_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void KEY1_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY1_INT_GPIO_PIN);         /* �����жϴ����ú��� ���KEY1�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY1_INT_GPIO_PIN);         /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void KEY2_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(KEY2_INT_GPIO_PIN);        /* �����жϴ����ú��� ���KEY2�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(KEY2_INT_GPIO_PIN);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void WKUP_INT_IRQHandler(void)
{ 
    HAL_GPIO_EXTI_IRQHandler(WKUP_INT_GPIO_PIN);        /* �����жϴ����ú��� ���KEY_UP�����ж��� ���жϱ�־λ���ж��°벿��HAL_GPIO_EXTI_Callbackִ�� */
    __HAL_GPIO_EXTI_CLEAR_IT(WKUP_INT_GPIO_PIN);        /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
}

void USART1_IRQHandler(void)
{
    if (LL_USART_IsEnabledIT_IDLE(USART1) && LL_USART_IsActiveFlag_IDLE(USART1)) 
    {
        uart_dmarx_idle_isr(DEV_UART1);
        LL_USART_ClearFlag_IDLE(USART1);                              
    }
}

void DMA2_Stream2_IRQHandler(void)
{
    if (LL_DMA_IsEnabledIT_HT(DMA2, LL_DMA_STREAM_2) && LL_DMA_IsActiveFlag_HT2(DMA2)) 
    {
        uart_dmarx_half_done_isr(DEV_UART1);
        LL_DMA_ClearFlag_HT2(DMA2);             
    }

    if (LL_DMA_IsEnabledIT_TC(DMA2, LL_DMA_STREAM_2) && LL_DMA_IsActiveFlag_TC2(DMA2)) 
    {
          uart_dmarx_done_isr(DEV_UART1);
          LL_DMA_ClearFlag_TC2(DMA2);          
    }
}

void DMA2_Stream7_IRQHandler(void)
{
    if (LL_DMA_IsEnabledIT_TC(DMA2, LL_DMA_STREAM_7) && LL_DMA_IsActiveFlag_TC7(DMA2)) 
    {
        uart_dmatx_done_isr(DEV_UART1);
        LL_DMA_ClearFlag_TC7(DMA2);             
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(20);      /* ���� */
    switch(GPIO_Pin)
    {
        case KEY0_INT_GPIO_PIN:
            if (KEY0 == 0)
            {
				BEEP_TOGGLE();  /* ������״̬ȡ�� */ 
            }
            break;

        case KEY1_INT_GPIO_PIN:
            if (KEY1 == 0)
            {
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */ 
            }
            break;

        case KEY2_INT_GPIO_PIN:
            if (KEY2 == 0)
            {
                LED1_TOGGLE();  /* LED1 ״̬ȡ�� */
                LED0_TOGGLE();  /* LED0 ״̬ȡ�� */ 
            }
            break;

        case WKUP_INT_GPIO_PIN:
            if (WK_UP == 1)
            {
                BEEP_TOGGLE();  /* ������״̬ȡ�� */ 
            }
            break;

        default : break;
    }
}

void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    key_init();
    gpio_init_struct.Pin = KEY0_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* �½��ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_INT_GPIO_PORT, &gpio_init_struct);    /* KEY0����Ϊ�½��ش����ж� */

    gpio_init_struct.Pin = KEY1_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* �½��ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY1_INT_GPIO_PORT, &gpio_init_struct);    /* KEY1����Ϊ�½��ش����ж� */
    
    gpio_init_struct.Pin = KEY2_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;            /* �½��ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(KEY2_INT_GPIO_PORT, &gpio_init_struct);    /* KEY2����Ϊ�½��ش����ж� */
    
    gpio_init_struct.Pin = WKUP_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_RISING;             /* �����ش��� */
    gpio_init_struct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(WKUP_GPIO_PORT, &gpio_init_struct);        /* WKUP����Ϊ�����ش����ж� */

    HAL_NVIC_SetPriority(KEY0_INT_IRQn, 0, 0);               /* ��ռ0�������ȼ�0 */
    HAL_NVIC_EnableIRQ(KEY0_INT_IRQn);                       /* ʹ���ж���4 */

    HAL_NVIC_SetPriority(KEY1_INT_IRQn, 1, 0);               /* ��ռ1�������ȼ�0 */
    HAL_NVIC_EnableIRQ(KEY1_INT_IRQn);                       /* ʹ���ж���3 */
    
    HAL_NVIC_SetPriority(KEY2_INT_IRQn, 2, 0);               /* ��ռ2�������ȼ�0 */
    HAL_NVIC_EnableIRQ(KEY2_INT_IRQn);                       /* ʹ���ж���2 */

    HAL_NVIC_SetPriority(WKUP_INT_IRQn, 3, 0);               /* ��ռ3�������ȼ�0 */
    HAL_NVIC_EnableIRQ(WKUP_INT_IRQn);                       /* ʹ���ж���0 */
}












