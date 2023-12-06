// Avoid duplication in code
#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include <math.h>

// Write your definitions and other macros here
void keyboardCallback(uint num, uint32_t mask);
void pwmIRQ(void);
void initPWMasPIT(uint8_t slice, uint16_t milis, bool enable);
void initMatrixKeyboard4x4(void);
void initKeyboard();

#endif