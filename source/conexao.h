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


#ifndef _CONEXAO_H
#define _CONEXAO_H


#include "comunicacao.h"
#include "jogo.h"

class Conexao : public Comunicacao {
	private:
		int porta;
		string enderecoservidor;
		void (*fnEventos) (void *,void*);
		
	public:
/*		struct s_msg {
			int tipo;
			float x;
			float y;
			char comando[255];
		};
		s_msg msg;*/
		char msg[255];

	
		Conexao(Jogo *j);
		Conexao::~Conexao();
		void servidor(int porta, void (*eventos) (void *,void*));
		void cliente(string enderecoservidor, int porta, void (*eventos) (void *,void *));
		void limparMsg();
		void enviarMsg(int socket);
		int receberMsg(int socket);

//		void (*getFnEventos())(void *, void*) { return fnEventos; }
		int getSocket() { return Socket; }
		int getListeningSocket() { return ListeningSocket; }
						
};

#endif
