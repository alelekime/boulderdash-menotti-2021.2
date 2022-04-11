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
    char *aux = malloc(sizeof(char) * 512);
    FILE *mapa = fopen(nome, "r");
    if (mapa == NULL)
    {
        perror("Error: ");
    }
    fgets(aux, 512, mapa);
    sscanf(aux, "%d %d", &boulder_dash->linhas, &boulder_dash->colunas);
    boulder_dash->niveis_jogo[nivel].mapa_jogo = aloca_matriz(boulder_dash->linhas+1, boulder_dash->colunas+1);
    itens **mapa_itens = boulder_dash->niveis_jogo[nivel].mapa_jogo;

    for (i = 0; i < boulder_dash->linhas; i++)
    {
        printf("i :>> %d\n", i);

        for (j = 0; j < boulder_dash->colunas; j++)
        {
            switch (fgetc(mapa))
            {
            case '#':
                mapa_itens[i][j].item = TIJOLO;
                break;
            case ' ':
                mapa_itens[i][j].item = VAZIO;
                break;
            case '.':
                mapa_itens[i][j].item = TERRA;
                break;
            case '*':
                mapa_itens[i][j].item = DIAMANTE;
                break;

            case 'o':
                mapa_itens[i][j].item = ROCHA;
                break;

            case '@':
                mapa_itens[i][j].item = PERSONAGEM;
                break;
            case 's':
                mapa_itens[i][j].item = PORTA;

                break;
            case '\n':
                continue;;

            default:
                mapa_itens[i][j].item = VAZIO;
                break;
            }
        }   
    }
}

void atualiza_mapa(jogo *boulder_dash, int nivel)
{

    int i,j;

    itens **mapa_itens = boulder_dash->niveis_jogo[nivel].mapa_jogo;

    for (i = 0; i < boulder_dash->linhas; i++)
    {
        // printf("\ni :>> %d\n", i);

        for (j = 0; j < boulder_dash->colunas; j++)
        {
            // printf(" %d", j);
            switch (mapa_itens[i][j].item)
            {
            case TIJOLO:
                mapa_itens[i][j].image = load_bitmap_at_size("resouces/texturas/tijolo.png", SPRITE, SPRITE);
                must_init(mapa_itens[i][j].image, "tijolo");
                break;

            case VAZIO:
                mapa_itens[i][j].image = load_bitmap_at_size("resouces/texturas/vazio.png", SPRITE, SPRITE);
                must_init(mapa_itens[i][j].image, "vazio");
                break;

            case TERRA:
                mapa_itens[i][j].image = load_bitmap_at_size("resouces/texturas/terra.png", SPRITE, SPRITE);
                must_init(mapa_itens[i][j].image, "terra");
                break;

            case DIAMANTE:
                mapa_itens[i][j].image = load_bitmap_at_size("resouces/texturas/diamante.png", SPRITE, SPRITE);
                must_init(mapa_itens[i][j].image, "diamante");
                break;

            case ROCHA:
                mapa_itens[i][j].image = load_bitmap_at_size("resouces/texturas/rocha.png", SPRITE, SPRITE);
                must_init(mapa_itens[i][j].image, "rocha");
                break;

            case PERSONAGEM:
                mapa_itens[i][j].image = load_bitmap_at_size("resouces/texturas/personagem.png", SPRITE, SPRITE);
                must_init(mapa_itens[i][j].image, "personagem");
                break;

            case PORTA:
                mapa_itens[i][j].image = load_bitmap_at_size("resouces/texturas/porta.png", SPRITE, SPRITE);
                must_init(mapa_itens[i][j].image, "porta");
                break;
            }
            al_draw_bitmap(mapa_itens[i][j].image, j * SPRITE, i * SPRITE, 0);

        }
    }
}

//     mapa_itens **preenche_mapa(mapa_itens **mapa, fila_imagens *fila, personagem *personagem, mapa_dados *dados)
// {
//     int i, j;
//     char c;
//     dados->diamante = 0;

//     FILE *mapa_arquivo = fopen("resouces/mapa.txt", "r");
//     if (mapa_arquivo == NULL)
//     {
//         printf("Erro: arquivo mapa");
//     }
//     for (i = 0; i < LINHAS; i++)
//     {
//         for (j = 0; j <= COLUNAS; j++)
//         {
//             c = fgetc(mapa_arquivo);
//             if (',' == c)
//             {
//                 continue;
//             }
//             else if ('B' == c)
//             {
//                 mapa[i][j].item = BORDA;
//                 // printf("borda.");
//                 // printf("borda.");
//             }
//             else if ('D' == c)
//             {
//                 mapa[i][j].item = DIAMANTE;
//                 dados->diamante++;
//                 // printf("diamante");
//             }
//             else if ('P' == c)
//             {
//                 mapa[i][j].item = PERSONAGEM;
//             }
//             else if ('T' == c)
//             {
//                 mapa[i][j].item = TERRA;
//                 // printf("terra");
//             }
//             else if ('K' == c)
//             {
//                 mapa[i][j].item = TIJOLO;
//                 // printf("tijolo");
//             }
//             else if ('V' == c)
//             {
//                 mapa[i][j].item = VAZIO;
//                 // printf("vazio");
//             }
//             else if ('R' == c)
//             {

//                 mapa[i][j].item = ROCHA;

//                 // printf("vazio");
//             }

//             // printf("%d ", mapa[i][j].item);
//         }
//     }
//     fclose(mapa_arquivo);
//     // printf("\n\n");
//     return mapa;
// }
