/*
	This project was developed by:
		Alexandre Amoedo Amorim (amoedo@im.ufba.br)
		Jailson A. de Brito JÃºnior (jailson@im.ufba.br)
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
#include "audio.h"
#include "console.h"
#include "gui/menu.h"
#include "gui/textwidget.h"
// #include "conexao.h"
#include "rede/aircliente.h"
#include "rede/airservidor.h"

void Jogo::inicializacao()
{
	visual = new Visual(this,320,240,false,"AirRox 0.0.3 ALFA");
	audio = new Audio();
	controle = new Controle(this);
}

Jogo::Jogo(int modo, char *host, int porta)
{
	inicializacao();
	this->jogaPartida(modo, host, porta);
	this->menu();
}

Jogo::Jogo() {
	inicializacao();

	this->menu();
}

Jogo::~Jogo() {
	delete visual;
	delete audio;
	delete controle;
}

/**
 * Joga a partida como servidor, cliente, observador ou singleplayer
 * @param modo Deve ser MODO_MULTIPLAYER_SERVIDOR, MODO_MULTIPLAYER_CLIENTE,
 *  MODO_OBSERVADOR ou MODO_SINGLEPLAYER
 * @param host Endereco do servidor (se necessario)
 * @param porta Porta de conexao (se necessario)
 */
void Jogo::jogaPartida(int modo, char *host, int porta)
{
	// reseta controle
	delete controle;
	controle = new Controle(this);

	// cria objetos
	console = new Console();
	partida = new Partida(this);
	
	switch (modo)
	{
		case MODO_MULTIPLAYER_SERVIDOR:
			this->iniciaServidor(porta);
			break;
		case MODO_MULTIPLAYER_CLIENTE:
		case MODO_OBSERVADOR:
			this->iniciaCliente(modo, host, porta);
			break;
		case MODO_SINGLEPLAYER:
			this->iniciaSinglePlayer();
			break;
	}

	delete partida;
	delete console;
}

void Jogo::atualizaConsole()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	visual->iniciaEscrita2D(); visual->desenhaConsole(); visual->fim();
}

/**
 * Tenta conectar-se a um servidor
 * @param modo Deve ser MODO_OBSERVADOR ou MODO_MULTIPLAYER_CLIENTE
 * @param host Endereco do servidor
 * @param porta Porta de conexao
 * @param tentativas Quantas vezes tentar conectar-se
 * @param intervalo Intervalo de tempo (em milisegundos) entre as tentativas
 * @return 1, se a conexao foi estabelecida; se não, 0
 */
int Jogo::tentaConectar(int modo, char *host, int porta, int tentativas, int intervalo)
{
	char msg[256];
	int i, t1, tipomsg;
	
	for (i = 1; i <= tentativas; i++)
	{
		sprintf(msg, "Tentando conectar a %s:%d (%d)", host, porta, i);
		console->insere(msg);		
		
		t1 = glutGet(GLUT_ELAPSED_TIME);
		
		((AirCliente *)(conexao))->conecta(host, porta, modo);
		
		// tenta receber mensagem no tempo esperado
		do {
			tipomsg = conexao->recebeMensagem();
			atualizaConsole();
		} while (glutGet(GLUT_ELAPSED_TIME) - t1 < intervalo && 
		   tipomsg != TIPO_CONEXAO_ACEITA && tipomsg != TIPO_CONEXAO_REJEITADA);
		
		// verifica a mensagem recebida
		switch (tipomsg)
		{
			case TIPO_CONEXAO_ACEITA:
				console->insere("Conexao aceita!");
				atualizaConsole();
				return 1;
				break;
			case TIPO_CONEXAO_REJEITADA:
				console->insere("Conexao rejeitada.");
				atualizaConsole();				
				return 0;
				break;
			default:
				console->insere("Nao houve resposta.");
				atualizaConsole();
				break;
		}
	}
	
	SDL_Delay(1200);
	// se chegou ate aqui, eh porque nao foi possivel contactar o servidor
	return 0;
	
}

/**
 * Inicia cliente (jogador ou observador).
 * Nao deve ser chamada diretamente! Use jogaPartida().
 * @param modo Deve ser MODO_OBSERVADOR ou MODO_MULTIPLAYER_CLIENTE
 * @param host Endereco do servidor
 * @param porta Porta de conexao
 */
void Jogo::iniciaCliente(int modo, char *host, int porta)
{
	if (modo == MODO_MULTIPLAYER_CLIENTE) // cliente jogador
		partida->inicializa(MODO_MULTIPLAYER_CLIENTE);
	else // cliente observador
		partida->inicializa(MODO_OBSERVADOR);
	conexao = new AirCliente(this->partida, 0);
	if (tentaConectar(modo == MODO_MULTIPLAYER_CLIENTE, host, porta))
		partida->executa();
	delete conexao;
}

/**
 * Inicia servidor.
 * Nao deve ser chamada diretamente! Use jogaPartida(). 
 * @param porta Porta de conexao
 */
void Jogo::iniciaServidor(int porta)
{
	conexao = new AirServidor(this->partida, porta);
	partida->inicializa(MODO_MULTIPLAYER_SERVIDOR);
	if (aguardaConexao())
		partida->executa();
	delete conexao;
}

int Jogo::aguardaConexao()
{
	int tipomsg;
	
	console->insere("Aguardando o cliente...");
	console->insere("(Tecle Esc para cancelar)");	
	
	do {
		controle->processaEventos();
		tipomsg = conexao->recebeMensagem();
		atualizaConsole();
	} while (tipomsg != TIPO_CONEXAO_ACEITA && !controle->getKeyState(SDLK_ESCAPE));
	
	if (controle->getKeyState(SDLK_ESCAPE)) // cancelou 
		return 0;
	else {
		console->insere("Cliente conectado!");
		atualizaConsole();
		SDL_Delay(1200);
		return 1;
	}
}

/** 
 * Joga contra o computador.
 * Nao deve ser chamada diretamente! Use jogaPartida().
 */
void Jogo::iniciaSinglePlayer()
{
	partida->inicializa(MODO_SINGLEPLAYER);
	partida->executa();
}

int Jogo::entradaDeTexto(TextWidget *text)
{
	int i;
	int pronto = 0;
	
	controle->processaEventos();
	for (i = 0; i < controle->getLastKeys().size(); i++) {
		if (controle->getLastKeys()[i] < 128)
			pronto = text->update((char)controle->getLastKeys()[i]);
	}
	text->paint();
	
	return pronto;
}

int Jogo::pegaPorta()
{
	static TextWidget *text = new TextWidget(20, 60, 5, GLUT_BITMAP_TIMES_ROMAN_24);
	int pronto = 0;
	
	text->limpa();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		visual->EscreveString(20, 30, GLUT_BITMAP_TIMES_ROMAN_24, "Digite a porta:");
		pronto = entradaDeTexto(text);
		SDL_GL_SwapBuffers();
	} while (!pronto);
	return atoi(text->getText());	
}

char *Jogo::pegaHost()
{
	static TextWidget *text = new TextWidget(20, 60, 50, GLUT_BITMAP_TIMES_ROMAN_24);
	int pronto = 0;
	
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		visual->EscreveString(20, 30, GLUT_BITMAP_TIMES_ROMAN_24, "Digite o endereco do servidor:");				
		pronto = entradaDeTexto(text);
		SDL_GL_SwapBuffers();
	} while (!pronto);
	return text->getText();
}

void Jogo::menu() {
	int ret = 0;
	int porta;
	char *host;
	
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
	  
	while (1)
	{
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
				jogaPartida(MODO_SINGLEPLAYER, 0, 0);
				break;
			case MENU_JOGAR_SERVIDOR:
				porta = pegaPorta();
				jogaPartida(MODO_MULTIPLAYER_SERVIDOR, 0, porta);
				break;
			case MENU_JOGAR_CLIENTE:
				host = pegaHost();
				porta = pegaPorta();
				jogaPartida(MODO_MULTIPLAYER_CLIENTE, host, porta);
				break;
			case MENU_OBSERVAR:
				host = pegaHost();
				porta = pegaPorta();
				jogaPartida(MODO_OBSERVADOR, host, porta);
				break;
			case MENU_SAIR:
				this->quitGame(0);
				break;
		}
	}
}

void Jogo::quitGame(int code) {
	SDL_Quit();
	printf("\n...Saindo do Jogo...:P\n\n");
	exit(code);
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

