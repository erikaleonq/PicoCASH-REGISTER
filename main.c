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
    LCDInit();
    LCDconfig();

    char key;
    bool *newKey;
    bool isUser = false, isAdmin;

    while (1) {
        newKey = newKeyPressed();
        if(*newKey) {
            key = getKey();
            if(!isUser) {
                isUser = isValidUser(key, &isAdmin);
            } else {
                if(isAdmin) {
                    printf("Es admin\n");
                }
            }
            //printf("%c \n", key);
            *newKey = false;
        }
        // Entrar en modo de espera hasta la próxima interrupción
        __wfi();
    }

    return 0;
}
