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


#include <stdio.h>
#include "disco.h"
#include "area.h"
#include "vetor.h"
#include "audio.h"

void Disco::setPos(const Vetor &v)
{
	Vetor p = v;	
	colisao = 0;
	
	// Verifica limites
	if (p.x < area.topleft.x) {
		p.x = area.topleft.x;
		vel.x = -vel.x;
		colisao = 1;
	}
	if (p.x > area.bottomright.x) {
		p.x = area.bottomright.x;
		vel.x = -vel.x;
		colisao = 1;
	}
	if (p.y < area.topleft.y && (p.x < -15 || p.x > 15)) {
		p.y = area.topleft.y;
		vel.y = -vel.y;
		colisao = 1;
	}
	if (p.y > area.bottomright.y && (p.x < -15 || p.x > 15)) {
		p.y = area.bottomright.y;
		vel.y = -vel.y;
		colisao = 1;
	}

	oldpos = pos;
	pos = p;
	
}

void Disco::atualiza(float tempo)
{
	// intensidade do atrito
	float intensidade = 2;
	// aplica atrito
	Vetor atrito = -vel.versor() * intensidade * tempo / 1000;

	if (atrito.norma() >= vel.norma())
		vel.set(0, 0, 0);
	else
		vel += atrito;
	
	setPos(pos + vel * (tempo / 1000));

}
int Disco::colisaoMesa(){
	return colisao;
}
