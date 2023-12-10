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
    init_uart();

    char key;
    bool *newKey;
    bool isUser = false, isAdmin, printMenu = true, keyIsNum;    

    printf("Bienvenido a picoCA$H");

    while (1) {
        newKey = newKeyPressed();
        if(*newKey || isUser) {
            key =  *newKey ? getKey() : 'p';
            keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

            if(key == 'F') {
                printf("");
                resetValidation();
                isUser = false;
                printMenu = true;
                *newKey = false;
            }

            if(!isUser && keyIsNum) {
                isValidUser(key, &isAdmin);
                *newKey = false;
            } else if (!isUser && key == 'E') {
                resetValidation();
                *newKey = false;
            } else if (!isUser && key == 'A') {
                isUser = confirmUser(&isAdmin);
                *newKey = false;
            }

            if(isAdmin && isUser) {
                if(printMenu == true) {
                    printf("Es admin\n");
                    printMenu = false;
                }

                if(*newKey && keyIsNum) {
                    
                }

            } else if (isUser){ //Vendedor
                if(printMenu == true) {
                    printf("Es vendedor\n");
                    printMenu = false;
                }
                if(*newKey) {
                    switch (key)
                    {
                    case 'f':
                        iniciarVenta();
                        break;
                    case '#':
                        *newKey = false;
                        ingresarDocumento();
                        break;
                    
                    default:
                        break;
                    }
                }
            }
            *newKey = false;
        }
        // Entrar en modo de espera hasta la próxima interrupción
        __wfi();
    }

    return 0;
}
