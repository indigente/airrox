#include <GL/glut.h>
#include "assert.h"
#include "menu.h"
#include "../3DSLoader/texture.h"
#include "string.h"

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
	fclose(file);		
	
	MenuItem *m = new MenuItem(id, im, h_im, x, y, w, h, al);

	this->items.push_back(m);

	// guarda informacoes, para o caso de ser necessario recarregar
	sItem s;
	s.id = id;
	strcpy(s.image, image);
	strcpy(s.hover_image, hover_image);
	s.x = x;
	s.y = y;
	s.al = al;
	iteminfo.push_back(s);

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

void Menu::init()
{

//	float g_LightPosition[4] = {0, 1, 0, 1};
	glViewport(0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h);
	
	glPushAttrib(GL_ENABLE_BIT);
	
	glEnable(GL_CULL_FACE);	
	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_LIGHTING);
//	glLightfv( GL_LIGHT0, GL_POSITION, g_LightPosition );	
//	glEnable(  GL_LIGHT0   );
//	glNormal3f(0, 0, -1);

	glViewport(0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Menu::deinit()
{
	glPopAttrib();
}

void EscreveString(float x, float y, char *string)
{
  char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++)
      glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
}

int Menu::update(int mousex, int mousey, int click)
{
	int i;
	int ret = 0;	
	MenuItem *m;	
	static int oldw = 0, oldh = 0;
	static Uint32 oldflags;
	
	// se a resolucao mudou
	if (oldw != SDL_GetVideoSurface()->w || oldh != SDL_GetVideoSurface()->h ||
	 oldflags != SDL_GetVideoSurface()->flags )
	{
		oldw = SDL_GetVideoSurface()->w;
		oldh = SDL_GetVideoSurface()->h;
		oldflags = SDL_GetVideoSurface()->flags;
		
		glViewport(0, 0, SDL_GetVideoSurface()->w, SDL_GetVideoSurface()->h);
	
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, SDL_GetVideoSurface()->w, 0, SDL_GetVideoSurface()->h);
		glScalef(1, -1, 1);
		glTranslatef(0, -SDL_GetVideoSurface()->h, -1);
// No Windows, eh necessario recarregar as texturas
// TODO: fazer funcionar
#ifdef _WIN32
		this->init();

		vector<sItem> copia(iteminfo);
		MenuItem *mi;
		int tex;
		sItem si;

		for (i = 0; i < items.size(); i++) {
			mi = items[i];
			tex = mi->getImage();
			glDeleteTextures(1, (GLuint *)&tex);
			tex = mi->getHoverImage();
			glDeleteTextures(1, (GLuint *)&tex);
			delete mi;
		}

		items.clear();
		iteminfo.clear();
		
		for (i = 0; i < copia.size(); i++) {
			si = copia[i];
			this->addItem(si.id, si.image, si.hover_image, si.x, si.y, si.al);
		}
#endif
	}
	
	// XXX - nao sei por que, mas fica lento se tirar isso
	::EscreveString(0, 0, " ");
	
	for (i = 0; i < items.size(); i++)
	{
		m = items[i];

		// Escolhe a textura a ser usada
		if (m->contains(mousex, mousey))
			glBindTexture(GL_TEXTURE_2D, m->getHoverImage());
		else
			glBindTexture(GL_TEXTURE_2D, m->getImage());
			
		// Desenha o plano, aplicando a textura		
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2i(m->getX(), m->getY());
		glTexCoord2d(0, 0); glVertex2i(m->getX(), m->getY() + m->getHeight());
		glTexCoord2d(1, 0); glVertex2i(m->getX() + m->getWidth(), m->getY() + m->getHeight());
		glTexCoord2d(1, 1); glVertex2i(m->getX() + m->getWidth(), m->getY());
		glEnd();

/*
		GLint texw, texh;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &texw);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &texh);
//		pixels = new unsigned char[m->getWidth() * m->getHeight() + 99999];
		pixels = new unsigned char[texw * texh * 3];
		glRasterPos2i(m->getX(), m->getY());
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
		glDrawPixels(m->getWidth(), m->getHeight(),
			GL_RGB, GL_UNSIGNED_BYTE, pixels);
		delete pixels;
*/
		if (click && m->contains(mousex, mousey))
			ret = m->getId();
	}			
	
	return ret;
}
