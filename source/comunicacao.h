/*
		
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


#ifndef _COMUNICACAO_H
#define _COMUNICACAO_H

// tamanho maximo da mensagem
#define MAXBUF 256

#include <string>
using namespace std;


////////////////////////////////////////////////
//Classe para o tipo Objeto Canal de Comunicação
//
//
class Comunicacao {
	public:
		void *objeto;
		//----Atributos
		int ListeningSocket; // socket listening do servidor
		int Socket; // socket de comunicacao entre os dois processos

		//----Construtor / Destrutor
		Comunicacao();
		~Comunicacao();

		//----Métodos
		int abrirSocket(string host, int porta);
		int fecharSocket();
		void iniciarEventos(int socket, void (*eventos) (void *,void *));
		int ouvirSocket(int socket, void (*eventos) (void *,void*));
		
		// Acesso a variaveis
	//	void *getMsg() { return msg; }
};
#endif
