#ifndef _NET_HPP
#define _NET_HPP

#include <SDL/SDL_net.h>

enum NetType
{
	CLIENT,
	SERVER
};

class Net
{
	protected:
		enum NetType netType;
		// reservados para o servidor
		TCPsocket listeningTCPsocket;
		UDPsocket listeningUDPsocket;
		
		// conjunto de sockets
		SDLNet_SocketSet socketset;
		
		

	public:	
		Net(enum NetType netType);
		~Net();

/*		
static TCPsocket tcpsock = NULL;
static UDPsocket udpsock = NULL;
static SDLNet_SocketSet socketset = NULL;
static UDPpacket **packets = NULL;
*/
};

#endif