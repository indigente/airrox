#include "menuitem.h"

MenuItem::MenuItem(int id, SDL_Surface image, SDL_Surface hover_image, int x,
  int y, Alignment al)
{
	this->image = image;
	this->hover_image = hover_image;	
	this->y = y;
	this->subMenu = 0;
	this->id = id;
	
	switch (al)
	{
		case CENTER:
			this->x = (SDL_GetVideoSurface()->w - image.w) / 2;
			break;
		case LEFT:
			this->x = x;
			break;
		case RIGHT:
			this->x = x - image.w;
			break;
	}
}

MenuItem::MenuItem(int id, SDL_Surface image, SDL_Surface hover_image,
  int x, int y)
{
	this->image = image;
	this->hover_image = hover_image;	
	this->x = x;
	this->y = y;
	this->subMenu = 0;
	this->id = id;
}

MenuItem::~MenuItem() {};
