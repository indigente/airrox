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
#include "modelo.h"
#include "vetor.h"
#include "visual.h"

#ifdef AIR_DEBUG
Vetor debug_eixo, debug_tang, debug_bolv, debug_bold;
#endif



/* Variaveis globais */
// executado no inicio e cada vez que alguem faz um gol
void Modelo::inicializaRodada() {
	bola.pos.x=0;
	bola.pos.y=0;
//	bola.vel.x = (rand() - RAND_MAX/2) / 2;
//	bola.vel.y = rand() - RAND_MAX/2;
	bola.vel.x = 0;
	bola.vel.y = 1;
		
	//normalizaVetor(&bola.vel); //Alterado por Lorde Darion, os caras sao doidos
	bola.vel.normaliza();

						  //Utilizando uma funcao q nao existia
//:\Projeto Netherdeep\airplus\source\airrox\modelo.cpp(22) : error C2065: 'normalizaVetor' : undeclared identifier
	bola.veltempo=50;
}

// executado so uma vez durante o jogo
void Modelo::inicializaJogo()
{
	/*
	camera.origem.x=0;
	camera.origem.y=10;
	camera.origem.z=-100;

	camera.alvo.x=0;
	camera.alvo.y=0;
	camera.alvo.z=0;*/
	
	bola.raio = 3;
	
	jogador[0].raio = 6;
	jogador[0].pos.x = 0;
	jogador[0].pos.y = -80;	
	jogador[0].pontos = 0;
	
	//copiaVetor(&jogador[0].oldpos, jogador[0].pos);
	jogador[0].oldpos = jogador[0].pos;

	jogador[1].raio = 6;
	jogador[1].pos.x = 0;
	jogador[1].pos.y = 80;
	jogador[1].pontos = 0;
	//copiaVetor(&jogador[1].oldpos, jogador[1].pos);
	jogador[0].oldpos = jogador[0].pos;
	
	mesa.comprimento=200;
	mesa.largura=100;
	mesa.atrito=0.998f;

	inicializaRodada();
}

/* Valida a coordenada de modo que ela represente um ponto dentro da mesa */
/* Recebe a coordenada em relacao aa mesa */
void Modelo::validaCoordenadasMesa(float *x, float *y, float raio) {
	if (*x - raio < -mesa.largura / 2) *x = -mesa.largura / 2 + raio;
	if (*x + raio > mesa.largura / 2)  *x = mesa.largura / 2 - raio;
	if (*y - raio < -mesa.comprimento / 2) *y = -mesa.comprimento / 2 + raio;
	if (*y + raio > mesa.comprimento / 2)  *y = mesa.comprimento / 2 - raio;	
}


// j eh o numero do jogador
void Modelo::colisaoJogadorBola(int j) {
	// Se nao colidiu, sai da funcao
	if (!(pow(jogador[j].pos.x - bola.pos.x, 2) + pow(jogador[j].pos.y - bola.pos.y, 2) <= pow(jogador[j].raio + bola.raio, 2)))
		return;
	
	// velocidade da bola
	Vetor bolavel(bola.vel.x, bola.vel.y);
	bolavel *= bola.velciclo;

	// normal (da bola para o jogador)
	Vetor normal(jogador[j].pos.x - bola.pos.x, jogador[j].pos.y - bola.pos.y);
	normal = (bolavel.prodEscalar(normal) / normal.prodEscalar(normal)) * normal; // projecao

	// vetor tangente
	Vetor tangente = bolavel - normal;
	
	// velocidade resultante (da bola)
	Vetor resultante = tangente - normal;
	bola.vel.x = resultante.x;
	bola.vel.y = resultante.y;

	// Atualiza a posicao da bola (para ficar _fora_ do jogador[j])	
	normal.x = bola.pos.x - jogador[j].pos.x;
	normal.y = bola.pos.y - jogador[j].pos.y;
	normal.normaliza();
	normal *= (bola.raio + jogador[j].raio);
	bola.pos.x = jogador[j].pos.x + normal.x;
	bola.pos.y = jogador[j].pos.y + normal.y;

	// Aplica velocidade do jogador `a bola
	float fator = 1.03; //(1 + normaVetor(jogador[j].vel) / mesa.largura * 5/2);
	bola.veltempo *= fator;

}

/* Recebe coordenadas de tela e retorna coordenadas de mesa */
void Modelo::coordsTela2Mesa(float *x, float *y) {
	//back_here
	float semiw = (float)tela.largura / 2;
	float semih = (float)tela.altura / 2;
	
	*x = (*x - semiw) / semiw * mesa.largura / 2;
	*y = -(*y - semih) / semih * (mesa.comprimento / 4 - jogador[0].raio) - mesa.comprimento / 4;
}

void Modelo::colisaoBolaMesa(void) {
	if (bola.pos.x - bola.raio < -mesa.largura / 2) {
		bola.pos.x = -mesa.largura/2 + bola.raio;
		bola.vel.x=-bola.vel.x;
	}		
	if (bola.pos.x + bola.raio > mesa.largura / 2) {
		bola.pos.x = mesa.largura/2 - bola.raio;
		bola.vel.x = -bola.vel.x;
	}
	if (bola.pos.y - bola.raio < -mesa.comprimento / 2) {
		bola.pos.y = -mesa.comprimento/2 + bola.raio;		
		bola.vel.y =-bola.vel.y;
	}
	if (bola.pos.y + bola.raio > mesa.comprimento / 2) {
		bola.pos.y = mesa.comprimento/2 - bola.raio;
		bola.vel.y =-bola.vel.y;
	}
	
//	validaCoordenadasMesa(&bola.pos.x, &bola.pos.y, (float)bola.raio);	
}

void Modelo::atualizaBola(void) {
	bola.pos.x += bola.vel.x * bola.velciclo;
	bola.pos.y += bola.vel.y * bola.velciclo;
}

void Modelo::calculaVelocidadesCiclo() {
	float fator;

	fator = (gameFPS ? 1 / gameFPS : 1 / 30);
	bola.velciclo = bola.veltempo * fator;
}

void Modelo::colisaoBolaGol()
{
	if (bola.pos.x >= -15.0 && bola.pos.x <= 15.0) {
		if (bola.pos.y < -mesa.comprimento/2 + bola.raio)  {
			jogador[1].pontos++;
			inicializaRodada();
			printf("GOL!!! Placar: %2d a %2d\n", jogador[0].pontos, jogador[1].pontos);
		}
		else if (bola.pos.y > mesa.comprimento/2 - bola.raio)  {
			jogador[0].pontos++;
			inicializaRodada();
			printf("GOL!!! Placar: %2d a %2d\n", jogador[0].pontos, jogador[1].pontos);
		}
	}
}

/* Guarda o estado atual do jogo (posicoes da bola e do jogador),
 * para usar no proximo ciclo */
void Modelo::guardaEstadoAtual(void) {
	//copiaVetor(&bola.oldpos, bola.pos);
    //copiaVetor(&jogador[0].oldpos, jogador[0].pos);
    //copiaVetor(&jogador[1].oldpos, jogador[1].pos);    
	
	//Alteracoes por LD
	bola.oldpos = bola.pos;
	jogador[0].oldpos = jogador[0].pos;
	jogador[1].oldpos = jogador[1].pos;
}

void Modelo::processaJogador(int j) {
    Vetor eixo;
    float dist;
    

    // se colidiu...
    dist = sqrt(pow(jogador[j].pos.x - bola.pos.x, 2) + pow(jogador[j].pos.y - bola.pos.y, 2));
   	if (dist <= jogador[j].raio + bola.raio) {
   	    eixo.x = jogador[j].pos.x - jogador[j].oldpos.x;
   	    eixo.y = jogador[j].pos.y - jogador[j].oldpos.y;
   	    eixo.normaliza();
   	    eixo *= dist - bola.raio - jogador[j].raio;
   	    eixo.inverte();
   	    
   	    jogador[j].pos += eixo;
	}
}

void Modelo::processaPosicaoJogadores(void) {
    validaCoordenadasMesa(&jogador[0].pos.x, &jogador[0].pos.y, jogador[0].raio);
    if (jogador[0].pos.y > -jogador[0].raio) jogador[0].pos.y = -jogador[0].raio;
	// solucao temporaria para o jogador 1. ToDo
	jogador[1].pos.x = jogador[0].pos.x;
	jogador[1].pos.y = mesa.comprimento/2 + jogador[0].pos.y;
	jogador[1].vel.y = jogador[0].vel.x;
	jogador[1].vel.y = jogador[0].vel.y;
}

void Modelo::jogaCiclo(void) {
	bola.veltempo *= mesa.atrito;
	calculaVelocidadesCiclo();
	
	/* Atualiza variaveis de jogo */
	processaPosicaoJogadores();
/*	processaJogador(0);
	processaJogador(1);*/
	colisaoJogadorBola(0);
	colisaoJogadorBola(1);
	colisaoBolaGol();
	colisaoBolaMesa();
	atualizaBola();
	
	jogador[0].vel.x = 0;
	jogador[0].vel.y = 0;
	
	guardaEstadoAtual();
	
	validaCoordenadasMesa(&jogador[0].pos.x, &jogador[0].pos.y, jogador[0].raio);
    	validaCoordenadasMesa(&jogador[1].pos.x, &jogador[1].pos.y, jogador[1].raio);
	
	/* Desenha */
	//glutPostRedisplay();
//	SDL_GL_SwapBuffers();
}
