Para gerar o programa é necessário executar dentro da pasta: make
Para excluir os arquivos .o basta executar: make clean

Para execução do programa servidor utilize em um terminal:
./servidor <porta>

Para execução do programa cliente em outro termina (e após executar o servidor):
./cliente <ip> <porta>

Durante o jogo é necessário que o cliente envie coordenadas para o servidor.
Estas coordenadas devem ser escritas de A a J em letra maiúscula junto com um número de 1 a 10.
Exemplo:
A5
Em seguida precione enter.
Para visualizar o conhecimento adiquirido no jogo e o próprio tabuleira basta digitar P e precionar enter.

O Mapa:
*: acertou tiro
X: errou tiro
~: não atirou ainda

O tabuleiro do cliente:
Preenchido em forma de matriz no arquivo "jogo_cliente.txt" com números separados por espaço.
0: espaço vazio
2: barco de duas posições
3: barco de três posições
4: barcos de quatro posições
5: barco de cinco posições