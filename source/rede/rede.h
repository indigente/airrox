#ifndef _REDE_HPP
#define _REDE_HPP

#include <SDL/SDL_net.h>


/**
 * Classe 'wrapper' para funcoes da biblioteca SDL_net comuns
 * a cliente e servidor.
 */
class Rede
{
	protected:
		UDPsocket sock;
		Uint16 porta;

	public:	
		Rede();
		~Rede();
		
		// enviar/receber
		int envia(int canal, UDPpacket *pacote);
		int recebe(UDPpacket *pacote);
		
		// manipulacao de canais
		int bind(int canal, IPaddress *ip);
		void unbind(int canal);
		
		// abrir/fechar porta
		int abre(Uint16 porta);
		void fecha();
		
		// acesso a variaveis
		UDPsocket getSocket() { return sock; }
		Uint16 getPorta() { return porta; }
};

/*
static TCPsocket tcpsock = NULL;
static UDPsocket udpsock = NULL;
static SDLNet_SocketSet socketset = NULL;
static UDPpacket **packets = NULL;
*/

#endif

