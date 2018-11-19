#include <stdio.h>

#ifdef _WIN32

#include <malloc.h>

#else
#include <stdlib.h>
#endif

#include <malloc.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "vars.c"
#include "cliente.h"
#include "main.h"

char *fgetsInput;
int TAMANHO_DA_LISTA_ESPETACULOS = 0;
int QUANTIDADE_VENDAS = 0;
char poltronasDisponiveis[] = "ABCDE";
Espetaculo espetaculosDisponiveis[10];
Compra ingressosVendidos[100];

/*header*/
void cadastrarEspetaculos();

void opcaoUsuario() {
    printf("############################################\n");
    printf("#            Tela Principal                #\n");
    printf("############################################\n");
    printf("### 1 - Cliente\n");
    printf("### 2 - Administrador\n");
    printf("### 3 - Fechar Programa\n");
}

void iniciarlizarVarivareis() {
    printf("Iniciando programa...\n");
    cadastrarEspetaculos();

    /*teste*/
    Espetaculo espetaculo = {100, "Espetaculo das Bandeiras", 70.00F, "18:00"};
    adicionarVenda(&espetaculo, "A1", 70.00F, 32);
    printf("\n\n");
}

void adicionarVenda(Espetaculo *espetaculo, char *poltrona, float valorPago, int idadeComprador) {
    char dataHora[22];
    sprintf(dataHora, "%s %s", __DATE__, __TIME__);
    Compra compra = {espetaculo, poltrona, valorPago, dataHora, idadeComprador};
    ingressosVendidos[QUANTIDADE_VENDAS++] = compra;
}

void adicionarEspetaculo(int codigo, char *nome, float valor, char *horario) {
    Espetaculo espetaculo = {codigo, nome, valor, horario};
    espetaculosDisponiveis[TAMANHO_DA_LISTA_ESPETACULOS++] = espetaculo;
}

void cadastrarEspetaculos() {
    printf("  * Cadastrando dados...");
    adicionarEspetaculo(100, "Espetaculo das Bandeiras", 70.00f, "18:00");
    adicionarEspetaculo(102, "Sisne Negro", 138.00f, "15:00");
    adicionarEspetaculo(103, "Vento Levou", 25.50f, "22:00");
    adicionarEspetaculo(104, "Garota de Ipanema", 55.99f, "21:00");
    adicionarEspetaculo(105, "Fluido Urbano", 110.00f, "12:00");
    printf("OK\n");
}

int main() {
    iniciarlizarVarivareis();
    fgetsInput = malloc(3);
    unsigned int opcao;
    while (opcao != 3) {
        opcaoUsuario();
        printf("Escolha modulo: ");
        fflush(stdin);
        fgets(fgetsInput, 3, stdin);
        opcao = atoi(fgetsInput);
        printf("\n");
        switch (opcao) {
            case 1: {
                iniciarTelaDoCliente();
                break;
            }
            case 3: {
                printf("Encerrando aplicacao...\n\n");
                break;
            }
            default:
                printf("Opcao invalida!\n");
        }
    }
    return 0;
}

void mostrarEspetaculosCadastrados() {
    printf("\n- - - - - - - Espetaculos Disponiveis - - - - - - -\n");
    printf("#####################################################\n");
    printf("# C - Cancelar                                      #\n");
    printf("#####################################################\n");
    for (int i = 0; i < TAMANHO_DA_LISTA_ESPETACULOS; i++) {
        Espetaculo esp = espetaculosDisponiveis[i];
        printf("%d", esp.codigo);
        printf(" - ");
        printf("%s - ", esp.nome);
        printf("%s - ", esp.horario);
        printf("R$ %3.2f", esp.valor);
        printf("\n");
    }
}

int verificarSePoltronaEstaDisponivel(char *poltrona) {
    for (int i = 0; i < 100; i++) {
        poltrona[0] = toupper(poltrona[0]);
        Compra cp = ingressosVendidos[i];
        if (cp.poltrona == NULL) {
            continue;
        }
        if (strcmp(cp.poltrona, poltrona) == 0) {
            return false;
        }
    }
    return true;
}

int verificarSeExistePoltrona(char *poltrona) {
    char *poltronaCopy;
    poltronaCopy = malloc(sizeof(char) * 3);
    strcpy(poltronaCopy, poltrona);
    poltronaCopy[0] = toupper(poltronaCopy[0]);
    int tamanhoArrayPoltrona = strlen(poltronasDisponiveis);
    for (int i = 0; i < tamanhoArrayPoltrona; i++) {
        if (toupper(poltronasDisponiveis[i]) == toupper(poltronaCopy[0])) {
            poltronaCopy[0] = '0';
            int _v = atoi(poltronaCopy);
            if (_v >= 1 && _v <= 10) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

void mostrarPoltronasDisponiveis() {
    int quantidadePoltronas = strlen(poltronasDisponiveis);
    for (int i = 0; i < quantidadePoltronas; i++) {
        printf("\n");
        for (int y = 0; y < 10; y++) {
            char poltrona[4];
            sprintf(poltrona, "%c%d", toupper(poltronasDisponiveis[i]), y + 1);
            if (verificarSePoltronaEstaDisponivel(poltrona)) {
                printf("[%c%d] ", poltronasDisponiveis[i], y + 1);
            } else {
                printf(" [*] ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

Espetaculo *encontrarEspetaculoPorCodigo(int codigo) {
    for (int i = 0; i < TAMANHO_DA_LISTA_ESPETACULOS; i++) {
        if (espetaculosDisponiveis[i].codigo == codigo) {
            return &espetaculosDisponiveis[i];
        }
    }
    return NULL;
}

float calcularValorDesconto(float valorEspetaculo, float valorDesconto) {
    float desconto = (valorDesconto / 100) * (valorEspetaculo);
    return valorEspetaculo - desconto;
}