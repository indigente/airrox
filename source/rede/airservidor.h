#ifndef _AIRSERVIDOR_H
#define _AIRSERVIDOR_H

#include "rede.h"
#include "airrede.h"

class Partida;

class AirServidor : public AirRede
{
	protected:
// 		Partida *partida;
// 		UDPpacket *pacote;
		
		int qtdJogadores;
		int qtdObservadores;
		
		void processaPedidoDeConexao();
		void enviaRespostaDeConexao(char tipo);
		void processaMensagem();
		
	public:
		AirServidor(Partida *partida, Uint16 porta) : AirRede(partida, porta)
		{
			this->qtdJogadores = 0;
			this->qtdObservadores = 0;
		}
		
		~AirServidor() {};
		
		int recebeMensagem();
		void enviaEstado();
};

#endif

