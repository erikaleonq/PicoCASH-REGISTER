#include "receptor.h"

char received_message[5];
int received_message_length = 0;
uint16_t converted_value = 0;
bool tag_detected = false;
uint16_t cuenta = 0;
uint16_t precio = 0;
uint16_t new_cant = 0;
int cant_products;

void clear_uart_buffer(uart_inst_t *uart)
{
    while (uart_is_readable(uart))
    {
        char c = uart_getc(uart);
    }
}

void init_uart()
{
    uart_init(UART_ID, BAUD_RATE);
    gpio_set_function(RX_PIN, GPIO_FUNC_UART);
}

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

void product_exist() {
    bool tag_exists = false;
    cant_products = read_position(EEPROM_ADDR, 4000);

    if (tag_detected) {
        printf("Aquiii %li\n", cant_products);
        for (int i = 0; i < cant_products; i++)
        {
            DatosFlotantes datosLeidos = i2c_read_struct(EEPROM_ADDR, i);

            // printf("valor1: %f\n", datosLeidos.valor1);
            if (datosLeidos.valor1 == converted_value) {
                printf("ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);

                displayProd(datosLeidos.valor1, datosLeidos.valor2);

                if (datosLeidos.valor3 > 0)
                {

                    DatosFlotantes misDatos;
                    misDatos.valor1 = datosLeidos.valor1;
                    misDatos.valor2 = datosLeidos.valor2;
                    misDatos.valor3 = datosLeidos.valor3 - 1 ;
                    i2c_write_struct(EEPROM_ADDR, misDatos, i);
                    precio = datosLeidos.valor2;
                    cuenta += precio;
                }
                tag_exists = true;
                break;
            }
            else {
                tag_exists = false;
            }
        }
        if (!tag_exists) {
            printf("Este producto no existe!!!!!! \n");
        }
        tag_detected = false;
    }
}

bool new_product() {
    recive_tag();
    recive_tag();
    recive_tag();
    tag_detected = false;
    printf("Acerque tag\n");

    char key, key2, precio[10] = "\0", cant[6] = "\0";
    bool *newKey, *newKey2, keyIsNum;
    int countp = 0, countCant = 0;


    while(!tag_detected) {
        recive_tag();
    }

    bool tag_exists = false;
    cant_products = read_position(EEPROM_ADDR, 4000);

    if (tag_detected) {
        for (int i = 0; i < cant_products; i++) {
            DatosFlotantes datosLeidos = i2c_read_struct(EEPROM_ADDR, i);
            if (datosLeidos.valor1 == converted_value) {
                printf("Ingrese cantidad de productos a agrgar: ");
                writeInfo(" MODIFICAR CANT", 15," EN INVENTARIO", 14);

                while (key != 'A' && countCant < 4) {
                    newKey = newKeyPressed();
                    sleep_us(5);
                    key =  *newKey ? getKey() : 'p';
                    keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

                    if(*newKey) {
                        if (keyIsNum) {
                            concatenarCaracter(key, cant, "Cnt:", &countCant);
                        } else if (key == 'A'){
                            writeInfo("    CANTIDAD", 12,"   INGRESADA", 12);
                            *newKey = false;
                            printf("Fin cantidad \n");
                            countCant = 4;
                            break;
                        } 
                    }
                    *newKey = false;
                }

                printf("ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);                 

                    DatosFlotantes misDatos;
                    misDatos.valor1 = datosLeidos.valor1;
                    misDatos.valor2 = datosLeidos.valor2;
                    misDatos.valor3 = atoi(cant) + datosLeidos.valor3;
                    i2c_write_struct(EEPROM_ADDR, misDatos, i);

                tag_exists = true;
                return true;
            }
            else {
                tag_exists = false;
            }
        }

        if(!tag_exists) {

            printf("Agregar nuevo producto..... \n");
            
            printf("Agregar precio..... \n");
            writeInfo("    INGRESE", 11,"     PRECIO", 11);

            while (key != 'A' && countp < 6) {
                newKey2 = newKeyPressed();
                sleep_us(5);
                key2 =  *newKey2 ? getKey() : 'p';
                keyIsNum = ((int)key2 >= 48 && (int)key2 <= 57) ? 1 : 0;

                if(*newKey2) {
                    printf("%c   \n", key2);
                    if (keyIsNum) {
                        concatenarCaracter(key2, precio, "$:  ", &countp);
                    } else if (key2 == 'A'){
                        *newKey2 = false;
                        countp = 6;
                        printf("Fin precio \n");
                        break;
                    } 
                }
                *newKey2 = false;
            }
            writeInfo("    INGRESE", 11,"    CANTIDAD", 12);
            
            while (key != 'A' && countCant < 4) {
                newKey = newKeyPressed();
                sleep_us(5);
                key =  *newKey ? getKey() : 'p';
                keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

                if(*newKey) {
                    printf("%c   \n", key);
                    if (keyIsNum) {
                        concatenarCaracter(key, cant, "Cnt:", &countCant);
                    } else if (key == 'A'){
                        writeInfo("    PRODUCTO", 12,"   INGRESADO", 12);
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
            misDatos.valor2 = atoi(precio)/100;
            misDatos.valor3 = atoi(cant);
            i2c_write_struct(EEPROM_ADDR, misDatos, cant_products++);
            write_Position(cant_products, 4000);            
            return true;
        }

        //printf("Producto agregad: ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);    

    }
    tag_detected = false;
    
    return false;
}

void reiniciarCuenta() {
    cuenta = 0;
}

uint16_t *getCuenta() {
    return &cuenta;
}

uint16_t getPrecio() {
    return precio;
}