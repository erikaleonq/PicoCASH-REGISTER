/**
 * @file salesMgent.c
 * @brief Funciones relacionadas con la gestión de ventas y operaciones asociadas a la venta de productos.
 */
#include "salesMgent.h"

int mult; /**< Variable que almacena la cantidad de productos a comprar. */

/**
 * @brief Inicia una nueva venta, permitiendo al usuario agregar o quitar productos de la cuenta.
 *
 * Esta función permite al usuario escanear etiquetas de productos para agregarlos a la cuenta de la venta. Además, permite modificar la cantidad de un producto en la cuenta o retirar un producto de la venta.
 */

void iniciarVenta()
{

    char key = 'n';         /**< Tecla presionada por el usuario. */
    bool *newKey, keyIsNum; /**< Punteros utilizados para verificar si se ha presionado una nueva tecla y si la tecla presionada es un número. */
    uint16_t *cuenta;       /**< Puntero a la variable que almacena la cuenta acumulada de la venta. */
    uint16_t precio;        /**< Precio del producto actual. */
    reiniciarCuenta();

    while (key != 'A')
    {
        newKey = newKeyPressed();
        keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

        if (*newKey)
        {
            key = getKey();
            if (key == '*')
            {
                printf("Seleccione cantidad: \n");
                writeInfo("    INGRESE", 11, "  CANTIDAD : ", 13);
                while (key != 'R')
                {
                    newKey = newKeyPressed();
                    key = *newKey ? getKey() : 'p';
                    keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;
                    mult = keyIsNum ? (int)key - 48 : mult;
                    if (keyIsNum)
                    {
                        WriteInt(mult);
                        *newKey = false;
                    }
                }

                cuenta = getCuenta();
                precio = getPrecio();
                printf("Se multiplica por %i\n", mult);

                *cuenta += precio * (mult - 1);
                mult = 1;
                printf("cuenta %li \n", *cuenta);

                displayProd(1, precio);
                ChgLine();
                WriteStr("TOTAL: $", 8);
                WriteInt(*cuenta * 100);
            }
            else if (key == 'L')
            {
                printf("Producto retirado de la cuenta\n");
                writeInfo("    PRODUCTO", 12, "    RETIRADO", 12);
                cuenta = getCuenta();
                precio = getPrecio();
                *cuenta -= precio;
            }
        }
        recive_tag();
        product_exist();
    }
    writeInfo("     VENTA", 10, "** FINALIZADA **", 16);

    printf("Compra finalizada");
}

/**
 * @brief Solicita al usuario ingresar el documento del cliente para iniciar una nueva venta.
 *
 * Esta función solicita al usuario ingresar el documento del cliente para iniciar una nueva venta. Luego, llama a la función `iniciarVenta` para gestionar la venta.
 */

void ingresarDocumento()
{

    printf("Ingrese documento del cliente: \n ");
    writeInfo("    INGRESE", 11, "   DOCUMENTO", 12);
    char key;
    bool *newKey, keyIsNum;
    char documento[10];
    int count = 0;

    while (key != 'A')
    {
        newKey = newKeyPressed();
        key = *newKey ? getKey() : 'p';
        keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

        if (*newKey && keyIsNum)
        {
            concatenarCaracter(key, documento, "DOC:", &count);
            *newKey = false;
        }
        else if (*newKey && key == 'A')
        {
            writeInfo("     LECTOR", 11, "    ACTIVADO", 12);
            printf("INCIA VENTA\n");
            *newKey = false;
        }
    }
    // TODO: Buscar usuario
    iniciarVenta();
}