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


#include "jogo.h"
#include "partida.h"
#include <stdio.h>
#include <ctype.h>

#define JOGO_TITULO "AirroX 0.0.0.0.2"

void instrucoes()
{
	printf("AirroX\n");
	printf("Parametros:\n");
	printf("  servidor -> S (porta)\n");
	printf("  cliente -> C (host) (porta)\n");
	printf("  observador -> O (host) (porta)\n");
	printf("  contra o PC -> P");
	printf("\n");
}

int main(int argc, char **argv) {
	Jogo *jogo;
	
	// o primeiro argumento eh o nome chamado
	
	// se forneceu argumentos...
	if (argc > 1)
	{
		char opcao = argv[1][0];
		switch (toupper(opcao))
		{
			// servidor
			case 'S':
				if (argc == 3)
					jogo = new Jogo(MODO_MULTIPLAYER_SERVIDOR, 0, atoi(argv[2]));
				else
					instrucoes();
				break;
			// cliente
			case 'C':
				if (argc == 4)
					jogo = new Jogo(MODO_MULTIPLAYER_CLIENTE, argv[2], atoi(argv[3]));
				else
					instrucoes();
				break;
			// observador
			case 'O':
				if (argc == 4)
					jogo = new Jogo(MODO_OBSERVADOR, argv[2], atoi(argv[3]));
				else
					instrucoes();
				break;
			// contra o PC
			case 'P':
				jogo = new Jogo(MODO_SINGLEPLAYER, 0, 0);
				break;
			// parametro invalido
			default:
				instrucoes();
				break;
		}
	}
	else
		jogo = new Jogo();
	
	return 1;
}
