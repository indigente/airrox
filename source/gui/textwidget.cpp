#include <GL/glut.h>
#include <SDL/SDL.h>
#include "textwidget.h"
#include <stdio.h>

TextWidget::TextWidget(int x, int y, int maxlen, void *font)
{
	// inicia com texto vazio
	this->text[0] = '\0';
	this->len = 0;
	
	this->posx = x;
	this->posy = y;
	this->maxlen = (maxlen <= MAXLEN ? maxlen : MAXLEN);	
	this->glutfont = font;
}

void TextWidget::paint()
{
	static int t1 = glutGet(GLUT_ELAPSED_TIME);
	int t2;

/*	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity;
	gluOrtho2D(0, SDL_GetVideoSurface()->w, 0, SDL_GetVideoSurface()->h);
	glScalef(1, -1, 1);
	glTranslatef(0, -SDL_GetVideoSurface()->h, -1);
*/
	
	printf("%s\n", text);
	char *c = text;
	glRasterPos2i(posx, posy);  
	while (*c++)
		glutBitmapCharacter(glutfont, *c);
		
	t2 = glutGet(GLUT_ELAPSED_TIME);
	if ((t2 - t1) % 500 > 250)
		glutBitmapCharacter(glutfont, '_');	
	t1 = t2;
}

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
		default:
			if (len < maxlen)
			{
				text[len] = c;
				len++;
				text[len] = '\0';
			}
			break;
	}

	paint();

	return ret;
}
