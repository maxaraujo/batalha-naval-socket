#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>


#define MAXBUF 100
#define LARGURA_BUFFER 4096

int main (int argc, char *argv[])
{
    int s, client_s;
    struct sockaddr_in6 self, client;
    int addrlen = sizeof(client);
    char msg_write[100], msg_read[100];
    char buffer[LARGURA_BUFFER];
    s = socket(AF_INET6, SOCK_STREAM, 0);
    int porta;
    if(argv[1] != 0){
        porta = atoi(argv[1]);
    }else{
        printf("Digite uma porta!\n");
        return 0;
    };

    self.sin6_family = AF_INET6;
    //Porta local na qual o socket irá aguardar conexões
    self.sin6_port = htons(porta);
    //Endereço ZERO -> utiliza endereço local padrão (endereço
    // de loopback)
    self.sin6_addr = in6addr_any;

    //Responsável por associar um endereço a porta locais a um socket
    if(bind(s, (struct sockaddr*)&self, sizeof(self)) == -1) {
        perror("Erro no bind do socket");
        return 1;
    };
    //Coloca-se o socket em modo de espera definido um máximo de 5 conexões
    //pendente que devem ser aguardadas
    if(listen(s, 1) == -1){
        perror("Erro no listen do socket");
        return 1;
    };

    while(1){
        /*
        client_s: socket destinado à conexão aceita pela função
        accept: Aguarda até que um pedido de conexão seja feito num socket que foi
        colocado previamente em modo de espera (listen) e,
        em seguida, retorna um novo descritor de socket para esta conexão.
        s: socket atuante como servidor(que agurada conexões)
        */
        client_s = accept(s,(struct sockaddr*)&client, &addrlen);
        strcpy(buffer, "Conectado\n\0");
        
        int NL[10][10];
        char mapa_tiro_servidor[10][10];
        int espaco_ocupado, ptiro,c_letra_tiro;
        char meu_tiro[2];
        ptiro = 0;
        inicializa_tabuleiro(NL);
        inicializa_mapa_de_tiros(mapa_tiro_servidor);
        preencher_navio(NL, PORTA_AVIOES, 1);
        preencher_navio(NL, NAVIOS_TANQUE, 2);
        preencher_navio(NL,CONTRATORPEDOS, 3);
        preencher_navio(NL, SUBMARINOS, 4);
        exibir_tabuleiro(NL);

        if(send(client_s, buffer, strlen(buffer), 0)) {
            printf("Cliente conectado.\n Aguardando por mensagens do cliente...\n");
            do{
                read(client_s, msg_read, MAXBUF);
                printf("%s\n", msg_read);
                if(traduzir_tiro(NL, msg_read, 0) == 0){
                    buffer[0] = 'E';
                }else{
                    buffer[0] = 'A';
                };
                if(ptiro > 0){
                    if(msg_read[3] == 'A'){
                        mapa_tiro_servidor[c_letra_tiro][meu_tiro[1]] = '*';
                    }else{
                        mapa_tiro_servidor[c_letra_tiro][meu_tiro[1]] = 'X';
                    };
                };
                while(1){
                    c_letra_tiro = casa_inicial(TAM_TABULEIRO-1);
                    meu_tiro[0] = letra_c(c_letra_tiro);
                    meu_tiro[1] = casa_inicial(TAM_TABULEIRO-1);
                    buffer[1] = meu_tiro[0];
                    buffer[2] = meu_tiro[1]; 
                    if(mapa_tiro_servidor[c_letra_tiro][meu_tiro[1]] == '~'){
                        break;
                    };
                };
            
                send(client_s, buffer, strlen(buffer), 0);
                ptiro++;
            } while (strcmp(msg_read, "bye"));
        }
        close(client_s);
    }
}