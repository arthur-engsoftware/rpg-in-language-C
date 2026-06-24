#ifndef DADOS_H
#define DADOS_H

typedef struct personagem {
    char nome[50];
    int hp;
    int hpmax;
    int ataque;
    int defesa;
    int xp;
    int ouro;
} personagem;

typedef struct inimigo {
    char nome_inimigo[50];
    int hp;
    int ataque;
    int defesa;
} inimigo;

#endif