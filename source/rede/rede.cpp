#include "net.h"
#include <SDL/SDL_net.h>
#include <stdlib.h>

Net::Net(enum NetType netType)
{
	this->netType = netType;
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
}

Net::~Net()
{
	SDLNet_Quit();
}

void Net::initServer(Uint16 port)
{	
	listeningUDPsocket = SDLNet_UDP_Open(port);
	if (!listeningUDPsocket) {
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
// 	SDLNet_UDP_Unbind(listeningUDPsocket, 0);
}

void Net::connectToServer(Uint32 host, Uint16 port);

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
  
// servidor: recebe mensagens e aceita clientes
  
  


*/
