#ifndef COMBATE_H
#define COMBATE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dados.h"

int escolha() {
    int opcao;
    printf("\nO que voce quer fazer?\n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("3. Fugir\n");
    scanf("%d", &opcao);
    return opcao;
}

void ataque(personagem *x, inimigo *p) {
    int dano = x->ataque - p->defesa;
    if (dano < 0) dano = 0;

    p->hp -= dano;

    printf("\n[COMBATE] %s causou %d de dano!\n", x->nome, dano);

    if (p->hp <= 0) {
        printf("[COMBATE] Parabens, voce matou o %s!\n", p->nome_inimigo);
    } else {
        printf("[COMBATE] O %s continua vivo com %d de vida.\n", p->nome_inimigo, p->hp);
    }
}

void combate(personagem *jogador, inimigo *inimigo_atual) {
    printf("\n[ALERTA] Um %s selvagem apareceu!\n", inimigo_atual->nome_inimigo);
    printf("HP inimigo: %d | Ataque: %d | Defesa: %d\n",
           inimigo_atual->hp, inimigo_atual->ataque, inimigo_atual->defesa);

    while (jogador->hp > 0 && inimigo_atual->hp > 0) {
        int opcao = escolha();

        if (opcao == 1) {
            // Jogador ataca
            ataque(jogador, inimigo_atual);
            if (inimigo_atual->hp <= 0) break;

            // Inimigo contra-ataca
            int dano_inimigo = inimigo_atual->ataque - jogador->defesa;
            if (dano_inimigo < 0) dano_inimigo = 0;
            jogador->hp -= dano_inimigo;
            printf("[COMBATE] O %s causou %d de dano em voce! HP restante: %d\n",
                   inimigo_atual->nome_inimigo, dano_inimigo, jogador->hp);

        } else if (opcao == 2) {
            // Defender: reduz dano pela metade
            int dano_inimigo = (inimigo_atual->ataque - jogador->defesa) / 2;
            if (dano_inimigo < 0) dano_inimigo = 0;
            jogador->hp -= dano_inimigo;
            printf("[COMBATE] Voce se defendeu! Recebeu apenas %d de dano. HP: %d\n",
                   dano_inimigo, jogador->hp);

        } else if (opcao == 3) {
            printf("[COMBATE] Voce fugiu da batalha!\n");
            return;
        }
    }

    if (jogador->hp <= 0) {
        printf("\n[GAME OVER] Voce foi derrotado...\n");
    }
} 

#endif