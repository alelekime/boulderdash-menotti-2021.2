#include "jogo.h"
#include "auxiliar.h"

int main()
{
    inicializa_allegro();

    ponteiros_allegro *ponteiroAllegro = malloc(sizeof(ponteiros_allegro));

    inicializa_timer(ponteiroAllegro);
    inicializa_queue(ponteiroAllegro);
    inicializa_display(ponteiroAllegro);
    inicializa_fontes(ponteiroAllegro);

    al_register_event_source(ponteiroAllegro->queue, al_get_keyboard_event_source());
    al_register_event_source(ponteiroAllegro->queue, al_get_display_event_source(ponteiroAllegro->disp));
    al_register_event_source(ponteiroAllegro->queue, al_get_timer_event_source(ponteiroAllegro->timer));

    ALLEGRO_BITMAP *personagem = al_load_bitmap("resouces/texturas/diamante.png");
    if (!personagem)
    {
        printf("couldn't load personagem\n");
        return 1;
    }
    jogo *boulder_dash = inicializa_jogo();
    inicializa_mapa(boulder_dash);

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;
    memset(key, 0, sizeof(key));

    al_start_timer(ponteiroAllegro->timer);

    while (1)
    {
        al_wait_for_event(ponteiroAllegro->queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            if (key[ALLEGRO_KEY_UP])
                y--;
            if (key[ALLEGRO_KEY_DOWN])
                y++;
            if (key[ALLEGRO_KEY_LEFT])
                x--;
            if (key[ALLEGRO_KEY_RIGHT])
                x++;

            if (key[ALLEGRO_KEY_ESCAPE])
                done = true;

            for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
                key[i] &= KEY_SEEN;

            redraw = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
            break;
        case ALLEGRO_EVENT_KEY_UP:
            key[event.keyboard.keycode] &= KEY_RELEASED;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(ponteiroAllegro->queue))
        {
            al_set_target_bitmap(ponteiroAllegro->buffer);

            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(ponteiroAllegro->fontesAllegro->fonte_principal, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
            atualiza_mapa(boulder_dash->niveis_jogo[0].mapa_jogo, 0,boulder_dash->linhas, boulder_dash->colunas );
            al_set_target_backbuffer(ponteiroAllegro->disp);
            al_draw_scaled_bitmap(ponteiroAllegro->buffer, 0, 0, LARGURA, ALTURA, 0, 0, DISP_W, DISP_H, 0);

            al_flip_display();

            redraw = false;
        }
    }

    // al_destroy_font(ponteiroAllegro->font);
    // al_destroy_display(ponteiroAllegro->disp);
    // al_destroy_timer(ponteiroAllegro->timer);
    // al_destroy_event_queue(ponteiroAllegro->queue);

    return 0;
}
