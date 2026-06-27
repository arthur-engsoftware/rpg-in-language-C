# RPG em C 🗡️

Um RPG de texto simples em **linguagem C**, onde o jogador cria um personagem com atributos sorteados aleatoriamente e enfrenta inimigos em um combate por turnos.

## 📋 Sobre o projeto

Ao iniciar um novo jogo, o jogador digita o nome do seu personagem e recebe atributos aleatórios (vida, ataque e defesa). Em seguida, um inimigo é sorteado entre três tipos — **Goblin**, **Zumbi** ou **Dragão Rei**, cada um com vida, ataque e defesa próprios — e a batalha começa.

A cada turno, o jogador escolhe entre:

- **Atacar** — causa dano ao inimigo (ataque do jogador − defesa do inimigo)
- **Defender** — recebe apenas metade do dano do contra-ataque do inimigo
- **Fugir** — encerra o combate imediatamente

O combate continua até o jogador ou o inimigo perderem todo o HP.

## 🗂️ Estrutura de arquivos

| Arquivo | Responsabilidade |
|---|---|
| `dados.h` | Define as `structs` `personagem` (nome, hp, hpmax, ataque, defesa, xp, ouro) e `inimigo` (nome, hp, ataque, defesa) |
| `funcao.h` | Função `cadastrar_jogador()`, que cria o personagem com stats aleatórios e salva em `save.txt`; e `gerador_inimigos_aleatorios()`, que sorteia um dos três inimigos |
| `combate.h` | Lógica do combate por turnos: menu de ações, cálculo de dano e condições de vitória/derrota |
| `main.c` | Menu principal do jogo (novo jogo / carregar jogo / sair) |
| `save.txt` | Arquivo onde os dados do personagem são salvos ao ser criado |

## ⚙️ Conceitos de C aplicados

- **Structs**: `personagem` e `inimigo` agrupam os atributos de cada entidade do jogo
- **Ponteiros para structs**: `combate()` e `ataque()` recebem `personagem *` e `inimigo *` para alterar o HP original durante a batalha, em vez de trabalhar com cópias
- **`rand()` e `srand()`**: usados para sortear os atributos do personagem e qual inimigo aparece
- **Manipulação de arquivos (`fopen`/`fprintf`)**: persiste os dados do personagem em `save.txt`
- **Funções definidas em headers**: diferente do projeto [7X0gameinlanguageC](https://github.com/arthur-engsoftware/7X0gameinlanguageC), aqui as funções são implementadas diretamente nos arquivos `.h` (protegidas por `#ifndef`/`#define`), então só é necessário compilar o `main.c`

## ▶️ Como compilar e rodar

```bash
gcc main.c -o jogo
./jogo
```

## 🎮 Como jogar

1. Execute o programa e escolha **1** para começar um novo jogo.
2. Digite o nome do seu personagem.
3. Veja os atributos sorteados (vida, ataque, defesa) e o inimigo que apareceu.
4. A cada turno, escolha **1** (Atacar), **2** (Defender) ou **3** (Fugir).
5. O combate termina quando você ou o inimigo perderem toda a vida — ou quando você fugir.

## 🚧 Melhorias futuras

- [ ] Implementar a opção "Carregar jogo" (hoje exibe apenas um aviso de "não implementada", apesar do personagem já ser salvo em `save.txt`)
- [ ] Validar entradas não-numéricas no `scanf` do menu e do combate
- [ ] Adicionar sistema de XP e level up após vencer um inimigo
- [ ] Adicionar mais tipos de inimigos e itens/equipamentos

## 👤 Autor

Projeto desenvolvido por Arthur José como exercício de structs, ponteiros e organização de jogos em C.
