// arquivo comum para cliente e servidor

#include "../vetor.h"

#define CANAL_JOGADOR    2
#define CANAL_OBSERVADOR 1
#define MAXJOGADORES 1
#define MAXOBSERVADORES SDLNET_MAX_UDPADDRESSES
#define MAXBUF 256

// posicao do jogador. enviado pelo cliente para o servidor.
#define TIPO_POS        1 
// estado do jogo. enviado pelo servidor para os clientes (jogador e observador).
#define TIPO_ESTADO     2
// alguem tentando conectar.
#define TIPO_CONECTAR   3
// mensagem de texto
#define TIPO_TEXTO      4

#define TIPO_CONEXAO_ACEITA 5
#define TIPO_CONEXAO_REJEITADA 6



struct msgPura
{
	char tipo;
};

struct msgConectar {
	char tipo;
	// 0, se a pessoa quer se conectar como observador
	// 1, se a pessoa quer se conectar como jogador
	char comoJogador;	
};

struct msgPosicao {
	char tipo; // tipo da mensagem
	Vetor jogpos;
};

struct msgEstado {
	char tipo;
	Vetor discopos;
	Vetor discovel;
	int pontserv; // pontuacao do servidor
	int pontcli; // pontuacao do cliente
	Vetor servpos; // posicao do servidor
	Vetor clipos; // posicao do cliente
};

