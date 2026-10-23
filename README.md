# RPG de Terminal em C

Jogo de RPG simples em modo texto, feito em C para praticar `struct`, ponteiros, modularizacao e arquivos.



## Como funciona

- Voce cria um personagem com atributos sorteados (vida, ataque e defesa).
- Em cada luta, escolhe entre **atacar**, **defender** (recebe metade do dano) ou **fugir**.
- Vencer da **XP** e **ouro**. Com XP suficiente, o personagem **sobe de nivel**.
- O **Dragao Rei** so aparece a partir do nivel 3.
- Na **estalagem**, voce gasta ouro para recuperar a vida.
- O jogo salva em `save.txt` depois de cada batalha e pode ser carregado pelo menu.

## Conceitos de C praticados

- `struct` e `typedef` (`personagem`, `inimigo`)
- Ponteiros para struct passados para funcoes (`->`)
- Biblioteca separada em `.h` e `.c`
- Leitura e escrita de arquivos (`fopen`, `fprintf`, `fscanf`)
- Numeros aleatorios (`rand`, `srand`)
- Leitura segura de entrada (`fgets` + `strtol`)

## Como compilar e executar

```bash
gcc main.c -o rpg
./rpg
```
