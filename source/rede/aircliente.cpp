#include "../partida.h"
#include "aircliente.h"
#include <stdio.h>
#include <stdlib.h>

bool AirCliente::conecta(const char *host, Uint16 porta, bool comoJogador)
{
	IPaddress ip;
	int ret;
	int canal;
	
	if (!this->conectado)
	{
		ret = SDLNet_ResolveHost(&ip, host, porta);
		if (ret == -1)
		{
			printf("AirCliente::conecta: %s\n", SDLNet_GetError());
			return false;
		}

		this->canal = (comoJogador ? CANAL_JOGADOR : CANAL_OBSERVADOR);
		
		ret = SDLNet_UDP_Bind(this->sock, this->canal, &ip);
		if (ret == -1)
		{
			printf("AirCliente::conecta: %s\n", SDLNet_GetError());
			return false;
		}

		enviaPedidoDeConexao();
	}
	
	return true;
}

void AirCliente::enviaPedidoDeConexao()
{
	msgConectar *m = (msgConectar *)this->pacote->data;
	
	m->tipo = TIPO_CONECTAR;
	m->comoJogador = (this->canal == CANAL_JOGADOR ? 1 : 0);
	
	this->pacote->len = sizeof(msgConectar);
	
	this->envia(this->canal, this->pacote);
}

bool AirCliente::recebeMensagem()
{
	int ret;
	
	ret = this->recebe(this->pacote);
	
	switch (ret)
	{
		// o pacote foi recebido
		case 1:
			switch (pacote->channel)
			{
				// mensagem externa. ignora...
				case -1:
					return true;
				// mensagem do jogador
				case CANAL_JOGADOR:
					if (this->conectado)
						processaMensagemDoJogador();
					else
						recebeRespostaDeConexao();
					return true;
				// mensagem de um observador
				case CANAL_OBSERVADOR:
					if (this->conectado)
						processaMensagemDoJogador();
					else
						recebeRespostaDeConexao();
					return true;
			}
			break;
		// nao foi recebido nenhum pacote
		case 0:
			return false;
		// erro
		case -1:
			printf("AirCliente::recebeMensagens: %s\n", SDLNet_GetError());
			return false;
	}
}

void AirCliente::processaMensagemDoJogador()
{
	switch (this->pacote->data[0])
	{
		case TIPO_ESTADO:
			msgEstado *m = (msgEstado *)this->pacote->data;

			partida->getDisco()->setPos(m->discopos);
			partida->getDisco()->setVel(m->discovel);
			partida->getJog(1)->setPontuacao(m->pontserv);
			partida->getJog(0)->setPontuacao(m->pontcli);
			partida->getJog(1)->setPos(m->servpos);
			
			// se eh observador, usa a posicao do jogador cliente
			if (this->canal == CANAL_OBSERVADOR)
				partida->getJog(0)->setPos(m->clipos);
			
			break;
	}
}

void AirCliente::recebeRespostaDeConexao()
{
	if (this->pacote->data[0] == TIPO_CONEXAO_ACEITA)
		this->conectado = true;
	printf("recebeRespostaDeConexao: %d\n", this->conectado); // DEBUG
}

void AirCliente::enviaEstado()
{
	msgPosicao *m = (msgPosicao *)this->pacote->data;
	
	if (this->conectado)
	{	
		m->tipo = TIPO_POSICAO;
		m->jogpos = partida->getJog(0)->getPos();
	
		this->pacote->len = sizeof(msgPosicao);
		
		this->envia(CANAL_JOGADOR, this->pacote);
	}
}
