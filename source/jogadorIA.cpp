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


#include "jogador.h"
#include "jogadorIA.h"
#include "partida.h"
#include "disco.h"
#include "vetor.h"
#include "objeto.h"
#include "area.h"

JogadorIA::JogadorIA(Partida *partida, float maxvel) {
	this->partida = partida;
	this->maxvel = maxvel;
}

void JogadorIA::tomaDecisao() {
	float px, py;
	
	Vetor i(1, 0);
	Vetor j(0, 1);
	
	Vetor d = (partida->getDisco()->getPos() - this->pos).versor() * maxvel;
	Vetor dx = d.prodEscalar(i) * i;
	Vetor dy = d.prodEscalar(j) * j;

	Vetor b = partida->getDisco()->getVel();
	Vetor by = b.prodEscalar(j) * j;

	if (!area.bContem(partida->getDisco()->getPos())) {
		px = 1.0;
		py = -0.35;
	}
	else {
		px = 1.0;
		py = 0.4;
	}

	// se o disco estiver na frente
	if (frente.prodEscalar(partida->getDisco()->getPos() - this->getPos())  > 0)	
		this->setVel(dx * px + dy * py); // antes era by * py
	else // se o disco estiver atras
		this->setVel(-dx * px + dy * py); // antes era by * py

//	this->setVel((partida->getDisco()->getPos() - this->pos) * maxvel);
}

void JogadorIA::setVel(const Vetor &v) {
	if (v.norma() > maxvel)
		vel = v.versor() * maxvel;
	else
		vel = v;
}

void JogadorIA::atualiza(float tempo)
{
	tomaDecisao();
	this->setPos(pos + vel * tempo / 1000);
}
