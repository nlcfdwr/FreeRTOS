#ifndef __DHT11_H
#define __DHT11_H

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "FreeRTOS.h"
#include "task.h"


void DHT_GPIO_SET_OUTPUT(void);
void DHT_GPIO_SET_INPUT(void);
uint8_t DHT_Read_Byte(void);
uint8_t DHT_Read(void);

#endif
