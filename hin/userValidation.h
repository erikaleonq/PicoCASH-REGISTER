#ifndef _USERVALIDATION_H_
#define _USERVALIDATION_H_

#include <stdio.h>
#include <string.h>

#define NUMADMINS 10
#define LENUSER 4
#define LENPWD 6

int confirmUser (char *user , char *password);
void concatenarCaracter(char key, char *cadena, char *tipo, int *count);
void reset(char* user, char* password, int* count_p, int* count_u);

#endif