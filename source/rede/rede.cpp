#include "rede.h"
#include <SDL/SDL_net.h>
#include <stdlib.h>

Rede::Rede()
{
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
}

Rede::~Rede()
{
	SDLNet_Quit();
}

/**
 * @return 0 em caso de erro.
 */
int Rede::abre(Uint16 porta)
{
	this->porta = porta;
	this->sock = SDLNet_UDP_Open(porta);
	if (this->sock == 0) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		return 0;
	}
	else
		return 1;
}

void Rede::fecha()
{
	SDLNet_UDP_Close(this->sock);
}

/**
 * @return O numero de destinos a que o pacote foi enviado.
 *   Retorna zero em caso de erro.
 */
int Rede::envia(int canal, UDPpacket *pacote)
{
	return SDLNet_UDP_Send(this->sock, canal, pacote);
}

/**
 * @return 1, se o pacote foi recebido
 *   0, se nenhum pacote foi recebido
 *   -1, se ocorreu um erro
 */
int Rede::recebe(UDPpacket *pacote)
{
	return SDLNet_UDP_Recv(this->sock, pacote);
}

/**
 * @return Retorna -1 em caso de erro.
 */
int Rede::bind(int canal, IPaddress *ip)
{
	return SDLNet_UDP_Bind(this->sock, canal, ip);
}
void Rede::unbind(int canal)
{
	SDLNet_UDP_Unbind(this->sock, canal);
}


/*************** ideias ******************************/
/*
// conectando-se a um servidor
  //-> o usuário escolhe o host e a porta
  #define CANAL 0
  IPaddress ip;
  UDPsocket sock;
  SDLNet_ResolveHost(&ip, host, porta); // erro: -1
  sock = SDLNet_UDP_Open(0);
  SDLNet_UDP_Bind(sock, CANAL, &ip); // erro: -1

// inicia servidor
	listeningUDPsocket = SDLNet_UDP_Open(port);
	if (!listeningUDPsocket) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
    
// servidor: recebe mensagens e aceita clientes
  
  


*/
