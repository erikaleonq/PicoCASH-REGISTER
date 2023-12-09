#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#define UART_ID uart1
#define BAUD_RATE 1000000
#define RX_PIN 5

void clear_uart_buffer(uart_inst_t *uart) {
    while (uart_is_readable(uart)) {
        char c = uart_getc(uart);
    }
}

int main() {
    stdio_init_all();

    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

    char received_message[256];
    int received_message_length = 0;

    while (1) {
        if (uart_is_readable(UART_ID)) {
            char received_char = uart_getc(UART_ID);
            sleep_ms(1);

            received_message[received_message_length] = received_char;
            received_message[received_message_length + 1] = '\0';
            received_message_length++;
           
        } else if( received_message_length > 0)
        {
            printf("Mensaje recibido: %s\n", received_message);
                received_message[0] = '\0';  // Reiniciar el mensaje
                received_message_length = 0;
        }
    }

    return 0;
}
