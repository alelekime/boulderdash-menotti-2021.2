#include "jogo.h"

int main()
{   inicializa();
    ponteiros_allegro *ponteiroAllegro = malloc(sizeof(ponteiros_allegro));

    ponteiroAllegro->timer = al_create_timer(1.0 / 30.0);
    must_init(ponteiroAllegro->timer, "timer");

    ponteiroAllegro->queue = al_create_event_queue();
    must_init(ponteiroAllegro->queue, "queue");

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ponteiroAllegro->disp = al_create_display(640, 480);
    must_init(ponteiroAllegro->disp, "display");

    ponteiroAllegro->font = al_create_builtin_font();
    must_init(ponteiroAllegro->font, "font");

    al_register_event_source(ponteiroAllegro->queue, al_get_keyboard_event_source());
    al_register_event_source(ponteiroAllegro->queue, al_get_display_event_source(ponteiroAllegro->disp));
    al_register_event_source(ponteiroAllegro->queue, al_get_timer_event_source(ponteiroAllegro->timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    float x, y;
    x = 100;
    y = 100;

#define KEY_SEEN 1
#define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
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
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(ponteiroAllegro->font, al_map_rgb(255, 255, 255), 0, 0, 0, "X: %.1f Y: %.1f", x, y);
            al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));

            al_flip_display();

            redraw = false;
        }
    }

    al_destroy_font(ponteiroAllegro->font);
    al_destroy_display(ponteiroAllegro->disp);
    al_destroy_timer(ponteiroAllegro->timer);
    al_destroy_event_queue(ponteiroAllegro->queue);

    return 0;
}