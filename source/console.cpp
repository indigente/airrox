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
	if (this->posAtual == this->qtdLinhas)
		this->posAtual = 1;
	else
		this->posAtual++;

	this->vec[this->posAtual - 1].assign(s);
}

void Console::limpa()
{
	int i;
	for (i = 0; i < this->qtdLinhas; i++)
		vec[i].assign((string)"");
	this->posAtual = 0;
}

