///*
//    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
//    All rights reserved

//    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

//    This file is part of the FreeRTOS distribution.

//    FreeRTOS is free software; you can redistribute it and/or modify it under
//    the terms of the GNU General Public License (version 2) as published by the
//    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

//    ***************************************************************************
//    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
//    >>!   distribute a combined work that includes FreeRTOS without being   !<<
//    >>!   obliged to provide the source code for proprietary components     !<<
//    >>!   outside of the FreeRTOS kernel.                                   !<<
//    ***************************************************************************

//    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
//    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
//    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
//    link: http://www.freertos.org/a00114.html

//    ***************************************************************************
//     *                                                                       *
//     *    FreeRTOS provides completely free yet professionally developed,    *
//     *    robust, strictly quality controlled, supported, and cross          *
//     *    platform software that is more than just the market leader, it     *
//     *    is the industry's de facto standard.                               *
//     *                                                                       *
//     *    Help yourself get started quickly while simultaneously helping     *
//     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
//     *    tutorial book, reference manual, or both:                          *
//     *    http://www.FreeRTOS.org/Documentation                              *
//     *                                                                       *
//    ***************************************************************************

//    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
//    the FAQ page "My application does not run, what could be wrong?".  Have you
//    defined configASSERT()?

//    http://www.FreeRTOS.org/support - In return for receiving this top quality
//    embedded software for free we request you assist our global community by
//    participating in the support forum.

//    http://www.FreeRTOS.org/training - Investing in training allows your team to
//    be as productive as possible as early as possible.  Now you can receive
//    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
//    Ltd, and the world's leading authority on the world's leading RTOS.

//    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
//    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
//    compatible FAT file system, and our tiny thread aware UDP/IP stack.

//    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
//    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

//    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
//    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
//    licenses offer ticketed support, indemnification and commercial middleware.

//    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
//    engineered and independently SIL3 certified version for use in safety and
//    mission critical applications that require provable dependability.

//    1 tab == 4 spaces!
//*/

//#ifndef FREERTOS_CONFIG_H
//#define FREERTOS_CONFIG_H

//#include "stm32f4xx_hal.h"

///*-----------------------------------------------------------
// * Application specific definitions.
// *
// * These definitions should be adjusted for your particular hardware and
// * application requirements.
// *
// * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
// * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE. 
// *
// * See http://www.freertos.org/a00110.html.
// *----------------------------------------------------------*/

//#define configUSE_PREEMPTION		1
//#define configUSE_IDLE_HOOK			0
//#define configUSE_TICK_HOOK			0
//#define configCPU_CLOCK_HZ			( ( unsigned long ) 72000000 )	
//#define configTICK_RATE_HZ			( ( TickType_t ) 1000 )
//#define configMAX_PRIORITIES		( 5 )
//#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 128 )
//#define configTOTAL_HEAP_SIZE		( ( size_t ) ( 17 * 1024 ) )
//#define configMAX_TASK_NAME_LEN		( 16 )
//#define configUSE_TRACE_FACILITY	0
//#define configUSE_16_BIT_TICKS		0
//#define configIDLE_SHOULD_YIELD		1

///* Co-routine definitions. */
//#define configUSE_CO_ROUTINES 		0
//#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

///* Set the following definitions to 1 to include the API function, or zero
//to exclude the API function. */

//#define INCLUDE_vTaskPrioritySet		1
//#define INCLUDE_uxTaskPriorityGet		1
//#define INCLUDE_vTaskDelete				1
//#define INCLUDE_vTaskCleanUpResources	0
//#define INCLUDE_vTaskSuspend			1
//#define INCLUDE_vTaskDelayUntil			1
//#define INCLUDE_vTaskDelay				1

///* This is the raw value as per the Cortex-M3 NVIC.  Values can be 255
//(lowest) to 0 (1?) (highest). */
//#define configKERNEL_INTERRUPT_PRIORITY 		255
///* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
//See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
//#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	191 /* equivalent to 0xb0, or priority 11. */


///* This is the value being used as per the ST library which permits 16
//priority values, 0 to 15.  This must correspond to the
//configKERNEL_INTERRUPT_PRIORITY setting.  Here 15 corresponds to the lowest
//NVIC value of 255. */
//#define configLIBRARY_KERNEL_INTERRUPT_PRIORITY	15

//#endif /* FREERTOS_CONFIG_H */






























#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* ͷ�ļ� */
#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include <stdint.h>

extern uint32_t SystemCoreClock;

/* ���������� */
#define configUSE_PREEMPTION                            1                       /* 1: ��ռʽ������, 0: Э��ʽ������, ��Ĭ���趨�� */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION         1                       /* 1: ʹ��Ӳ��������һ��Ҫ���е�����, 0: ʹ������㷨������һ��Ҫ���е�����, Ĭ��: 0 */
#define configUSE_TICKLESS_IDLE                         0                       /* 1: ʹ��tickless�͹���ģʽ, Ĭ��: 0 */
#define configCPU_CLOCK_HZ                              SystemCoreClock         /* ����CPU��Ƶ, ��λ: Hz, ��Ĭ���趨�� */
//#define configSYSTICK_CLOCK_HZ                          (configCPU_CLOCK_HZ / 8)/* ����SysTickʱ��Ƶ�ʣ���SysTickʱ��Ƶ�����ں�ʱ��Ƶ�ʲ�ͬʱ�ſ��Զ���, ��λ: Hz, Ĭ��: ������ */
#define configTICK_RATE_HZ                              1000                    /* ����ϵͳʱ�ӽ���Ƶ��, ��λ: Hz, ��Ĭ���趨�� */
#define configMAX_PRIORITIES                            32                      /* ����������ȼ���, ������ȼ�=configMAX_PRIORITIES-1, ��Ĭ���趨�� */
#define configMINIMAL_STACK_SIZE                        128                     /* ������������ջ�ռ��С, ��λ: Word, ��Ĭ���趨�� */
#define configMAX_TASK_NAME_LEN                         16                      /* ��������������ַ���, Ĭ��: 16 */
#define configUSE_16_BIT_TICKS                          0                       /* 1: ����ϵͳʱ�ӽ��ļ���������������Ϊ16λ�޷�����, ��Ĭ���趨�� */
#define configIDLE_SHOULD_YIELD                         1                       /* 1: ʹ������ռʽ������,ͬ���ȼ�����������ռ��������, Ĭ��: 1 */
#define configUSE_TASK_NOTIFICATIONS                    1                       /* 1: ʹ�������ֱ�ӵ���Ϣ����,�����ź������¼���־�����Ϣ����, Ĭ��: 1 */
#define configTASK_NOTIFICATION_ARRAY_ENTRIES           1                       /* ��������֪ͨ����Ĵ�С, Ĭ��: 1 */
#define configUSE_MUTEXES                               1                       /* 1: ʹ�ܻ����ź���, Ĭ��: 0 */
#define configUSE_RECURSIVE_MUTEXES                     1                       /* 1: ʹ�ܵݹ黥���ź���, Ĭ��: 0 */
#define configUSE_COUNTING_SEMAPHORES                   1                       /* 1: ʹ�ܼ����ź���, Ĭ��: 0 */
#define configUSE_ALTERNATIVE_API                       0                       /* ������!!! */
#define configQUEUE_REGISTRY_SIZE                       8                       /* �������ע����ź�������Ϣ���еĸ���, Ĭ��: 0 */
#define configUSE_QUEUE_SETS                            1                       /* 1: ʹ�ܶ��м�, Ĭ��: 0 */
#define configUSE_TIME_SLICING                          1                       /* 1: ʹ��ʱ��Ƭ����, Ĭ��: 1 */
#define configUSE_NEWLIB_REENTRANT                      0                       /* 1: ���񴴽�ʱ����Newlib������ṹ��, Ĭ��: 0 */
#define configENABLE_BACKWARD_COMPATIBILITY             0                       /* 1: ʹ�ܼ����ϰ汾, Ĭ��: 1 */
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS         0                       /* �����̱߳��ش洢ָ��ĸ���, Ĭ��: 0 */
#define configSTACK_DEPTH_TYPE                          uint16_t                /* ���������ջ��ȵ���������, Ĭ��: uint16_t */
#define configMESSAGE_BUFFER_LENGTH_TYPE                size_t                  /* ������Ϣ����������Ϣ���ȵ���������, Ĭ��: size_t */

/* �ڴ������ض��� */
#define configSUPPORT_STATIC_ALLOCATION                 0                       /* 1: ֧�־�̬�����ڴ�, Ĭ��: 0 */
#define configSUPPORT_DYNAMIC_ALLOCATION                1                       /* 1: ֧�ֶ�̬�����ڴ�, Ĭ��: 1 */
#define configTOTAL_HEAP_SIZE                           ((size_t)(10 * 1024))   /* FreeRTOS���п��õ�RAM����, ��λ: Byte, ��Ĭ���趨�� */
#define configAPPLICATION_ALLOCATED_HEAP                0                       /* 1: �û��ֶ�����FreeRTOS�ڴ��(ucHeap), Ĭ��: 0 */
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP       0                       /* 1: �û�����ʵ�����񴴽�ʱʹ�õ��ڴ��������ͷź���, Ĭ��: 0 */

/* ���Ӻ�����ض��� */
#define configUSE_IDLE_HOOK                             0                       /* 1: ʹ�ܿ��������Ӻ���, ��Ĭ���趨��  */
#define configUSE_TICK_HOOK                             0                       /* 1: ʹ��ϵͳʱ�ӽ����жϹ��Ӻ���, ��Ĭ���趨�� */
#define configCHECK_FOR_STACK_OVERFLOW                  0                       /* 1: ʹ��ջ�����ⷽ��1, 2: ʹ��ջ�����ⷽ��2, Ĭ��: 0 */
#define configUSE_MALLOC_FAILED_HOOK                    0                       /* 1: ʹ�ܶ�̬�ڴ�����ʧ�ܹ��Ӻ���, Ĭ��: 0 */
#define configUSE_DAEMON_TASK_STARTUP_HOOK              0                       /* 1: ʹ�ܶ�ʱ�����������״�ִ��ǰ�Ĺ��Ӻ���, Ĭ��: 0 */

/* ����ʱ�������״̬ͳ����ض��� */
#define configGENERATE_RUN_TIME_STATS                   0                       /* 1: ʹ����������ʱ��ͳ�ƹ���, Ĭ��: 0 */
#if configGENERATE_RUN_TIME_STATS
#include "./BSP/TIMER/btim.h"
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()        ConfigureTimeForRunTimeStats()
extern uint32_t FreeRTOSRunTimeTicks;
#define portGET_RUN_TIME_COUNTER_VALUE()                FreeRTOSRunTimeTicks
#endif
#define configUSE_TRACE_FACILITY                        1                       /* 1: ʹ�ܿ��ӻ����ٵ���, Ĭ��: 0 */
#define configUSE_STATS_FORMATTING_FUNCTIONS            1                       /* 1: configUSE_TRACE_FACILITYΪ1ʱ�������vTaskList()��vTaskGetRunTimeStats()����, Ĭ��: 0 */

/* Э����ض��� */
#define configUSE_CO_ROUTINES                           0                       /* 1: ����Э��, Ĭ��: 0 */
#define configMAX_CO_ROUTINE_PRIORITIES                 2                       /* ����Э�̵�������ȼ�, ������ȼ�=configMAX_CO_ROUTINE_PRIORITIES-1, ��Ĭ��configUSE_CO_ROUTINESΪ1ʱ�趨�� */

/* �����ʱ����ض��� */
#define configUSE_TIMERS                                1                               /* 1: ʹ�������ʱ��, Ĭ��: 0 */
#define configTIMER_TASK_PRIORITY                       ( configMAX_PRIORITIES - 1 )    /* ���������ʱ����������ȼ�, ��Ĭ��configUSE_TIMERSΪ1ʱ�趨�� */
#define configTIMER_QUEUE_LENGTH                        5                               /* ���������ʱ��������еĳ���, ��Ĭ��configUSE_TIMERSΪ1ʱ�趨�� */
#define configTIMER_TASK_STACK_DEPTH                    ( configMINIMAL_STACK_SIZE * 2) /* ���������ʱ�������ջ�ռ��С, ��Ĭ��configUSE_TIMERSΪ1ʱ�趨�� */

/* ��ѡ����, 1: ʹ�� */
#define INCLUDE_vTaskPrioritySet                        1                       /* �����������ȼ� */
#define INCLUDE_uxTaskPriorityGet                       1                       /* ��ȡ�������ȼ� */
#define INCLUDE_vTaskDelete                             1                       /* ɾ������ */
#define INCLUDE_vTaskSuspend                            1                       /* �������� */
#define INCLUDE_xResumeFromISR                          1                       /* �ָ����ж��й�������� */
#define INCLUDE_vTaskDelayUntil                         1                       /* ���������ʱ */
#define INCLUDE_vTaskDelay                              1                       /* ������ʱ */
#define INCLUDE_xTaskGetSchedulerState                  1                       /* ��ȡ���������״̬ */
#define INCLUDE_xTaskGetCurrentTaskHandle               1                       /* ��ȡ��ǰ����������� */
#define INCLUDE_uxTaskGetStackHighWaterMark             1                       /* ��ȡ�����ջ��ʷʣ����Сֵ */
#define INCLUDE_xTaskGetIdleTaskHandle                  1                       /* ��ȡ��������������� */
#define INCLUDE_eTaskGetState                           1                       /* ��ȡ����״̬ */
#define INCLUDE_xEventGroupSetBitFromISR                1                       /* ���ж��������¼���־λ */
#define INCLUDE_xTimerPendFunctionCall                  1                       /* ��������ִ�йҵ���ʱ���������� */
#define INCLUDE_xTaskAbortDelay                         1                       /* �ж�������ʱ */
#define INCLUDE_xTaskGetHandle                          1                       /* ͨ����������ȡ������ */
#define INCLUDE_xTaskResumeFromISR                      1                       /* �ָ����ж��й�������� */

/* �ж�Ƕ����Ϊ���� */
#ifdef __NVIC_PRIO_BITS
    #define configPRIO_BITS __NVIC_PRIO_BITS
#else
    #define configPRIO_BITS 4
#endif

#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15                  /* �ж�������ȼ� */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5                   /* FreeRTOS�ɹ��������ж����ȼ� */
#define configKERNEL_INTERRUPT_PRIORITY                 ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_API_CALL_INTERRUPT_PRIORITY           configMAX_SYSCALL_INTERRUPT_PRIORITY

/* FreeRTOS�жϷ�������ض��� */
#define xPortPendSVHandler                              PendSV_Handler
#define vPortSVCHandler                                 SVC_Handler

/* ���� */
#define vAssertCalled(char, int) printf("Error: %s, %d\r\n", char, int)
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )

/* FreeRTOS MPU ���ⶨ�� */
//#define configINCLUDE_APPLICATION_DEFINED_PRIVILEGED_FUNCTIONS 0
//#define configTOTAL_MPU_REGIONS                                8
//#define configTEX_S_C_B_FLASH                                  0x07UL
//#define configTEX_S_C_B_SRAM                                   0x07UL
//#define configENFORCE_SYSTEM_CALLS_FROM_KERNEL_ONLY            1
//#define configALLOW_UNPRIVILEGED_CRITICAL_SECTIONS             1

/* ARMv8-M ��ȫ��˿���ض��塣 */
//#define secureconfigMAX_SECURE_CONTEXTS         5

#endif /* FREERTOS_CONFIG_H */
