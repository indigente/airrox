
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

#ifndef _JOGO_H
#define _JOGO_H

#include "main.h"

//#include <GL/glu.h>
#include "auxiliar.h"  // Vetor
#include "visual.h"   // camera

#define MAX_JOGADORES 2

class Modelo {
	public:
		typedef struct {
			int	largura;
			int	altura;
			int	cheia;
			int	bpp;
		} s_tela;

		typedef struct {
			float largura;
			float comprimento;
			float larg_gol;
			float atrito;
		} s_mesa;

		typedef struct {
			float massa;
			Vetor pos; // posicao
			Vetor oldpos; // posicao anterior
			Vetor vel; // velocidade (versor)
			float veltempo;
			float velciclo;
			int  raio; 
			int  altura;
			GLuint  lista;  // ToDo (display list id)
		} s_bola;

		typedef struct {
			float massa;
			Vetor pos;
			Vetor oldpos; // posicao anterior
			Vetor vel;
			GLuint tempo;
			int  raio;
			int  altura;
			int  pontos; // pontuacao do jogador
			GLuint  lista; // ToDo
		} s_jogador;

		s_mesa mesa;
		s_bola bola;
		s_jogador jogador[MAX_JOGADORES];
		s_tela tela;
	        Vetor debug_eixo, debug_tang, debug_bolv, debug_bold;
		
		void inicializaJogo();
		
		void jogaCiclo(void);
		void validaCoordenadasMesa(float *x, float *y, float raio);
		void coordsTela2Mesa(float *x, float *y);
		
		void inicializaRodada(); //Declarado por Lorde Darion
		void colisaoJogadorBola(int j); //Declarado por Lorde Darion
		void colisaoBolaMesa(void);	//Declarado por Lorde Darion
		void atualizaBola(void);	//...
		void calculaVelocidadesCiclo(); //...
		void colisaoBolaGol(); //...
		void guardaEstadoAtual(); //...
		void processaJogador(int j); //...
		void processaPosicaoJogadores(void); //...


};
#endif

