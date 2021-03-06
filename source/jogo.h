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
class AirRede;
class Console;
class TextWidget;
class Config;

/**
 * Classe principal do jogo
 */
class Jogo {
	private:
		Partida *partida;
		Controle *controle;
		Visual *visual;
		Eventos *eventos;
		Audio *audio;
		AirRede *conexao;
		Console *console;
		Config *config;
		
		void inicializacao();
	
	public:
		Jogo();
		Jogo(int modo, char *host, int porta);
		~Jogo();

		void quitGame(int code);
		void menu(void);
		
		void jogaPartida(int modo, char *host, int porta);
		void iniciaCliente(int modo, char *host, int porta);
		void iniciaServidor(int porta);
		void iniciaSinglePlayer();
		
		int entradaDeTexto(TextWidget *text);
		char *pegaHost();
		int pegaPorta();
		
		int aguardaConexao();
		int tentaConectar(int modo, char *host, int porta, int tentativas=2, int intervalo=2000);
		void atualizaConsole();

		// acesso aos membros
		Partida *getPartida() { return partida; }
		Eventos *getEventos() { return eventos; }
		Controle *getControle() { return controle; }
		Visual *getVisual() { return visual; }
		AirRede *getConexao() { return conexao; }
		Audio *getAudio() { return audio; }
		Console *getConsole() { return console; }
		Config *getConfig() { return config; }
};

#endif
