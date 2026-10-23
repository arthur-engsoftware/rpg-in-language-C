#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RESULTADO_VITORIA 1
#define RESULTADO_FUGA 0
#define RESULTADO_DERROTA -1
#define CUSTO_ESTALAGEM 10
#define ARQUIVO_SAVE "save.txt"

typedef struct personagem {
    char nome[50];
    int hp;
    int hpmax;
    int ataque;
    int defesa;
    int xp;
    int nivel;
    int ouro;
} personagem;

typedef struct inimigo {
    char nome_inimigo[50];
    int hp;
    int ataque;
    int defesa;
    int xp_recompensa;
    int ouro_recompensa;
} inimigo;

int ler_int(const char *msg, int min, int max);
void ler_texto(const char *msg, char *dest, int tam);
int sortear(int min, int max);
int salvar_jogo(const personagem *jogador);
int carregar_jogo(personagem *jogador);
int combate(personagem *jogador, inimigo *inimigo_atual);
personagem cadastrar_jogador(void);
inimigo gerar_inimigo(int nivel_jogador);
void exibir_status(const personagem *jogador);
void menu_jogo(personagem *jogador);

int ler_int(const char *msg, int min, int max)
{
    char buf[32], *fim;
    long valor;

    for (;;) {
        printf("%s", msg);
        if (fgets(buf, sizeof buf, stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            exit(EXIT_FAILURE);
        }
        valor = strtol(buf, &fim, 10);
        while (*fim == ' ' || *fim == '\t' || *fim == '\n') fim++;

        if (fim == buf || *fim != '\0')
            printf("  Digite um numero inteiro.\n");
        else if (valor < min || valor > max)
            printf("  Digite um valor entre %d e %d.\n", min, max);
        else
            return (int)valor;
    }
}

void ler_texto(const char *msg, char *dest, int tam)
{
    printf("%s", msg);
    if (fgets(dest, tam, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    size_t len = strlen(dest);
    if (len > 0 && dest[len - 1] == '\n')
        dest[len - 1] = '\0';
    else {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int sortear(int min, int max)
{
    return min + rand() % (max - min + 1);
}

int salvar_jogo(const personagem *jogador)
{
    FILE *arquivo = fopen(ARQUIVO_SAVE, "w");
    if (arquivo == NULL) {
        printf("\n[ERRO] Nao foi possivel criar o arquivo de save.\n");
        return 0;
    }
    fprintf(arquivo, "%s\n", jogador->nome);
    fprintf(arquivo, "%d %d %d %d %d %d %d\n",
            jogador->hp, jogador->hpmax, jogador->ataque, jogador->defesa,
            jogador->xp, jogador->nivel, jogador->ouro);
    fclose(arquivo);
    return 1;
}

int carregar_jogo(personagem *jogador)
{
    FILE *arquivo = fopen(ARQUIVO_SAVE, "r");
    int lidos;

    if (arquivo == NULL)
        return 0;

    if (fgets(jogador->nome, sizeof jogador->nome, arquivo) == NULL) {
        fclose(arquivo);
        return 0;
    }
    jogador->nome[strcspn(jogador->nome, "\n")] = '\0';

    lidos = fscanf(arquivo, "%d %d %d %d %d %d %d",
                   &jogador->hp, &jogador->hpmax, &jogador->ataque,
                   &jogador->defesa, &jogador->xp, &jogador->nivel,
                   &jogador->ouro);
    fclose(arquivo);

    return lidos == 7;
}

static int calcular_dano(int ataque, int defesa)
{
    int dano = ataque - defesa;
    return (dano < 1) ? 1 : dano;
}

static void ganhar_xp(personagem *jogador, int xp)
{
    jogador->xp += xp;

    while (jogador->xp >= jogador->nivel * 20) {
        jogador->xp -= jogador->nivel * 20;
        jogador->nivel++;
        jogador->hpmax += 5;
        jogador->ataque += 1;
        jogador->defesa += 1;
        jogador->hp = jogador->hpmax;
        printf("[NIVEL] %s subiu para o nivel %d! (+5 HP, +1 ataque, +1 defesa)\n",
               jogador->nome, jogador->nivel);
    }
}

static int escolha(void)
{
    printf("\nO que voce quer fazer?\n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("3. Fugir\n");
    return ler_int("Opcao: ", 1, 3);
}

static void ataque(personagem *x, inimigo *p)
{
    int dano = calcular_dano(x->ataque, p->defesa);

    p->hp -= dano;
    if (p->hp < 0) p->hp = 0;

    printf("\n[COMBATE] %s causou %d de dano!\n", x->nome, dano);

    if (p->hp == 0)
        printf("[COMBATE] Parabens, voce matou o %s!\n", p->nome_inimigo);
    else
        printf("[COMBATE] O %s continua vivo com %d de vida.\n", p->nome_inimigo, p->hp);
}

int combate(personagem *jogador, inimigo *inimigo_atual)
{
    int opcao, dano;

    printf("\n[ALERTA] Um %s selvagem apareceu!\n", inimigo_atual->nome_inimigo);
    printf("HP inimigo: %d | Ataque: %d | Defesa: %d\n",
           inimigo_atual->hp, inimigo_atual->ataque, inimigo_atual->defesa);

    while (jogador->hp > 0 && inimigo_atual->hp > 0) {
        printf("\n--- %s: %d/%d HP ---\n", jogador->nome, jogador->hp, jogador->hpmax);
        opcao = escolha();

        if (opcao == 1) {
            ataque(jogador, inimigo_atual);
            if (inimigo_atual->hp <= 0) break;

            dano = calcular_dano(inimigo_atual->ataque, jogador->defesa);
            jogador->hp -= dano;
            if (jogador->hp < 0) jogador->hp = 0;
            printf("[COMBATE] O %s causou %d de dano em voce! HP restante: %d\n",
                   inimigo_atual->nome_inimigo, dano, jogador->hp);

        } else if (opcao == 2) {
            dano = calcular_dano(inimigo_atual->ataque, jogador->defesa) / 2;
            jogador->hp -= dano;
            if (jogador->hp < 0) jogador->hp = 0;
            printf("[COMBATE] Voce se defendeu! Recebeu apenas %d de dano. HP: %d\n",
                   dano, jogador->hp);

        } else {
            printf("[COMBATE] Voce fugiu da batalha!\n");
            return RESULTADO_FUGA;
        }
    }

    if (jogador->hp <= 0) {
        printf("\n[GAME OVER] Voce foi derrotado...\n");
        return RESULTADO_DERROTA;
    }

    printf("\n[VITORIA] Voce ganhou %d de XP e %d de ouro!\n",
           inimigo_atual->xp_recompensa, inimigo_atual->ouro_recompensa);
    jogador->ouro += inimigo_atual->ouro_recompensa;
    ganhar_xp(jogador, inimigo_atual->xp_recompensa);

    return RESULTADO_VITORIA;
}

void exibir_status(const personagem *jogador)
{
    printf("\n======== %s ========\n", jogador->nome);
    printf("Nivel:  %d (XP %d/%d)\n", jogador->nivel, jogador->xp, jogador->nivel * 20);
    printf("Vida:   %d/%d\n", jogador->hp, jogador->hpmax);
    printf("Ataque: %d\n", jogador->ataque);
    printf("Defesa: %d\n", jogador->defesa);
    printf("Ouro:   %d\n", jogador->ouro);
}

personagem cadastrar_jogador(void)
{
    personagem jogador;

    ler_texto("Digite o nome do seu personagem [MAX 49 CARACTERES]: ",
              jogador.nome, sizeof jogador.nome);
    if (jogador.nome[0] == '\0')
        strcpy(jogador.nome, "Heroi");

    jogador.nivel  = 1;
    jogador.xp     = 0;
    jogador.ouro   = 0;
    jogador.hpmax  = sortear(20, 30);
    jogador.hp     = jogador.hpmax;
    jogador.ataque = sortear(5, 8);
    jogador.defesa = sortear(2, 4);

    printf("\n[Personagem criado]");
    exibir_status(&jogador);

    return jogador;
}

inimigo gerar_inimigo(int nivel_jogador)
{
    inimigo novo;
    int maximo = (nivel_jogador >= 3) ? 3 : 2;
    int codigo = sortear(1, maximo);

    if (codigo == 1) {
        strcpy(novo.nome_inimigo, "Goblin");
        novo.hp              = sortear(8, 15);
        novo.ataque          = sortear(3, 5);
        novo.defesa          = 1;
        novo.xp_recompensa   = 10;
        novo.ouro_recompensa = sortear(5, 10);
    } else if (codigo == 2) {
        strcpy(novo.nome_inimigo, "Zumbi");
        novo.hp              = sortear(15, 25);
        novo.ataque          = sortear(4, 6);
        novo.defesa          = 2;
        novo.xp_recompensa   = 20;
        novo.ouro_recompensa = sortear(10, 20);
    } else {
        strcpy(novo.nome_inimigo, "Dragao Rei");
        novo.hp              = sortear(40, 60);
        novo.ataque          = sortear(8, 11);
        novo.defesa          = 4;
        novo.xp_recompensa   = 60;
        novo.ouro_recompensa = sortear(50, 100);
    }

    return novo;
}

void menu_jogo(personagem *jogador)
{
    int opcao, resultado;
    inimigo inimigo_atual;

    do {
        printf("\n---------- AVENTURA ----------\n");
        printf("1. Lutar\n");
        printf("2. Ver status\n");
        printf("3. Estalagem (%d ouro: recupera toda a vida)\n", CUSTO_ESTALAGEM);
        printf("4. Salvar e voltar ao menu principal\n");
        opcao = ler_int("Opcao: ", 1, 4);

        switch (opcao) {
            case 1:
                inimigo_atual = gerar_inimigo(jogador->nivel);
                resultado = combate(jogador, &inimigo_atual);

                if (resultado == RESULTADO_DERROTA) {
                    printf("Seu ultimo save continua salvo. Use 'Carregar jogo' para tentar de novo.\n");
                    return;
                }
                salvar_jogo(jogador);
                break;

            case 2:
                exibir_status(jogador);
                break;

            case 3:
                if (jogador->hp == jogador->hpmax)
                    printf("\nVoce ja esta com a vida cheia.\n");
                else if (jogador->ouro < CUSTO_ESTALAGEM)
                    printf("\nOuro insuficiente (precisa de %d).\n", CUSTO_ESTALAGEM);
                else {
                    jogador->ouro -= CUSTO_ESTALAGEM;
                    jogador->hp = jogador->hpmax;
                    printf("\nVoce descansou e recuperou toda a vida!\n");
                }
                break;

            case 4:
                if (salvar_jogo(jogador))
                    printf("\n[Sucesso] Jogo salvo em save.txt!\n");
                break;
        }
    } while (opcao != 4);
}

int main(void)
{
    int opcao;
    personagem jogador;

    srand((unsigned)time(NULL));

    do {
        printf("\n========== RPG ==========\n");
        printf("1. Comecar novo jogo\n");
        printf("2. Carregar jogo\n");
        printf("3. Sair\n");
        opcao = ler_int("Opcao: ", 1, 3);

        switch (opcao) {
            case 1:
                jogador = cadastrar_jogador();
                salvar_jogo(&jogador);
                menu_jogo(&jogador);
                break;

            case 2:
                if (carregar_jogo(&jogador)) {
                    printf("\n[Sucesso] Jogo carregado!");
                    exibir_status(&jogador);
                    menu_jogo(&jogador);
                } else {
                    printf("\n[ERRO] Nenhum save valido encontrado.\n");
                }
                break;

            case 3:
                printf("\nAte logo!\n");
                break;
        }
    } while (opcao != 3);

    return 0;
}
