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
		
		string getLinha(unsigned int n)
		{
			if (n >= 1 && n <= this->qtdLinhas)
				return vec[n - 1];
			else
				return (string)" ";
		}
		
		unsigned int getTamanho() { return /*vec.size();*/ qtdLinhas; }
		unsigned int getCapacidade() { return qtdLinhas; }
};

#endif

