
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
#include "conexao.h"
#include "eventos.h"
#include "audio.h"

Partida::Partida(Jogo *j)
{
	int i;
	
	jogo = j;
	this->modo = modo;

	disco = new Disco();
		
	//inicializaPartida();
}

void Partida::inicializa(int modo) {

	Vetor v, u, w;
	this->modo = modo;


	switch (modo) {
		case MODO_SINGLEPLAYER:
			jog[0] = new Jogador();
			jog[1] = new JogadorIA(this);
			break;
		case MODO_MULTIPLAYER_CLIENTE:
		case MODO_MULTIPLAYER_SERVIDOR:
			jog[0] = new Jogador();
			jog[1] = new JogadorNet(this);
			break;
	}
	jogo->getControle()->registra(jog[0], CON_MOUSE);
	jogo->getControle()->registra(jog[1], CON_IA);
	colisao = new Colisao(disco, jog[0], jog[1]);
	
	if (modo == MODO_MULTIPLAYER_SERVIDOR || modo == MODO_SINGLEPLAYER)
		jc = 1;
	else
		jc = 0;
	jb = (jc + 1) % 2; // o de baixo eh o outro

	
	v.set(0,0,0);
	disco->setPos(v);

	v.set(-70, 103);
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
	int sock = jogo->getConexao()->getSocket();
	
	jogo->getAudio()->tocarMusica();

	while(1) {
		initempo = glutGet(GLUT_ELAPSED_TIME);
		
		jogo->getControle()->processaEventos();

		switch (this->modo) {
			case MODO_MULTIPLAYER_SERVIDOR:
				jogo->getEventos()->servidor(&sock, jogo);
				break;
			case MODO_MULTIPLAYER_CLIENTE:
				jogo->getEventos()->cliente(&sock, jogo);
				break;
		}

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
				printf("pontuacao: %d a %d\n", jog[jc]->getPontuacao(), jog[jb]->getPontuacao());
				disco->setPos(zero);
				//disco->setVel(zero);
				jogo->getAudio()->tocarFX("gol");
			}
			else if (d.y > 100) {
				jog[jb]->addPontuacao();
				printf("pontuacao: %d a %d\n", jog[jc]->getPontuacao(), jog[jb]->getPontuacao());
				disco->setPos(zero);
				//disco->setVel(zero);
				jogo->getAudio()->tocarFX("gol");
			}
		}
				
		if (jog[jc]->getPontuacao() == 7 || jog[jb]->getPontuacao() == 7 ) {
			cout << "FIM DE JOGO" << endl;

			//TODO criar quitPartida e substituir aqui
			jogo->quitGame(0);
			
		}
		//////////////////////////////

		jog[0]->atualiza(tempo);
		jog[1]->atualiza(tempo);
		disco->atualiza(tempo);
		if (disco->colisaoMesa() > 0 ) {
			jogo->getAudio()->tocarFX("colisaodiscomesa");
		}
		jogo->getVisual()->getCamera()->atualiza(tempo);
		
		jogo->getVisual()->Desenha();
		
		fimtempo = glutGet(GLUT_ELAPSED_TIME);
		tempo = fimtempo - initempo;
	}
}
