#ifndef FUNCAO_H
#define FUNCAO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "dados.h"

personagem cadastrar_jogador() {
    personagem jogador;

    getchar(); // Consome o Enter do menu anterior
    printf("Digite o nome do seu personagem [MAX 50 CARACTERES]: \n");
    fgets(jogador.nome, 50, stdin);
    jogador.nome[strcspn(jogador.nome, "\n")] = '\0';

    jogador.ouro   = 0;
    jogador.xp     = 1;
    jogador.hp     = (rand() % 20) + 1;
    jogador.hpmax  = jogador.hp;
    jogador.ataque = (rand() % 10) + 1;
    jogador.defesa = (rand() % 7)  + 1;

    printf("\n======== Personagem Criado ========\n");
    printf("Nome:   %s\n", jogador.nome);
    printf("Vida:   %d\n", jogador.hp);
    printf("Forca:  %d\n", jogador.ataque);
    printf("Defesa: %d\n", jogador.defesa);
    printf("Ouro:   %d\n", jogador.ouro);
    printf("Nivel:  %d\n", jogador.xp);

    FILE *arquivo = fopen("save.txt", "w");
    if (arquivo == NULL) {
        printf("\n[Erro] Nao foi possivel criar o arquivo de save.\n");
        return jogador;
    }
    fprintf(arquivo, "%s\n", jogador.nome);
    fprintf(arquivo, "%d\n", jogador.hp);
    fprintf(arquivo, "%d\n", jogador.ataque);
    fprintf(arquivo, "%d\n", jogador.defesa);
    fprintf(arquivo, "%d\n", jogador.ouro);
    fprintf(arquivo, "%d\n", jogador.xp);
    fclose(arquivo);

    printf("\n[Sucesso] Personagem salvo em save.txt!\n");
    printf("\nPressione ENTER para continuar...");
    getchar();
    system("clear");

    return jogador; // ← retorna o jogador com todos os dados preenchidos
}

inimigo gerador_inimigos_aleatorios() {
    inimigo novo_inimigo;
    int cod_inimigo = (rand() % 3) + 1;

    if (cod_inimigo == 1) {
        strcpy(novo_inimigo.nome_inimigo, "Goblin");
        novo_inimigo.hp     = (rand() % 8)  + 8;
        novo_inimigo.ataque = (rand() % 4)  + 2;
        novo_inimigo.defesa = 1;
    }
    if (cod_inimigo == 2) {
        strcpy(novo_inimigo.nome_inimigo, "Zumbi");
        novo_inimigo.hp     = (rand() % 11) + 15;
        novo_inimigo.ataque = (rand() % 4)  + 3;
        novo_inimigo.defesa = 2;
    }
    if (cod_inimigo == 3) {
        strcpy(novo_inimigo.nome_inimigo, "Dragao Rei");
        novo_inimigo.hp     = (rand() % 21) + 40;
        novo_inimigo.ataque = (rand() % 6)  + 10;
        novo_inimigo.defesa = 5;
    }

    return novo_inimigo;
}

#endif