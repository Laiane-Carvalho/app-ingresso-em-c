#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "config.c"
#include "main.h"
#include "client.h"

char poltronasDisponiveis[] = "ABCDE";
char poltronasSelecionadas[100][3];
Espetaculo *espetaculos;
int moduloSelecionado;

void cadastrarEspetaculos();

void opcaoUsuario() {
    printf("### 1 - Cliente\n");
    printf("### 2 - Administrador\n");
    printf("### 3 - Fechar Programa\n");
}

int main() {

    poltronasSelecionadas[0][0] = 'A';
    poltronasSelecionadas[0][1] = '1';

    printf("Iniciando programa...\n");
    cadastrarEspetaculos();
    printf("\n\n");

    while (moduloSelecionado != 3) {
        opcaoUsuario();
        printf("Escolha modulo: ");
        scanf("%d", &moduloSelecionado);
        fpurge(stdin);
        printf("\n");
        switch (moduloSelecionado) {
            case 1: {
                inicializarCliente();
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                printf("Encerrando Aplicacao.....OK\n");
                break;
            }
            default: {
                printf("Opcao invalida!\n\n");
            }
        }
    }
    return 0;
}

static Espetaculo createEspetaculo(int codigo, char *nome, float valor) {
    Espetaculo espetaculo;
    espetaculo.codigo = codigo;
    strcpy(espetaculo.nome, nome);
    espetaculo.valor = valor;
    return espetaculo;
}

void cadastrarEspetaculos() {
    printf("  * Cadastrando dados...");
    espetaculos = (Espetaculo *) malloc(sizeof(Espetaculo) * 100);
    Espetaculo es0 = createEspetaculo(100, "Espetaculo das Bandeiras", 70.00f);
    espetaculos[0] = es0;

    Espetaculo es1 = createEspetaculo(102, "Sisne Negro", 138.00f);
    espetaculos[1] = es1;

    Espetaculo es2 = createEspetaculo(103, "Vento Levou", 25.50f);
    espetaculos[2] = es2;

    Espetaculo es3 = createEspetaculo(104, "Garota de Ipanema", 55.99f);
    espetaculos[3] = es3;

    Espetaculo es4 = createEspetaculo(105, "Fluido Urbano", 110.00f);
    espetaculos[4] = es4;
    printf("OK\n");
}

int quantidadeDeEspetaculo() {
    int quantidadeEspetaculo = 0;
    while (strcmp(espetaculos[quantidadeEspetaculo].nome, "") != 0) {
        quantidadeEspetaculo++;
    }
    return quantidadeEspetaculo;
}

void mostrarEspetaculosCadastrados() {
    int quantidadeEspetaculo = quantidadeDeEspetaculo();
    printf("\n- - - - - - - Espetaculos Disponiveis - - - - - - -\n");
    printf("#####################################################\n");
    printf("# C - Cancelar                                      #\n");
    printf("#####################################################\n");

    for (int i = 0; i < quantidadeEspetaculo; i++) {
        Espetaculo esp = espetaculos[i];
        printf("%d", esp.codigo);
        printf(" - ");
        printf("%s - ", esp.nome);
        printf("R$ %3.2f", esp.valor);
        printf("\n");
    }
}

Espetaculo *encontrarEspetaculoPorCodigo(int codigo) {
    int quantidadeEspetaculo = quantidadeDeEspetaculo();
    for (int i = 0; i < quantidadeEspetaculo; i++) {
        if (espetaculos[i].codigo == codigo) {
            return &espetaculos[i];
        }
    }
    return NULL;
}

Espetaculo *selecionarEspetaculo() {
    printf("Digite o codigo do espetaculo: ");
    char caracteresDigitado;
    scanf("%s", &caracteresDigitado);

    int codigo = atoi(&caracteresDigitado);
    fpurge(stdin);

    Espetaculo *esp = encontrarEspetaculoPorCodigo(codigo);
    if (esp != NULL) {
        printf("Confirma \"%s\" para ver?\n[ S = Sim\n| N = Nao\n[ C = Cancelar: ", &esp->nome);
        char confirm;
        fgets(&confirm, sizeof(char) + 1, stdin);
        if (confirm == 's' || confirm == 'S') {
            return encontrarEspetaculoPorCodigo(codigo);
        } else {
            if (confirm == 'n' || confirm == 'N') {
                return NULL;
            } else {
                if (confirm == 'c' || confirm == 'C') {
                    return -1;
                }
            }
        }
    } else {
        if (caracteresDigitado == 'c' || caracteresDigitado == 'C') {
            return -1;
        }
        printf("\n### ==> Codigo %d invalido <== ###\n", codigo);
        return NULL;
    }
}

int verificarSePoltronaEstaDisponivel(char *poltrona) {
    for (int i = 0; i < 100; i++) {
        if (strcmp(poltronasSelecionadas[i], poltrona) == 0) {
            return false;
        }
    }
    return true;
}

void mostrarPoltronasDisponiveis() {
    int tamanhoArrayPoltrona = strlen(poltronasDisponiveis);
    for (int i = 0; i < tamanhoArrayPoltrona; i++) {
        printf("\n");
        for (int y = 0; y < 10; y++) {
            //if (!verificarSePoltronaEstaDisponivel(poltronasDisponiveis[i])) {
            printf("[%c%d] ", poltronasDisponiveis[i], y + 1);
//            }else{
//                printf(" [*] ");
//            }
        }
        printf("\n");
    }
    printf("\n");
}

int verificarSeExistePoltrona(char *poltrona) {
    char *poltronaCopy;
    poltronaCopy = malloc(sizeof(char) * 2);
    strcpy(poltronaCopy, poltrona);
    int tamanhoArrayPoltrona = strlen(poltronasDisponiveis);
    for (int i = 0; i < tamanhoArrayPoltrona; i++) {
        if (toupper(poltronasDisponiveis[i]) == toupper(poltronaCopy[0])) {
            poltronaCopy[0] = '0';
            if (atoi(poltronaCopy) <= 10) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}

char *selecionarPoltroa() {
    char poltrona[3];
    do {
        printf("C - Cancelar\n");
        printf("Digite a poltrona: ");
        scanf("%s", &poltrona);
        fpurge(stdin);
        if (strcmp(poltrona, "c") == 0 || strcmp(poltrona, "c") == 0) {
            return NULL;
        }
        printf("\n");
        poltrona[0] = toupper(poltrona[0]);
        if (verificarSeExistePoltrona(poltrona)) {
            if (verificarSePoltronaEstaDisponivel(poltrona)) {
                return poltrona;
            } else {
                printf("Poltrona nao esta disponivel!\n");
            }
        } else {
            printf("Poltrona \"%s\" invalida!\n", poltrona);
        }
    } while (true);
}

void adicionarNovaPoltrona(char *poltrona){
    int posicao = 0;
    while (strcmp(poltronasSelecionadas[posicao++], "") != 0);
    strcpy(poltronasSelecionadas[posicao], poltrona);
    printf("");
}









/*


int main3() {







    return 0;
}

int main2() {


    Espetaculo *esp = NULL;
    do {
        mostrarEspetaculosCadastrados();
        esp = selecionarEspetaculo();
    } while (esp == NULL);
    return 0;
}

int quantidadeDeEspetaculo() {
    int quantidadeEspetaculo = 0;
    while (strcmp(espetaculos[quantidadeEspetaculo].nome, "") != 0) {
        quantidadeEspetaculo++;
    }
    return quantidadeEspetaculo;
}

void mostrarEspetaculosCadastrados() {
    int quantidadeEspetaculo = quantidadeDeEspetaculo();
    printf("\n- - - - - - - Espetaculos Disponiveis - - - - - - -\n");
    for (int i = 0; i < quantidadeEspetaculo; i++) {
        Espetaculo esp = espetaculos[i];
        printf("%d", esp.codigo);
        printf(" - ");
        printf("%s - ", esp.nome);
        printf("R$ %3.2f", esp.valor);
        printf("\n");
    }
}
















//
//char poltronasDisponiveis[] = "ABCDEFGHIJ";
//char poltronasSelecionadas[100][5];
//
//int main() {
//    mostrarPoltronasESelecionar();
//    selecionarUmaPoltronaDisponivel();
//    return 0;
//}
//
//void flush_in() {
//    int ch;
//    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {}
//}
//
//void perguntarPoltrola(char *poltrona){
//    printf("Digite o nome da poltrona: ");
//    scanf("%s", poltrona);
//    flush_in();
//    printf("\n");
//}
//
//void selecionarUmaPoltronaDisponivel() {
//    char *poltrona, confirmacao;
//    poltrona = malloc(2);
//
//    while (confirmacao != 's') {
////        if (confirmacao != '\0') {
//            perguntarPoltrola(poltrona);
//
//            printf("\nConfirma a poltrona %s? ", poltrona);
//            printf("\nS = Sim");
//            printf("\nN = Nao");
//            printf("\nC = Cancelar");
//            scanf("%c", &confirmacao);
//            flush_in();
//            if (confirmacao == 'S' || confirmacao == 's') {
//                strcpy(poltronasSelecionadas[0], poltrona);
//            }
//            if (confirmacao == 'n' || confirmacao == 'N') {
//                mostrarPoltronasESelecionar();
//            }
////        }
//    }
//    printf("fim...");
//}
//
//void mostrarPoltronasESelecionar() {
//    clearScreen();
//
//    int tamanhoArrayPoltrona = strlen(poltronasDisponiveis);
//    for (int i = 0; i < tamanhoArrayPoltrona; i++) {
//        printf("\n");
//        for (int y = 0; y < 10; y++) {
//            printf("[%c%d] ", poltronasDisponiveis[i], y + 1);
//        }
//        printf("\n");
//    }
//    printf("\n");
//}
//
//void clearScreen(){
//#ifdef _WIN32
//    system("cls");
//#else
//    system("clear");
//#endif
//}
//
////
////char poltronasDisponiveis[] = "ABCDEFGHIJ";
////char poltronasSelecionadas[100][5];
////
////int verificarSeJaEstaSelecinada(char *poltrona){
////    int tamanhoArrayPoltrona = strlen(poltronasDisponiveis);
////    for (int i = 0; i < tamanhoArrayPoltrona; i++) {
////        if (poltrona == poltronasDisponiveis[i]){
////            return 1;
////        }
////    }
////    return 0;
////}
////
////void mostrarPoltronasESelecionar(){
////    int tamanhoArrayPoltrona = strlen(poltronasDisponiveis);
////    for (int i = 0; i < tamanhoArrayPoltrona; i++) {
////        printf("\n");
////        for (int y = 0; y < 10; y++) {
////            printf("[%c%d] ", poltronasDisponiveis[i], y + 1);
////        }
////        printf("\n");
////    }
//////    char poltrona[2];
//////    selecionarPoltrona(poltrona);
//////    strcpy(poltronasSelecionadas[0], poltrona);
////}
////
////void selecionarPoltrona(char *poltrona){
////
////}
////
////void selecionarPoltrona(char *poltrona) {
////    printf("Digite o nome da poltrona:\n");
////    scanf("%s", poltrona);
////}
////
////int main() {
////
////
////
//////    mostrarPoltronasESelecionar();
//////
//////    char confirmacao = 'N';
//////    printf("Confirmar poltrona \"%s\"?", poltrona);
//////    do{
//////
//////    }while (poltrona != '\0' && poltrona[0] != '\0');
////
////    return 0;
////}
////
*/