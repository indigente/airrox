#ifndef _TEXTWIDGET_HPP
#define _TEXTWIDGET_HPP

#include <GL/glut.h>

/**
 * Campo de entrada de texto (uma linha)
 */
class TextWidget
{
	private:
		int posx;
		int posy;
		int len;
		int maxlen;
		char *text;
		void *glutfont;

	public:
		TextWidget(int x, int y, unsigned int maxlen, void *font = GLUT_BITMAP_8_BY_13);
		
		int update(char c);
		void paint();
		void posiciona(int x, int y);
		void limpa();
		void mudaFonte(void *font);
		
		int getX() { return posx; }
		int getY() { return posy; }
		char *getText() { return text; }
};

#endif
