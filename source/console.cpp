#include "console.h"
#include <iostream>

Console::Console(unsigned int qtdLinhas)
{
	this->qtdLinhas = qtdLinhas;
	vec = new string[this->qtdLinhas];
	this->posAtual = 0;
	this->limpa();
}

Console::~Console()
{

}

void Console::insere(const string &s)
{
	this->posAtual = (this->posAtual + 1) % this->qtdLinhas;

	this->vec[this->posAtual].assign(s);
}

void Console::limpa()
{
	int i;
	for (i = 0; i < this->qtdLinhas; i++)
		vec[i].assign((string)"");
	this->posAtual = 0;
}

string Console::getLinha(unsigned int n)
{
	if (n >= 1 && n <= this->qtdLinhas)
		return vec[(posAtual + n) % qtdLinhas];
	else
		return (string)" ";
}
