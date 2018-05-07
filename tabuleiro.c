#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "tabuleiro.h"

void inicializa_tabuleiro(int tabuleiro[][TAM_TABULEIRO])
{
    int numero, letra;
    for(numero = 0; numero < 10; numero++)
    {
        for(letra = 0; letra < 10; letra++)
        {
            tabuleiro[numero][letra] = 0;
        }
    };
};

/*
** 0: vertical
** 1: horizontal
**/
int orientacao()
{
    srand(time(NULL)+clock());
    return rand() % 2;
};

int casa_inicial(int inicialMax)
{
    srand(time(NULL)+clock());
    return (rand() % (inicialMax+1));
};

int verifica_disponibilidade(int orientacao, int x, int y,int tabuleiro[][TAM_TABULEIRO], int tamanho)
{
    int i, casa_final;
    int soma = 0;
    if(orientacao == 0)
    {
        casa_final = y + tamanho;
        for(i = y; i < casa_final; i++)
        {
            if(tabuleiro[i][y] != 0){ return 0;};
        };
    }
    else{
        casa_final = x + tamanho;
        for(i = x; i < casa_final; i++)
        {
            if(tabuleiro[x][i] != 0){
                return 0;
            };
        };
    };
    return 1;
};

void preencheTNavio(int orientacao, int x, int y, int tabuleiro[][TAM_TABULEIRO], int tamanho)
{
    int i, casa_final;
    int soma = 0;
    if(orientacao == 0)
    {
        casa_final = y + tamanho;
        for(i = y; i < casa_final; i++)
        {
            tabuleiro[x][i] = tamanho;
        };
    }
    else{
        casa_final = x + tamanho;
        for(i = x; i < casa_final; i++)
        {
            tabuleiro[i][y] = tamanho;
        };
    };
};

void preencher_navio(int tabuleiro[][TAM_TABULEIRO], int tamanho, int qtde )
{
    int ix, iy;
    int x, y;
    int b;
    for(int i = 0; i < qtde; i++){
        int resp = 0;
        do
        {   
            int direcao;
            direcao = orientacao();
            if(direcao == 0){
                ix = 10;
                iy = TAM_TABULEIRO - tamanho;
            }else{
                iy = 10;
                ix = TAM_TABULEIRO - tamanho;
            };
            x = casa_inicial(ix);
            y = casa_inicial(iy);
            if(tabuleiro[x][y] == 0){
                if(verifica_disponibilidade(direcao,x, y,tabuleiro,tamanho) == 1){
                    preencheTNavio(direcao,x, y,tabuleiro,tamanho);
                    resp = 1;
                };     
            };
        }while(resp != 1);   
    };
};

void exibir_tabuleiro(int tabuleiro[][TAM_TABULEIRO])
{
    printf("- ");
    for(int j = 0; j < 10; j++){
        printf("%d ", j+1);
    };
    printf("\n");
    for(int i = 0; i < TAM_TABULEIRO; i++)
    {
        printf("%c ", letra_c(i));
        for(int j = 0; j < TAM_TABULEIRO; j++)
        {
            printf("%d ",tabuleiro[i][j]);
        };
        printf("\n");
    };
};

void carregar_tabuleiro_de_um_arquivo(int tabuleiro[][TAM_TABULEIRO])
{
    FILE *file;
    file = fopen("jogo_cliente.txt", "r");
    int numero, letra;
    int c;
    int i, j;
    i = 0;
    j = 0;
    for(i = 0; i < TAM_TABULEIRO; i++){
        for(j = 0; j < TAM_TABULEIRO; j++){
            fscanf( file, "%d", &tabuleiro[i][j]);
        };
    };

    fclose(file);
};

void inicializa_mapa_de_tiros(char tabuleiro[][TAM_TABULEIRO])
{
    int numero, letra;
    for(numero = 0; numero < TAM_TABULEIRO; numero++)
    {
        for(letra = 0; letra < TAM_TABULEIRO; letra++)
        {
            tabuleiro[numero][letra] = '~';
        }
    };
};

void exibir_mapa(char tabuleiro[][TAM_TABULEIRO])
{
    printf("- ");
    for(int j = 0; j < 10; j++){
        printf("%d ", j+1);
    };
    printf("\n");
    for(int i = 0; i < TAM_TABULEIRO; i++)
    {
        printf("%c ", letra_c(i));
        for(int j = 0; j < TAM_TABULEIRO; j++)
        {
            printf("%c ",tabuleiro[i][j]);
        };
        printf("\n");
    };
};

int c_letra(char tiro[3], int flag)
{
    return tiro[0+flag]%65;
};

char letra_c(int letra)
{
    char mapa[10];
    mapa[0] = 'A';
    mapa[1] = 'B';
    mapa[2] = 'C';
    mapa[3] = 'D';
    mapa[4] = 'E';
    mapa[5] = 'F';
    mapa[6] = 'G';
    mapa[7] = 'H';
    mapa[8] = 'I';
    mapa[9] = 'J';
    return mapa[letra];
};

int c_numero(char tiro[3])
{
    int numero;
    if((tiro[1]+tiro[2]) != 97){
        numero = (tiro[1] + tiro[2]) % 49;
    }else{
        numero = 9;
    };
    return numero;
};

int traduzir_tiro(int tabuleiro[][TAM_TABULEIRO], char tiro[3], int flag)
{   
    printf("%d %d\n", c_letra(tiro,flag), c_numero(tiro));
    if(flag == 0){
        if(tabuleiro[c_letra(tiro,flag)][c_numero(tiro)] > 0){
            tabuleiro[c_letra(tiro,flag)][c_numero(tiro)] = -1;
            return 1;
        }else{
            return 0;
        };
    }else{
        if(tabuleiro[c_letra(tiro,flag)][tiro[2]] > 0){
            tabuleiro[c_letra(tiro,flag)][tiro[2]] = -1;
            return 1;
        }else{
            return 0;
        };
    };
};