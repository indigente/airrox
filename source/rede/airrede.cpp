#include "airrede.h"
#include <stdlib.h>

AirRede::AirRede(Partida *partida, Uint16 porta)
{
	pacote = SDLNet_AllocPacket(MAXBUF);
	
	if (!partida) {
		printf("AirRede::AirRede: partida == NULL!\n");
		exit(2);
	}
	this->partida = partida;
	
	this->abre(porta);
}

AirRede::~AirRede()
{
	SDLNet_FreePacket(pacote);
	this->fecha();
}

