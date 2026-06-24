#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dados.h"
#include "funcao.h"
#include "combate.h"

int main(void) {
    int opcao;

    srand(time(NULL));

    do {
        printf("\n========== RPG ==========\n");
        printf("1. Comecar novo jogo\n");
        printf("2. Carregar jogo\n");
        printf("3. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                personagem jogador = cadastrar_jogador(); // ← recebe o jogador com HP correto

                inimigo inimigo_atual = gerador_inimigos_aleatorios();
                combate(&jogador, &inimigo_atual);
                break;
            }
            case 2:
                printf("\n[INFO] Funcao de carregar jogo ainda nao implementada.\n");
                break;
            case 3:
                printf("\nAte logo!\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (opcao != 3);

    return 0;
}