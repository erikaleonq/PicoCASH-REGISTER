#include "salesMgent.h"

void iniciarVenta() {

    char Key = 'n';
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
                *newKey = false;
                printf("Se multiplica por %i\n", mult);
            }
        }
        recive_tag();
        product_exist();
    }
    writeInfo("     VENTA", 10, "** FINALIZADA **", 16);

    printf("Compra finalizada");
}

void ingresarDocumento() {

    printf("Ingrese documento del cliente: \n ");
    writeInfo("    INGRESE", 11, "   DOCUMENTO", 12);
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
            writeInfo("     LECTOR", 11, "    ACTIVADO", 12);
            printf("INCIA VENTA\n");
            *newKey = false;
        }
    }
    //TODO: Buscar usuario
    iniciarVenta();
}