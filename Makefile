CFLAGS = -g -Wall `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5  allegro_ttf-5  --libs --cflags`

object = jogo.c main.c auxiliar.c

all:  $(object)
	gcc -g $(object) -o BoulderDash $(CFLAGS)

clean:
	rm -f *.o BoulderDash

purge:	BoulderDash
	rm -f BoulderDash

