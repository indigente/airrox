#ifndef _AIRCLIENTE_H
#define _AIRCLIENTE_H

#include "rede.h"
#include "airrede.h"

class Partida;

class AirCliente : public AirRede
{
	protected:
// 		Partida *partida;
// 		UDPpacket *pacote;
		
		bool conectado;
		
// 		void processaPedidoDeConexao();
// 		void enviaRespostaDeConexao(char tipo);
		void enviaPedidoDeConexao();
		void processaMensagemDoJogador();
		void recebeRespostaDeConexao();
		
	public:
		AirCliente(Partida *partida, Uint16 porta) : AirRede(partida, porta)
		{
			this->conectado = false;
		}
		
		~AirCliente() {};
		
		bool conecta(const char *host, Uint16 porta);
		
		bool recebeMensagem();
		void enviaEstado();
};

#endif
