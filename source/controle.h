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


#ifndef _CONTROLE_H
#define _CONTROLE_H

#include <SDL/SDL.h>
#include <vector>
#include "partida.h" // MAXJOG

#define CON_MOUSE 1
#define CON_TECLADO 2
#define CON_JOYSTICK 4
#define CON_IA 8

using std::vector;

class Jogo;

class Controle {
	private:
		
		Jogo *jogo;
		float SENSIBILIDADE;

		struct {
			Jogador *jog;
			int controle;
		} jog[MAXJOG];
		int qtdjog;

		// Estado dos controles
		int mouseX, mouseY;
		int mouseButton;
		char KeyBuffer[SDLK_LAST];
		vector<SDLKey> lastKeys; // ultimas teclas pressionadas
		

	public:
		Controle(Jogo *j, float SENSIBILIDADE = 0.75);

		void registra(Jogador *j, int controle);
		void desregistra(Jogador *j);
		
		void processaEventos();

		int getMouseX() { return this->mouseX; }
		int getMouseY() { return this->mouseY; }
		int getMouseButton() { return this->mouseButton; }
		int getKeyState(SDLKey key) { return (key <= SDLK_LAST) ? KeyBuffer[key] : 0; }
		vector<SDLKey> getLastKeys() { return lastKeys; }
		
		void redesenhado() { precisaRedesenhar = false; }
		bool precisaRedesenhar;
};
#endif

