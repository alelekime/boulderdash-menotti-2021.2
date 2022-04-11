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

jogo *inicializa_jogo()
{
    jogo *boulder_dash = malloc(sizeof(jogo));
    boulder_dash->dados_jogo = malloc(sizeof(dados));
    boulder_dash->niveis_jogo = malloc(sizeof(niveis) * NIVEIS);
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
            case ' ':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = VAZIO;
                break;
            case '.':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = TERRA;
                break;
            case '*':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = DIAMANTE;
                break;

            case 'o':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = ROCHA;
                break;

            case '@':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = PERSONAGEM;
                break;
            case 's':
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = PORTA;

                break;
            case '\n':
                continue;;

            default:
            printf("erro");
                boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item = VAZIO;
                break;
            }
            printf(" %c",a);
            // printf("%d ", boulder_dash->niveis_jogo[nivel].mapa_jogo[i][j].item);
        }   
        printf("\n");

    }
}

void atualiza_mapa(itens **mapa_jogo, int nivel, int linhas, int colunas)
{

    int i,j;

    for (i = 0; i < linhas; i++)
    {
        printf("\ni :>> %d\n", i);

        for (j = 0; j < colunas; j++)
        {
            // printf(" %d", j);
            switch (mapa_jogo[i][j].item)
            {
            case TIJOLO:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/tijolo.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "tijolo");
                break;

            case VAZIO:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/vazio.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "vazio");
                break;

            case TERRA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/terra.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "terra");
                break;

            case DIAMANTE:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/diamante.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "diamante");
                break;

            case ROCHA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/rocha.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "rocha");
                break;

            case PERSONAGEM:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/personagem.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "personagem");
                break;

            case PORTA:
                mapa_jogo[i][j].image = load_bitmap_at_size("resouces/texturas/porta.png", SPRITE, SPRITE);
                must_init(mapa_jogo[i][j].image, "porta");
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
