#include "salesMgent.h"

int mult;

void iniciarVenta() {

    char key = 'n';
    bool *newKey, keyIsNum;
    uint16_t *cuenta;
    uint16_t precio;
    reiniciarCuenta();

    
    while (key != 'A') {
        newKey = newKeyPressed();
        keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;

        if(*newKey) {
            key =  getKey();
            if (key == '*') {
                printf("Seleccione cantidad: \n");
                writeInfo("    INGRESE", 11, "  CANTIDAD : ", 13);
                while(key != 'R') {
                    newKey = newKeyPressed();
                    key =  *newKey ? getKey() : 'p';
                    keyIsNum = ((int)key >= 48 && (int)key <= 57) ? 1 : 0;
                    mult = keyIsNum ? (int)key - 48 : mult;
                    if(keyIsNum){
                        WriteInt(mult);
                        *newKey = false;
                    }
                }

                cuenta = getCuenta();
                precio = getPrecio();
                printf("Se multiplica por %i\n", mult);

                *cuenta += precio * (mult - 1);
                mult = 1;
                printf("cuenta %li \n", *cuenta);
                
                
                displayProd(1, precio);
                ChgLine();
                WriteStr("TOTAL: $", 8);
                WriteInt(*cuenta*100);

            } else if (key == 'L') {
                printf("Producto retirado de la cuenta\n");
                writeInfo("    PRODUCTO", 12, "    RETIRADO", 12);
                cuenta = getCuenta();
                precio = getPrecio();
                *cuenta -= precio;
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