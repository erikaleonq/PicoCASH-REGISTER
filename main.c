/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "keyboard.h"


#define NUM_FILAS 5
#define NUM_COLUMNAS 4
char lastKey;


int main() {
    stdio_init_all();

    // Dormir durante 5000 milisegundos (5 segundos) antes de iniciar
    sleep_ms(5000);
    // Imprimir un saludo después de la espera
    printf("¡Hola!");

    initKeyboard();

    while (1) {
        // Entrar en modo de espera hasta la próxima interrupción
        __wfi();
    }

    return 0;
}
