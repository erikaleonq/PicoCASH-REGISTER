#include "salesMgent.h"

void iniciarVenta() {
    char key;
    bool *newKey, keyIsNum;
    int mult;
    reiniciarCuenta();

    
    while (key != 'A') {
        newKey = newKeyPressed();
        keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

        if(*newKey) {
            key =  getKey();
            if (key == '*') {
                printf("Seleccione cantidad: \n");
                while(!keyIsNum) {
                    newKey = newKeyPressed();
                    key =  *newKey ? getKey() : 'p';
                    keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;
                    mult = keyIsNum ? (int)key - 48 : 1;
                }
                printf("Se multiplica por %i\n", mult);
            }
        }
        recive_tag();
        product_exist();
    }
    printf("Compra finalizada");
}

void ingresarDocumento() {

    printf("Ingrese documento del cliente: \n ");
    char key;
    bool *newKey, keyIsNum;
    char documento[10];
    int count = 0;
    
    while (key != 'A') {
        newKey = newKeyPressed();
        key =  *newKey ? getKey() : 'p';
        keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

        if(*newKey && keyIsNum) {
            concatenarCaracter(key, documento, "DOC:", &count);
            *newKey = false;
        } else if(*newKey && key == 'A') {
            printf("Venta finalizada\n");
        }
    }
    //TODO: Buscar usuario
    iniciarVenta();
}