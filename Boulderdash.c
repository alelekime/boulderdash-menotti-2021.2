#include "jogo.h"
#include "utils.h"

int main(int argc, char const *argv[])
{
    inicializa_allegro();

    ponteiros_allegro *ponteiroAllegro = malloc(sizeof(ponteiros_allegro));

    inicializa_timer(ponteiroAllegro);
    inicializa_queue(ponteiroAllegro);
    inicializa_display(ponteiroAllegro);
    inicializa_fontes(ponteiroAllegro);
    estado *estado_jogo;
    dados *dados_jogo;
    itens **mapa_jogo;
    personagem *personagem_jogo;
    inicializa_jogo(estado_jogo, dados_jogo, mapa_jogo, personagem_jogo);

    int nivel_atual = 1;
    inicializa_nivel(dados_jogo, mapa_jogo, personagem_jogo, nivel_atual);
    return 0;
}