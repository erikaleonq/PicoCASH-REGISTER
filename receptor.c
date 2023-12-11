#include "receptor.h"
#include "memoria.h"

char received_message[5];
int received_message_length = 0;
int cuenta = 0;
int cant_products;
uint16_t converted_value = 0;
uint16_t new_cant = 0;
bool tag_detected = false;


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

uint16_t *tag_value()
{
    return &converted_value;
}

bool *is_tag_detected()
{
    return &tag_detected;
}

void new_product()
{
    bool *tag_detected;
    uint16_t *tag_number;
    bool tag_exists = false;
    tag_detected = is_tag_detected();
    tag_number = tag_value();
    cant_products = read_position(EEPROM_ADDR, 4000);

    if (*tag_detected)
    {

        for (int i = 0; i < cant_products; i++)
        {
            DatosFlotantes datosLeidos = i2c_read_struct(EEPROM_ADDR, i);

            // printf("valor1: %f\n", datosLeidos.valor1);
            if (datosLeidos.valor1 == *tag_number)
            {
                printf("Ingrese cantidad de productos a agrgar: ");

///////////////Recibir cantidad de productos a argregar////////////////////////

                printf("ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);                 
                    
                    DatosFlotantes misDatos;
                    misDatos.valor1 = datosLeidos.valor1;
                    misDatos.valor2 = datosLeidos.valor2;
                    misDatos.valor3 = datosLeidos.valor3  /*+ nuevo numero de cantidad*/;
                    i2c_write_struct(EEPROM_ADDR, misDatos, i);
                
                tag_exists = true;
                break;
            }
            else
            {
                tag_exists = false;
            }
        }
        if(!tag_exists)
        {

            printf("Agregar nuevo producto..... \n");

            printf("Agregar precio..... \n");

            /*Ingresar valor del producto*/

            printf("Agregar cantidad..... \n");
            /*Ingresar cantidad del producto*/


          
            DatosFlotantes misDatos;
                    misDatos.valor1 = converted_value;
                    misDatos.valor2 = /*Ingrese el valor del producto*/;
                    misDatos.valor3 = /*ingrese su cantidad*/;
                    i2c_write_struct(EEPROM_ADDR, misDatos, cant_products+1);



            printf("Producto agregad: ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);    
            
        }
        *tag_detected = false;
    }
}

void product_exist()
{
    bool *tag_detected;
    uint16_t *tag_number;
    bool tag_exists = false;
    tag_detected = is_tag_detected();
    tag_number = tag_value();
    cant_products = read_position(EEPROM_ADDR, 4000);


    if (*tag_detected)
    {

        for (int i = 0; i < cant_products; i++)
        {
            DatosFlotantes datosLeidos = i2c_read_struct(EEPROM_ADDR, i);

            
            if (datosLeidos.valor1 == *tag_number)
            {
                
                printf("ID: %li, Precio: %li, Cantidad %li\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);
                cuenta = cuenta + datosLeidos.valor2;
                printf("Cuenta total: %d\n", cuenta);

                if (datosLeidos.valor3 > 0)
                {
                    
                    
                    DatosFlotantes misDatos;
                    misDatos.valor1 = datosLeidos.valor1;
                    misDatos.valor2 = datosLeidos.valor2;
                    misDatos.valor3 = datosLeidos.valor3 - 1 ;
                    i2c_write_struct(EEPROM_ADDR, misDatos, i);
                }
                tag_exists = true;
                break;
            }
            else
            {
                tag_exists = false;
            }
        }
        if (!tag_exists)
        {

            printf("Este producto no existe!!!!!! \n");
        }
        *tag_detected = false;
    }
}