#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "funcao.h"

int main (void){
    int opcao; 
    setlocale(LC_ALL, "Portuguese");

    do
    {
       printf ("\n ========== RPG ==========\n"); 
       printf ("1. COMEÇAR NOVO JOGO\n"); 
       printf ("2. CARREGAR JOGO\n");
       printf ("3. Sair\n");

       scanf ("%d", &opcao);
       switch (opcao)
       {
       case 1:
       cadastrar_jogador ();
        
        break;
       
       default:
        break;
       }
    } while (opcao== -1);
    
    











    return 0;
}