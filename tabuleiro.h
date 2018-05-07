#ifndef TABULEIRO_H
#define TABULEIRO_H
#define TAM_TABULEIRO 10
#define PORTA_AVIOES 5
#define NAVIOS_TANQUE 4
#define CONTRATORPEDOS 3
#define SUBMARINOS 2

void inicializa_tabuleiro(int tabuleiro[][TAM_TABULEIRO]);

int orientacao();

int casa_inicial(int inicialMax);

int verifica_disponibilidade(int orientacao, int x, int y,int tabuleiro[][TAM_TABULEIRO], int tamanho);

void preencheTNavio(int orientacao, int x, int y, int tabuleiro[][TAM_TABULEIRO], int tamanho);

void preencher_navio(int tabuleiro[][TAM_TABULEIRO], int tamanho, int qtde );

void exibir_tabuleiro(int tabuleiro[][TAM_TABULEIRO]);

void carregar_tabuleiro_de_um_arquivo(int tabuleiro[][TAM_TABULEIRO]);

void inicializa_mapa_de_tiros(char tabuleiro[][TAM_TABULEIRO]);

void exibir_mapa(char tabuleiro[][TAM_TABULEIRO]);

int traduzir_tiro(int tabuleiro[][TAM_TABULEIRO], char tiro[3], int flag);

int c_letra(char tiro[3], int flag);

char letra_c(int letra);

#endif
