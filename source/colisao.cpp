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


#include <math.h>
#include "colisao.h"
#include "jogador.h"
#include "disco.h"
#include <stdio.h> // TODO: retirar isso e remover o debug

Colisao::Colisao(Disco *disco, Jogador *jog1, Jogador *jog2)
{
	this->disco = disco;
	this->jog[0] = jog1;
	this->jog[1] = jog2;
}

/*
int Colisao::colisaoJogadorDisco(int j)
{
	static bool antcol[2];
	// Se nao colidiu, sai da funcao
	if ( (jog[j]->getPos() - disco->getPos()).norma() > jog[j]->getRaio() + disco->getRaio()) {
		antcol[j] = false;
		return 0;
	}

	if (antcol[j] == true) {
		return 0;
	}
	// normal (do disco para o jogador)
	Vetor normal(jog[j]->getPos() - disco->getPos());
	normal = (disco->getVel().prodEscalar(normal) / normal.prodEscalar(normal)) * normal; // projecao

	// vetor tangente
	Vetor tangente = disco->getVel() - normal;
	
	// velocidade resultante (da disco)
	disco->setVel(tangente - normal);
	if (tangente.z != 0 || normal.z != 0)
		printf("Erro!!!\n"); // DEBUG

	// Atualiza a posicao do disco (para ficar _fora_ do jog[j]->	
	normal = (disco->getPos() - jog[j]->getPos()).versor() * (disco->getRaio() + jog[j]->getRaio());
	disco->setPos(jog[j]->getPos() + normal);

	// Aumenta velocidade do disco (armengue)
	Vetor v = disco->getVel().versor();
	disco->setVel(disco->getVel() + v * 1.8);
	
	return 1;
}
*/

/**
 * Colisao entre o jogador j e o disco.
 * Algoritmo extraído do livro "Mathematics for 3D Game
 * Programming & Computer Graphics", 1a edicao, p221-225
 */

int Colisao::colisaoJogadorDisco(int j)
{
	static bool antcol[2]; // estado anterior da colisao (true/false)
		
	// Seja P o jogador e Q o disco.
	// Seja P1 a posicao anterior e P2 a posicao atual (o mesmo vale para Q)
	Vetor P1(jog[j]->getOldPos()), P2(jog[j]->getPos());
	Vetor Q1(disco->getOldPos()), Q2(disco->getPos());
	// Calcularemos agora as velocidades
	Vetor VP = P2 - P1;
	Vetor VQ = Q2 - Q1;
	// Definindo variaveis para otimizar o calculo
	Vetor A = P1 - Q1;
	Vetor B = VP - VQ;
	float A2 = A.prodEscalar(A);
	float B2 = B.prodEscalar(B);
	float AB = A.prodEscalar(B);
	float AB2 = AB * AB;
	// quadrado da distancia entre os centros
	float d2 = pow(jog[j]->getRaio() + disco->getRaio(), 2);
	float t; // tempo
	
	// se ainda nao esta colidindo
	if ((jog[j]->getPos() - disco->getPos()).norma() > jog[j]->getRaio() + disco->getRaio()) {
		

		//LD fixes
		float zero = 0.0f;

		// Teste para verificar a nao-colisao
		if (B == zero)  // movimento relativo == 0
			{ antcol[j] = false; return 0; }  // nao houve colisao
		
		// Teste para verificar a nao-colisao
		if (A2 - AB2 / B2 > d2)
			{ antcol[j] = false; return 0; }  // nao houve colisao

		// Teste para verificar a nao colisao
		float raiz = AB2 - B2 * (A2 - d2);
		if (raiz < 0)
			{ antcol[j] = false; return 0; }  // nao houve colisao
		
		// tempo da colisao
		t = (-(AB) - sqrt(raiz)) / B2;

		// Teste para verificar a nao-colisao
		if (!(t > 0 && t <= 1))
			{ antcol[j] = false; return 0; }  // nao houve colisao

		// Verifica se ja houve colisao no instante anterior
		if (antcol[j])
			return 0;
			
		// Atualiza posicoes para o instante de colisao
		jog[j]->setPos(P1 + t * VP);
		disco->setPos(Q1 + t * VQ);	
	}
	else {
		// Atualiza a posicao do disco (para ficar _fora_ do jog[j]->	
		Vetor normal = (disco->getPos() - jog[j]->getPos()).versor() * (disco->getRaio() + jog[j]->getRaio());
		disco->setPos(jog[j]->getPos() + normal);
	}

	// normal (do disco para o jogador)
	Vetor normal(jog[j]->getPos() - disco->getPos());
	normal = (disco->getVel().prodEscalar(normal) / normal.prodEscalar(normal)) * normal; // projecao

	// vetor tangente
	Vetor tangente = disco->getVel() - normal;
	
	// velocidade resultante (da disco)
	disco->setVel(tangente - normal);
	
	// afasta um pouco o disco do jogador
	disco->setPos(disco->getPos() + disco->getVel().versor() * 3);

	// Aumenta velocidade do disco (armengue)
	Vetor v = disco->getVel().versor();
	if (v.norma() == 0)
		v = jog[j]->getVel().versor() * 10.0;
	disco->setVel(disco->getVel() + v * 2.0);

	antcol[j] = true;
	return 1;
}

int Colisao::checa()
{
	int a,b;
	
	a = colisaoJogadorDisco(0);
	b = colisaoJogadorDisco(1);

	return a?a:b;
}
				
