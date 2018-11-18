#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "config.c"
#include "client.h"
#include "main.h"

void venderIngresso();

void mostrarOpcoesClient() {
    printf("\n");
    printf("1 - Comprar Ingresso\n");
    printf("2 - Cancelar Ingresso\n");
    printf("3 - Reimprimir Ingresso\n");
    printf("4 - Encerrar Cliente\n");
}

void inicializarCliente() {
    printf("############################################\n");
    printf("#                 Cliente                  #\n");
    printf("############################################\n");
    int opcao;
    while (opcao != 4) {
        mostrarOpcoesClient();
        printf("\nDigite uma opcao: ");
        scanf("%d", &opcao);
        fpurge(stdin);
        printf("\n");
        switch (opcao) {
            case 1: {
                venderIngresso();
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

void venderIngresso() {
    Espetaculo *esp = NULL;
    do {
        mostrarEspetaculosCadastrados();
        esp = selecionarEspetaculo();
        if (esp == -1) {
            break;
        }
    } while (esp == NULL);

    char *poltronaSelecionada;
    char *poltr_;
    poltr_ = malloc(sizeof(char) * 100);
    do {
        mostrarPoltronasDisponiveis();
        poltronaSelecionada = selecionarPoltroa();
        //strcpy(poltr_, poltronaSelecionada);
        if (poltronaSelecionada != NULL) {
            adicionarNovaPoltrona(poltronaSelecionada);
        }
    } while (poltronaSelecionada != NULL);
}