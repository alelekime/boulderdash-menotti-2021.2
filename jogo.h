#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap_draw.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro.h>
#include <allegro5/bitmap.h>
#include <allegro5/timer.h>
#include <allegro5/color.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>

#define KEY_SEEN 1
#define KEY_RELEASED 2
#define NIVEIS 10
#define LINHAS 22
#define COlUNAS 41
#define SPRITE 40

unsigned char key[ALLEGRO_KEY_MAX];

typedef enum
{
    borda_cinza,
    borda_roxa,
    borda_laranja,
    borda_rosa,
    borda_azul,
    terra_marrom,
    terra_rosa,
    terra_laranja,
    terra_roxa,
    terra_azul,
    terra_vermelha,
    rocha_cinza,
    rocha_rosa,
    rocha_laranja,
    rocha_azul,
    rocha_roxa,
    diamante,
    tijolo,
    rockford,
    vagalume,
    borboleta,
    amoeba,
    vazio,
    porta
} item;

typedef enum
{
    CIMA,
    BAIXO,
    DIREITA,
    ESQUERDA,
    NADA
} teclado;

typedef enum
{
    GANHOU,
    PERDEU,
    PAUSADO
} estado;

typedef struct
{
    int x;
    int y;
    int diamantes;
    int pontos;
    item item;
} personagem;

typedef struct
{
    ALLEGRO_BITMAP *image;
    item item;
    int alterado;
} itens;

typedef struct
{
    int diamantes;
    int amoebas;
    int vagalumes;
    int borboletas;
    int tempo;
    int nivel_atual;
} dados;

typedef struct
{
    item monstro_tipo;
    ALLEGRO_BITMAP *image;
    int x;
    int y;
    int perigo;

} monstro;

typedef struct
{
    monstro *vagalume;
    monstro *borboleta;
    monstro *amoeba;
} monstros;

itens **aloca_matriz(int linhas, int colunas);
void libera_matriz(itens **mapa);
void inicializa_nivel(dados *dados_jogo, itens **mapa_jogo, personagem *personagem_jogo, int nivel_atual);
void le_mapa(dados *dados_jogo, itens **mapa_jogo, char *mapa_nome);
void atualiza_mapa(itens **mapa_jogo);
ALLEGRO_BITMAP *encontra_imagem(item elemento);
item encontra_tipo(char tipo);
void encontra_objetos(dados *dados_jogo, monstros *monstros_jogo, itens **mapa_jogo);
