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


#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "conexao.h"

Conexao::Conexao(Jogo *j) {
	objeto = j;
	ListeningSocket = 0;
}

Conexao::~Conexao() {
		
	fecharSocket();
}

void Conexao::servidor(int porta, void (*eventos) (void *,void*)) {
	this->fnEventos = eventos;
	this->porta = porta;
	this->ListeningSocket = abrirSocket("", porta);
	cout << "socket: " << this->ListeningSocket << endl;
	if (this->ListeningSocket == -1) {
	perror("server.sockopen");
		exit(1);
	}
	cout << "Servidor esperando clientes..." << endl;
	ouvirSocket(this->ListeningSocket, eventos);
}

//Cria o socket do cliente, e conecta o cliente ao servidor
void Conexao::cliente(string enderecoservidor, int porta, void (*eventos) (void *,void*)) {
	this->fnEventos = eventos;
	cout << enderecoservidor << endl;
	this->enderecoservidor = enderecoservidor;
	this->Socket = abrirSocket(enderecoservidor, porta);

	cout << "socket: " << this->ListeningSocket << endl;
	if (this->Socket == -1) {
		cout << "Erro, Servidor não encontrado.\n";
		exit(1);
	}
	cout << "iniciando eventos" << endl;
	iniciarEventos(this->Socket, eventos);
}
void Conexao::limparMsg() {
	memset(msg, 0, sizeof(msg));
/*	this->msg.tipo = 0;
	this->msg.x = 0;
	this->msg.y = 0;
	strcpy(this->msg.comando,"");*/
}

void Conexao::enviarMsg(int socket) {
	send(socket, &msg, sizeof(msg), 0);
}

int Conexao::receberMsg(int socket) {
	int buff;
	buff = recv(socket, &msg, sizeof(msg), 0);
	return buff;
}
