#include "jogo.h"
#include "auxiliar.h"

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

/*ALOCA OS PONTEIROS PARA AS STRUCT DO JOGO*/
jogo *inicializa_jogo()
{
    int i;
    jogo *boulder_dash = malloc(sizeof(jogo));
    boulder_dash->dados_jogo = malloc(sizeof(dados));
    boulder_dash->niveis_jogo = malloc(sizeof(niveis) * NIVEIS);
    for (i = 0; i < NIVEIS; i++)
    {
        boulder_dash->niveis_jogo[i].personagem_jogo = malloc(sizeof(personagem));
    }

    return boulder_dash;
}

void inicializa_mapa(jogo *boulder_dash)
{
    int k = 0;
    DIR *diretorio_mapas;
    struct dirent *dir;
    char *aux = malloc(sizeof(char) * 512);

    diretorio_mapas = opendir("resouces/mapas");
    if (diretorio_mapas)
    {
        while ((dir = readdir(diretorio_mapas)) != NULL)
        {
            if (!strcmp(dir->d_name, "."))
                continue;
            if (!strcmp(dir->d_name, ".."))
                continue;
            boulder_dash->niveis_jogo->nivel = k;
            printf("boulder_dash->niveis_jogo->nivel  :>> %d\n", boulder_dash->niveis_jogo->nivel);
            fprintf(stderr, "%s\n", dir->d_name);
            sprintf(aux, "resouces/mapas/%s", dir->d_name);
            le_mapa(boulder_dash, aux, k);
            k++;
        }
        closedir(diretorio_mapas);
    }
}

void altera_posicao_personagem(personagem *personagem_jogo, int i, int j)
{
    personagem_jogo->x = i;
    personagem_jogo->y = j;
}

void le_mapa(jogo *boulder_dash, char *nome, int nivel)
{
    int i, j;
    char a;
    char *aux = malloc(sizeof(char) * 512);
    FILE *mapa = fopen(nome, "r");
    if (mapa == NULL)
    {
        perror("Error: ");
    }
    fgets(aux, 512, mapa);
    sscanf(aux, "%d %d", &boulder_dash->linhas, &boulder_dash->colunas);
    boulder_dash->colunas++;
    boulder_dash->niveis_jogo[nivel].mapa_jogo = aloca_matriz(boulder_dash->linhas, boulder_dash->colunas);
    for (i = 0; i < boulder_dash->linhas; i++)
    {
        for (j = 0; j < boulder_dash->colunas; j++)
        {
            a = fgetc(mapa);
            switch (a)
            {
            case '#':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = TIJOLO;
                break;
            case '|':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = TIJOLO_BRANCO;
                break;
            case '?':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = BARRA;
                break;
            case ' ':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = VAZIO;
                break;
            case '.':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = TERRA;
                break;
            case ',':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = METAL;
                break;
            case '*':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = DIAMANTE;
                break;
            case '<':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = ESTRELA;
                break;
            case 'o':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = ROCHA;
                break;
            case '0':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = ROCHA_BRANCA;
                break;
            case '@':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = PERSONAGEM;
                boulder_dash->niveis_jogo[nivel].personagem_jogo->item = PERSONAGEM;
                altera_posicao_personagem(boulder_dash->niveis_jogo[nivel].personagem_jogo, i, j);

                printf(" x: %d\n", boulder_dash->niveis_jogo[nivel].personagem_jogo->x);
                printf(" y: %d\n", boulder_dash->niveis_jogo[nivel].personagem_jogo->y);
                break;
            case '&':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = PERSONAGEM_BRANCO;
                boulder_dash->niveis_jogo[nivel].personagem_jogo->item = PERSONAGEM_BRANCO;
                altera_posicao_personagem(boulder_dash->niveis_jogo[nivel].personagem_jogo, i, j);
                printf(" x: %d\n", boulder_dash->niveis_jogo[nivel].personagem_jogo->x);
                printf(" y: %d\n", boulder_dash->niveis_jogo[nivel].personagem_jogo->y);
                break;
            case 's':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = PORTA;
                break;
            case 'x':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = PORTA_BRANCA;
                break;

            case '\n':
                continue;
            default:
                printf("erro");
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = VAZIO;
                break;
            }

            // printf("%d ", boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item);
        }
        // printf("\n");
    }
}

void atualiza_mapa(itens **mapa_jogo, int nivel, int linhas, int colunas)
{
    int i, j;
    for (i = 0; i < linhas; i++)
    {
        for (j = 0; j < colunas; j++)
        {
            switch (mapa_jogo[i][j].item)
            {
            case TIJOLO:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/tijolo.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "tijolo");
                break;
            case BARRA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/barra.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "barra");
                break;
            case TIJOLO_BRANCO:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/tijolo_branco.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "tijolo_branco");
                break;
            case VAZIO:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/vazio.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "vazio");
                break;

            case TERRA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/terra.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "terra");
                break;
            case METAL:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/metal.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "metal");
                break;

            case DIAMANTE:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/diamante.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "diamante");
                break;
            case ESTRELA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/estrela.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "estrela");
                break;

            case ROCHA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/rocha.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "rocha");
                break;
            case ROCHA_BRANCA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/rocha_branca.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "rocha_branca");
                break;

            case PERSONAGEM:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/personagem.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "personagem");
                break;
            case PERSONAGEM_BRANCO:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/personagem_branco.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "personagem_branco");
                break;

            case PORTA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/porta.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "porta");
                break;
            case PORTA_BRANCA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/porta_branca.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "porta_branca");
                break;
            default:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/vazio.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "vazio");
                break;
            }
            al_draw_bitmap(mapa_jogo[i][j].image, j * SPRITE, i * SPRITE, 0);
        }
    }
}

void verifica_bloqueios(jogo *boulder_dash, int nivel, int x, int y)
{
    item elemento = boulder_dash->niveis_jogo[nivel].mapa_jogo[x][y].item;

    if ((elemento == TERRA) || (elemento == METAL) || (elemento == ESTRELA) || (elemento == DIAMANTE))
    {
        boulder_dash->niveis_jogo[nivel].mapa_jogo[x][y].item = VAZIO;
        boulder_dash->niveis_jogo[nivel].mapa_jogo[x][y].image = load_bitmap_at_size("resouces/texturas/vazio.png", SPRITE, SPRITE);
    }
}
void verifica_lados(jogo *boulder_dash, int nivel, int x, int y)
{
    printf(". x: %d\n", boulder_dash->niveis_jogo[nivel].personagem_jogo->x);
    printf(". y: %d\n", boulder_dash->niveis_jogo[nivel].personagem_jogo->y);
    item elemento = boulder_dash->niveis_jogo[nivel].mapa_jogo[x][y].item;

    if ((elemento == TERRA) || (elemento == METAL))
        boulder_dash->niveis_jogo[nivel].personagem_jogo->pontos = boulder_dash->niveis_jogo[nivel].personagem_jogo->pontos + 10;

    if ((elemento == ESTRELA) || (elemento == DIAMANTE))
        boulder_dash->niveis_jogo[nivel].personagem_jogo->diamantes++;

    if ((elemento == PORTA) || (elemento == PORTA_BRANCA))
        boulder_dash->estado_jogo = GANHOU;

    elemento = boulder_dash->niveis_jogo[nivel].personagem_jogo->item;
    boulder_dash->niveis_jogo[nivel].mapa_jogo[x][y].item = elemento;
    fprintf(stderr, "====%d", elemento);

    if (elemento == PERSONAGEM)
        boulder_dash->niveis_jogo[nivel].mapa_jogo[x][y].image = load_bitmap_at_size("resouces/texturas/personagem.png", SPRITE, SPRITE);
    if (elemento == PERSONAGEM_BRANCO)
        boulder_dash->niveis_jogo[nivel].mapa_jogo[x][y].image = load_bitmap_at_size("resouces/texturas/personagem_branco.png", SPRITE, SPRITE);
}
void atualiza_personagem(jogo *boulder_dash, int nivel, teclado movimento)
{
    int x, y, atual_x, atual_y;
    printf("aqui");
    x = boulder_dash->niveis_jogo[nivel].personagem_jogo->x;
    y = boulder_dash->niveis_jogo[nivel].personagem_jogo->y;
    atual_x = x;
    atual_y = y;
    if (movimento == ESQUERDA)
    {
        verifica_lados(boulder_dash, nivel, x, y--);
        verifica_bloqueios(boulder_dash, nivel, x, y--);

        boulder_dash->niveis_jogo[nivel].personagem_jogo->y--;
    }

    else if (movimento == DIREITA)
    {
    verifica_bloqueios(boulder_dash, nivel, x, y);
    verifica_lados(boulder_dash, nivel, x, y++);
    boulder_dash->niveis_jogo[nivel].personagem_jogo->y++;
    }

    else if (movimento == CIMA)
    {
        verifica_lados(boulder_dash, nivel, x--, y);
        verifica_bloqueios(boulder_dash, nivel, x--, y);

        boulder_dash->niveis_jogo[nivel].personagem_jogo->x--;
    }

    else if (movimento == BAIXO)
    {
        verifica_lados(boulder_dash, nivel, x++, y);
        verifica_bloqueios(boulder_dash, nivel, x, y++);

        boulder_dash->niveis_jogo[nivel].personagem_jogo->x++;
    }
    else
    {
        fprintf(stderr, "erro");
    }
}
