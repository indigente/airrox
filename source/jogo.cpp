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


#include <iostream>
#include <string>

using namespace std;

#include <stdlib.h>
#include <GL/glut.h>
#include <SDL/SDL.h>

#include "jogo.h"
#include "partida.h"
#include "controle.h"
#include "visual.h"
#include "conexao.h"
#include "eventos.h"
#include "audio.h"
#include "gui/menu.h"

Jogo::Jogo() {
	
	visual = new Visual(this,640,480,false,"AirRox 0.1 BETA");
	controle = new Controle(this);
	conexao = new Conexao(this);
	eventos = new Eventos(this);
	partida = new Partida(this);
	audio = new Audio();
//	gui = new Gui();
	this->menu();
	
	//partida->executa(); // TODO: desvincular inicio da partida do construtor de jogo
}

Jogo::~Jogo() {
	delete visual;
	delete controle;
	delete partida;
	delete conexao;
	delete audio;
}


/*
void Jogo::eventos(void *param, void *objeto){
	printf("jogo::eventos\n");
	Jogo *obj = (Jogo *)objeto;
	Vetor pos;
	int socket = (int) *param;
	
	struct s_msg_pos {
		char tipo;
		float x;
		float y;
	};
	s_msg_pos msg;	
	
	// envia posicoes para o oponente
	msg.tipo = TIPO_POS;
	pos = obj->getPartida.jog[0]->getPos();
	msg.x = pos.x;
	msg.y = pos.y;
	Comunicacao::enviarMsg(socket,msg);
	// espera por uma msg do oponente
	while(Comunicacao::receberMsg(socket)) {
		// processa msg do oponente
		if (msg.tipo == TIPO_POS) {
			pos.x = msg.x;
			pos.y = msg.y;
			obj->getPartida.jog[1]->setPos(pos);	
			
		}
		      
		// envia posicao para o oponente
		msg.tipo = TIPO_POS;
		pos = obj->getPartida().jog[0]->getPos();
		msg.x = pos.x;
		msg.y = pos.y;	
		Comunicacao::enviarMsg(socket,msg);
		
	}	
}
*/


void Jogo::menu() {
	int ret = 0;
#define MENU_JOGAR 2
#define MENU_SAIR  3
	
	Menu *menu = new Menu();

	menu->addItem(MENU_JOGAR, "../imagens/mjogar.bmp",
	  "../imagens/mjogarh.bmp", 20, 40);
	menu->addItem(MENU_SAIR, "../imagens/msair.bmp",
	  "../imagens/msairh.bmp", 20, 100);
	  
	menu->init();

	SDL_ShowCursor(SDL_ENABLE);

	while (!ret)
	{
		controle->processaEventos();
		ret = menu->update(controle->getMouseX(), 
		  controle->getMouseY(), controle->getMouseButton());
//		SDL_UpdateRect(SDL_GetVideoSurface(), 0, 0, 0, 0);
//		SDL_Flip(SDL_GetVideoSurface());
		SDL_GL_SwapBuffers();
	}
	
	SDL_ShowCursor(SDL_DISABLE);
	menu->deinit();

	switch (ret)
	{
		case MENU_JOGAR:
			partida->inicializa(MODO_SINGLEPLAYER);
			partida->executa();
			break;
		case MENU_SAIR:
			this->quitGame(0);
			break;
	}

	
}

/*
void Jogo::menu() {
	//Menu bizarro temporario
	char b,c;
	int porta;
	string host;
	
	
	do {
		system("clear");
		cout << "b:" << b << endl;
		cout << "AirRox v.0.1" << endl;
		cout << "(U)m jogador\n(M)ulti-Jogador\n(s)air" << endl;
		cin >> b;
		b = toupper(b);
		
	
		switch (b){
			case 'U':
				partida->inicializa(MODO_SINGLEPLAYER);
				partida->executa();
				cout << "Singleplayer" << endl;
				break;
			case 'M':
				cout << "Multiplayer" << endl;
				do {
					cout << "ser(V)idor \n(C)liente" << endl;
					cin >> c;
					c = toupper(c);
					switch (c) {
						case 'V':
							cout << "Escolha a porta:" << endl;
							cin >> porta;
							partida->inicializa(MODO_MULTIPLAYER_SERVIDOR);
							conexao->servidor(porta,eventos->servidor);
							partida->executa();
							break;
						case 'C':
							cout << "Escolha o servidor:" << endl;
							cout << "Host:  ";
							cin >> host;
							cout << "Porta: ";
							cin >> porta;
							partida->inicializa(MODO_MULTIPLAYER_CLIENTE);
							conexao->cliente(host,porta,eventos->cliente);
							partida->executa();
							break;
					}
				} while ( c!='S');

				break;
		} 
	} while (c != 'S');
	this->quitGame(0);
}
*/

void Jogo::quitGame(int code) {
	SDL_Quit();
	printf("\n...Saindo do Jogo...:P\n\n");
	exit(code);
}

