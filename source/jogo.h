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


#ifndef _JOGO_H
#define _JOGO_H

// declaracoes forward
class Partida;
class Controle;
class Visual;
class Eventos;
class Audio;
// class Conexao;
class AirRede;
class Console;

class Jogo {
	private:
		Partida *partida;
		Controle *controle;
		Visual *visual;
// 		Conexao *conexao;
		Eventos *eventos;
		Audio *audio;
		AirRede *conexao;
		Console *console;
		
		void inicializacao();
	
	public:
		Jogo();
		Jogo(int modo, char *host, int porta);
		~Jogo();

		void quitGame(int code);
		void menu(void);
		//static void eventos(void *param, void *objeto);
		
		Partida *getPartida() { return partida; }
		Eventos *getEventos() { return eventos; }
		Controle *getControle() { return controle; }
		Visual *getVisual() { return visual; }
// 		Conexao *getConexao() { return conexao; }
		AirRede *getConexao() { return conexao; }
		Audio *getAudio() { return audio; }
		Console *getConsole() { return console; }
};

#endif
