#include "userValidation.h"

void concatenarCaracter(char key, char *cadena, char *tipo, int *count) {
    // Incrementa el contador de caracteres en 1
    *count += 1;
    // Obtiene la longitud actual de la cadena
    int len = strlen(cadena);
    // Agrega el carácter 'key' al final de la cadena
    cadena[len] = key;
    // Añade un carácter nulo para asegurarse de que la cadena esté terminada correctamente
    cadena[len + 1] = '\0';
    //printf("\n\n\n\n\n\n\n\n\n\n\n");
    // Imprime un mensaje de depuración que muestra el tipo de datos y la cadena resultante
    printf("%s: %s\n", tipo, cadena);
}

int confirmUser (char *user , char *password){    
    char *users[NUMADMINS][2] = {
        {"1182", "999991"},
        {"4155", "777775"},
        {"7456", "818181"},
        {"1111", "155858"},
        {"1991", "222222"},
        {"1855", "755222"},
        {"8269", "666666"},
        {"1999", "757575"},
        {"5548", "285858"},
        {"2566", "333332"}
    };

    for(int i=0 ; i<NUMADMINS ; i++){
        int resultado = strncmp(users[i][0], user, LENUSER); //Si las cadenas son iguales resultado = 0
        if (resultado == 0) {  // verificamos usuario
            resultado = strncmp(users[i][1], password, LENPWD);
            if (resultado == 0) {  // verificamos contraseña
                return 1;
            }
        }
    }
    return 0;
}

void reset(char* user, char* password, int* count_p, int* count_u) {
    strcpy(user, "");	
    strcpy(password, "");
    *count_p = 0;
    *count_u = 0;
}