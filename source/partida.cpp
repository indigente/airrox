
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

#include <GL/glut.h>
#include "partida.h"
#include "jogo.h"
#include "jogador.h"
#include "jogadorIA.h"
#include "jogadorNet.h"
#include "visual.h"
#include "controle.h"
#include "colisao.h"
#include "camera.h"
#include "console.h"
// #include "conexao.h"
// #include "eventos.h"
#include "audio.h"
#include "gui/textwidget.h"

Partida::Partida(Jogo *j)
{
	int i;
	
	jogo = j;
	this->modo = modo;

	disco = new Disco();
	texto = new TextWidget(10, 46, 40);
		
	//inicializaPartida();
}
Partida::~Partida()
{
	delete texto;
	delete disco;
}

void Partida::inicializa(int modo) {

	Vetor v, u, w;
	this->modo = modo;


	switch (modo) {
		case MODO_SINGLEPLAYER:
			jog[0] = new Jogador();
			jog[1] = new JogadorIA(this);
			jogo->getControle()->registra(jog[0], CON_MOUSE);
			jogo->getControle()->registra(jog[1], CON_IA);
			break;
		// case MODO_MULTIPLAYER_CLIENTE:
		// case MODO_MULTIPLAYER_SERVIDOR:
		// 	jog[0] = new Jogador();
		// 	jog[1] = new JogadorNet(this);
		// 	jogo->getControle()->registra(jog[0], CON_MOUSE);
		// 	break;
		// case MODO_OBSERVADOR:
		// 	jog[0] = new JogadorNet(this);
		// 	jog[1] = new JogadorNet(this);
			break;
	}

	colisao = new Colisao(disco, jog[0], jog[1]);
	
	if (modo == MODO_MULTIPLAYER_SERVIDOR || modo == MODO_SINGLEPLAYER)
		jc = 1;
	else
		jc = 0;
	jb = (jc + 1) % 2; // o de baixo eh o outro

	
	v.set(0,0,0);
	//Vetor zerojb(-15,-80,0);
	
	disco->setPos(v);

//	v.set(-70, 103);
	v.set(-120, 150);
	//v.set(0,0,0);
	disco->setVel(v);

	disco->setRaio(5);
	jog[jb]->setRaio(8);
	jog[jc]->setRaio(8);

	w = disco->getRaio();
	u.set(-50,-100); u += w;
	v.set(50,100); v -= w;
	disco->setArea(u, v);

	
	w = jog[jc]->getRaio();
	u.set(-50,0); u += w;
	v.set(50,100); v -= w;
	jog[jc]->setArea(u, v);
	u.set(0, -1, 0);
	jog[jc]->setFrente(u);

	w = jog[jb]->getRaio();
	u.set(-50,-100); u += w;
	v.set(50,0); v -= w;
	jog[jb]->setArea(u, v);
	u.set(0, 1, 0);
	jog[jb]->setFrente(u);

	v.set(0,-25);
	jog[jc]->setPos(v);

	v.set(0, 25);
	jog[jb]->setPos(v);
	
	v.set(0,0);
	jog[jb]->setVel(v);
	jog[jc]->setVel(v);

	jogo->getVisual()->getCamera()->setModo(CAM_GIRO);
}

void Partida::executa()
{
	float tempo=0;
	float initempo, fimtempo;
	int pronto = 0; // indica se o usuario terminou de digitar a mensagem
	int i;
	bool fimDeJogo = false;
	
	jogo->getAudio()->tocarMusica();

	// loop da partida
	while(!fimDeJogo) {
		initempo = glutGet(GLUT_ELAPSED_TIME);
		
		// controle
		jogo->getControle()->processaEventos();
		if (jogo->getControle()->getKeyState(SDLK_ESCAPE))
			fimDeJogo = true;
		
		// texto, se estiver conectado
		// if (modo == MODO_MULTIPLAYER_SERVIDOR ||
		//  modo == MODO_MULTIPLAYER_CLIENTE ||
		//  modo == MODO_OBSERVADOR)
		// {
		// 	for (i = 0; i < jogo->getControle()->getLastKeys().size(); i++) {
		// 		if (jogo->getControle()->getLastKeys()[i] < 128)
		// 			pronto = texto->update((char)jogo->getControle()->getLastKeys()[i]);
		// 	}
			
		// 	if (pronto) {
		// 		jogo->getConexao()->enviaTexto(texto->getText());
		// 		// o servidor nao envia mensagem a si proprio.
		// 		// por isso eh necessario fazer um tratamento especial.
		// 		if (this->modo == MODO_MULTIPLAYER_SERVIDOR)
		// 			jogo->getConsole()->insere(texto->getText());
		// 		texto->limpa();
		// 		pronto = 0;
		// 	}
		// }

		// rede
		// switch (this->modo) {
		// 	int tipomsg;
		// 	case MODO_MULTIPLAYER_SERVIDOR:
		// 	case MODO_MULTIPLAYER_CLIENTE:
		// 		jogo->getConexao()->enviaEstado();
		// 	case MODO_OBSERVADOR:
		// 		while(tipomsg = jogo->getConexao()->recebeMensagem())
		// 		{
		// 			switch (tipomsg)
		// 			{
		// 				case TIPO_TEXTO:
		// 					jogo->getConsole()->insere((const char *)jogo->getConexao()->getDados() + 1);
		// 					break;
		// 				case TIPO_DESCONECTAR:							
		// 					if (modo == MODO_MULTIPLAYER_CLIENTE || modo == MODO_OBSERVADOR)
		// 					{
		// 						jogo->getConsole()->insere("-- O servidor desconectou");
		// 						jogo->atualizaConsole();
		// 						SDL_Delay(1200);
		// 						fimDeJogo = true;
		// 					}
		// 					else {
		// 						jogo->getConsole()->insere("-- Alguem desconectou");
		// 						jogo->atualizaConsole();
		// 					}
								
								
		// 			}
		// 		}
		// 		break;
		// 		break;
		// }

		// audio da colisao
		if ( colisao->checa()>0)
			jogo->getAudio()->tocarFX("colisaodiscojogador");
		
		// colisao simploria com o gol
		Vetor d = disco->getPos();
		Vetor zero(10, 10, 0);
		Vetor zerojc(15,-80,0);
	        Vetor zerojb(-15,80,0);
		
		if (d.x > -15 && d.x < 15) {
			if (d.y < -100) {
				jog[jc]->addPontuacao();
				jogo->getConsole()->insere("GOL");
				printf("pontuacao: %d a %d\n", jog[jc]->getPontuacao(), jog[jb]->getPontuacao());
				disco->setPos(zero);
				jogo->getAudio()->tocarFX("gol");
			}
			else if (d.y > 100) {
				jog[jb]->addPontuacao();
				jogo->getConsole()->insere("GOL");
				printf("pontuacao: %d a %d\n", jog[jc]->getPontuacao(), jog[jb]->getPontuacao());
				disco->setPos(zero);
				jogo->getAudio()->tocarFX("gol");
			}
		}
				
		if (jog[jc]->getPontuacao() == 7 || jog[jb]->getPontuacao() == 7 ) {
			cout << "FIM DE JOGO" << endl;
			fimDeJogo = true;
		}
		//////////////////////////////

		jog[0]->atualiza(tempo);
		jog[1]->atualiza(tempo);
		disco->atualiza(tempo);
		if (disco->colisaoMesa() > 0 ) {
			jogo->getAudio()->tocarFX("colisaodiscomesa");
		}
		jogo->getVisual()->getCamera()->atualiza(tempo);
		
		// desenha
		jogo->getVisual()->inicio();
		jogo->getVisual()->desenhaNoBuffer();
		texto->paint();
		jogo->getVisual()->fim();
		
		fimtempo = glutGet(GLUT_ELAPSED_TIME);
		tempo = fimtempo - initempo;
	}
	
	///////// fim de jogo! ///////////////
	
	// manda mensagem de desconexao
	// if (modo == MODO_MULTIPLAYER_SERVIDOR ||
	//  modo == MODO_MULTIPLAYER_CLIENTE ||
	//  modo == MODO_OBSERVADOR)
	// 	jogo->getConexao()->desconecta();

	// para a musica
	jogo->getAudio()->musicaParada();
}
