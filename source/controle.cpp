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


#include "main.h"
#include "controle.h"
#include "vetor.h"
#include "jogo.h"
#include "partida.h"
#include "camera.h"
#include "visual.h"
#include "audio.h"
#include "config.h"
#include <ctype.h>

using std::vector;

Controle::Controle(Jogo *j, float SENSIBILIDADE) {
	jogo = j;

	// Limpa o buffer de teclas
	memset(KeyBuffer, 0, sizeof(KeyBuffer));

	this->SENSIBILIDADE = SENSIBILIDADE;
	// desativa o cursor
	SDL_ShowCursor(SDL_DISABLE);
	
	// Ativa unicode
// 	SDL_EnableUNICODE(1);

	// Inicializa sem jogadores registrados
	int i;
	for (i = 0; i < MAXJOG; i++) {
		jog[i].jog = NULL;
		jog[i].controle = 0;
	}
	qtdjog = 0;

	mouseButton = 0;
	
	precisaRedesenhar = false;
}

void Controle::registra(Jogador *j, int controle) {
	int i;

	if (qtdjog >= MAXJOG)
		return;
	
	for (i = 0; i < MAXJOG; i++)
		if (jog[i].jog == NULL) {
			jog[i].jog = j;
			jog[i].controle = controle;
			qtdjog++;
			return;
		}
}

void Controle::desregistra(Jogador *j) {
	int i;

	if (qtdjog <= 0)
		return;

	for (i = 0; i < MAXJOG; i++)
		if (jog[i].jog == j) {
			jog[i].jog = NULL;
			jog[i].controle = 0;
			qtdjog--;
		}
}

void Controle::processaEventos(){
	SDL_Event evento;
	Vetor v;

	lastKeys.clear();

	while (SDL_PollEvent( &evento) ) {
		switch (evento.type) {
			case SDL_VIDEOEXPOSE:
				precisaRedesenhar = true;
				break;
			case SDL_QUIT:
				// isso esta causando falhas no Windows
				SDL_Quit();
				break;
				
			case SDL_MOUSEBUTTONUP:
				this->mouseButton &= ~(1 << evento.button.button);
				break;
				
			case SDL_MOUSEBUTTONDOWN:
				this->mouseX = evento.button.x;
				this->mouseY = evento.button.y;
				this->mouseButton |= (1 << evento.button.button);
				
		 		switch (evento.button.button) {
					
					case SDL_BUTTON_WHEELUP:
						jogo->getVisual()->getCamera()->zoomdown();
						break;
					case SDL_BUTTON_WHEELDOWN:
						jogo->getVisual()->getCamera()->zoomup();
						break;
					
					case SDL_BUTTON_LEFT:
						break;
					case SDL_BUTTON_RIGHT:
						break;
				}
							//printf("botao:%d\n",evento.button.button);
				 break;
			case SDL_MOUSEMOTION:
				this->mouseX = evento.motion.x;
				this->mouseY = evento.motion.y;
				
				float xrel, yrel; // posicao do mouse relativa aa ultima posicao
				xrel = (float) evento.motion.xrel * SENSIBILIDADE;
				yrel = (float) evento.motion.yrel * SENSIBILIDADE;

				if (evento.button.button == SDL_BUTTON_MIDDLE)
				{
					jogo->getVisual()->getCamera()->rotatez(-xrel / 50);
					jogo->getVisual()->getCamera()->rotatex(-yrel / 50);
				}
				else {
					// calcula vetores horizontal (u) e vertical (v)
					// em relacao aa camera, para fazer a movimentacao
					// do jogador relativa aa camera
					Vetor v = (jogo->getVisual()->getCamera()->alvo - jogo->getVisual()->getCamera()->origem);
					v.z = 0;
					v.normaliza();

					Vetor u;
					u.x = v.x * cos(-M_PI/2) - v.y * sin(-M_PI/2);
					u.y = v.y * cos(-M_PI/2) + v.x * sin(-M_PI/2);
					u.z = 0;
					u.normaliza();

					int i;
					for (i = 0; i < MAXJOG; i++)
						if (jog[i].jog != NULL && jog[i].controle == CON_MOUSE)
							jog[i].jog->setVel(30 * (xrel*u - yrel*v));
				}			
				break;
			case SDL_KEYDOWN:
				this->KeyBuffer[evento.key.keysym.sym] = 1;
				if (evento.key.keysym.sym <= 127 && 
				 isalpha(evento.key.keysym.sym) && 
				 (this->KeyBuffer[SDLK_LSHIFT] ||
				 this->KeyBuffer[SDLK_RSHIFT]))
					evento.key.keysym.sym = (SDLKey)toupper((char)evento.key.keysym.sym);
				if (evento.key.keysym.sym == SDLK_KP_ENTER)
					evento.key.keysym.sym = SDLK_RETURN;
				lastKeys.push_back(evento.key.keysym.sym);
// 				if (evento.key.keysym.unicode & 0xFF80 == 0 )
// 					lastKeys.push_back(evento.key.keysym.unicode & 0x7F);
				
				switch (evento.key.keysym.sym) {
					// Audio
					case SDLK_KP_PLUS:
						jogo->getAudio()->aumentarMusica();
						break;
					case SDLK_KP_MINUS:
						jogo->getAudio()->diminuirMusica();
						break;
					case SDLK_m:
						if (SDL_GetModState() & KMOD_CTRL)
							jogo->getAudio()->desligarSom();
						break;
					//
					case (SDLK_HOME):
						jogo->getVisual()->reconfiguraCamera();
						jogo->getVisual()->defineCamera();
						break;
//					case (SDLK_r):
//						modelo->inicializaJogo();
//						break;
					case SDLK_f:
						if (SDL_GetModState() & KMOD_CTRL) {
							jogo->getVisual()->setarTelaCheia();
							jogo->getConfig()->set("TelaCheia", &jogo->getVisual()->telaCheia);
						}
						break;
						
					/* Grab input */
					case SDLK_F4:
						// alterna controles exclusivos para o jogo
						if (SDL_WM_GrabInput(SDL_GRAB_QUERY) == SDL_GRAB_OFF)
							SDL_WM_GrabInput(SDL_GRAB_ON);
						else
							SDL_WM_GrabInput(SDL_GRAB_OFF);
						break;

					/* Modos de camera */
					case SDLK_F5:
						jogo->getVisual()->getCamera()->setModo(CAM_ESTATICA);
						break;
					case SDLK_F6:
						jogo->getVisual()->getCamera()->setModo(CAM_GIRO);
						break;
					case SDLK_F7:
						jogo->getVisual()->getCamera()->setModo(CAM_TV);
						break;

					/* Sensibilidade do mouse */
					case SDLK_F9:
						if (this->SENSIBILIDADE > 0.1) {
							this->SENSIBILIDADE -= 0.1;
							jogo->getConfig()->set("Sensibilidade", &this->SENSIBILIDADE);
						}
						break;
					case SDLK_F10:
						if (this->SENSIBILIDADE < 4.1) {
							this->SENSIBILIDADE += 0.1;
							jogo->getConfig()->set("Sensibilidade", &this->SENSIBILIDADE);
						}
						break;
						
					/* Resolucao do video */
					case SDLK_F11:
						jogo->getVisual()->diminuirResolucao();
						jogo->getConfig()->set("TelaLargura", &jogo->getVisual()->telaLargura);
						jogo->getConfig()->set("TelaAltura", &jogo->getVisual()->telaAltura);
						break;
					case SDLK_F12:
						jogo->getVisual()->aumentarResolucao();
						jogo->getConfig()->set("TelaLargura", &jogo->getVisual()->telaLargura);
						jogo->getConfig()->set("TelaAltura", &jogo->getVisual()->telaAltura);
						break;
// 					case SDLK_q:
					case SDLK_ESCAPE:
// 						jogo->quitGame(0);
						break;
				}
				break;
			case SDL_KEYUP:
				this->KeyBuffer[evento.key.keysym.sym] = 0;
				break;
		}
	}

	/*** Processa teclas ***/

	if (KeyBuffer[SDLK_UP])
		jogo->getVisual()->getCamera()->moveup();
	if (KeyBuffer[SDLK_DOWN])
		jogo->getVisual()->getCamera()->movedown();
	if (KeyBuffer[SDLK_RIGHT])
		jogo->getVisual()->getCamera()->rotatez(M_PI / 10);
	if (KeyBuffer[SDLK_LEFT])
		jogo->getVisual()->getCamera()->rotatez(-M_PI / 10);
	if (KeyBuffer[SDLK_a] && SDL_GetModState() & KMOD_CTRL)
		jogo->getVisual()->getCamera()->moveleft();
	if (KeyBuffer[SDLK_d] && SDL_GetModState() & KMOD_CTRL)
		jogo->getVisual()->getCamera()->moveright();
}

