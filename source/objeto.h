
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

#ifndef _OBJETO_H
#define _OBJETO_H

#include "vetor.h"
#include "area.h"

/**
 * Modelo de objeto espacial movel.
 */
class Objeto
{
	protected:
		Vetor pos;
		Vetor oldpos;
		Vetor vel;
		Area area;
		float massa;

	public:
		Vetor getPos() const { return pos; }
		Vetor getOldPos() const { return oldpos; }
		Vetor getVel() const { return vel; }
		float getMassa() const { return massa; }

		virtual void setPos(const Vetor &v);
		virtual void setVel(const Vetor &v) { vel = v; }
		virtual void setMassa(float f) { massa = f; }
		virtual void setArea(const Vetor &v, const Vetor &u);

		virtual void atualiza(float tempo) = 0;
};

#endif

