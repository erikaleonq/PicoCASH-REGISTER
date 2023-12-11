#ifndef _MEMORIA_H_
#define _MEMORIA_H_

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <string.h>


#define EEPROM_ADDR 0b1010000 // Dirección I2C de la EEPROM (A0-A2 a tierra)
#define MAX_POS 20

// Estructura para almacenar tres valores flotantes
typedef struct {
    uint16_t valor1;
    uint16_t valor2;
    uint16_t valor3;
} DatosFlotantes;

void init_i2c();
void i2c_write_struct( uint8_t address, DatosFlotantes datos, uint16_t offset);
DatosFlotantes i2c_read_struct( uint8_t address, uint16_t offset);
int read_position(uint8_t address, uint16_t offset);



#endif