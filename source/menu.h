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
		MenuItem *addItem(int id, char *image, char *hover_image, 
		  int x, int y);
		MenuItem *addItem(int id, char *image, char *hover_image, 
		  int x, int y, Alignment al);

		void attachSubMenu(MenuItem *item, Menu *subMenu);
		void setBgColor(Uint8 r, Uint8 g, Uint8 b);

		int update(int mousex, int mousey, bool click)
		{
			int i;
			int ret = 0;
			SDL_Rect rect;
			MenuItem *m;
			
			SDL_Surface *surf = SDL_GetVideoSurface();
			rect.w = surf->w;
			rect.h = surf->h;

			for (i = 0; i < items.size(); i++)
			{
				m = items[i];
				rect.x = m->getX();
				rect.y = m->getY();

				if (m->contains(mousex, mousey)) {
					SDL_BlitSurface(m->getHoverImage(), 0, surf, &rect);
					if (click)
						ret = m->getId();
				}
				else
					SDL_BlitSurface(m->getImage(), 0, surf, &rect);

			}			
			
			return ret;
		}

//		vector<MenuItem *> *getItems
};

#endif

