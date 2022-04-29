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

#define LARGURA 1930
#define ALTURA 1050

#define ESCALA 3
#define DISP_W (LARGURA * ESCALA)
#define DISP_H (ALTURA * ESCALA)

typedef struct fontes_allegro
{
    ALLEGRO_FONT *fonte_principal;
    ALLEGRO_FONT *fonte_secundaria;
    ALLEGRO_FONT *fonte;
} fontes_allegro;

typedef struct
{

    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_BITMAP *buffer;
    fontes_allegro *fontesAllegro;

} ponteiros_allegro;

void must_init(bool test, const char *description);
void inicializa_allegro();
void inicializa_timer(ponteiros_allegro *ponteiroAllegro);
void inicializa_queue(ponteiros_allegro *ponteiroAllegro);
void inicializa_display(ponteiros_allegro *ponteiroAllegro);
void inicializa_fontes(ponteiros_allegro *ponteiroAllegro);
ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h);
