#include "airrede.h"
#include "string.h"
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

void AirRede::enviaTexto(char *msg)
{
	msgTexto *m = (msgTexto *)this->pacote->data;
	
	m->tipo = TIPO_TEXTO;
	strcpy(m->texto, msg);
	this->pacote->len = strlen(msg) + 2 * sizeof(char);
	
	this->envia(CANAL_JOGADOR, this->pacote);
	this->envia(CANAL_OBSERVADOR, this->pacote);
}

void AirRede::desconecta()
{
	this->pacote->data[0] = TIPO_DESCONECTAR;
	
	this->pacote->len = 1;
	
	this->envia(CANAL_JOGADOR, this->pacote);
	this->envia(CANAL_OBSERVADOR, this->pacote);

}

