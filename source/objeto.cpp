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


#include "objeto.h"
#include "vetor.h"
#include "area.h"

void Objeto::setArea(const Vetor &v, const Vetor &u)
{
	area.topleft = v;
	area.bottomright = u;
}

void Objeto::setPos(const Vetor &v)
{
	Vetor p = v;

	// Verifica limites
	if (p.x < area.topleft.x)
		p.x = area.topleft.x;
	if (p.x > area.bottomright.x)
		p.x = area.bottomright.x;
	if (p.y < area.topleft.y)
		p.y = area.topleft.y;
	if (p.y > area.bottomright.y)
		p.y = area.bottomright.y;

	oldpos = pos;
	pos = p;
}
