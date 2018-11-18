#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char nome[100];
    float valor;
} Espetaculo;

//char caracteresDigitados[20];
Espetaculo *espetaculos;