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


// Universidade Federal da Bahia
// Instituto de Matemática
// Departamento de Ciência da Computação
// Matéria: MAT-147 Linguagens de Programação I
// Prof: Augusto Loureiro
// Alunos:
//    Jailson A. de Brito Júnior
//    Wilson de Oliveira Leite Júnior
// 
// Semestre: 2003.2
// Data: 10/05/2004
// 
// Trabalho II - Implementação de um serviço de reserva de recurso,
// composto por processo servidor e um processo cliente em C++
// 
//
// // 
// COMUNICAÇÃO COM SOCKETS
// 

#include <iostream>
#include <string>
#include <netdb.h>
#include <netinet/in.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

#include "comunicacao.h"

Comunicacao::Comunicacao() {
}

Comunicacao::~Comunicacao()
{
}

// - Se host não é NULL, conecta como cliente no host e porta recebidos
// - Se host é NULL, associa o socket a porta dada
// em ambos casos retorna um socket valido ou  -1.
int Comunicacao::abrirSocket(string host,int porta) {
	int sd;
	static struct sockaddr_in sin;
	struct hostent *hp;

	//  pega o nome do socket
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		return -1;

	// completa a estrutura do socket
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons((short)porta);
	if (host.compare("")) {
		// pega o IP do host
		if ((hp = gethostbyname(host.c_str())) == 0)
			return -1;
		sin.sin_addr.s_addr = ((struct in_addr *) (hp->h_addr))->s_addr;
		if (connect(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1)
			return -1;
	} else {
		int zero = 0;
		int um = 1;
		// Socket já em uso
		if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &um, sizeof(um)) < 0)
			return -1;
		// Associar socket ao numero da porta
		if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1)
			return -1;
	}
	
	return sd;
}

//Fecha o socket
int Comunicacao::fecharSocket() {
	return close(ListeningSocket);
}

//Passando para a funcao eventos para cuidar dos eventos do socket
void Comunicacao::iniciarEventos(int socket, void (*eventos) (void *, void *)) {
/*	pid_t pid;	
	pid = fork();
	if (pid == 0) {
		cout << "Conexão iniciada" << endl;
		eventos((void *)socket,(void *) objeto);
		exit(0);
	} else if (pid == -1)
		perror("fork");
	else
		close(Socket);*/
}

//Fica Esperando novas conexões
int Comunicacao::ouvirSocket(int socket, void (*eventos) (void *,void *)){
	struct sockaddr enderecoSocket;
	int novoSocket;
	socklen_t enderecoTamanho = sizeof(enderecoSocket);
		
	if (listen(socket, 5) == -1)
		exit(0);
	
	while (1) {
		memset(&enderecoSocket, 0, sizeof(enderecoSocket));
		novoSocket = accept(socket, &enderecoSocket, &enderecoTamanho);
		if (novoSocket != -1) {
			this->Socket = novoSocket;
			iniciarEventos(novoSocket, eventos);
			return novoSocket;
		} else 
			exit(0);
	}
}

