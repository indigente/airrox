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

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "audio.h"
#include "jogo.h"
#include "partida.h"

using namespace std;

Audio::Audio() {
	musica = NULL;
	fx = NULL;
	fxcanal = -1;
	audio_rate = 44100;
	audio_format = AUDIO_S16; /* 16-bit stereo */
	audio_channels = 2;
	audio_buffers = 4096;
	audio_on = true;
	faixa = 0; 

	music_path = "../audio/music/"; 
	fx_path = "../audio/fx/";
	playlist_path = music_path + "playlist";
	fxlist_path = fx_path + "fxlist";
	
	if (audio_on) {
		
		SDL_Init (SDL_INIT_AUDIO);
		
		
		if(Mix_OpenAudio(audio_rate, AUDIO_S16, audio_channels, audio_buffers)) {
			cout <<  "Audio não pode ser iniciado!" << endl;
			SDL_Quit();
			exit(1);
		}

		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
	
		carregarPlaylist();
		carregarfxs();
	}	
}

Audio::~Audio() {
	Mix_CloseAudio();
}

void Audio::tocarMusica() {
	
	if (audio_on) {
	
		string m_path;
		m_path = music_path + playlist[faixa];
		
		cout << "musica " << m_path << endl;
		
		if ( musica == NULL ) {
			musica = Mix_LoadMUS(m_path.c_str());
			Mix_PlayMusic(musica, -1);
			
			//Mix_HookMusic(tocadorMusicas, &faixa);
			//Mix_HookMusicFinished(musicaParada);
		} else {
			musicaParada();
		}
	}
}
/*TODO
void tocadorMusicas(void *udata, Uint8 *stream, int len){
}
*/
void Audio::proximaMusica(){
	if(faixa++ > playlist.size() )
		faixa = 0;
}

void Audio::musicaParada() {
	if (audio_on) {
		Mix_HaltMusic();
		Mix_FreeMusic(musica);
		musica = NULL;
		//proximaMusica();
		//tocarMusica();
	}
}

void Audio::tocarFX(string caso) {
	if (audio_on) {
		string path;
		int i;
		
		path = caso + ".wav";
		//fx = Mix_LoadWAV(path.c_str());
		for (i=0; fxlist[i] != path && (i < fxChunks.size());i++);
		
		fxcanal = Mix_PlayChannel(-1, fxChunks[i], 0);
	
		fxcanal = -1;
	}
}
void Audio::aumentarMusica() {
	Mix_VolumeMusic(Mix_VolumeMusic(-1)+10);
}

void Audio::diminuirMusica() {
	Mix_VolumeMusic(Mix_VolumeMusic(-1)-10);
}

void Audio::desligarSom() {

}
void Audio::carregarPlaylist() {
	string buffer;
	ifstream playlistStream(playlist_path.c_str());

	if (!playlistStream) {
		cerr << "Erro ao ler o arquivo " << playlist_path.c_str() << endl;
	}
	for (int i=0; !playlistStream.eof(); i++ ) {
		 getline(playlistStream,buffer);
		 playlist.push_back(buffer);
	}
	playlist.pop_back();
	
	playlistStream.close();
}

void Audio::carregarfxs() {
	string buffer, path;
	ifstream fxStream(fxlist_path.c_str());

	if (!fxStream) {
		cerr << "Erro ao ler o arquivo " << fxlist_path.c_str() << endl;
	}
	for (int i=0; !fxStream.eof(); i++ ) {
		 getline(fxStream,buffer);
		 fxlist.push_back(buffer);
		 path = fx_path + fxlist[i];
		 fxChunks.push_back( Mix_LoadWAV(path.c_str()) );
		cout << "lista" << fxlist[i] << endl;
	}
	fxlist.pop_back();
	
	fxStream.close();
	
}
