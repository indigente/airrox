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


#ifndef _JOGADOR_H
#define _JOGADOR_H

#include "objeto.h"
#include "area.h"
#include "vetor.h"

/**
 * Jogador
 */
class Jogador: public Objeto
{
	private:
		float raio;
		int pontuacao;

	protected:
		Vetor frente; // vetor que parte do centro da mesa e aponta para o gol
		
	public:
		Jogador() { pontuacao = 0; }
		void setFrente(const Vetor &frente) { this->frente = frente; }
		void atualiza(float tempo);
		void setRaio(float r) { raio = r; }
		float getRaio() { return raio; }
		Vetor getFrente() { return frente; }
		
		void addPontuacao() { pontuacao++; }
		int getPontuacao() { return pontuacao; }		
		int setPontuacao(int p) { pontuacao = p; }
};
#endif
