#include "userValidation.h"
#include "Data.h"

char user[LENUSER] = "", password[LENPWD] = "";
int count_u = 0, count_p = 0;
bool inputUser = true;

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

int confirmUser (bool *isAdmin){ 
    for(int i=0 ; i<NUMADMINS ; i++){
        int resultado = strncmp(usersData[i][0], user, LENUSER); //Si las cadenas son iguales resultado = 0
        if (resultado == 0 && strlen(password) == LENPWD) {  // verificamos usuario
            resultado = strncmp(usersData[i][1], password, LENPWD);
            if (resultado == 0) {  // verificamos contraseña
                *isAdmin = (bool)usersData[i][2];
                printf("Usuario y contraseña correctos \n");
                inputUser = true;
                resetValidation();
                return true;
            }
        }
    }
    printf("Usuario o contraseña incorrectos \n");
    inputUser = true;
    resetValidation();
    return 0;
}

void resetValidation() {
    strcpy(user, "");	
    strcpy(password, "");
    count_p = 0;
    count_u = 0;
    inputUser = true;
}

bool isValidUser(char key, bool *isAdmin) {
    if(inputUser){
        concatenarCaracter(key, user, "ID", &count_u);
        if(count_u == LENUSER){
            inputUser = false;
            printf("Termina usuario \n");
        }
    }
    else if (!inputUser){
        concatenarCaracter(key, password, "PSW", &count_p);
    }
    return false;
}