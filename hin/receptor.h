#ifndef _RECEPTOR_H_
#define _RECEPTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/sync.h"
#include "memoria.h"
#include "LCD.h"
#include "keyboard.h"
#include "userValidation.h"

#define UART_ID uart0
#define BAUD_RATE 1000000
#define RX_PIN 17


void clear_uart_buffer(uart_inst_t *uart);
void init_uart();
void recive_tag();
void product_exist();
void reiniciarCuenta();
uint16_t *getCuenta();
uint16_t getPrecio();
bool new_product();

#endif