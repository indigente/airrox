#ifndef _PARAMETRO_H
#define _PARAMETRO_H

#include <string>

using std::string;

enum TipoDeParametro
{
	INT,
	FLOAT,
	STRING
};

/**
 * Parametro de configuracao
 */
class Parametro
{
	protected:
		string nome;
		enum TipoDeParametro tipo;

		int valori;
		float valorf;
		string valors;

	public:

		
		Parametro(string nome, enum TipoDeParametro tipo);
		~Parametro();
		
		void set(void *valor);
		const string &getNome() { return nome; }
		enum TipoDeParametro getTipo() { return tipo; }
		const void *getValor();
};


#endif

