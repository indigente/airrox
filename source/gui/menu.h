#ifndef _MENU_H
#define _MENU_H

#include <SDL/SDL.h>
#include <vector>
#include "menuitem.h"

using std::vector;

class Menu
{
	protected:
		vector<MenuItem *> items;
		SDL_Color bgcolor;

	public:
//		MenuItem *addItem(int id, char *image, char *hover_image, 
//		  int x, int y);
		MenuItem *addItem(int id, char *image, char *hover_image, 
		  int x, int y, Alignment al=CENTER);

		void attachSubMenu(MenuItem *item, Menu *subMenu);
		void setBgColor(Uint8 r, Uint8 g, Uint8 b);

		int update(int mousex, int mousey, bool click);
//		vector<MenuItem *> *getItems
};

#endif

