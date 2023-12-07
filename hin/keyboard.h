// Avoid duplication in code
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdio.h>
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include <math.h>

#define NUM_FILAS 5
#define NUM_COLUMNAS 4

// Write your definitions and other macros here
void keyboardCallback(uint num, uint32_t mask);
void pwmIRQ(void);
void initPWMasPIT(uint8_t slice, uint16_t milis, bool enable);
void initMatrixKeyboard5x4(void);
void initKeyboard();
bool *newKeyPressed();
char getKey();

#endif