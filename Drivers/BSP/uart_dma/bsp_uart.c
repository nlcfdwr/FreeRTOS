
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

void bsp_uart1_dmatx_config(uint8_t *mem_addr, uint32_t mem_size)//配置 USART1 的 DMA 发送通道,将准备好的数据从内存通过DMA传输到USART1的发送数据寄存器
{
    LL_DMA_DisableStream(DMA2, LL_DMA_STREAM_7);//禁用USART1_TX对应的DMA通道(DMA2 的 Stream 7)，
    LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_7, LL_DMA_CHANNEL_4);//设置这个 Stream 使用哪个 Channel
    LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_7, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);//设置传输方向为从内存传输到外设
    LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_7, LL_DMA_PRIORITY_LOW);//设置为低优先级
    LL_DMA_SetMode(DMA2, LL_DMA_STREAM_7, LL_DMA_MODE_NORMAL);//设置传输模式为单次传输，传完自动停止
    LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_7, LL_DMA_PERIPH_NOINCREMENT);//设置外设地址不递增
    LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_7, LL_DMA_MEMORY_INCREMENT);//设置内存地址递增,表示每发完一个字节，从下一个内存地址读取下一个字节
    LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_7, LL_DMA_PDATAALIGN_BYTE);//设置数据宽度（按字节传输）
    LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_7, LL_DMA_MDATAALIGN_BYTE);//设置数据宽度（按字节传输）
    LL_DMA_DisableFifoMode(DMA2, LL_DMA_STREAM_7);//禁用 FIFO,直接从内存向寄存器传输
    LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_7, LL_USART_DMA_GetRegAddr(USART1));//将外设地址设为USART1的发送数据寄存器
    
    LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_7, (uint32_t)mem_addr);//设置内存起始地址
    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_7, mem_size);//设置数据长度（字节数），即发送多少字节
	
    //清除 DMA 状态标志位
    LL_DMA_ClearFlag_TC1(DMA2);
    LL_DMA_ClearFlag_HT1(DMA2);
    LL_DMA_ClearFlag_TE1(DMA2);
    LL_DMA_ClearFlag_DME1(DMA2);
    LL_DMA_ClearFlag_FE1(DMA2);
        
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_7);//启用传输完成中断
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_7);//启用DMA传输
}

void bsp_uart1_dmarx_config(uint8_t *mem_addr, uint32_t mem_size)//配置 DMA 用于 USART1 的接收（RX）功能,将串口收到的数据通过DMA自动存入内存
{
    LL_DMA_DeInit(DMA2, LL_DMA_STREAM_2);//重置 DMA2 Stream2 的寄存器配置
    LL_DMA_SetChannelSelection(DMA2, LL_DMA_STREAM_2, LL_DMA_CHANNEL_4);//设置这个 Stream 使用哪个 Channel
    LL_DMA_SetDataTransferDirection(DMA2, LL_DMA_STREAM_2, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);//设置传输方向为从外设传输到内存
    LL_DMA_SetStreamPriorityLevel(DMA2, LL_DMA_STREAM_2, LL_DMA_PRIORITY_LOW);//设置为低优先级
    LL_DMA_SetMode(DMA2, LL_DMA_STREAM_2, LL_DMA_MODE_CIRCULAR);//设置为循环模式,当接收缓冲区填满后，DMA 会从头开始重新覆盖，而不会停下来。
    LL_DMA_SetPeriphIncMode(DMA2, LL_DMA_STREAM_2, LL_DMA_PERIPH_NOINCREMENT);//设置外设地址不递增
    LL_DMA_SetMemoryIncMode(DMA2, LL_DMA_STREAM_2, LL_DMA_MEMORY_INCREMENT);//内存地址递增
    LL_DMA_SetPeriphSize(DMA2, LL_DMA_STREAM_2, LL_DMA_PDATAALIGN_BYTE);//设置数据宽度（按字节传输）
    LL_DMA_SetMemorySize(DMA2, LL_DMA_STREAM_2, LL_DMA_MDATAALIGN_BYTE);//设置数据宽度（按字节传输）
    LL_DMA_DisableFifoMode(DMA2, LL_DMA_STREAM_2);//不使用中间缓冲区
    LL_DMA_SetPeriphAddress(DMA2, LL_DMA_STREAM_2, LL_USART_DMA_GetRegAddr(USART1));//将外设地址设为USART1的发送数据寄存器
    LL_DMA_SetMemoryAddress(DMA2, LL_DMA_STREAM_2, (uint32_t)mem_addr);//设置内存起始地址,用于接收数据
    LL_DMA_SetDataLength(DMA2, LL_DMA_STREAM_2, mem_size);//设置 DMA 要接收的总字节数,在 循环模式下，DMA 会从头到尾填满 mem_size 字节，然后自动从头开始覆盖
    
    LL_DMA_EnableIT_HT(DMA2, LL_DMA_STREAM_2);//DMA 缓冲区填了一半时触发
    LL_DMA_EnableIT_TC(DMA2, LL_DMA_STREAM_2);//DMA 缓冲区全部填满时触发
    LL_DMA_EnableStream(DMA2, LL_DMA_STREAM_2);//开始 DMA 接收流程
}

uint16_t bsp_uart1_get_dmarx_buf_remain_size(void)
{
	return LL_DMA_GetDataLength(DMA2, LL_DMA_STREAM_2);	
}
