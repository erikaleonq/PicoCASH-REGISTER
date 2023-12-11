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
    init_i2c();
    LCDInit();
    LCDconfig();

    char key;
    bool *newKey;
    bool isUser = false, isAdmin, printMenu = true, keyIsNum;    

    printf("Bienvenido a picoCA$H");

    while (1) {
        newKey = newKeyPressed();
        if(*newKey || isUser) {
            key =  *newKey ? getKey() : 'p';
            keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

            if(key == 'F' && isUser) {
                //FINALIZAR SESION
                writeInfo("     SESION", 11, "   FINALIZADA", 13);
                resetValidation();
                isUser = false;
                printMenu = true;
                *newKey = false;
            }

            if(!isUser && keyIsNum) {
                isValidUser(key, &isAdmin);
                *newKey = false;
            } else if (!isUser && key == 'E') {
                writeInfo("   REPITA SUS", 13, "  CREDENCIALES", 14);
                resetValidation();
                *newKey = false;
            } else if (!isUser && key == 'A') {
                //printf("Ent ACEPTAR")
                isUser = confirmUser(&isAdmin);
                ChgLine();
                WriteStr("ENT para Aceptar.", 16);
                *newKey = false;
            }

            if(isAdmin && isUser) {
                if(printMenu == true) {
                    writeInfo("** BIENVENIDO **", 16, "*ADMINISTRADOR* ", 16);
                    printf("Es admin\n"); //BIENVENIDO ADMINISTRADOR
                    printMenu = false;
                }

                if(*newKey && keyIsNum) {
                    
                }

            } else if (isUser){ //Vendedor
                if(printMenu == true) {
                    writeInfo("** BIENVENIDO **", 16, "  * VENDEDOR *", 14);
                    printf("Es vendedor\n");
                    printMenu = false;
                }
                if(*newKey) {
                    switch (key)
                    {
                    case 'f':
                        writeInfo("     LECTOR", 11, "    ACTIVADO", 12);
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
