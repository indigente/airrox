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

#ifndef _AUDIO_H
#define _AUDIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <vector>

using namespace std;

class Audio {
	private:
		int audio_rate;
		Uint16 audio_format;
		int audio_channels;
		int audio_buffers;
		Mix_Music *musica;
		Mix_Chunk *fx;
		int fxcanal;
		bool audio_on;
		vector<string> playlist;
		int faixa;
		vector<string> fxlist;
		vector<Mix_Chunk *> fxChunks;
	public:
		string music_path;
		string fx_path;
		string playlist_path;
		string fxlist_path;
		
		Audio();
		~Audio();
		void tocarMusica();
		void tocarFX(string caso);
		void musicaParada();
		void aumentarMusica();
		void diminuirMusica();
		void desligarSom();
		void carregarPlaylist();	
		void proximaMusica();
		void carregarfxs();
};

#endif
