#include <GL/glut.h>
#include <SDL/SDL.h>
#include "textwidget.h"
#include <stdio.h>

/**
 * Cria uma caixa de texto
 * @param x Posicao x
 * @param y Posicao y
 * @param maxlen Tamanho maximo do texto/
 * @param font Fonte GLUT a ser usada. Deve ser
 *  GLUT_BITMAP_8_BY_13, GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
 *  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
 *  GLUT_BITMAP_HELVETICA_12 ou GLUT_BITMAP_HELVETICA_18.
 */
TextWidget::TextWidget(int x, int y, unsigned int maxlen, void *font)
{
	// inicia com texto vazio
	this->maxlen = maxlen;
	this->text = new char[this->maxlen + 1];
	this->limpa();
	this->posiciona(x, y);
	this->mudaFonte(font);
}

/**
 * Escreve o texto na tela, no buffer do OpenGL.
 * Inclui um underline ("_") no final.
 */
void TextWidget::paint()
{
	char *c = text;
	
	glRasterPos2i(posx, posy);  
	while (*c)
		glutBitmapCharacter(glutfont, *c++);

	glutBitmapCharacter(glutfont, '_');
}

/**
 * Atualiza o texto de acordo com o caracter fornecido.
 * Backspace apaga a ultima letra, Enter finaliza, 
 * Escape limpa o texto.
 * @param c Caracter fornecido
 */
int TextWidget::update(char c)
{
	int ret = 0;
	
	switch (c)
	{
		case 8: // backspace
			if (len > 0) {
				len--;
				text[len] = '\0';
			}		
			break;			
		case 10:
		case 13: // enter
			ret = 1;
			break;
		case 27: // esc
			this->limpa();
			break;
		default:
			if (len < maxlen)
			{
				text[len] = c;
				len++;
				text[len] = '\0';
			}
			break;
	}

	return ret;
}

/**
 * Muda a posicao do texto
 * @param x Posicao x
 * @param x Posicao y
 */ 
void TextWidget::posiciona(int x, int y)
{
	this->posx = x;
	this->posy = y;
}

/**
 * Limpa o texto
 */
void TextWidget::limpa()
{
	this->text[0] = '\0';
	this->len = 0;
}

/**
 * Muda a fonte do texto
 * @param font Fonte GLUT a ser usada. Deve ser
 *  GLUT_BITMAP_8_BY_13, GLUT_BITMAP_9_BY_15, GLUT_BITMAP_TIMES_ROMAN_10,
 *  GLUT_BITMAP_TIMES_ROMAN_24, GLUT_BITMAP_HELVETICA_10,
 *  GLUT_BITMAP_HELVETICA_12 ou GLUT_BITMAP_HELVETICA_18.
 */
void TextWidget::mudaFonte(void *font)
{
	this->glutfont = font;
}
