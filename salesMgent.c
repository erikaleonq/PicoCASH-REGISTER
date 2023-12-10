#include "salesMgent.h"

void iniciarVenta() {
    char key;
    bool *newKey;

    
    while (key != 'F') {
        newKey = newKeyPressed();

        if(*newKey) {
            key =  getKey();
        }
        recive_tag();
    }
}