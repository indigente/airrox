#include "menuitem.h"

MenuItem::MenuItem(int id, int image, int hover_image, int x,
  int y, int width, int height, Alignment al)
{
	this->image = image;
	this->hover_image = hover_image;	
	this->y = y;
	this->subMenu = 0;
	this->id = id;
	this->width = width;
	this->height = height;
	
	switch (al)
	{
		case CENTER:
			this->x = (SDL_GetVideoSurface()->w - width) / 2;
			break;
		case LEFT:
			this->x = x;
			break;
		case RIGHT:
			this->x = x - width;
			break;
	}
}

MenuItem::~MenuItem() {};
