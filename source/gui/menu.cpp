#include "assert.h"
#include "menu.h"

MenuItem *Menu::addItem(int id, char *image, char *hover_image, 
  int x, int y)
{
	SDL_Surface *im, *h_im;
	im = SDL_LoadBMP(image);
	h_im = SDL_LoadBMP(hover_image);

	assert(im);
	assert(h_im);
	
	MenuItem *m = new MenuItem(id, *im, *h_im, x, y);

	this->items.push_back(m);

	return m;
}

MenuItem *Menu::addItem(int id, char *image, char *hover_image, 
  int x, int y, Alignment al)
{
	SDL_Surface *im, *h_im;
	im = SDL_LoadBMP(image);
	h_im = SDL_LoadBMP(hover_image);
	
	assert(im);
	assert(h_im);

	MenuItem *m = new MenuItem(id, *im, *h_im, x, y, al);

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

