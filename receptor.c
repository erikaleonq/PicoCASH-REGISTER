/**
 * @file receptor.c
 * @brief Funciones para el manejo de un receptor UART y operaciones relacionadas con la memoria EEPROM e I2C.
 */

#include "receptor.h"

char received_message[5];        /**< Almacena los caracteres recibidos por UART. */
int received_message_length = 0; /**< Longitud del mensaje recibido por UART. */
uint16_t converted_value = 0;    /**< Valor convertido del mensaje recibido. */
bool tag_detected = false;       /**< Indica si se ha detectado una etiqueta mediante el receptor UART. */
uint16_t cuenta = 0;             /**< Cuenta acumulada de precios de productos. */
uint16_t precio = 0;             /**< Precio del producto actual. */
uint16_t new_cant = 0;           /**< Nueva cantidad de productos. */
int cant_products;               /**< Cantidad total de productos almacenados en la memoria EEPROM. */

/**
 * @brief Limpia el búfer de la UART.
 *
 * Esta función lee y descarta los caracteres presentes en el búfer de la UART.
 *
 * @param[in] uart Instancia de la UART.
 */

void clear_uart_buffer(uart_inst_t *uart)
{
    while (uart_is_readable(uart))
    {
        char c = uart_getc(uart);
    }
}
/**
 * @brief Inicializa la configuración de la UART.
 *
 * Esta función configura la UART con el baud rate especificado y establece el pin RX para la entrada UART.
 */
void init_uart()
{
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);
}
/**
 * @brief Recibe una etiqueta mediante la UART y convierte el valor a un formato utilizable.
 *
 * Esta función lee caracteres de la UART hasta que se completa una etiqueta. Luego, convierte el valor a un formato utilizable.
 */
void recive_tag()
{

    if (uart_is_readable(UART_ID))
    {
        char received_char = uart_getc(UART_ID);
        sleep_ms(1);

        received_message[received_message_length] = received_char;
        received_message[received_message_length + 1] = '\0';
        received_message_length++;
    }
    else if (received_message_length > 0)
    {
        converted_value = atof(received_message);
        received_message[0] = '\0'; // Reiniciar el mensaje
        received_message_length = 0;
        tag_detected = true;
    }
}
/**
 * @brief Verifica si un producto ya existe y realiza operaciones correspondientes.
 *
 * Esta función verifica si un producto ya existe en la memoria EEPROM y realiza las operaciones correspondientes, como decrementar la cantidad y actualizar el precio acumulado.
 */
void product_exist()
{
    bool tag_exists = false;
    recive_tag();
    recive_tag();

    uint16_t id;
    id = converted_value;
    cant_products = read_position(EEPROM_ADDR, 4000);

    if (tag_detected)
    {
        // Detecta si el tag se encuentra
        printf("Aquiii %li\n", cant_products);
        for (int i = 0; i < cant_products; i++)
        {
            DatosFlotantes datosLeidos = i2c_read_struct(EEPROM_ADDR, i);

            // Revisa si el tag existe en memoria
            if (datosLeidos.valor1 == converted_value)
            {
                printf("ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);
                // Asegura que se elimine un producto del inventario
                if (datosLeidos.valor3 > 0)
                {
                    DatosFlotantes misDatos;
                    misDatos.valor1 = datosLeidos.valor1;
                    misDatos.valor2 = datosLeidos.valor2;
                    misDatos.valor3 = datosLeidos.valor3 - 1;
                    i2c_write_struct(EEPROM_ADDR, misDatos, i);

                    precio = datosLeidos.valor2;
                    cuenta += precio;
                    displayProd(datosLeidos.valor1, datosLeidos.valor2);
                    ChgLine();
                    WriteStr("TOTAL: $", 8);
                    WriteInt(cuenta * 100);
                }
                else
                {

                    writeInfo("SIN EXISTENCIAS", 15, "  DEL PRODUCTO", 14);
                }
                tag_exists = true;
                break;
            }
            else
            {
                tag_exists = false;
            }
        }
        // Asegura que no existe el producto
        if (!tag_exists && id != 0)
        {
            writeInfo("    PRODUCTO", 12, "  DESCONOCIDO", 13);
            ;
        }
        tag_detected = false;
    }
}

/**
 * @brief Verifica si un nuevo producto será añadido y realiza operaciones correspondientes.
 *
 * Esta función verifica si un nuevo producto será añadido a la memoria EEPROM y realiza las operaciones correspondientes, como solicitar al usuario ingresar el precio y la cantidad.
 *
 * @return Devuelve `true` si se ha añadido un nuevo producto, de lo contrario, devuelve `false`.
 */
bool new_product()
{
    recive_tag();
    recive_tag();
    recive_tag();
    tag_detected = false;
    printf("Acerque tag\n");

    char key, key2, precio[10] = "\0", cant[6] = "\0";
    bool *newKey, *newKey2, keyIsNum;
    int countp = 0, countCant = 0;

    while (!tag_detected)
    {
        recive_tag();
    }

    bool tag_exists = false;
    cant_products = read_position(EEPROM_ADDR, 4000);
    // Dtecta que el tag este leyendose
    if (tag_detected)
    {
        for (int i = 0; i < cant_products; i++)
        {
            DatosFlotantes datosLeidos = i2c_read_struct(EEPROM_ADDR, i);
            if (datosLeidos.valor1 == converted_value)
            {
                // Se ingresa el la cantidad de objetos a agegar al inventario
                printf("Ingrese cantidad de productos a agrgar: ");
                writeInfo(" MODIFICAR CANT", 15, " EN INVENTARIO", 14);

                while (key != 'A' && countCant < 4)
                {
                    newKey = newKeyPressed();
                    sleep_us(5);
                    key = *newKey ? getKey() : 'p';
                    keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

                    if (*newKey)
                    {
                        if (keyIsNum)
                        {
                            concatenarCaracter(key, cant, "Cnt:", &countCant);
                        }
                        else if (key == 'A')
                        {
                            writeInfo("    CANTIDAD", 12, "   INGRESADA", 12);
                            *newKey = false;
                            printf("Fin cantidad \n");
                            countCant = 4;
                            break;
                        }
                    }
                    *newKey = false;
                }
                // Imprime el estado actualizado del producto
                printf("ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);

                DatosFlotantes misDatos;
                misDatos.valor1 = datosLeidos.valor1;
                misDatos.valor2 = datosLeidos.valor2;
                misDatos.valor3 = atoi(cant) + datosLeidos.valor3;
                i2c_write_struct(EEPROM_ADDR, misDatos, i);

                tag_exists = true;
                return true;
            }
            else
            {
                tag_exists = false;
            }
        }
        // Se detecta nuevo producto y se agregan los precios y ademas la catidad en el nventario
        if (!tag_exists)
        {

            printf("Agregar nuevo producto..... \n");

            printf("Agregar precio..... \n");
            writeInfo("    INGRESE", 11, "     PRECIO", 11);

            while (key != 'A' && countp < 6)
            {
                newKey2 = newKeyPressed();
                sleep_us(5);
                key2 = *newKey2 ? getKey() : 'p';
                keyIsNum = ((int)key2 >= 48 && (int)key2 <= 57) ? 1 : 0;

                if (*newKey2)
                {
                    printf("%c   \n", key2);
                    if (keyIsNum)
                    {
                        concatenarCaracter(key2, precio, "$:  ", &countp);
                    }
                    else if (key2 == 'A')
                    {
                        *newKey2 = false;
                        countp = 6;
                        printf("Fin precio \n");
                        break;
                    }
                }
                *newKey2 = false;
            }
            writeInfo("    INGRESE", 11, "    CANTIDAD", 12);

            while (key != 'A' && countCant < 4)
            {
                newKey = newKeyPressed();
                sleep_us(5);
                key = *newKey ? getKey() : 'p';
                keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

                if (*newKey)
                {
                    printf("%c   \n", key);
                    if (keyIsNum)
                    {
                        concatenarCaracter(key, cant, "Cnt:", &countCant);
                    }
                    else if (key == 'A')
                    {
                        writeInfo("    PRODUCTO", 12, "   INGRESADO", 12);
                        *newKey = false;
                        printf("Fin cantidad \n");
                        countCant = 4;
                        break;
                    }
                }
                *newKey = false;
            }

            printf("precio %i,    cantidad   %i \n", atoi(precio), atoi(cant));
            printf("id  %i \n", converted_value);

            DatosFlotantes misDatos;
            misDatos.valor1 = converted_value;
            misDatos.valor2 = atoi(precio) / 100;
            misDatos.valor3 = atoi(cant);
            i2c_write_struct(EEPROM_ADDR, misDatos, cant_products++);
            write_Position(cant_products, 4000);
            return true;
        }
    }
    tag_detected = false;

    return false;
}
/**
 * @brief Reinicia la cuenta acumulada de precios.
 *
 * Esta función reinicia la variable `cuenta` que almacena la suma acumulada de precios de productos.
 */
void reiniciarCuenta()
{
    cuenta = 0;
}
/**
 * @brief Obtiene el puntero a la cuenta acumulada de precios.
 *
 * @return Puntero a la variable `cuenta`.
 */
uint16_t *getCuenta()
{
    return &cuenta;
}
/**
 * @brief Obtiene el precio del producto actual.
 *
 * @return Valor del precio del producto.
 */
uint16_t getPrecio()
{
    return precio;
}