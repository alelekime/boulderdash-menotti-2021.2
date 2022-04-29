
#include "jogo.h"
#include "utils.h"

/* ALOCA A MATRIZ DE VETORES DE VETORES */
itens **aloca_matriz(int linhas, int colunas)
{
    int i;

    itens **mapa = malloc(sizeof(itens *) * (linhas));
    mapa[0] = malloc(sizeof(itens) * (colunas * linhas));

    for (i = 1; i < linhas; i++)
        mapa[i] = mapa[0] + i * colunas;

    return mapa;
}

/* DESALOCA A MATRIZ */
void libera_matriz(itens **mapa)
{
    free(mapa[0]);
    free(mapa);
}

void inicializa_nivel(dados *dados_jogo, itens **mapa_jogo, personagem *personagem_jogo, int nivel_atual)
{
    char *mapa_nome = malloc(sizeof(char) * 512);
    sprintf(mapa_nome, "resources/mapas/mapa%d.txt", nivel_atual);
    fprintf(stderr, "%s\n", mapa_nome);
    le_mapa(dados_jogo, mapa_jogo, mapa_nome);
}
void le_mapa(dados *dados_jogo, itens **mapa_jogo, char *mapa_nome)
{
    int i, j;
    char a;
    FILE *mapa_arquivo = fopen(mapa_nome, "r");
    must_init(mapa_arquivo, "arquivo mapa");
    fscanf(mapa_arquivo, "%d", &dados_jogo->tempo);

    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COlUNAS; j++)
        {
            a = fgetc(mapa_arquivo);
            if (a == '\n')
                continue;

            mapa_jogo[i][j].item = encontra_tipo(a);
            mapa_jogo[i][j].image = encontra_imagem(mapa_jogo[i][j].item);
            mapa_jogo[i][j].alterado = 1;
            fprintf(stderr,"%c", a);
        }
        fprintf(stderr, "\n");
    }
    fclose(mapa_arquivo);
}
void atualiza_mapa(itens **mapa_jogo)
{
    int i, j;
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COlUNAS; j++)
        {
            al_draw_bitmap(mapa_jogo[i][j].image, i, j, 0);
        }
    }
}
ALLEGRO_BITMAP *encontra_imagem(item elemento)
{
    ALLEGRO_BITMAP *imagem;

    switch (elemento)
    {
    case borda_cinza:
        imagem = load_bitmap_at_size("resources/texturas/borda_cinza.png", SPRITE, SPRITE);
        must_init(imagem, "borda_cinza");
        return imagem;
    case borda_roxa:
        imagem = load_bitmap_at_size("resources/texturas/borda_roxa.png", SPRITE, SPRITE);
        must_init(imagem, "borda_roxa");
        return imagem;
    case borda_laranja:

        imagem = load_bitmap_at_size("resources/texturas/borda_laranja.png", SPRITE, SPRITE);
        must_init(imagem, "borda_laranja");
        return imagem;
    case borda_rosa:

        imagem = load_bitmap_at_size("resources/texturas/borda_rosa.png", SPRITE, SPRITE);
        must_init(imagem, "borda_rosa");
        return imagem;
    case borda_azul:

        imagem = load_bitmap_at_size("resources/texturas/borda_azul.png", SPRITE, SPRITE);
        must_init(imagem, "borda_azul");
        return imagem;
    case terra_marrom:

        imagem = load_bitmap_at_size("resources/texturas/terra_marrom.png", SPRITE, SPRITE);
        must_init(imagem, "terra_marrom");
        return imagem;
    case terra_rosa:

        imagem = load_bitmap_at_size("resources/texturas/terra_rosa.png", SPRITE, SPRITE);
        must_init(imagem, "terra_rosa");
        return imagem;
    case terra_laranja:

        imagem = load_bitmap_at_size("resources/texturas/terra_laranja.png", SPRITE, SPRITE);
        must_init(imagem, "terra_laranja");
        return imagem;
    case terra_roxa:

        imagem = load_bitmap_at_size("resources/texturas/terra_roxa.png", SPRITE, SPRITE);
        must_init(imagem, "terra_roxa");
        return imagem;
    case terra_azul:

        imagem = load_bitmap_at_size("resources/texturas/terra_azul.png", SPRITE, SPRITE);
        must_init(imagem, "terra_azul");
        return imagem;
    case terra_vermelha:

        imagem = load_bitmap_at_size("resources/texturas/terra_vermelha.png", SPRITE, SPRITE);
        must_init(imagem, "terra_vermelha");
        return imagem;
    case rocha_cinza:

        imagem = load_bitmap_at_size("resources/texturas/rocha_cinza.png", SPRITE, SPRITE);
        must_init(imagem, "rocha_cinza");
        return imagem;
    case rocha_rosa:

        imagem = load_bitmap_at_size("resources/texturas/rocha_rosa.png", SPRITE, SPRITE);
        must_init(imagem, "rocha_rosa");
        return imagem;
    case rocha_laranja:

        imagem = load_bitmap_at_size("resources/texturas/rocha_laranja.png", SPRITE, SPRITE);
        must_init(imagem, "rocha_laranja");
        return imagem;
    case rocha_azul:

        imagem = load_bitmap_at_size("resources/texturas/rocha_azul.png", SPRITE, SPRITE);
        must_init(imagem, "rocha_azul");
        return imagem;
    case rocha_roxa:

        imagem = load_bitmap_at_size("resources/texturas/rocha_roxa.png", SPRITE, SPRITE);
        must_init(imagem, "rocha_roxa");
        return imagem;
    case diamante:

        imagem = load_bitmap_at_size("resources/texturas/diamante.png", SPRITE, SPRITE);
        must_init(imagem, "diamante");
        return imagem;
    case tijolo:

        imagem = load_bitmap_at_size("resources/texturas/tijolo.png", SPRITE, SPRITE);
        must_init(imagem, "tijolo");
        return imagem;
    case rockford:

        imagem = load_bitmap_at_size("resources/texturas/rockford.png", SPRITE, SPRITE);
        must_init(imagem, "rockford");
        return imagem;
    case vagalume:

        imagem = load_bitmap_at_size("resources/texturas/vagalume.png", SPRITE, SPRITE);
        must_init(imagem, "vagalume");
        return imagem;
    case borboleta:

        imagem = load_bitmap_at_size("resources/texturas/borboleta.png", SPRITE, SPRITE);
        must_init(imagem, "borboleta");
        return imagem;
    case amoeba:

        imagem = load_bitmap_at_size("resources/texturas/amoeba.png", SPRITE, SPRITE);
        must_init(imagem, "amoeba");
        return imagem;
    case vazio:

        imagem = load_bitmap_at_size("resources/texturas/vazio.png", SPRITE, SPRITE);
        must_init(imagem, "vazio");
        return imagem;
    case porta:

        imagem = load_bitmap_at_size("resources/texturas/vazio.png", SPRITE, SPRITE);
        must_init(imagem, "vazio");
        return imagem;

    default:
        imagem = load_bitmap_at_size("resources/texturas/vazio.png", SPRITE, SPRITE);
        must_init(imagem, "vazio");
        return imagem;
        break;
    }
}
item encontra_tipo(char tipo)
{
    switch (tipo)
    {
    /*BORDA*/
    case '#':
        return borda_cinza;
    case '$':
        return borda_roxa;
    case '(':
        return borda_rosa;
    case ')':
        return borda_laranja;
    case '/':
        return borda_azul;
    /*ROCHA*/
    case 'o':
        return rocha_cinza;
    case 'r':
        return rocha_roxa;
    case 'l':
        return rocha_laranja;
    case 'n':
        return rocha_rosa;
    case 'a':
        return rocha_azul;
    /*TERRA*/
    case '.':
        return terra_marrom;
    case ',':
        return terra_rosa;
    case ';':
        return terra_laranja;
    case 'p':
        return terra_roxa;
    case '!':
        return terra_azul;
    case '-':
        return terra_vermelha;
    /*COMUM*/
    case '*':
        return diamante;
    case '@':
        return rockford;
    case '|':
        return tijolo;
    case '&':
        return borboleta;
    case '%':
        return vagalume;
    case '?':
        return amoeba;
    case ' ':
        return vazio;
    case 's':
        return porta;
    default:
        return vazio;
    }
}

void encontra_objetos(dados *dados_jogo, monstros *monstros_jogo, itens **mapa_jogo)
{
    dados_jogo->amoebas = 0;
    dados_jogo->vagalumes = 0;
    dados_jogo->borboletas = 0;
    dados_jogo->diamantes = 0;

    int i, j;
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COlUNAS; j++)
        {
            switch (mapa_jogo[i][j].item)
            {
            case vagalume:
                dados_jogo->vagalumes++;
                break;
            case amoeba:
                dados_jogo->amoebas++;
                break;
            case diamante:
                dados_jogo->diamantes++;
                break;
            case borboleta:
                dados_jogo->borboletas++;
                break;

            default:
                continue;
            }
        }
    }
    monstros_jogo->vagalume = malloc(sizeof(monstro) * dados_jogo->vagalumes);
    monstros_jogo->amoeba = malloc(sizeof(monstro) * dados_jogo->amoebas);
    monstros_jogo->borboleta = malloc(sizeof(monstro) * dados_jogo->borboletas);
    fprintf(stderr, "vagalumes = %d\n", dados_jogo->vagalumes);
    fprintf(stderr, "amoebas = %d\n", dados_jogo->amoebas);
    fprintf(stderr, "diamantes = %d\n", dados_jogo->diamantes);
    fprintf(stderr, "borboletas = %d\n", dados_jogo->borboletas);
}