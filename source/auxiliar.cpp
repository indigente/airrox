
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
#include "auxiliar.h"

//Rotinas Construtoras/Demolidoras adicionadas por LD
auxiliar::auxiliar(void) {
		//Carregamento/Construtor
		//Adicionado por LD
	this->frame = 0;
	this->tempo = 0;
	this->tempobase = 0;

}

auxiliar::~auxiliar(void) {
		//Descarregamento
}

void auxiliar::Eixos(void) {
	glBegin(GL_LINES);
	glColor3f(1.0f,0.0f,0.0f); //Eixo Ox
	glVertex3i(0,0,10);
	glVertex3i(10,0,10);
	
	glColor3f(0.0f,1.0f,0.0f); //Eixo Oy
	glVertex3i(0,0,10);
	glVertex3i(0,10,10);

	glColor3f(0.0f,0.0f,1.0f); //Eixo Oz
	glVertex3i(0,0,10);
	glVertex3i(0,0,20);
	glEnd();
}

float auxiliar::retornaFPS(float ultimaFPS) {
	float	novaFPS;
	frame++;
	tempo = glutGet(GLUT_ELAPSED_TIME);
	if (tempo - tempobase > 1000) {
		novaFPS = frame*1000/(tempo-tempobase);
		tempobase = tempo;
		frame = 0;
		return novaFPS;
	}else
		return ultimaFPS;
}
void auxiliar::quitGame(int code) {
	SDL_Quit();
	printf("\n...Saindo do AirRox...:P\n\n");
	exit(code);
}
