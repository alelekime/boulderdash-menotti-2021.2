#include "auxiliar.h"

/*TESTES*/
void must_init(bool test, const char *description)
{

    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

/*INICIALIZACAO*/
void inicializa_allegro()
{
    /*CONFIGURACOES ESSENCIAIS DO ALLEGRO*/
    must_init(al_init(), "allegro");
    /*INICIA CONFIGURACOES DE IMAGENS*/
    must_init(al_init_image_addon(), "Imagem");
    /*INICIA CONFIGURACOES DE FONTES*/
    must_init(al_init_font_addon(), "Fontes");
    /*INICIA CONFIGURACOES DE FONTES PERSONALIZADAS*/
    must_init(al_init_ttf_addon(), "Fontes_ttf");
    /*INICIA CONFIGURACOES DE INPUT POR TECLADO*/
    must_init(al_install_keyboard(), "Teclado");
    /*INICIA CONFIGURACOES DE SONS/IMAGENS*/
    must_init(al_install_audio(), "Musica");
    /*INICIA CONFIGURACOES DE SONS/IMAGENS*/
    must_init(al_init_acodec_addon(), "Musica_acodec");
    /*INICIA CONFIGURACOES DE SONS/IMAGENS*/
    must_init(al_reserve_samples(1), "Samples");
}

/*TIMER*/
void inicializa_timer(ponteiros_allegro *ponteiroAllegro)
{
    ponteiroAllegro->timer = al_create_timer(1.0 / 60.0);
    must_init(ponteiroAllegro->timer, "timer");
}

/*QUEUE*/
void inicializa_queue(ponteiros_allegro *ponteiroAllegro)
{
    ponteiroAllegro->queue = al_create_event_queue();
    must_init(ponteiroAllegro->queue, "queue");
}

/*DISPLAY*/
void inicializa_display(ponteiros_allegro *ponteiroAllegro)
{
    /*SCALED DISPLAY*/
    ponteiroAllegro->buffer = al_create_bitmap(LARGURA, ALTURA);
    must_init(ponteiroAllegro->buffer, "bitmap buffer");
    /**/
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ponteiroAllegro->disp = al_create_display(LARGURA, ALTURA);
    must_init(ponteiroAllegro->disp, "display");
}

/*FONTES*/
void inicializa_fontes(ponteiros_allegro *ponteiroAllegro)
{
    /*ALOCACAO DINAMICA DE UM STRUCT PARA GERENCIAR AS FONTES */
    ponteiroAllegro->fontesAllegro = malloc(sizeof(fontes_allegro));
    /*PONTEIRO USADO PARA A FONTE*/
    ponteiroAllegro->fontesAllegro->fonte_principal = al_load_font("resouces/fonte/BoulderDash.ttf", 20, 0);
    must_init(ponteiroAllegro->fontesAllegro->fonte_principal, "Fonte Principal ");

    /*PONTEIRO USADO PARA A FONTE*/
    ponteiroAllegro->fontesAllegro->fonte_secundaria = al_load_font("resouces/fonte/BoulderDash.ttf", 70, 0);
    must_init(ponteiroAllegro->fontesAllegro->fonte_secundaria, "Fonte Secundaria");

    /*INICIA CONFIGURACOES DE FONTES*/
    ponteiroAllegro->fontesAllegro->fonte = al_create_builtin_font();
    must_init(ponteiroAllegro->fontesAllegro->fonte, "Fontes");
}

ALLEGRO_BITMAP *load_bitmap_at_size(const char *filename, int w, int h)
{
    ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;

    // 1. create a temporary bitmap of size we want
    resized_bmp = al_create_bitmap(w, h);
    if (!resized_bmp)
        return NULL;

    // 2. load the bitmap at the original size
    loaded_bmp = al_load_bitmap(filename);
    if (!loaded_bmp)
    {
        al_destroy_bitmap(resized_bmp);
        return NULL;
    }

    // 3. set the target bitmap to the resized bmp
    prev_target = al_get_target_bitmap();
    al_set_target_bitmap(resized_bmp);

    // 4. copy the loaded bitmap to the resized bmp
    al_draw_scaled_bitmap(loaded_bmp,
                          0, 0,                             // source origin
                          al_get_bitmap_width(loaded_bmp),  // source width
                          al_get_bitmap_height(loaded_bmp), // source height
                          0, 0,                             // target origin
                          w, h,                             // target dimensions
                          0                                 // flags
    );

    // 5. restore the previous target and clean up
    al_set_target_bitmap(prev_target);
    al_destroy_bitmap(loaded_bmp);

    return resized_bmp;
}