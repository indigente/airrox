#ifndef _AIRSERVIDOR_H
#define _AIRSERVIDOR_H

#include "rede.h"
#include "airrede.h"

class Partida;

class AirServidor : public Rede
{
	protected:
		Partida *partida;
		UDPpacket *pacote;
		
		int qtdJogadores;
		int qtdObservadores;
		
		void processaPedidoDeConexao();
		void enviaRespostaDeConexao(char tipo);
		
	public:
		AirServidor(Partida *partida, Uint16 porta);
		~AirServidor();
		
		void recebeMensagens();
		void enviaEstado();
};

#endif

