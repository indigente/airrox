#ifndef _CONFIG_H
#define _CONFIG_H

#include "parametro.h"
#include <string>
#include <vector>

using namespace std;

/**
 * Classe responsavel por gerenciar as configuracoes do jogo.
 * As configuracoes sao lidas de um arquivo.
 * Cada parametro de configuracao e' unicamente identificado pelo seu nome.
 * Desta maneira, nao pode haver dois parametros com o mesmo nome.
 */
class Config
{
	protected:
		vector<Parametro> params;
		string arquivo;
		
		Parametro *ponteiroParaParametro(string nome);
		void set(string param, string *valor);
		
	public:
		Config(string arquivo);
		~Config();
		
		void set(string param, void *valor);
		const void *get(string param);
		void cria(string param, enum TipoDeParametro tipo);
		
		void carrega();
		void salva();
};

#endif
