#include "jogo.h"

void must_init(bool test, const char *description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}
void inicializa()
{

    must_init(al_init(), "allegro");
    must_init(al_init_image_addon(), "imagem");
    must_init(al_init_font_addon(), "fontes");
    must_init(al_init_ttf_addon(), "fontes_ttf");
    must_init(al_install_keyboard(), "teclado");
    must_init(al_install_audio(), "musica");
    must_init(al_init_acodec_addon(), "mausica_acodec");
    must_init(al_reserve_samples(1), "samples");
}