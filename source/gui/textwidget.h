#ifndef _TEXTWIDGET_HPP
#define _TEXTWIDGET_HPP

#include <GL/glut.h>

#define MAXLEN 255

class TextWidget
{
	private:
		int posx;
		int posy;
		int len;
		int maxlen;
		char text[MAXLEN + 1];
		
		void *glutfont;

	public:
		TextWidget(int x, int y, int maxlen, void *font = GLUT_BITMAP_8_BY_13);
		
		int update(char c);
		void paint();
		
		int getX() { return posx; }
		int getY() { return posy; }
		char *getText() { return text; }
};

#endif
