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


#ifndef _DESENHO_H
#define _DESENHO_H

#include <SDL/SDL.h>
#include <GL/glut.h>
#include "camera.h"
#include "3DSLoader/main.h"

#include <string>
using namespace std;

class Jogo;
class Vetor;

//LD - coloquei esta variavel aki, como globai
//Variavel externa global, a variavel se encontra no visual.cpp
extern float gameFPS;

class Visual {
	private:
		Jogo *jogo;
		Camera *camera;	

	public:		
		GLuint listaMesa;
		int font;
		int telaLargura;
		int telaAltura;
		int telaCheia;
		string telaTitulo;
		int frame,tempobase;
		obj_type mesa;
		obj_type mallet;	
		obj_type puck;
		obj_type placar;
		int display[10];
		int logomesa;
	
		
		float retornaFPS(float ultimaFPS);
		
		Camera *getCamera() { return camera; }

		Visual(Jogo *j, int telaLargura=320, int telaAltura=240, bool telaCheia=true, string telaTitulo="indigente");
		int criarJanela(void);
		int setarVideo(int telaLargura, int telaAltura, bool telaCheia);
		int setarTelaCheia(void);
		int aumentarResolucao(void);
		int diminuirResolucao(void);
		GLvoid matarJanela(GLvoid);
		
		void Escrita2D(void);
		void EscreveString(float x, float y, void *font, const char *string);
		void cylinder(float r, float h, int segs=8);

		void defineCamera(void);
		void reconfiguraCamera(void);
		void RedimensionaTela(int x, int y);
		
		void Desenha(void);
		
		void DesenhaMesh(obj_type_ptr mesh);

		void DesenhaPlacar();
		void DesenhaJogador(int j);
		void DesenhaMesa(void);
		void DesenhaDisco(void);
		
		void inicio();
		void desenhaNoBuffer();
		void desenhaConsole();
		void iniciaEscrita2D();
		void fim();

		void recarregaTexturas();
		void inicializaOpenGL();
};
#endif

