#include "airservidor.h"
#include "../partida.h"
#include <stdlib.h>
#include <string.h>

int AirServidor::recebeMensagem()
{
	int ret;
	
	ret = this->recebe(this->pacote);
	
	switch (ret)
	{
		// o pacote foi recebido
		case 1:
			switch (pacote->channel)
			{
				// provavelmente alguem tentando conectar
				case -1:
					this->processaPedidoDeConexao();
					return this->pacote->data[0];
					break;
				// mensagem do jogador
				case CANAL_JOGADOR:
					processaMensagem();
					return this->pacote->data[0];
					break;
				// mensagem de um observador
				case CANAL_OBSERVADOR:
					processaMensagem();
					return this->pacote->data[0];
					break;
			}
			break;
		// nao foi recebido nenhum pacote
		case 0:
			return 0;
		// erro
		case -1:
			printf("AirServidor::recebeMensagens: %s\n", SDLNet_GetError());
			return 0;
	}
}

void AirServidor::processaMensagem()
{
	switch (this->pacote->data[0])
	{
		case TIPO_POSICAO:
		{
			msgPosicao *m = (msgPosicao *)this->pacote->data;
			partida->getJog(1)->setPos(m->jogpos);
			break;
		}
		case TIPO_TEXTO:
			// repassa para todos os clientes
			this->envia(CANAL_JOGADOR, this->pacote);
			this->envia(CANAL_OBSERVADOR, this->pacote);
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

