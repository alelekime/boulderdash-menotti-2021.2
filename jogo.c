#include "jogo.h"
#include "auxiliar.h"

void *inializa_niveis(jogo *boulder_dash)
{
    int i, j, k, linhas, colunas;
    linhas = boulder_dash->linhas;
    colunas = boulder_dash->colunas;

    for (k = 0; k < NIVEIS; k++)
    {
        boulder_dash->niveis_jogo[k].mapa_jogo = aloca_matriz(linhas, colunas);
    }
}

mapa_itens **preenche_mapa(mapa_itens **mapa, fila_imagens *fila, personagem *personagem, mapa_dados *dados)
{
    int i, j;
    char c;
    dados->diamante = 0;

    FILE *mapa_arquivo = fopen("resouces/mapa.txt", "r");
    if (mapa_arquivo == NULL)
    {
        printf("Erro: arquivo mapa");
    }
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j <= COLUNAS; j++)
        {
            c = fgetc(mapa_arquivo);
            if (',' == c)
            {
                continue;
            }
            else if ('B' == c)
            {
                mapa[i][j].item = BORDA;
                // printf("borda.");
                // printf("borda.");
            }
            else if ('D' == c)
            {
                mapa[i][j].item = DIAMANTE;
                dados->diamante++;
                // printf("diamante");
            }
            else if ('P' == c)
            {
                mapa[i][j].item = PERSONAGEM;
            }
            else if ('T' == c)
            {
                mapa[i][j].item = TERRA;
                // printf("terra");
            }
            else if ('K' == c)
            {
                mapa[i][j].item = TIJOLO;
                // printf("tijolo");
            }
            else if ('V' == c)
            {
                mapa[i][j].item = VAZIO;
                // printf("vazio");
            }
            else if ('R' == c)
            {

                mapa[i][j].item = ROCHA;

                // printf("vazio");
            }

            // printf("%d ", mapa[i][j].item);
        }
    }
    fclose(mapa_arquivo);
    // printf("\n\n");
    return mapa;
}
