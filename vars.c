#include <sys/types.h>

typedef struct {
    int codigo;
    char *nome;
    float valor;
    char *horario;
} Espetaculo;

typedef struct {
    int codigoRetorno;
    Espetaculo *espetaculo;
} Espectaculo_aux;

typedef struct {
    Espetaculo *espetaculo;
    char *poltrona;
    float valorPago;
    char *dataCompra;
    int idade;
} Compra;
