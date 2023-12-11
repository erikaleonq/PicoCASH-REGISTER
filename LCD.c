#include "LCD.h"

/**
 * @file LCD.c
 * @brief Este archivo contiene funciones relacionadas con el control de una pantalla LCD. 
 * Incluye funciones para inicializar los pines de la pantalla LCD, configurarla con comandos específicos, enviar datos a la 
 * pantalla y realizar operaciones como cambiar de línea y limpiar la pantalla.
 */

/**
 *                       GPIO      MASK
 * Pin D4.                 9    0x00000200 
 * Pin D5.                10    0x00000400    
 * Pin D6.                11    0x00000800
 * Pin D7.                12    0x00001000
 * Pin RS.                13    0x00002000
 * Pin ENABLE.            14    0x00004000
 *
 * @brief Inicializa los pines de la pantalla LCD.
 *
 * Esta función inicializa los pines configurados previamente para la pantalla LCD.
 */


void LCDInit(){ 

    gpio_init_mask(0x00007E00);
    gpio_set_dir_out_masked(0x00007E00);
    gpio_put_masked(0x00007E00, 0);

}

/**
 * @brief Configura la pantalla LCD.
 *
 * Esta función configura la pantalla LCD con los comandos iniciales necesarios.
 */
void LCDconfig() {
    sleep_ms(100);
    for (int i=0;  i<3; i++){
        Write4Bits(LCD_INIT, MSB, LCD_RS_CMD);
        sleep_ms(5);
    }
        
    Write4Bits(LCD_SET, MSB, LCD_RS_CMD);
    sleep_ms(1);

    Write4Bits(LCD_SET, MSB, LCD_RS_CMD);
    Write4Bits(LCD_SET, LSB, LCD_RS_CMD);
    sleep_ms(1);

    Write4Bits(LCD_SHOW, MSB, LCD_RS_CMD);
    Write4Bits(LCD_SHOW, LSB, LCD_RS_CMD);
    sleep_ms(1);

    Write4Bits(LCD_CLR, MSB, LCD_RS_CMD);
    Write4Bits(LCD_CLR, LSB, LCD_RS_CMD);
    sleep_ms(1);

    Write4Bits(LCD_ENTRY_MODE, MSB, LCD_RS_CMD);
    Write4Bits(LCD_ENTRY_MODE, LSB, LCD_RS_CMD);
    sleep_ms(1);
    
    Write4Bits(LCD_BLINK, MSB, LCD_RS_CMD);
    Write4Bits(LCD_BLINK, LSB, LCD_RS_CMD);
    sleep_ms(1);

    ClearScreen();
    WriteStr("*** PICOCA$H ***", 16);
    ChgLine();
    WriteStr("     LOG IN     ", 16);

}

/**
 * @brief Genera un pulso en el pin ENABLE.
 *
 * Esta función genera un pulso en el pin ENABLE para enviar datos a la pantalla LCD.
 */
void PulseEnable(){
    gpio_put_masked(0x00004000, 0);  //
    sleep_ms(1);
    gpio_put_masked(0x00004000, 1 << 14);
    sleep_ms(1);
    gpio_put_masked(0x00004000, 0);
    sleep_ms(3);
}

/**
 * @brief Escribe 4 bits de datos en la pantalla LCD.
 *
 * @param[in] data Datos a escribir.
 * @param[in] isLSB Indica si se trata del byte menos significativo.
 * @param[in] isData Indica si los datos son comandos o datos de pantalla.
 *
 * Esta función escribe 4 bits de datos en la pantalla LCD.
 */
void Write4Bits(uint8_t data, int isLSB, int isData){
    
    if(!isLSB)  {
        data = data >> 4;
    } else {
        data = data << 4;
        data = data >> 4;
    }
    
    gpio_put_masked(0x00002000, isData << 13);
    gpio_put_masked(0x00001E00, data << 9);

    PulseEnable();
}

/**
 * @brief Cambia de línea en la pantalla LCD.
 *
 * Esta función cambia de línea en la pantalla LCD.
 */
void ChgLine(){
    Write4Bits(LCD_CHG_LINE, MSB, LCD_RS_CMD);
    Write4Bits(LCD_CHG_LINE, LSB, LCD_RS_CMD);
}

/**
 * @brief Limpia la pantalla LCD.
 *
 * Esta función limpia la pantalla LCD.
 */
void ClearScreen(){
    Write4Bits(LCD_CLR, 0, 0);
    Write4Bits(LCD_CLR, 1, 0);
}

/**
 * @brief Escribe una cadena de caracteres en la pantalla LCD.
 *
 * @param[in] array Cadena de caracteres a escribir.
 * @param[in] len Longitud de la cadena.
 *
 * Esta función escribe una cadena de caracteres en la pantalla LCD.
 */
void WriteStr(char (*array), int len){

    for(int i = 0; i < len; i++){
        Write4Bits(*(array + i), MSB, LCD_RS_DATA);
        Write4Bits(*(array + i), LSB, LCD_RS_DATA);
    }
}

/**
 * @brief Escribe un número entero en la pantalla LCD.
 *
 * @param[in] value Número entero a escribir.
 *
 * Esta función escribe un número entero en la pantalla LCD.
 */
void WriteInt(int value){

    int digito, longitud, i;
    
    // Calcular la longitud del número
    longitud = value != 0 ? (int)log10(value) + 1 : 1;
    
    char digitos[longitud];
    
    int temp = value;
    for (i = 0; i < longitud; i++) {
        digito = temp % 10;
        digitos[longitud - i - 1] = (char)(digito + 48);
        temp = temp / 10;
    }
    WriteStr(&digitos[0] , longitud);
}

void writeInfo(char *info1, int len1, char *info2, int len2){
    ClearScreen();
    WriteStr(info1, len1);
    ChgLine();
    WriteStr(info2, len2);
}

void displayProd(int ID, int valor){
    ClearScreen();
    WriteStr("REF:", 4);
    WriteInt(ID);
    WriteStr(" $", 2); 
    WriteInt(valor*100);
}