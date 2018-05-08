#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabuleiro.h"

//Headers:
/*
** sys/types.h: definição de tipos de dados
** sys/socket.h: funções e constantes relativas a sockets
** netinet/in.h: manipulação de estruturas, dados e endereços da família internet
** netdb.h: permite o uso de funções relativas a hostnames, portas, etc
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define MAXBUF 100


int main (int argc, char *argv[])
{
    int porta_do_servidor, rc;
    char* nome_do_servidor;
    struct addrinfo hints, *res;
    int errcode;
    int s, slen;
    struct in6_addr dest;

    char msg_write[100], msg_read[100];

    if(argv[1] != 0 && argv[2] != 0){
        nome_do_servidor = argv[1];
        porta_do_servidor = atoi(argv[2]);
    };

    memset(&hints, 0x00, sizeof(hints));
    hints.ai_flags    = AI_NUMERICSERV;
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    rc = inet_pton(AF_INET, argv[1], &dest);
      if (rc == 1)    /* valid IPv4 text address? */
      {
         hints.ai_family = AF_INET;
         hints.ai_flags |= AI_NUMERICHOST;
      }
      else
      {
         rc = inet_pton(AF_INET6, argv[1], &dest);
         if (rc == 1) /* valid IPv6 text address? */
         {

            hints.ai_family = AF_INET6;
            hints.ai_flags |= AI_NUMERICHOST;
         }
      };

    rc = getaddrinfo(argv[1], argv[2], &hints, &res);
      if (rc != 0)
      {
         printf("Host nao encontrado --> %s\n", gai_strerror(rc));
         if (rc == EAI_SYSTEM)
            perror("getaddrinfo() falha");
         return 0;
    };

    s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
      if (s < 0)
      {
         perror("socket() falha");
         return 0;
      };

      rc = connect(s, res->ai_addr, res->ai_addrlen);
      if (rc < 0)
      {

         perror("connect() falha");
         return 0;
      };


    if((slen = recv(s, msg_read, 100, 0)) > 0){
        msg_read[slen + 1] = '\0';
        printf("%s\n",msg_read);
    };

    int meu_jogo[TAM_TABULEIRO][TAM_TABULEIRO];
    char meu_mapa[TAM_TABULEIRO][TAM_TABULEIRO];
    int tiro_dado_l, tiro_dado_n;
    int peca_cliente = 28, peca_servidor = 28;
    carregar_tabuleiro_de_um_arquivo(meu_jogo);
    inicializa_mapa_de_tiros(meu_mapa);
    printf("\n");    

    do
    {
        printf("Atire:\n");
        scanf("%s", msg_write);
        if(msg_write[0] == 'P'){
            exibir_tabuleiro(meu_jogo);
            printf("\n");
            exibir_mapa(meu_mapa);
        }else{
            tiro_dado_l = c_letra(msg_write,0);
            tiro_dado_n = c_numero(msg_write);
            //Escrever no socket a mensagem digitada
            write(s, msg_write, strlen(msg_write)+1);
            if((slen = recv(s, msg_read, 100, 0)) > 0){
                if(msg_read[0] == 'E'){
                    printf("Errou!\n");
                    meu_mapa[tiro_dado_l][tiro_dado_n] = 'X';
                }else if (msg_read[0] == 'A'){
                    printf("Acertou!\n");
                    peca_cliente--;
                    if(peca_cliente==0){
                        printf("Você venceu!\n");
                        break;
                    };
                    meu_mapa[tiro_dado_l][tiro_dado_n] = '*';
                };
            };
            printf("Oponente:\n");
            printf("%c%d\n",msg_read[1],msg_read[2]+1);
            if(traduzir_tiro(meu_jogo, msg_read, 1) == 1){
                printf("Acertou!\n");
                msg_read[3] = 1;
                peca_servidor--;
                    if(peca_servidor==0){
                        printf("Você perdeu!\n");
                        break;
                    };
            }else{
                printf("Errou!\n");
                msg_read[3] = 0;
            };
        };

    } while (strcmp(msg_read, "bye"));
    //Fechando o socket
    close(s);
}