
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "./BSP/uart_dma/bsp_uart.h"

void uart1_dma_init(uint8_t *mem_addr, uint32_t mem_size)
{
    LL_USART_InitTypeDef UART_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA2);
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

    GPIO_InitStruct.Pin = LL_GPIO_PIN_9|LL_GPIO_PIN_10;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
    GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
    LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    bsp_uart1_dmarx_config(mem_addr, mem_size);
    
    NVIC_SetPriority(DMA2_Stream2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
    NVIC_EnableIRQ(DMA2_Stream2_IRQn);
    NVIC_SetPriority(DMA1_Stream7_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
    NVIC_EnableIRQ(DMA2_Stream7_IRQn);
    
    NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 6, 0));
    NVIC_EnableIRQ(USART1_IRQn);

    UART_InitStruct.BaudRate = 1000000;
    UART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
    UART_InitStruct.StopBits = LL_USART_STOPBITS_1;
    UART_InitStruct.Parity = LL_USART_PARITY_NONE;
    UART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
    UART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
    UART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
    LL_USART_Init(USART1, &UART_InitStruct);
    LL_USART_ConfigAsyncMode(USART1);
    
    LL_USART_EnableDMAReq_RX(USART1);
    LL_USART_EnableDMAReq_TX(USART1);
    LL_USART_EnableIT_IDLE(USART1);
    LL_USART_Enable(USART1);
}

void bsp_uart1_dmatx_config(uint8_t *mem_addr, uint32_t mem_size)//���� USART1 �� DMA ����ͨ��,��׼���õ����ݴ��ڴ�ͨ��DMA���䵽USART1�ķ������ݼĴ���
{
    LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_7);//����USART1_TX��Ӧ��DMAͨ��(DMA2 �� Stream 7)��
    LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_7, LL_DMA_CHANNEL_4);//������� Stream ʹ���ĸ� Channel
    LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_7, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);//���ô��䷽��Ϊ���ڴ洫�䵽����
    LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_7, LL_DMA_PRIORITY_LOW);//����Ϊ�����ȼ�
    LL_DMA_SetMode(DMA2, LL_DMA_STREAM_7, LL_DMA_MODE_NORMAL);//���ô���ģʽΪ���δ��䣬�����Զ�ֹͣ
    LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_7, LL_DMA_PERIPH_NOINCREMENT);//���������ַ������
    LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_7, LL_DMA_MEMORY_INCREMENT);//�����ڴ��ַ����,��ʾÿ����һ���ֽڣ�����һ���ڴ��ַ��ȡ��һ���ֽ�
    LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_7, LL_DMA_PDATAALIGN_BYTE);//�������ݿ�ȣ����ֽڴ��䣩
    LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_7, LL_DMA_MDATAALIGN_BYTE);//�������ݿ�ȣ����ֽڴ��䣩
    LL_DMA_DisableFifoMode(DMA2, LL_DMA_STREAM_7);//���� FIFO,ֱ�Ӵ��ڴ���Ĵ�������
    LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_7, LL_USART_DMA_GetRegAddr(USART1));//�������ַ��ΪUSART1�ķ������ݼĴ���
    
    LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_7, (uint32_t)mem_addr);//�����ڴ���ʼ��ַ
    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_7, mem_size);//�������ݳ��ȣ��ֽ������������Ͷ����ֽ�
	
    //��� DMA ״̬��־λ
    LL_DMA_ClearFlag_TC1(DMA2);
    LL_DMA_ClearFlag_HT1(DMA2);
    LL_DMA_ClearFlag_TE1(DMA2);
    LL_DMA_ClearFlag_DME1(DMA2);
    LL_DMA_ClearFlag_FE1(DMA2);
        
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_7);//���ô�������ж�
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_7);//����DMA����
}

void bsp_uart1_dmarx_config(uint8_t *mem_addr, uint32_t mem_size)//���� DMA ���� USART1 �Ľ��գ�RX������,�������յ�������ͨ��DMA�Զ������ڴ�
{
    LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);//���� DMA2 Stream2 �ļĴ�������
    LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_2, LL_DMA_CHANNEL_4);//������� Stream ʹ���ĸ� Channel
    LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_2, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);//���ô��䷽��Ϊ�����贫�䵽�ڴ�
    LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_2, LL_DMA_PRIORITY_LOW);//����Ϊ�����ȼ�
    LL_DMA_SetMode(DMA2, LL_DMA_STREAM_2, LL_DMA_MODE_CIRCULAR);//����Ϊѭ��ģʽ,�����ջ�����������DMA ���ͷ��ʼ���¸��ǣ�������ͣ������
    LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_2, LL_DMA_PERIPH_NOINCREMENT);//���������ַ������
    LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_2, LL_DMA_MEMORY_INCREMENT);//�ڴ��ַ����
    LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_2, LL_DMA_PDATAALIGN_BYTE);//�������ݿ�ȣ����ֽڴ��䣩
    LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_2, LL_DMA_MDATAALIGN_BYTE);//�������ݿ�ȣ����ֽڴ��䣩
    LL_DMA_DisableFifoMode(DMA2, LL_DMA_STREAM_2);//��ʹ���м仺����
    LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_2, LL_USART_DMA_GetRegAddr(USART1));//�������ַ��ΪUSART1�ķ������ݼĴ���
    LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_2, (uint32_t)mem_addr);//�����ڴ���ʼ��ַ,���ڽ�������
    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_2, mem_size);//���� DMA Ҫ���յ����ֽ���,�� ѭ��ģʽ�£�DMA ���ͷ��β���� mem_size �ֽڣ�Ȼ���Զ���ͷ��ʼ����
    
    LL_DMA_EnableIT_HT(DMA2, LL_DMA_STREAM_2);//DMA ����������һ��ʱ����
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_2);//DMA ������ȫ������ʱ����
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);//��ʼ DMA ��������
}

uint16_t bsp_uart1_get_dmarx_buf_remain_size(void)
{
	return LL_DMA_GetDataLength(DMA2, LL_DMA_STREAM_2);	
}
