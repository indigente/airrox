#ifndef _MENU_H
#define _MENU_H

#include <SDL/SDL.h>
#include <vector>
#include "menuitem.h"

using std::vector;

struct sItem {
	int id;
	char image[256];
	char hover_image[256];
	int x;
	int y;
	Alignment al;
};

class Menu
{
	protected:
		vector<MenuItem *> items;
		vector<sItem> iteminfo;
		SDL_Color bgcolor;
// 		int mousex, mousey, click;
		MenuItem *selected;
		
		void reconfigureDisplay();

	public:
//		MenuItem *addItem(int id, char *image, char *hover_image, 
//		  int x, int y);
		MenuItem *addItem(int id, char *image, char *hover_image, 
		  int x, int y, Alignment al=LEFT);

		void attachSubMenu(MenuItem *item, Menu *subMenu);
		void setBgColor(Uint8 r, Uint8 g, Uint8 b);

		void init();
		void deinit();
		
		int update(int mousex, int mousey, int click);
		void paint();
//		vector<MenuItem *> *getItems
		bool painted;
};

#endif

