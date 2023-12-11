/**
 * @file main.c
 * @brief Este es el archivo principal para una aplicación picoCA$H.
 *
 * Se inicializa y gestiona la funcionalidad principal de la aplicación picoCA$H,
 * sistema que involucra teclado, comunicación UART, comunicación I2C,
 * y una pantalla LCD. Admite sesiones de usuario y administrador, permitiendo la adición de productos,
 * el inicio de ventas y la entrada de documentos.
 */

#include "main.h" /**< Incluir el archivo de encabezado para declaraciones y definiciones. */

/**
 * * @brief Función principal del programa.
 * @return Devuelve 0 para indicar una ejecución exitosa del programa.
 */

int main()
{
    stdio_init_all(); /**< Inicializar la entrada/salida estándar para la comunicación. */
    initKeyboard();   /**< Inicializar el teclado para la entrada del usuario. */
    init_uart();      /**< Inicializar la comunicación UART. */
    init_i2c();       /**< Inicializar la comunicación I2C. */
    LCDInit();        /**< Inicializar la pantalla LCD. */
    LCDconfig();      /**< Configurar la pantalla LCD. */

    // Descomentar la siguiente línea para habilitar la escritura de una posición en la EEPROM.
    // write_Position(2, 4000);

    char key;                                                 /**< Variable para almacenar la tecla actual presionada. */
    bool *newKey;                                             /**< Puntero a una variable que indica si se ha presionado una nueva tecla. */
    bool isUser = false, isAdmin, printMenu = true, keyIsNum; /**< Banderas que indica si hay un usuario conectado,  si el usuario conectado es un administrador, y si imprimir el menú.. */

    printf("Bienvenido a picoCA$H"); /**< Mostrar un mensaje de bienvenida. */

    // Bucle principal de la aplicación.
    while (1)
    {
        newKey = newKeyPressed(); /**< Verificar si se ha presionado una nueva tecla. */
        if (*newKey || isUser)
        {
            key = *newKey ? getKey() : 'p';                        /**< Obtener la tecla presionada o usar un marcador de posición. */
            keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0; /**< Verificar si la tecla es un número (0-9).*/

            if (key == 'F' && isUser)
            {
                // FINALIZAR SESION
                writeInfo("     SESION", 11, "   FINALIZADA", 13);
                resetValidation();
                isUser = false;
                printMenu = true;
                *newKey = false;
            }

            if (!isUser && keyIsNum)
            {
                // Verificar si la tecla es un número y validar al usuario.
                isValidUser(key, &isAdmin);
                *newKey = false;
            }
            else if (!isUser && key == 'E')
            {
                // Mostrar un mensaje y restablecer la validación si se presiona 'E'.
                writeInfo("   REPITA SUS", 13, "  CREDENCIALES", 14);
                resetValidation();
                *newKey = false;
            }
            else if (!isUser && key == 'A')
            {
                // Confirmar al usuario y establecer la sesión de usuario.
                isUser = confirmUser(&isAdmin);
                *newKey = false;
            }

            if (isAdmin && isUser)
            {
                // Si el usuario es un administrador, mostrar las opciones del menú.
                if (printMenu == true)
                {
                    writeInfo("BIENVENIDO ADMIN", 16, "1: AGREGA PRODUC ", 16);
                    printf("Presione 1 para agregar productos\n"); // BIENVENIDO ADMINISTRADOR
                    printMenu = false;
                }

                if (*newKey && keyIsNum)
                {
                    // Si se presiona una nueva tecla y es un número, verificar acciones específicas.
                    if (key == '1')
                    {
                        writeInfo("     LECTOR", 11, "    ACTIVADO", 12);
                        *newKey = false;
                        // Si se agrega un nuevo producto, manejar el proceso.
                        if (!new_product())
                        {
                            printMenu = true;
                            *newKey = true;
                        }
                    }
                }
            }
            else if (isUser)
            { // Vendedor
                // Si el usuario no es un administrador (un vendedor), mostrar el menú específico del vendedor.
                if (printMenu == true)
                {
                    writeInfo("** BIENVENIDO **", 16, "  * VENDEDOR *", 14);
                    printf("Es vendedor\n");
                    printMenu = false;
                }
                if (*newKey)
                {
                    // Si se presiona una nueva tecla, verificar acciones específicas para los vendedores.
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
            *newKey = false; /**< Restablecer la bandera de nueva tecla. */
        }
        // Entrar en modo de espera hasta la próxima interrupción
        __wfi();
    }

    return 0; /**< Devolver 0 para indicar una ejecución exitosa del programa. */
}