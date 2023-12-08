/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

#include "main.h"


int main() {

    char user[LENUSER] = "", password[LENPWD] = "";
    int count_u = 0, count_p = 0;
    bool isUser = true;

    stdio_init_all();
    initKeyboard();
    char key;
    bool *newKey;
    while (1) {
        newKey = newKeyPressed();
        if(*newKey) {
            key = getKey();
            if(isUser == true){
                concatenarCaracter(key, user, "ID", &count_u);
                if(count_u == LENUSER){
                    isUser = false;
                    printf("Termina usuario \n");
                }
            }
            else if (isUser == false){
                concatenarCaracter(key, password, "PSW", &count_p);
                if(count_p == LENPWD){
                    if(confirmUser (user, password)){ //Usuario y contraseña correctos
                        printf("Usuario y contraseña correctos \n");
                        isUser = true;
                        reset(user, password, &count_p, &count_u);
                    }
                    else{
                        printf("Usuario o contraseña incorrectos \n");
                        isUser = true;
                        reset(user, password, &count_p, &count_u);
                    }
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
