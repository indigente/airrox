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


#ifndef _CAMERA_H
#define _CAMERA_H

#include <math.h>  // M_PI
#include "vetor.h"
#include "objeto.h"

#define CAM_ESTATICA 0
#define CAM_GIRO 1
#define CAM_TV 2

class Jogo;

class Camera
{
	private:
		// cinematica
		int modo; // estatica, giro, etc.
		float contador;
		Jogo *jogo;
		
	public:
		Vetor origem;
		Vetor alvo;

		Camera(Jogo *jogo, Vetor origem, Vetor alvo);
		void zoomup(void);
		void zoomdown(void);
		void rotatez(double theta);
		void rotatex(double theta);
		void moveup(void);
		void movedown(void);
		void moveleft(void);
		void moveright(void);

		void setOrigem(const Vetor &v) { origem = v; }
		void setAlvo(const Vetor &v) { alvo = v; }
		void setModo(int modo);

		void atualiza(float tempo);
};

#endif
