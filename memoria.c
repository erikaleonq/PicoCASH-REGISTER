#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>

#define EEPROM_ADDR 0b1010000 // Dirección I2C de la EEPROM (A0-A2 a tierra)

// Estructura para almacenar tres valores flotantes
typedef struct {
    float valor1;
    float valor2;
    float valor3;
} DatosFlotantes;

void i2c_write_struct(i2c_inst_t *i2c, uint8_t address, DatosFlotantes datos, uint16_t offset) {
    uint8_t data[14]; // tres flotantes (4 bytes cada uno) más 2 bytes para el offset

    // Copiamos los valores de la estructura en el array de bytes
    memcpy(data, &offset, 2); // Copiamos los 2 bytes del offset
    memcpy(data + 2, &datos, sizeof(DatosFlotantes)); // Copiamos la estructura en los bytes restantes

    i2c_write_blocking(i2c, EEPROM_ADDR, data, 14, false); // Escribimos los datos en la EEPROM

    sleep_ms(10);
}

DatosFlotantes i2c_read_struct(i2c_inst_t *i2c, uint8_t address, uint16_t offset) {
    DatosFlotantes datos;
    uint8_t data[sizeof(DatosFlotantes)]; // Tamaño de la estructura de datos

    i2c_write_blocking(i2c, EEPROM_ADDR, (uint8_t *)&offset, 2, true); // Enviamos la dirección de memoria a leer
    i2c_read_blocking(i2c, EEPROM_ADDR, data, sizeof(DatosFlotantes), false); // Leemos los datos desde la EEPROM

    memcpy(&datos, data, sizeof(DatosFlotantes)); // Copiamos los bytes leídos en la estructura de datos

    return datos;
}

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
