#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dados.h"
#include <time.h> 

void cadastrar_jogador (){

    
    personagem jogador; 
    getchar(); // Consome o Enter do menu anterior

    printf ("Digite o nome do seu personagem[MAX 50 CARACTERES]: \n");
    fgets (jogador.nome_personagem, 50, stdin);
     int c;
    while ((c = getchar()) != '\n' && c != EOF && c != '\0');


    jogador.nome_personagem[strcspn(jogador.nome_personagem, "\n")] = '\0';
    
    // Inicia o gerador de numero aleatório 
    srand(time(NULL));

    jogador.ouro = 0;
    jogador.xp = 1; 
    
    jogador.hp = (rand() % (20 - 1 + 1) + 1);
    jogador.ataque = (rand() % (10 - 1 + 1) + 1);
    jogador.defesa = (rand() % (7 - 1 + 1) + 1);

    printf("\n======== Personagem Criado ======== \n");
    printf("Nome: %s\n", jogador.nome_personagem);
    printf("Vida: %d\n", jogador.hp);
    printf("Forca: %d\n", jogador.ataque);
    printf("Defesa: %d\n", jogador.defesa);
    printf("Ouro: %d\n", jogador.ouro);
    printf("Nivel: %d\n", jogador.xp);

    // ALTERAÇÃO 1: Mudança do nome para .txt e modo para "w" (escrita de texto)
    FILE *arquivo = fopen("save.txt", "w");
    if (arquivo == NULL) {
        printf("\n[Erro] Nao foi possivel criar o arquivo de save.\n");
        return; 
    }

    fprintf(arquivo, "%d\n", jogador.nome_personagem);
    fprintf(arquivo, "%d\n", jogador.hp);
    fprintf(arquivo, "%d\n", jogador.ataque);
    fprintf(arquivo, "%d\n", jogador.defesa);
    fprintf(arquivo, "%d\n", jogador.ouro);
    fprintf(arquivo, "%d\n", jogador.xp);

    fclose(arquivo); // Fecha e garante a gravação permanente

    printf("\n[Sucesso] Personagem gravado permanentemente no arquivo save.txt!\n");

    printf("\nPressione ENTER para continuar...");
    getchar(); // Aguarda o jogador apertar Enter antes de sumir com os dados

      
    system("clear"); 
    
}