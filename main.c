/**
 * @file main.c
 * @brief This is a brief description of the main C file.
 *
 * Detailed description of the main C file.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define NUM_FILAS 5
#define NUM_COLUMNAS 4
char lastKey;

void teclaPresionada_callback(uint gpio, uint32_t events) {
    // Leer el estado de las filas y columnas para determinar la tecla presionada
    for (uint fila = 0; fila < NUM_FILAS; fila++) {
        gpio_put(fila + NUM_COLUMNAS, 0);  // Configurar fila como salida y en bajo

        for (uint columna = 0; columna < NUM_COLUMNAS; columna++) {
            if (gpio_get(columna)) {
                // Tecla presionada en la fila 'fila' y columna 'columna'
                printf("Tecla presionada: Fila %u, Columna %u\n", fila, columna);
            }
        }

        gpio_put(fila + NUM_COLUMNAS, 1);  // Restaurar fila a alto
    }
}

/**
 * @brief Obtiene la tecla presionada en el teclado matricial.
 *
 * @param lastKey Puntero al último carácter de tecla presionada.
 * @return El carácter de la tecla presionada o 0 si ninguna tecla está presionada.
 */
void getKey() {
    char keymap[NUM_FILAS][NUM_COLUMNAS] = {
        {'F', 'f', '#', '*'},  //F -> F1, //f -> F2
        {'1', '2', '3', 'U'},
        {'4', '5', '6', 'D'},
        {'7', '8', '9', 'E'},  //E -> Esc
        {'L', '0', 'R', 'A'}   //A -> Enter
    };
    
    for (int row = 0; row < NUM_FILAS; row++) {
        // Establece la fila actual a HIGH
        gpio_put(row + NUM_COLUMNAS, 1);

        for (int col = 0; col < NUM_COLUMNAS; col++) {
            if (gpio_get(col) == 1) {
                // La columna actual está activada
                // Devuelve el carácter correspondiente en el mapa
                gpio_put(row + NUM_COLUMNAS, 0); // Restaura la fila a LOW

                if (lastKey != keymap[row][col]) {
                    lastKey = keymap[row][col];
                    printf ("%c \n", keymap[row][col]);
                    col = NUM_COLUMNAS + 1;
                    row = NUM_FILAS + 1;
                }
            }
        }
        // Restaura la fila a LOW
        gpio_put(row + NUM_COLUMNAS, 0);
    }
    //lastKey = 'n';
}


/**
 * @brief Inicializa el teclado matricial configurando los pines GPIO correspondientes.
 */
void initKeyboard(){
    // Configura pines de filas como salidas y pines de columnas como entradas
    for (uint fila = 0; fila < NUM_FILAS; fila++) {
        gpio_init(fila + NUM_COLUMNAS);
        gpio_set_dir(fila + NUM_COLUMNAS, GPIO_OUT);
        gpio_put(fila + NUM_COLUMNAS, 1);
    }

    // Configurar pines de columnas como entradas con interrupciones
    for (uint columna = 0; columna < NUM_COLUMNAS; columna++) {
        gpio_init(columna);
        gpio_set_dir(columna, GPIO_IN);
        gpio_pull_up(columna);
        gpio_set_irq_enabled_with_callback(columna, GPIO_IRQ_EDGE_RISE, true, &getKey);
    }


}

/**
 * @brief Verifica si una tecla está presionada y la obtiene.
 *
 * @param key Puntero al carácter de la tecla presionada.
 * @param lastKey Puntero al último carácter de tecla presionada.
 * @return 1 si una tecla está presionada, 0 en caso contrario.
 */
int isPressed(char* key, char* lastKey) {
    
    //*key = getKey(lastKey);

    if (*key != 0) {
        return 1;
    }
    return 0;
}

int main() {
    stdio_init_all();
    initKeyboard();

    while (1) {
        // Tu lógica principal puede ir aquí
    }

    return 0;
}
