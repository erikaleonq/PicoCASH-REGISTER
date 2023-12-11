#ifndef _USERVALIDATION_H_
#define _USERVALIDATION_H_

#include <stdio.h>
#include <string.h>
#include "hardware/sync.h"

#define LENUSER 4
#define LENPWD 6

int confirmUser (bool *isAdmin);
void concatenarCaracter(char key, char *cadena, char *tipo, int *count);
void resetValidation();
bool isValidUser(char key, bool *isAdmin);

#endif