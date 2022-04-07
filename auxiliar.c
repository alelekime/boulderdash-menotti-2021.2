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
    /**/
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ponteiroAllegro->disp = al_create_display(1280, 960);
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

/* ALOCA A MATRIZ DE VETORES DE VETORES */
int **aloca_matriz(int linhas, int colunas)
{
    int i;

    int **mapa = malloc(sizeof(int *) * (linhas));
    mapa[0] = malloc(sizeof(int) * (colunas * linhas));

    for (i = 0; i < linhas; i++)
        mapa[i] = mapa[0] + i * colunas;

    return mapa;
}

/* DESALOCA A MATRIZ */
void libera_matriz(unsigned char **tabulheiro)
{
    free(tabulheiro[0]);
    free(tabulheiro);
}