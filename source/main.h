/*
	This project was developed by:
		Alexandre Amoedo Amorim (amoedo@im.ufba.br)
		Jailson A. de Brito Júnior (jailson@im.ufba.br)
		Rodrigo Rocha Gomes de Souza (rodrigo@im.ufba.br)
	This project was started at 2004.
	
	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/


//M_PI ... adicionado por Lorde Darion (nd_math.h)
#define	M_PI	3.14159265358979323846

#ifdef _WIN32
	#include <math.h>
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <stdarg.h>
	#include <windows.h>
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <SDL/SDL.h>
#else
	#include <math.h>
	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <stdarg.h>
	#include <GL/glut.h>
#endif

/*
class airrox{
	public:
		Visual *visual;
		Controle *controle;
		Modelo *modelo;
};
*/
