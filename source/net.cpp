#include "net.h"
#include <SDL/SDL_net.h>

Net::Net(enum NetType netType)
{
	this->netType = netType;
	if (SDLNet_Init() == -1) {
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
}

}

Net::~Net()
{
	SDLNet_Quit();
}

