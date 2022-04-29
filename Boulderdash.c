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
    monstros *monstros_jogo = malloc(sizeof(monstros));
    must_init(monstros_jogo, "struct monstros");
    estado *estado_jogo = malloc(sizeof(estado));
    must_init(estado_jogo, "struct estado");
    dados *dados_jogo = malloc(sizeof(dados_jogo));
    must_init(dados_jogo, "struct dados");
    itens **mapa_jogo = aloca_matriz(LINHAS, COlUNAS);
    must_init(estado_jogo, "matriz mapa");
    personagem *personagem_jogo = malloc(sizeof(personagem_jogo));
    must_init(estado_jogo, "struct personagem");
    int nivel_atual;
    for (int i = 1; i < 11; i++)
    {
        nivel_atual = i;
        inicializa_nivel(dados_jogo, mapa_jogo, personagem_jogo, nivel_atual);
        encontra_objetos(dados_jogo, monstros_jogo, mapa_jogo);
    }

    return 0;
}