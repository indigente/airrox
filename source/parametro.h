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
/*
		union u_valor {
			int i;
			float f;
			string s;
		} valor;
*/
		void *valor;
			
	public:

		
		Parametro(string nome, enum TipoDeParametro tipo);
		~Parametro();
		
		void set(void *valor);
		const string &getNome() { return nome; }
		enum TipoDeParametro getTipo() { return tipo; }
		const void *getValor() { return valor; }
};


#endif

