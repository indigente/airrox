#include <GL/glut.h>
#include "assert.h"
#include "menu.h"
#include "../3DSLoader/texture.h"

MenuItem *Menu::addItem(int id, char *image, char *hover_image, 
  int x, int y, Alignment al)
{
	int w, h;
	FILE *file;
	
	int im, h_im;
	im = LoadBitmap(image);
	h_im = LoadBitmap(hover_image);
	
	assert(im);
	assert(h_im);

	// start reading width & height
	file = fopen(image, "rb");
	fseek(file, 18, SEEK_CUR);  
	fread(&w, sizeof(int), 1, file);
	fread(&h, sizeof(int), 1, file);
		
	
	MenuItem *m = new MenuItem(id, im, h_im, x, y, w, h, al);

	this->items.push_back(m);

	return m;

}

void Menu::attachSubMenu(MenuItem *item, Menu *subMenu)
{
	item->attachSubMenu(subMenu);
}

void Menu::setBgColor(Uint8 r, Uint8 g, Uint8 b)
{
	bgcolor.r = r;
	bgcolor.g = g;
	bgcolor.b = b;
}

int Menu::update(int mousex, int mousey, bool click)
{
	int i;
	int ret = 0;
	SDL_Rect rect;
	MenuItem *m;

        float g_LightPosition[4] = {0, 1, 0, 1};
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_LIGHTING);
        glLightfv( GL_LIGHT0, GL_POSITION, g_LightPosition );
        glEnable(  GL_LIGHT0   );
        glNormal3f(1, 0, 1);
//        glDisable(GL_TEXTURE_2D);
//        glDisable(GL_LIGHTING);

	
	/// debug

	glViewport(0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, SDL_GetVideoSurface()->w, 0, SDL_GetVideoSurface()->h);
//	glScalef(1, -1, 1);
//	glTranslatef(0, SDL_GetVideoSurface()->h, 0);
	
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2i(0, 0);
		glVertex2i(100, 0);
		glVertex2i(100, 100);
		glVertex2i(0, 100);
	glEnd();
		
	for (i = 0; i < items.size(); i++)
	{
		m = items[i];

//		glRasterPos2f(m->getX(), m->getY());

		if (m->contains(mousex, mousey)) {
			glBindTexture(GL_TEXTURE_2D, m->getHoverImage());
			glBegin(GL_QUADS);
//				glTexCoord2d(0, 0); glVertex2i(m->getX(), m->getY());
//				glTexCoord2d(0, 1); glVertex2i(m->getX(), m->getY() + m->getHeight());
//				glTexCoord2d(1, 1); glVertex2i(m->getX() + m->getWidth(), m->getY() + m->getHeight());
//				glTexCoord2d(1, 0); glVertex2i(m->getX() + m->getWidth(), m->getY());
				glTexCoord2d(0, 0); glVertex2i(0, 0);
				glTexCoord2d(0, 1); glVertex2i(0, 100);
				glTexCoord2d(1, 1); glVertex2i(100, 100);
				glTexCoord2d(1, 0); glVertex2i(100, 0);
			glEnd();

			//SDL_BlitSurface(m->getHoverImage(), 0, surf, &rect);
			
			if (click)
				ret = m->getId();
		}
		else {
			glBindTexture(GL_TEXTURE_2D, m->getImage());
			glBegin(GL_QUADS);
				glTexCoord2d(0, 0); glVertex2i(m->getX(), m->getY());
				glTexCoord2d(0, 1); glVertex2i(m->getX(), m->getY() + m->getHeight());
				glTexCoord2d(1, 1); glVertex2i(m->getX() + m->getWidth(), m->getY() + m->getHeight());
				glTexCoord2d(1, 0); glVertex2i(m->getX() + m->getWidth(), m->getY());
			glEnd();
			
//			SDL_BlitSurface(m->getImage(), 0, surf, &rect);
		}

	}			
	
	return ret;
}
