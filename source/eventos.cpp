/*
	This project was developed by:
		Alexandre Amoedo Amorim (amoedo@im.ufba.br)
		Jailson A. de Brito Júnior (jailson@im.ufba.br)
		Rodrigo Rocha Gomes de Souza (rodrigo@im.ufba.br)
	This project was started at 2004.
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


#include "eventos.h"
#include <iostream>
#include <stdio.h>
#include "jogo.h"
#include "partida.h"
#include "jogador.h"
#include "vetor.h"
#include "conexao.h"

#define TIPO_POS        1 // posicao do jogador
#define TIPO_CHAT       2
#define TIPO_COMANDO    3
#define TIPO_POSVEL     4 // posicao do jogador, pos. e vel. do disco e placar

struct s_msg_jogpos {
	int tipo;
	Vetor jogpos;
};

struct s_msg_jogdisco {
	int tipo;
	Vetor jogpos;
	Vetor discopos;
	Vetor discovel;
	int pontserv; // pontuacao do servidor
	int pontcli; // pontuacao do cliente
};

Jogo *Eventos::jogo = NULL;
fd_set Eventos::rfds, Eventos::wfds;
struct timeval Eventos::tv;

void Eventos::servidor(void *param, void *obj) {
	struct s_msg_jogpos *msg_jogpos;
	struct s_msg_jogdisco *msg_jogdisco;
	
	jogo = (Jogo *)obj;
	Conexao *conexao = jogo->getConexao();
	Vetor v;
	int socket = *((int *) param);
	int retval;

	conexao->limparMsg();

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(socket, &rfds);
	FD_SET(socket, &wfds);
	
	retval = select(socket + 1, &rfds, &wfds, NULL, &tv);

	if (retval) {
		
		if (FD_ISSET(socket, &rfds)) {	
			conexao->receberMsg(socket);
			// processa msg do oponente 
			msg_jogpos = (struct s_msg_jogpos *)conexao->msg;
			if (msg_jogpos->tipo == TIPO_POS) {
				v = msg_jogpos->jogpos;
				jogo->getPartida()->getJog(1)->setPos(v);
			}
		}

		if (FD_ISSET(socket, &wfds)) {

			// envia posicao para o oponente
			msg_jogdisco = (struct s_msg_jogdisco *)conexao->msg;			
			msg_jogdisco->tipo = TIPO_POSVEL;

			v = jogo->getPartida()->getJog(0)->getPos();
			msg_jogdisco->jogpos = v;
			v = jogo->getPartida()->getDisco()->getPos();
			msg_jogdisco->discopos = v;
			v = jogo->getPartida()->getDisco()->getVel();
			msg_jogdisco->discovel = v;

			msg_jogdisco->pontserv = jogo->getPartida()->getJog(0)->getPontuacao();
			msg_jogdisco->pontcli = jogo->getPartida()->getJog(1)->getPontuacao();
			
			conexao->enviarMsg(socket);
		}
	}
}

void Eventos::cliente(void *param, void *obj) {
	struct s_msg_jogpos *msg_jogpos;
	struct s_msg_jogdisco *msg_jogdisco;
	
	jogo = (Jogo *)obj;
	Conexao *conexao = jogo->getConexao();
	Vetor v;
	int socket = *((int *) param);
	int retval;

	conexao->limparMsg();

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(socket, &rfds);
	FD_SET(socket, &wfds);
	
	retval = select(socket + 1, &rfds, &wfds, NULL, &tv);

	if (retval) {
		
		if (FD_ISSET(socket, &rfds)) {	
			conexao->receberMsg(socket);
			// processa msg do oponente 
			msg_jogdisco = (struct s_msg_jogdisco *)conexao->msg;
			if (msg_jogdisco->tipo == TIPO_POSVEL) {
				v = msg_jogdisco->jogpos;
				jogo->getPartida()->getJog(1)->setPos(v);
				v = msg_jogdisco->discopos;
				jogo->getPartida()->getDisco()->setPos(v);
				v = msg_jogdisco->discovel;
				jogo->getPartida()->getDisco()->setVel(v);
				
				jogo->getPartida()->getJog(0)->setPontuacao(msg_jogdisco->pontcli);
				jogo->getPartida()->getJog(1)->setPontuacao(msg_jogdisco->pontserv);
			}
		}

		if (FD_ISSET(socket, &wfds)) {

			// envia posicao para o oponente
			msg_jogpos = (struct s_msg_jogpos *)conexao->msg;			
			msg_jogpos->tipo = TIPO_POS;

			v = jogo->getPartida()->getJog(0)->getPos();
			msg_jogpos->jogpos = v;
			
			conexao->enviarMsg(socket);
		}
	}
}
