CFLAGS = -g -Wall `pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 allegro_primitives-5 allegro_audio-5 allegro_acodec-5  allegro_ttf-5  --libs --cflags`

object = boulderdash.c utils.c jogo.c

all:  $(object)
	gcc $(object) -o BoulderDash $(CFLAGS)

clean:
	rm -f *.o

purge:	clean
	rm -f BoulderDash


