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
	this->valori = 0;
	this->valorf = 0.0;
	this->valors = "";
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
			case TIPO_FLOAT:
				delete ((float *)this->valor);
				break;
			case TIPO_INT:
				delete ((int *)this->valor);
				break;
			case TIPO_STRING:
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
		switch (this->tipo)
		{
			case TIPO_FLOAT:
				this->valorf = *((float *)valor);
				break;
			case TIPO_INT:
				this->valori = *((int *)valor);
				break;
			case TIPO_STRING:
				this->valors = *((string *)valor);
				break;
		}
}


const void *Parametro::getValor()
{
		switch (this->tipo)
		{
			case TIPO_FLOAT:
				return &valorf;
				break;
			case TIPO_INT:
				return &valori;
				break;
			case TIPO_STRING:
				return &valors;
				break;
		}
}


