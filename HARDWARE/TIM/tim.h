#ifndef __TIM_H
#define __TIM_H
#include "stm32f4xx.h"
#include "sys.h"
void TIM3_Init(uint16_t arr, uint16_t psc);
void TIM4_Init(uint16_t arr, uint16_t psc);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
#endif
