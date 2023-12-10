#ifndef _RECEPTOR_H_
#define _RECEPTOR_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart0
#define BAUD_RATE 1000000
#define RX_PIN 17

void clear_uart_buffer(uart_inst_t *uart);
void init_uart();
void recive_tag();


#endif