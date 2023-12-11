#include "memoria.h"

i2c_inst_t *i2c = i2c1;

void init_i2c(){
    
    
    gpio_set_function(18, GPIO_FUNC_I2C);
    gpio_set_function(19, GPIO_FUNC_I2C);
    gpio_pull_up(18);
    gpio_pull_up(19);

    i2c_init(i2c, 100 * 1000); // Inicializamos la comunicación I2C a 100 kHz
    
}


void i2c_write_struct(uint8_t address, DatosFlotantes datos, uint16_t offset) {
    uint8_t data[14]; // tres flotantes (4 bytes cada uno) más 2 bytes para el offset

    // Copiamos los valores de la estructura en el array de bytes
    memcpy(data, &offset, 2); // Copiamos los 2 bytes del offset
    memcpy(data + 2, &datos, sizeof(DatosFlotantes)); // Copiamos la estructura en los bytes restantes

    i2c_write_blocking(i2c, EEPROM_ADDR, data, 14, false); // Escribimos los datos en la EEPROM

    sleep_ms(10);
}

DatosFlotantes i2c_read_struct( uint8_t address, uint16_t offset) {
    DatosFlotantes datos;
    uint8_t data[sizeof(DatosFlotantes)]; // Tamaño de la estructura de datos

    i2c_write_blocking(i2c, EEPROM_ADDR, (uint8_t *)&offset, 2, true); // Enviamos la dirección de memoria a leer
    i2c_read_blocking(i2c, EEPROM_ADDR, data, sizeof(DatosFlotantes), false); // Leemos los datos desde la EEPROM

    memcpy(&datos, data, sizeof(DatosFlotantes)); // Copiamos los bytes leídos en la estructura de datos

    return datos;
}

int read_position(uint8_t address, uint16_t offset)
{
    int data;
    uint8_t buffer[sizeof(int)];
    i2c_write_blocking(i2c, EEPROM_ADDR, (uint8_t *)&offset, 2, true);
    i2c_read_blocking(i2c, EEPROM_ADDR, buffer, sizeof(int), false);
    memcpy(&data, buffer, sizeof(int));
    return data;
}

void write_Position(int pos, uint16_t mem_pos) {
    uint8_t buffer[sizeof(int) + 2];
    memcpy(buffer, &mem_pos, 2);
    memcpy(buffer + 2, &pos, sizeof(int));
    i2c_write_blocking(i2c, EEPROM_ADDR, buffer, sizeof(int) + 2, false);
    sleep_ms(10);
}