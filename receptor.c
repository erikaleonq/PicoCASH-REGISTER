#include "receptor.h"

char received_message[5];
int received_message_length = 0;

void clear_uart_buffer(uart_inst_t *uart) {
    while (uart_is_readable(uart)) {
        char c = uart_getc(uart);
    }
}

void init_uart(){
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);

}

void recive_tag(){
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
