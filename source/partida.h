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


#ifndef _PARTIDA_H
#define _PARTIDA_H

#define MAXJOG 2
#define MODO_SINGLEPLAYER 0
#define MODO_MULTIPLAYER_CLIENTE  1
#define MODO_MULTIPLAYER_SERVIDOR 2

#include "jogo.h"
#include "disco.h"
#include "jogador.h"
#include "conexao.h"

class Colisao;

class Partida
{
	private:

		Jogador *jog[MAXJOG];
		Disco *disco;
		Jogo *jogo;
		Colisao *colisao;
		int jc, jb; // jogador de cima, jogador de baixo


	public:
		int modo;
		Partida(Jogo *j);
		void executa();
		void inicializa(int modo);

		Jogador *getJog(int n) { return jog[n]; }
		Disco *getDisco() { return disco; }
		
};

#endif
