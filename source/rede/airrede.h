#ifndef _AIRREDE_H
#define _AIRREDE_H

#include "rede.h"
#include "SDL/SDL_net.h"

// arquivo comum para cliente e servidor

#include "../vetor.h"

#define CANAL_JOGADOR    2
#define CANAL_OBSERVADOR 1
#define MAXJOGADORES 1
#define MAXOBSERVADORES SDLNET_MAX_UDPADDRESSES
#define MAXBUF 256

// posicao do jogador. enviado pelo cliente para o servidor.
#define TIPO_POSICAO    1 
// estado do jogo. enviado pelo servidor para os clientes (jogador e observador).
#define TIPO_ESTADO     2
// alguem tentando conectar.
#define TIPO_CONECTAR   3
// mensagem de texto
#define TIPO_TEXTO      4
// outros...
#define TIPO_OUTROS     255

#define TIPO_CONEXAO_ACEITA 5
#define TIPO_CONEXAO_REJEITADA 6


struct msgPura
{
	char tipo;
};

struct msgTexto
{
	char tipo;
	char texto[MAXBUF - sizeof(char)];
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

class Partida;

class AirRede : public Rede
{
	protected:
		Partida *partida;
		UDPpacket *pacote;
		
	public:
		AirRede(Partida *partida, Uint16 porta);
		~AirRede();
		
		void enviaTexto(char *msg);
		virtual int recebeMensagem()=0;
		virtual void enviaEstado()=0;

		const unsigned char *getDados() { return pacote->data; }
};

#endif

