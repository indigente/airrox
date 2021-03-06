#ifdef _WIN32
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
	#include <iostream>
#else
	#include <iostream>
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>
	#include <SDL/SDL.h>
	#include <GL/glut.h>
	#include <GL/gl.h>
#endif

#include "tutorial4.h"
#include "3dsloader.h"
#include "texture.h"
/*
#define SCREEN_WIDTH 640								
#define SCREEN_HEIGHT 480								
#define SCREEN_DEPTH 16									
*/
/*
extern int VideoFlags;									
extern SDL_Surface * MainWindow;						

void MainLoop(void);
void ToggleFullScreen(void);
void SetupPixelFormat(void);
void CreateMyWindow(const char *strWindowName, int width, int height, int VideoFlags);
void SizeOpenGLScreen(int width, int height);
void InitializeOpenGL(int width, int height);
void Init();
void HandleKeyPressEvent(SDL_keysym * keysym);
void HandleKeyReleaseEvent(SDL_keysym * keysym);
void display();
void Quit(int ret_val);
*/
