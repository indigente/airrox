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
		int image;
		int hover_image;
		int x, y;
		int width, height;
		Menu *subMenu;
		int id;

	public:
		// image eh o codigo de textura do OpenGL
		MenuItem(int id, int image, int hover_image, 
		  int x, int y, int width, int height, Alignment al=CENTER);
		~MenuItem();
		
		void attachSubMenu(Menu *m) { this->subMenu = m; }
		bool contains(int x, int y) {
			return (x >= this->x && y >= this->y &&
			  x < this->x + width && y < this->y + height);
		}

		int getImage() { return image; }
		int getHoverImage() { return hover_image; }
		int getX() { return x; }
		int getY() { return y; }
		int getWidth() { return width; }
		int getHeight() { return height; }
		int getId() { return id; }
		
};

#endif

