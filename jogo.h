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

typedef struct
{

    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_DISPLAY *disp;
    ALLEGRO_FONT *font;

} ponteiros_allegro;

void must_init(bool test, const char *description);
void inicializa();