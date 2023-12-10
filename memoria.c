#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>
#include "memoria.h"

#define EEPROM_ADDR 0b1010000 // Dirección I2C de la EEPROM (A0-A2 a tierra)

// Estructura para almacenar tres valores flotantes
typedef struct {
    float valor1;
    float valor2;
    float valor3;
} DatosFlotantes;



int main() {
    stdio_init_all();

    i2c_inst_t *i2c = i2c0;
    gpio_set_function(20, GPIO_FUNC_I2C);
    gpio_set_function(21, GPIO_FUNC_I2C);
    gpio_pull_up(20);
    gpio_pull_up(21);

    i2c_init(i2c, 100 * 1000); // Inicializamos la comunicación I2C a 100 kHz

    // Crear una estructura con dos valores flotantes
    DatosFlotantes misDatos;
    misDatos.valor1 = 8589;
    misDatos.valor2 = 2871;
    misDatos.valor3 = 5223;


    // Escribir la estructura en la memoria EEPROM en la dirección 0
    i2c_write_struct(i2c, EEPROM_ADDR, misDatos, 0);

    misDatos.valor1 = 9114;
    misDatos.valor2 = 4871;
    misDatos.valor3 = 7722;

    i2c_write_struct(i2c, EEPROM_ADDR, misDatos, 1);
    // Leer la estructura desde la memoria EEPROM

    while(1){

    DatosFlotantes datosLeidos = i2c_read_struct(i2c, EEPROM_ADDR, 0);
    printf("Valores leídos desde la EEPROM: %.2f, %.2f\n", datosLeidos.valor1, datosLeidos.valor2, datosLeidos.valor3);
    sleep_ms(1000);

    DatosFlotantes datosLeidos2 = i2c_read_struct(i2c, EEPROM_ADDR, 1);
    printf("Valores leídos desde la EEPROM: %.2f, %.2f\n", datosLeidos2.valor1, datosLeidos2.valor2, datosLeidos.valor3);

    sleep_ms(1000);
    
    }
    return 0;
}
