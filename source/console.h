#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <vector>
#include <string>
#include <sstream>

/*
using std::vector;
using std::string;
*/
using namespace std;

class Console
{
	protected:
		unsigned int qtdLinhas;
		unsigned int posAtual;
		string *vec;
		
	public:
		Console(unsigned int qtdLinhas=5);
		~Console();
		
		void insere(const string &s);
		
		void limpa();
		
		string getLinha(unsigned int n);
		
		unsigned int getTamanho() { return /*vec.size();*/ qtdLinhas; }
		unsigned int getCapacidade() { return qtdLinhas; }
};

#endif

