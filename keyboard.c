#include "keyboard.h"

volatile uint8_t gKeyCnt = 0; // Contador global de teclas ingresadas
volatile uint8_t gSeqCnt = 0; // Contador global de secuencia
volatile bool gDZero = false; // Bandera para debouncer

char keymap[5][4] = { //NUM_FILAS][NUM_COLUMNAS] = {
    {'F', 'f', '#', '*'},  //F -> F1, //f -> F2
    {'1', '2', '3', 'U'},
    {'4', '5', '6', 'D'},
    {'7', '8', '9', 'E'},  //E -> Esc
    {'L', '0', 'R', 'A'}   //A -> Enter
};


/// @brief Función de devolución de llamada para el teclado
/// @param num Número de la interrupción de GPIO que activó la función de devolución de llamada
/// @param mask Máscara de interrupción de GPIO
void keyboardCallback(uint num, uint32_t mask) {
    // Congelar la secuencia de filas deshabilitando el PWM correspondiente
    pwm_set_enabled(0, false);

    // Habilitar el PWM para la secuencia de columna
    pwm_set_enabled(1, true);
    
    // Deshabilitar las interrupciones de GPIO para las filas durante el debounce
    gpio_set_irq_enabled(0, GPIO_IRQ_EDGE_RISE, false);
    gpio_set_irq_enabled(1, GPIO_IRQ_EDGE_RISE, false);
    gpio_set_irq_enabled(2, GPIO_IRQ_EDGE_RISE, false);
    gpio_set_irq_enabled(3, GPIO_IRQ_EDGE_RISE, false);

    // Obtener datos de teclado (bits 2-9) y decodificar la tecla
    uint32_t keyData = gpio_get_all() & 0x000001FF;
    
    // Calcular el logaritmo en base 2
    int col = log2(keyData & 0xF);
    int fil = 4 - log2((keyData >> 4) & 0x1F);
    printf("%c \n", keymap[fil][col]);

    // Incrementar el contador de teclas ingresadas
    gKeyCnt++;

    // Confirmar la interrupción de GPIO
    gpio_acknowledge_irq(num, mask);
    // ... (se omite el comentario original)
}

/// @brief Función de devolución de llamada para la interrupción de PWM
void pwmIRQ(void) {
    uint32_t gpioValue;
    uint32_t keyc;

    // Determinar qué slice de PWM generó la interrupción
    switch (pwm_get_irq_status_mask()) {
        case 0x01UL: 
            // ISR de la slice de PWM 0 utilizada como un temporizador para generar la secuencia de filas
            gSeqCnt = (gSeqCnt + 1) % 5;
            // Actualizar las filas activas en la matriz del teclado
            gpio_put_masked(0x000001F0, 0x00000001 << (gSeqCnt + 4));
            // Reconocer la interrupción de PWM de la slice 0
            pwm_clear_irq(0);
            break;
        case 0x02UL: 
            // ISR de la slice de PWM 1 utilizada como un temporizador para implementar el debounce
            keyc = gpio_get_all() & 0x0000000F; // Obtener los valores brutos de los GPIO
            if (gDZero) {
                if (!keyc) {
                    // Congelar la secuencia de filas
                    pwm_set_enabled(0, true);
                    // Deshabilitar las interrupciones de GPIO para las filas
                    pwm_set_enabled(1, false);
                    gpio_set_irq_enabled(0, GPIO_IRQ_EDGE_RISE, true);
                    gpio_set_irq_enabled(1, GPIO_IRQ_EDGE_RISE, true);
                    gpio_set_irq_enabled(2, GPIO_IRQ_EDGE_RISE, true);
                    gpio_set_irq_enabled(3, GPIO_IRQ_EDGE_RISE, true);
                }
                gDZero = false;
            } else {
                gDZero = true;
            }
            // Reconocer la interrupción de PWM de la slice 1
            pwm_clear_irq(1);
            break;
        default:
            // Manejar un caso inesperado
            printf("Se produjo un evento inesperado en PWM IRQ\n");
            break;
    }
}

/// @brief Inicializa PWM como temporizador periódico (PIT).
/// @param slice Número de la slice de PWM a utilizar.
/// @param milis Duración del período del temporizador en milisegundos (máximo 262 ms).
/// @param enable Indica si se debe habilitar el temporizador después de la inicialización.
void initPWMasPIT(uint8_t slice, uint16_t milis, bool enable) {
    // Asegurarse de que la duración del período sea válida (máximo 262 ms)
    assert(milis <= 262);

    // Calcular el valor del prescaler para el temporizador PWM
    float prescaler = (float)SYS_CLK_KHZ / 500;
    // Asegurarse de que el valor del prescaler no sea mayor a 255
    assert(prescaler < 256);

    // Calcular el valor de envolvente para el temporizador PWM
    uint32_t wrap = 500000 * milis / 2000;
    // Asegurarse de que el valor de envolvente no exceda el límite de 17 bits
    assert(wrap < ((1UL << 17) - 1));

    // Configurar la estructura de configuración del PWM
    pwm_config cfg = pwm_get_default_config();
    pwm_config_set_phase_correct(&cfg, true);
    pwm_config_set_clkdiv(&cfg, prescaler);
    pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_FREE_RUNNING);
    pwm_config_set_wrap(&cfg, wrap);

    // Habilitar la interrupción para la slice de PWM
    pwm_set_irq_enabled(slice, true);
    // Habilitar la interrupción de envolvente del temporizador PWM
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // Inicializar la slice de PWM con la configuración proporcionada
    pwm_init(slice, &cfg, enable);
}


/// @brief Inicializa una matriz de teclado 4x4.
void initMatrixKeyboard4x4(void) {
    // Configuración de los GPIO para las filas de la matriz (secuencia one hot)
    // Los GPIOs 8 a 4 controlan las filas del teclado
    gpio_set_function(4, GPIO_FUNC_SIO);
    gpio_set_function(5, GPIO_FUNC_SIO);
    gpio_set_function(6, GPIO_FUNC_SIO);
    gpio_set_function(7, GPIO_FUNC_SIO);
    gpio_set_function(8, GPIO_FUNC_SIO);

    // Configuración de los GPIO para las columnas de la matriz (interrupciones de GPIO)
    // Los GPIOs 3 a 0 controlan las columnas del teclado
    gpio_set_function(0, GPIO_FUNC_SIO);
    gpio_set_function(1, GPIO_FUNC_SIO);
    gpio_set_function(2, GPIO_FUNC_SIO);
    gpio_set_function(3, GPIO_FUNC_SIO);

    // Establecer la dirección de los GPIOs 6 a 9 como entradas (columnas)
    gpio_set_dir_in_masked(0x0000000F);
    // Establecer la dirección de los GPIOs 2 a 5 como salidas (filas)
    gpio_set_dir_out_masked(0x000001F0);
    // Escribir 0 en las filas
    gpio_put_masked(0x000001F0, 0);

    // Habilitar interrupciones de GPIO con callback para las columnas
    gpio_set_irq_enabled_with_callback(0, GPIO_IRQ_EDGE_RISE, true, keyboardCallback);
    gpio_set_irq_enabled_with_callback(1, GPIO_IRQ_EDGE_RISE, true, keyboardCallback);
    gpio_set_irq_enabled_with_callback(2, GPIO_IRQ_EDGE_RISE, true, keyboardCallback);
    gpio_set_irq_enabled_with_callback(3, GPIO_IRQ_EDGE_RISE, true, keyboardCallback);
}

void initKeyboard() {
    // Inicializar PWM como PIT para controlar las secuencias de tiempo
    initPWMasPIT(0, 2, true);
    initPWMasPIT(1, 50, false);

       // Configurar el controlador de interrupción exclusivo para la interrupción PWM
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwmIRQ);
    // Establecer la prioridad de la interrupción PWM
    irq_set_priority(PWM_IRQ_WRAP, 0xC0);

    // Inicializar la matriz del teclado 4x4
    initMatrixKeyboard4x4();
}