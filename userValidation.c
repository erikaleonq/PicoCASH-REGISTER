/**
 * @file userValidation.c
 * @brief Funciones relacionadas con la validación de usuarios y contraseñas.
 */

// Se incluyen .h necesarios para el funcionamiento.
#include "userValidation.h"
#include "Data.h"
#include "LCD.h"

char user[LENUSER] = "", password[LENPWD] = ""; /**< Almacena temporalmente el ID del usuario ingresado. */ /**< Almacena temporalmente la contraseña ingresada. */
int count_u = 0, count_p = 0; /**< Contador para el ID del usuario. */                                      /**< Contador para la contraseña. */
bool inputUser = true;                                                                                      /**< Indica si se está ingresando el ID del usuario o la contraseña. */

/**
 * @brief Concatena un carácter a una cadena y muestra el progreso en la pantalla LCD.
 *
 * @param[in] key Carácter a concatenar.
 * @param[in,out] cadena Cadena a la que se le añadirá el carácter.
 * @param[in] tipo Tipo de cadena (ID o PSW).
 * @param[in,out] count Contador de caracteres en la cadena.
 */

void concatenarCaracter(char key, char *cadena, char *tipo, int *count)
{
    // Incrementa el contador de caracteres en 1
    *count += 1;
    // Obtiene la longitud actual de la cadena
    int len = strlen(cadena);
    // Agrega el carácter 'key' al final de la cadena
    cadena[len] = key;
    // Añade un carácter nulo para asegurarse de que la cadena esté terminada correctamente
    cadena[len + 1] = '\0';
    // printf("\n\n\n\n\n\n\n\n\n\n\n");
    //  Imprime un mensaje de depuración que muestra el tipo de datos y la cadena resultante
    printf("%s: %s\n", tipo, cadena);
    ClearScreen();
    WriteStr(tipo, 4);
    WriteStr(cadena, len + 1);
}

/**
 * @brief Verifica la validez del usuario y la contraseña ingresados.
 *
 * @param[out] isAdmin Puntero a una variable que indicará si el usuario es administrador.
 * @return true si el usuario y la contraseña son válidos, false de lo contrario.
 */

int confirmUser(bool *isAdmin)
{
    for (int i = 0; i < NUMADMINS; i++)
    {
        int resultado = strncmp(usersData[i][0], user, LENUSER); // Si las cadenas son iguales resultado = 0
        if (resultado == 0 && strlen(password) == LENPWD)
        { // verificamos usuario
            resultado = strncmp(usersData[i][1], password, LENPWD);
            if (resultado == 0)
            { // verificamos contraseña
                *isAdmin = usersData[i][2] == "1";
                printf("Usuario y contraseña correctos \n");
                inputUser = true;
                resetValidation();
                return true;
            }
        }
    }
    printf("Usuario o contraseña incorrectos \n");
    writeInfo("    ID o PSW", 12, "   INCORRECTO", 13);
    inputUser = true;
    resetValidation();
    return 0;
}

/**
 * @brief Reinicia las variables de validación de usuario.
 */

void resetValidation()
{
    strcpy(user, "");
    strcpy(password, "");
    count_p = 0;
    count_u = 0;
    inputUser = true;
}

/**
 * @brief Verifica y almacena los caracteres ingresados como ID de usuario y contraseña.
 *
 * @param[in] key Carácter ingresado por el usuario.
 * @param[out] isAdmin Puntero a una variable que indicará si el usuario es administrador.
 * @return false.
 */

bool isValidUser(char key, bool *isAdmin)
{
    if (inputUser)
    {
        concatenarCaracter(key, user, "ID :", &count_u);

        if (count_u == LENUSER)
        {
            inputUser = false;
            printf("Termina usuario \n");
            ClearScreen();
            WriteStr("PSW:", 4);
        }
    }
    else if (!inputUser)
    {
        concatenarCaracter(key, password, "PSW:", &count_p);
    }
    return false;
}