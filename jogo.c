
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

void *inicializa_jogo(estado *estado_jogo, dados *dados_jogo, itens **mapa_jogo, personagem *personagem_jogo)
{
    estado_jogo = malloc(sizeof(estado));
    must_init(estado_jogo, "struct estado");
    dados_jogo = malloc(sizeof(dados_jogo));
    must_init(dados_jogo, "struct dados");
    mapa_jogo = aloca_matriz(LINHAS, COlUNAS);
    must_init(estado_jogo, "matriz mapa");
    personagem_jogo = malloc(sizeof(personagem_jogo));
    must_init(estado_jogo, "struct personagem");
}

void inicializa_nivel(dados *dados_jogo, itens **mapa_jogo, personagem *personagem_jogo, int nivel_atual)
{
    char *mapa_nome = malloc(sizeof(char) * 512);
    sprintf(mapa_nome, "resouces/mapas/mapa%d.txt", nivel_atual);
    le_mapa(dados_jogo, mapa_jogo, mapa_nome);
}
void le_mapa(dados *dados_jogo, itens **mapa_jogo, char *mapa_nome)
{
    int i, j;
    char *aux = malloc(sizeof(char) * 512);
    FILE *mapa_arquivo = fopen(mapa_nome, "r");
    must_init(mapa_arquivo, "arquivo mapa");
    fgets(aux, 512, mapa_arquivo);
    sscanf(aux, "%d", &dados_jogo->tempo);
    for (i = 0; i < LINHAS; i++)
    {
        for (j = 0; j < COlUNAS; j++)
        {
            mapa_jogo[i][j].item = encontra_tipo(fgetc(mapa_arquivo));
            mapa_jogo[i][j].alterado = 1;
        }
    }
    free(aux);
    fclose(mapa_arquivo);
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
    }
}