#include "config.h"
#include <iostream>
#include <fstream>
#include <ctype.h>

using namespace std;

/**
 * Funcao auxiliar que remove espacos no inicio e no fim da string
 * @param s Ponteiro para a string. O conteudo da string e' modificado.
 * @return A propria string passada como parametro, com espacos removidos
 */
string *removeEspacos(string *s)
{
	int i;

	// apaga espacos iniciais
	while (s->size() && isspace(s->at(0)))
		s->erase(0, 1);
		
	// apaga espacos finais
	i = s->size() - 1;
	while (i >= 0 && isspace(s->at(i)))
		s->erase(i--, 1);
		
	return s;
}

/**
 * Retorna o ponteiro para um parametro
 * @param nome Nome do parametro
 * @return Um ponteiro para o parametro, ou 0, se nao existir
 */
Parametro *Config::ponteiroParaParametro(string nome)
{
	int i;
	
	removeEspacos(&nome);
	
	for (i = 0; i < params.size(); i++)
	{
		if (params[i].getNome() == nome)
			return &params[i];
	}
	
	return 0;
}

/**
 * Define o arquivo de configuracao que sera utilizado.
 * Em caso de erro, uma mensagem eh escrita na saida de erros padrao.
 */
Config::Config(string arquivo)
{
	ifstream ifs(arquivo.c_str(), ios::in);
	
	if (ifs.is_open()) {
		this->arquivo = arquivo;
		ifs.close();
	}
	else {
		cerr << "Config: erro ao abrir arquivo " << arquivo << endl;
	}

	this->autoSalvar = false;
}

/** 
 * Destrutor
 */
Config::~Config()
{
	// nao faz nada...
}

/**
 * Define ou altera valor de um parametro, se o parametro existir
 * @param param Nome do parametro a definir/alterar
 * @param valor Ponteiro para o novo valor
 */
void Config::set(string param, void *valor)
{
	Parametro *p;
	if (p = ponteiroParaParametro(param)) {
		p->set(valor);
		if (autoSalvar)
			salva();
	}
	else
		cerr << "Config: Cuidado! Parametro '" << param << "' inexistente!" << endl;
}

/**
 * Retorna o valor de um parametro, se existir
 * @param param Nome do parametro
 * @return Um ponteiro para o valor do parametro, se aplicavel.
 *  0, se o parametro nao tiver valor ou o parametro nao existir.
 */
const void *Config::get(string param)
{
	Parametro *p;
	if (p = ponteiroParaParametro(param))
		return p->getValor();
	else
		return 0;
}

/**
 * @return O valor do parametro, convertido em inteiro
 */
int Config::getInt(string param)
{
	return *((int *)get(param));
}

/**
 * @return O valor do parametro, convertido em ponto flutuante
 */
float Config::getFloat(string param)
{
	return *((float *)get(param));
}

/**
 * @return O valor do parametro, convertido em string
 */
string Config::getString(string param)
{
	return *((string *)get(param));
}

/**
 * Cria um novo parametro de configuracao.
 * @param param Nome do parametro
 * @param tipo Tipo do parametro. Deve ser INT, FLOAT ou STRING.
 */
void Config::cria(string param, enum TipoDeParametro tipo)
{
	removeEspacos(&param);
	if (!ponteiroParaParametro(param))
		params.push_back(*(new Parametro(param, tipo)));
	else
		cerr << "Config: Parametro '" << param << "' ja existia e nao foi recriado." << endl;
}


void Config::set(string param, string *valor)
{
	int *i = new int;
	float *f = new float;	
	Parametro *p;
	
	removeEspacos(&param);
	
	if (p = ponteiroParaParametro(param)) {
		switch (p->getTipo()) {
			case TIPO_INT:
				*i = atoi(valor->c_str());
				p->set(i);
				break;
			case TIPO_FLOAT:
				sscanf(valor->c_str(), "%f", f);
				p->set(f);
				break;
			case TIPO_STRING:
				p->set(valor);
				break;
		}
	}
	else
		cerr << "Config: Cuidado! Parametro '" << param << "' inexistente!" << endl;
}

/**
 * Carrega os parametros de configuracao do arquivo
 */
void Config::carrega()
{
	ifstream ifs(arquivo.c_str(), ios::in);
	string linha, nome;
	string *valor;	
	string::size_type pos1;
	bool oldAutoSalvar;
	
	// verifica se ha algum problema com o arquivo
	if (!ifs.is_open()) {
		cerr << "Config: erro ao abrir arquivo " << arquivo << endl;
		return;
	}
	
	// arquivo ok, carregando configuracoes
	while (!ifs.eof()) {
		getline(ifs, linha);
		pos1 = linha.find('=');
		// so continua se houver o simbolo igual
		if (pos1 != string::npos && pos1 > 0)
		{
			nome = linha.substr(0, pos1);
			valor = new string(linha, pos1 + 1, linha.length() - (pos1 + 1));
			removeEspacos(&nome);
			removeEspacos(valor);

			oldAutoSalvar = autoSalvar;
			autoSalvar = false;
			this->set(nome, valor);
			autoSalvar = oldAutoSalvar;
		}
	}
	
	ifs.close();
}

/**
 * Salva os parametros de configuracao no arquivo
 */
void Config::salva()
{
	ofstream ofs(arquivo.c_str(), ios::out | ios::trunc);
	string linha;
	int i;
	
	// verifica se ha algum problema com o arquivo
	if (!ofs.is_open()) {
		cerr << "Config: erro ao abrir arquivo " << arquivo << endl;
		return;
	}
	
	for (i = 0; i < params.size(); i++) {
		switch (params[i].getTipo()) {
			case TIPO_INT:
				ofs << params[i].getNome() << " = " << *((int *)params[i].getValor()) << endl;;
				break;
			case TIPO_FLOAT:
				ofs << params[i].getNome() << " = " << *((float *)params[i].getValor()) << endl;
				break;
			case TIPO_STRING:
				ofs << params[i].getNome() << " = " << *((string *)params[i].getValor()) << endl;
				break;
		}
	}
	
	ofs.close();
}
