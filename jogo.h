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
#define SPRITE 16

unsigned char key[ALLEGRO_KEY_MAX];

typedef enum
{
    VAZIO,
    TIJOLO,
    TERRA,
    ROCHA,
    // BORDA,
    DIAMANTE,
    PERSONAGEM,
    PORTA
} item;

typedef struct
{
    ALLEGRO_BITMAP *image;
    item item;

} itens;

typedef struct
{
    int ganhou;
    int diamante;
    int pontos;
    int tempo;
} dados;

typedef struct
{
    itens **mapa_jogo;
    int nivel;
} niveis;

typedef struct
{
    niveis *niveis_jogo;
    dados *dados_jogo;
    int linhas;
    int colunas;
} jogo;

itens **aloca_matriz(int linhas, int colunas);
void libera_matriz(itens **mapa);

jogo *inicializa_jogo();
void inicializa_mapa(jogo *boulder_dash);
void le_mapa(jogo *boulder_dash, char *nome, int nivel);
void atualiza_mapa(jogo *boulder_dash, int nivel);