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
#include "eventos.h"
#include "audio.h"
#include "console.h"
#include "gui/menu.h"
#include "gui/textwidget.h"
// #include "conexao.h"
#include "rede/aircliente.h"
#include "rede/airservidor.h"

void Jogo::inicializacao()
{
// 	visual = new Visual(this,640,480,false,"AirRox 0.1 BETA");
	visual = new Visual(this,320,240,false,"AirRox 0.0.3 ALFA");
	
	controle = new Controle(this);
// 	conexao = new Conexao(this);
// 	eventos = new Eventos(this);
	partida = new Partida(this);
	audio = new Audio();
	console = new Console();
}

Jogo::Jogo(int modo, char *host, int porta)
{
	inicializacao();
	switch (modo)
	{
		case MODO_MULTIPLAYER_SERVIDOR:
			conexao = new AirServidor(this->partida, porta);
			partida->inicializa(MODO_MULTIPLAYER_SERVIDOR);
			partida->executa();
			break;
		case MODO_MULTIPLAYER_CLIENTE:
		case MODO_OBSERVADOR:
			if (modo == MODO_MULTIPLAYER_CLIENTE) // cliente jogador
				partida->inicializa(MODO_MULTIPLAYER_CLIENTE);
			else // cliente observador
				partida->inicializa(MODO_OBSERVADOR);
			conexao = new AirCliente(this->partida, 0);
			((AirCliente *)(conexao))->conecta(host, porta, modo == MODO_MULTIPLAYER_CLIENTE);
			partida->executa();
		case MODO_SINGLEPLAYER:
			partida->inicializa(MODO_SINGLEPLAYER);
			partida->executa();
			break;
	}
}

Jogo::Jogo() {
	inicializacao();

	this->menu();
}

Jogo::~Jogo() {
	delete visual;
	delete controle;
	delete partida;
	delete conexao;
	delete audio;
	delete console;
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
	int pronto = 0;
	int i;
	TextWidget *text = new TextWidget(20, 20, 50, GLUT_BITMAP_TIMES_ROMAN_24);	
	int porta;
	char host[256];
	
#define MENU_JOGAR_PC 2
#define MENU_JOGAR_SERVIDOR 3
#define MENU_JOGAR_CLIENTE 4
#define MENU_OBSERVAR 5
#define MENU_SAIR  6

	Menu *menu = new Menu();

	menu->addItem(MENU_JOGAR_PC, "../imagens/mjogar1.bmp",
	  "../imagens/mjogar1h.bmp", 0, 20, LEFT);
	menu->addItem(MENU_JOGAR_SERVIDOR, "../imagens/mjogar2.bmp",
	  "../imagens/mjogar2h.bmp", 0, 60, LEFT);
	menu->addItem(MENU_JOGAR_CLIENTE, "../imagens/mjogar3.bmp",
	  "../imagens/mjogar3h.bmp", 0, 100, LEFT);
	menu->addItem(MENU_OBSERVAR, "../imagens/mobs.bmp",
	  "../imagens/mobsh.bmp", 0, 140, LEFT);
	menu->addItem(MENU_SAIR, "../imagens/msair.bmp",
	  "../imagens/msairh.bmp", 0, 180, LEFT);
	  
	menu->init();

	SDL_ShowCursor(SDL_ENABLE);

	do
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		controle->processaEventos();
		ret = menu->update(controle->getMouseX(), 
		  controle->getMouseY(), controle->getMouseButton());
		SDL_GL_SwapBuffers();
	} while (!ret);
	
	SDL_ShowCursor(SDL_DISABLE);
	menu->deinit();

	switch (ret)
	{
		case MENU_JOGAR_PC:
			partida->inicializa(MODO_SINGLEPLAYER);
			partida->executa();
			break;
		case MENU_JOGAR_SERVIDOR:
			pronto = 0;			
			text->posiciona(20, 60);
			text->limpa();
			do
			{	
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				visual->EscreveString(20, 30, GLUT_BITMAP_TIMES_ROMAN_24, "Digite a porta:");
				controle->processaEventos();
				for (i = 0; i < controle->getLastKeys().size(); i++) {
					if (controle->getLastKeys()[i] < 128)
						pronto = text->update((char)controle->getLastKeys()[i]);
				}
				text->paint();
		
				SDL_GL_SwapBuffers();
			} while (!pronto);
			porta = atoi(text->getText());
			conexao = new AirServidor(this->partida, porta);
			partida->inicializa(MODO_MULTIPLAYER_SERVIDOR);
			partida->executa();
			break;
		case MENU_JOGAR_CLIENTE:
		case MENU_OBSERVAR:
			pronto = 0;
			text->posiciona(20, 60);
			text->limpa();
			do
			{	
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				visual->EscreveString(20, 30, GLUT_BITMAP_TIMES_ROMAN_24, "Digite o endereco do servidor:");				
				controle->processaEventos();
				for (i = 0; i < controle->getLastKeys().size(); i++) {
					if (controle->getLastKeys()[i] < 128)
						pronto = text->update((char)controle->getLastKeys()[i]);
				}
				text->paint();
		
				SDL_GL_SwapBuffers();
			} while (!pronto);
			strcpy(host, text->getText());

			pronto = 0;
			text->posiciona(20, 60);
			text->limpa();
			do
			{	
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				visual->EscreveString(20, 30, GLUT_BITMAP_TIMES_ROMAN_24, "Digite a porta:");
				controle->processaEventos();
				for (i = 0; i < controle->getLastKeys().size(); i++) {
					if (controle->getLastKeys()[i] < 128)
						pronto = text->update((char)controle->getLastKeys()[i]);
				}
				text->paint();
		
				SDL_GL_SwapBuffers();
			} while (!pronto);
			porta = atoi(text->getText());
							
			if (ret == MENU_JOGAR_CLIENTE) // cliente jogador
				partida->inicializa(MODO_MULTIPLAYER_CLIENTE);
			else // cliente observador
				partida->inicializa(MODO_OBSERVADOR);
			conexao = new AirCliente(this->partida, 0);
			((AirCliente *)(conexao))->conecta(host, porta, ret == MENU_JOGAR_CLIENTE);
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
					cout << "ser(V)idor \n(C)liente \n(O)bservador" << endl;
					cin >> c;
					c = toupper(c);
					switch (c) {
						case 'V':
							cout << "Escolha a porta:" << endl;
							cin >> porta;
							partida->inicializa(MODO_MULTIPLAYER_SERVIDOR);
// 							conexao->servidor(porta,eventos->servidor);
							conexao = new AirServidor(this->partida, porta);
							SDL_WM_SetCaption("servidor",NULL); // DEBUG
							partida->executa();
							break;
						case 'C':
						case 'O':
							cout << "Escolha o servidor:" << endl;
							cout << "Host:  ";
							cin >> host;
							cout << "Porta: ";
							cin >> porta;
							if (c == 'C') // cliente jogador
								partida->inicializa(MODO_MULTIPLAYER_CLIENTE);
							else // cliente observador
								partida->inicializa(MODO_OBSERVADOR);
// 							conexao->cliente(host,porta,eventos->cliente);
							conexao = new AirCliente(this->partida, 0);
							SDL_WM_SetCaption(c == 'C' ? "cliente" : "observador",NULL); // DEBUG
							((AirCliente *)(conexao))->conecta(host.c_str(), porta, c == 'C');
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

