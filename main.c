/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

#include "main.h"


int main() {
    stdio_init_all();
    initKeyboard();
    char key;
    bool *newKey;
    while (1) {
        newKey = newKeyPressed();
        if(*newKey) {
            key = getKey();
            printf("%c \n", key);
            *newKey = false;
        }
        // Entrar en modo de espera hasta la próxima interrupción
        __wfi();
    }

    return 0;
}
