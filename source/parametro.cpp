#include "parametro.h"

/**
 * Cria um parametro de configuracao, sem atribuir valor
 * @param nome Nome do parametro
 * @param tipo Tipo do parametro. Deve ser INT, FLOAT ou STRING.
 */
Parametro::Parametro(string nome, enum TipoDeParametro tipo)
{
	this->nome = nome;
	this->tipo = tipo;
	this->valor = 0;
}

/**
 * Desaloca a memoria reservada ao parametro.
 * O valor tambem e' desalocado.
 */
Parametro::~Parametro()
{
/*
	if (this->valor) {
		switch (this->tipo)
		{
			case FLOAT:
				delete ((float *)this->valor);
				break;
			case INT:
				delete ((int *)this->valor);
				break;
			case STRING:
				delete ((string *)this->valor);
				break;
		}
	}
*/
}

/**
 * Define o valor do parametro
 * @param valor Ponteiro para o valor
 */
void Parametro::set(void *valor)
{
	this->valor = valor;
}
