#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>

#include "vars.c"
#include "main.h"
#include "cliente.h"

extern char *fgetsInput;

void comprarIngresso();

char *selecionarPoltrona();

void efetuarVenda(char *poltrona, Espetaculo *espetaculo);

bool hojeETerca();

void mostrarOpcoesClient() {
    printf("1 - Comprar Ingresso\n");
    printf("2 - Cancelar Ingresso\n");
    printf("3 - Reimprimir Ingresso\n");
    printf("4 - Encerrar Cliente\n");
}

void iniciarTelaDoCliente() {
    printf("############################################\n");
    printf("#                 Cliente                  #\n");
    printf("############################################\n");
    fgetsInput = malloc(3);
    unsigned int opcao;
    while (opcao != 4) {
        mostrarOpcoesClient();
        printf("Escolha funcao: ");
        fflush(stdin);
        fgets(fgetsInput, 3, stdin);
        opcao = atoi(fgetsInput);
        switch (opcao) {
            case 1: {
                comprarIngresso();
                break;
            }
            case 2: {
                break;
            }
            case 3: {
                break;
            }
            case 4: {
                break;
            }
            default: {
                printf("Opcao invalida!\n\n");
            }
        }
    }
}

Espectaculo_aux *selecionarEspetaculo() {
    Espectaculo_aux *aux = NULL;
    aux = malloc(sizeof(Espectaculo_aux) * 10);
    aux->codigoRetorno = -2;

    fgetsInput = malloc(6);
    printf("Digite o codigo do espetaculo: ");
    fflush(stdin);
    fgets(fgetsInput, 6, stdin);

    //Digitou C para Cancelar
    if (toupper(fgetsInput[0]) == 'C') {
        aux->codigoRetorno = -1;
        return aux;
    }

    int codigo = atoi(fgetsInput);
    Espetaculo *esp = encontrarEspetaculoPorCodigo(codigo);
    if (esp != NULL) {
        aux->codigoRetorno = 200;
        aux->espetaculo = esp;
        return aux;
    }
    printf("\n### ==> Codigo %d invalido <== ###\n", codigo);
    return aux;
}

void comprarIngresso() {
    Espectaculo_aux *esp = NULL;
    do {
        mostrarEspetaculosCadastrados();
        esp = selecionarEspetaculo();
        if (esp->codigoRetorno == -1) {
            break;
        }
    } while (esp->codigoRetorno != 200);

    if (esp->codigoRetorno == 200) {
        char *poltrona = selecionarPoltrona();
        if (poltrona != NULL) {
            efetuarVenda(poltrona, esp->espetaculo);
        }
    }
}

void efetuarVenda(char *poltrona, Espetaculo *espetaculo) {
    printf("############################################\n");
    printf("#            Finalizar Compra              #\n");
    printf("# C - Cancelar                             #\n");
    printf("############################################\n");

    int idade;
    float desconto = 0.0F;

    fgetsInput = malloc(20);
    printf("\nDigite sua idade: ");
    fflush(stdin);
    fgets(fgetsInput, 3, stdin);
    if (fgetsInput[0] == 'C') {
        return;
    }

    idade = atoi(fgetsInput);
    if (idade <= 12 || idade >= 60) {
        desconto = 50.0F;
        if (idade <= 12 && hojeETerca()) {
            printf("\nVoce e estudante da rede publica? ");
            printf("\n1 - Sim");
            printf("\n2 - Nao\n");
            if (fgetsInput[0] == 'C') {
                return;
            }
            if (fgetsInput[0] == '1') {
                desconto = 100.0F;
            }
        }
    } else {
        if (idade >= 13 && idade <= 17) {
            printf("\nVoce e estudante? ");
            printf("\n1 - Sim");
            printf("\n2 - Nao\n");
            fflush(stdin);
            fgets(fgetsInput, 2, stdin);
            if (fgetsInput[0] == 'C') {
                return;
            }
            if (fgetsInput[0] == '1') {
                desconto = 50.0F;
            }
        } else {
            if (idade >= 18 && idade <= 59) {
                printf("\nVoce e professor da rede publica? ");
                printf("\n1 - Sim");
                printf("\n2 - Nao\n");
                fflush(stdin);
                fgets(fgetsInput, 2, stdin);
                if (fgetsInput[0] == 'C') {
                    return;
                }
                if (fgetsInput[0] == '1') {
                    desconto = 50.0F;
                }
            }
        }
    }

    float valorAPagar = calcularValorDesconto(espetaculo->valor, desconto);
    printf("\nConfirma este dados para finalizar a compra?\n\n");
    printf("----------------------TICKET------------------------\n");
    printf("#   Esperaculo: %s\n", espetaculo->nome);
    printf("#   Horario: %s\n", espetaculo->horario);
    printf("#   Valor: R$ %4.2f\n", espetaculo->valor);
    printf("#   Desconto: R$ %4.2f\n", desconto);
    printf("#   Total a Pagar: R$ %4.2f\n", valorAPagar);
    printf("----------------------------------------------------\n");
    printf("\n1 - Sim, confirmo a compra.");
    printf("\n2 - Nao, quero cancelar.\n");
    fflush(stdin);
    fgets(fgetsInput, 2, stdin);
    printf("\n\n\n");

    do {
        if (fgetsInput[0] == 'C' || fgetsInput[0] == '2') {
            return;
        } else {
            if (fgetsInput[0] == '1') {
                adicionarVenda(espetaculo, poltrona, valorAPagar, idade);
                return;
            }
        }
    } while (true);
}

bool hojeETerca() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    return timeinfo->tm_wday == 2 ? true : false;
}

char *selecionarPoltrona() {
    fgetsInput = malloc(3);
    do {
        mostrarPoltronasDisponiveis();

        printf("Digite a Poltrona: ");
        fflush(stdin);
        fgets(fgetsInput, 3, stdin);

        fgetsInput[0] = toupper(fgetsInput[0]);

        //Digitou C para Cancelar
        if (fgetsInput[0] == 'C' && fgetsInput[1] == '\0') {
            break;
        }
        if (verificarSeExistePoltrona(fgetsInput)) {
            if (verificarSePoltronaEstaDisponivel(fgetsInput)) {
                return fgetsInput;
            } else {
                printf("Poltrona \"%s\" nao esta disponivel!\n", fgetsInput);
                fgetsInput = "";
            }
        } else {
            printf("Poltrona \"%s\" nao existe!\n", fgetsInput);
            fgetsInput = "";
        }
    } while (strcmp(fgetsInput, "") == 0);
    return NULL;
}