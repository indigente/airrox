#include "airservidor.h"
#include "../partida.h"
#include <stdlib.h>
#include <string.h>

/*		Partida *partida;
		UDPpacket *pacote;*/

AirServidor::AirServidor(Partida *partida, Uint16 porta)
{
	this->qtdJogadores = 0;
	this->qtdObservadores = 0;
	
	pacote = SDLNet_AllocPacket(MAXBUF);
	
	if (!partida) {
		printf("AirServidor::AirServidor: partida == NULL!\n");
		exit(2);
	}
	this->partida = partida;
	
	this->abre(porta);
}

AirServidor::~AirServidor()
{
	SDLNet_FreePacket(pacote);
	this->fecha();
}

void AirServidor::recebeMensagens()
{
	int ret;
	
	ret = this->recebe(this->pacote);
	
	switch (ret)
	{
		// o pacote foi recebido
		case 1:
			printf("pacote recebido (DEBUG)\n");
			switch (pacote->channel)
			{
				// provavelmente alguem tentando conectar
				case -1:
					this->processaPedidoDeConexao();
					break;
				// mensagem do jogador
				case CANAL_JOGADOR:
					break;
				// mensagem de um observador
				case CANAL_OBSERVADOR:
					break;
			}
			break;
		// nao foi recebido nenhum pacote
		case 0:
			break;
		// erro
		case -1:
			printf("AirServidor::recebeMensagens: %s\n", SDLNet_GetError());
			break;
	}
}



void AirServidor::enviaEstado()
{
	msgEstado *m = (msgEstado *)this->pacote->data;
	
	m->tipo = TIPO_ESTADO;
	m->discopos = partida->getDisco()->getPos();
	m->discovel = partida->getDisco()->getVel();
	m->pontserv = partida->getJog(0)->getPontuacao();
	m->pontcli = partida->getJog(1)->getPontuacao();
	m->servpos = partida->getJog(0)->getPos();
	m->clipos = partida->getJog(1)->getPos();
	
	this->pacote->len = sizeof(msgEstado);
	
	this->envia(CANAL_JOGADOR, this->pacote);
	this->envia(CANAL_OBSERVADOR, this->pacote);
}

/**
 * @param tipo Deve ser TIPO_CONEXAO_ACEITA ou TIPO_CONEXAO_REJEITADA
 */
void AirServidor::enviaRespostaDeConexao(char tipo)
{
	UDPpacket *p = SDLNet_AllocPacket(8);
	
	p->data[0] = tipo;
	p->len = 1;
	memcpy(&p->address, &pacote->address, sizeof(IPaddress));
	SDLNet_UDP_Send(this->getSocket(), -1, p);
	
	SDLNet_FreePacket(p);
}

/**
 * Aceita/rejeita conexao de um observador ou de um jogador
 */
void AirServidor::processaPedidoDeConexao()
{
	msgConectar *m = (msgConectar *)this->pacote->data;
	UDPpacket *p = SDLNet_AllocPacket(10);
		
	if (m->tipo == TIPO_CONECTAR)
	{
		switch (m->comoJogador) {
			// conexao como jogador
			case 1:
				// aceita conexao
				if (qtdJogadores < MAXJOGADORES) {
					enviaRespostaDeConexao(TIPO_CONEXAO_ACEITA);
					this->bind(CANAL_JOGADOR, &this->pacote->address);
					qtdJogadores++;
				}
				// rejeita conexao
				else
				{
					enviaRespostaDeConexao(TIPO_CONEXAO_REJEITADA);
				}
				
				break;
			// conexao como observador
			case 0:
				// aceita conexao
				if (qtdObservadores < MAXOBSERVADORES) {
					enviaRespostaDeConexao(TIPO_CONEXAO_ACEITA);					
					this->bind(CANAL_OBSERVADOR, &this->pacote->address);					
					qtdObservadores++;
				}
				// rejeita conexao
				else
				{
					enviaRespostaDeConexao(TIPO_CONEXAO_REJEITADA);
				}				
				break;
		}
	}
	
	SDLNet_FreePacket(p);
}

