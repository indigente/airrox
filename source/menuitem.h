#ifndef _MENUITEM_H
#define _MENUITEM_H

#include <SDL/SDL.h>

enum Alignment
{
	CENTER,
	LEFT,
	RIGHT
};

class Menu;

// image e hover_image devem ter o mesmo tamanho!
class MenuItem
{
	protected:
		SDL_Surface image;
		SDL_Surface hover_image;
		int x, y;
		Menu *subMenu;
		int id;

	public:
		MenuItem(int id, SDL_Surface image, SDL_Surface hover_image, 
		  int x, int y, Alignment al);
		MenuItem(int id, SDL_Surface image, SDL_Surface hover_image, 
		  int x, int y);
		~MenuItem();
		
		void attachSubMenu(Menu *m) { this->subMenu = m; }
		bool contains(int x, int y) {
			return (x >= this->x && y >= this->y &&
			  x < this->x + image.w && y < this->y + image.h);
		}

		SDL_Surface *getImage() { return &image; }
		SDL_Surface *getHoverImage() { return &hover_image; }
		int getX() { return x; }
		int getY() { return y; }
		int getWidth() { return image.w; }
		int getHeight() { return image.h; }
		int getId() { return id; }
		
};

#endif

