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

#include "main.h"
#include "visual.h"
#include "partida.h"
#include "jogador.h"
#include "disco.h"
#include "jogo.h"
#include "console.h"
#include <string>
using namespace std;

float gameFPS;

/******************* Metodos de inicializacao ***************************/

Visual::Visual(Jogo *j, int telaLargura, int telaAltura, bool telaCheia, string telaTitulo) {
	jogo = j;
	
	this->font = (int)GLUT_BITMAP_8_BY_13;
	this->telaLargura = telaLargura;
	this->telaAltura = telaAltura;
	this->telaTitulo = telaTitulo.c_str();

	Load3DS (&mesa,"../meshs/mesa.3ds");
	Load3DS(&mallet,"../meshs/mallet.3ds");
	Load3DS(&puck,"../meshs/puck.3ds");
	Load3DS(&placar,"../meshs/placar.3ds");

	criarJanela();
	inicializaOpenGL();
	setarVideo(telaLargura, telaAltura, telaCheia);

	/* Camera */
	Vetor origem(0,-180,100), alvo(0,0,0);
	camera = new Camera(jogo,origem,alvo);
	

}

void Visual::inicializaOpenGL()
{
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE,5);

	glViewport(0,0,this->telaLargura,this->telaAltura);
	
	GLfloat luzAmbiente[4]={0.3,0.3,0.3,1.0};
	GLfloat luzDifusa[4]={55.0,55.0,55.0,55.0};
	GLfloat luzEspecular[4]={0.0,0.0,0.0,0.0};
	GLfloat posicaoLuz[4]={0.0,0.0,50.0,0.0};
	GLfloat especularidade[4]={0.0,0.0,0.0,0.0};
	
	GLint especMaterial=120;
	
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glMaterialfv(GL_FRONT,GL_SPECULAR,especularidade);
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,luzAmbiente);

	glLightfv(GL_LIGHT0,GL_AMBIENT,luzAmbiente);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,luzDifusa);
	glLightfv(GL_LIGHT0,GL_SPECULAR,luzEspecular);
	glLightfv(GL_LIGHT0,GL_POSITION,posicaoLuz);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	/*TODO criar uma variavel Path de texturas e meshs*/
	mesa.id_texture=LoadBitmap("../texturas/mesa.bmp");
	mallet.id_texture=LoadBitmap("../texturas/mallet.bmp");
    	puck.id_texture=LoadBitmap("../texturas/puck.bmp");
	placar.id_texture=LoadBitmap("../texturas/placar.bmp");
	
	display[0]=LoadBitmap("../texturas/display0.bmp");
	display[1]=LoadBitmap("../texturas/display1.bmp");
	display[2]=LoadBitmap("../texturas/display2.bmp");
	display[3]=LoadBitmap("../texturas/display3.bmp");
	display[4]=LoadBitmap("../texturas/display4.bmp");
	display[5]=LoadBitmap("../texturas/display5.bmp");
	display[6]=LoadBitmap("../texturas/display6.bmp");
	display[7]=LoadBitmap("../texturas/display7.bmp");
	//display[8]=LoadBitmap("../texturas/display8.bmp");
	//display[9]=LoadBitmap("../texturas/display9.bmp");
	logomesa=LoadBitmap("../texturas/logomesa.bmp");

	/*TODO Criar metodo pra fazer isso abaixo */
	if (mesa.id_texture==-1) {
		std::cout << "Image file: mesa.bmp not found\n" << std::endl;
		exit (0);
	}
        if (mallet.id_texture==-1) {
		std::cout << "Image file: mallet.bmp not found\n" << std::endl;
		exit (0);
	}
	if (puck.id_texture==-1) {
		std::cout << "Image file: puck.bmp not found\n" << std::endl;
		exit (0);
	}
	if (placar.id_texture==-1) {
		std::cout << "Image file: placar.bmp not found\n" << std::endl;
		exit (0);
	}
	glClearColor(0.0f,0.0f,0.0f,1.0f);
}

void Visual::recarregaTexturas()
{
// So eh necessario no Windows
#ifdef _WIN32

	glDeleteTextures(1, (const GLuint *)&mesa.id_texture);
	glDeleteTextures(1, (const GLuint *)&mallet.id_texture);	
	glDeleteTextures(1, (const GLuint *)&puck.id_texture);	
	glDeleteTextures(1, (const GLuint *)&placar.id_texture);	
	glDeleteTextures(8, (const GLuint *)display);
	glDeleteTextures(1, (const GLuint *)&logomesa);

	inicializaOpenGL();
#endif
}

int Visual::criarJanela(void) {
	const SDL_VideoInfo* telaInfo = NULL;
//	int telaBpp;
//	Uint32 telaFlags = SDL_OPENGL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		printf("\nInicialização de Video falhou: %s\n",SDL_GetError());
		return 0;
	}
	telaInfo = SDL_GetVideoInfo();
	if ( !telaInfo ) {
		printf("\nChamada de video falhou: %s\n",SDL_GetError());
		return 0;
	}

	//telaBpp = telaInfo->vfmt->BitsPerPixel;

	SDL_WM_SetIcon(SDL_LoadBMP("../icones/airrox.bmp"), NULL);
	SDL_WM_SetCaption(this->telaTitulo.c_str(),NULL);

	return 1;
}

int Visual::setarVideo(int telaLargura, int telaAltura, bool telaCheia) {
        Uint32 telaFlags = SDL_OPENGL;
	
	if (telaCheia)
		telaFlags |= SDL_FULLSCREEN;
	if ( !(SDL_SetVideoMode( telaLargura, telaAltura,0, telaFlags )) ) {
		printf("\nVideo mode set falhou: %s \n", SDL_GetError() );
		return 0;
	}
	this->telaLargura = telaLargura;
	this->telaAltura = telaAltura;
	this->telaCheia = telaCheia;

#ifdef _WIN32
	recarregaTexturas(); //inicializaOpenGL();
#endif
	
	return 1;
}

int Visual::setarTelaCheia(void) {
	this->telaCheia = !this->telaCheia;
	setarVideo(this->telaLargura, this->telaAltura,this->telaCheia);
	return 1;
}	

int Visual::aumentarResolucao(void) {
	int novaLargura = 160*((this->telaLargura/160)+1);
	int novaAltura = 120*((this->telaAltura/120)+1);
	if ( setarVideo( novaLargura, novaAltura, this->telaCheia) ){
		this->telaLargura = novaLargura;
		this->telaAltura = novaAltura;
		glViewport(0,0,this->telaLargura,this->telaAltura);
	}
	return 1;
}

int Visual::diminuirResolucao(void) {
	int novaLargura = 160*((this->telaLargura/160)-1);
	int novaAltura = 120*((this->telaAltura/120)-1);
	if ( setarVideo(novaLargura, novaAltura, this->telaCheia) ) {
		this->telaLargura = novaLargura;
		this->telaAltura = novaAltura;
		glViewport(0,0,this->telaLargura,this->telaAltura);
	}
	return 1;
}

GLvoid Visual::matarJanela(GLvoid) {}

/**************** Metodos auxiliares ***********************************/

void Visual::EscreveString(float x, float y, void *font, const char *string)
{
  const char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++)
      glutBitmapCharacter(font, *c);
}

void Visual::iniciaEscrita2D()
{
	int w = this->telaLargura;
	int h = this->telaAltura;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0, w, 0, h);
	glScalef(1, -1, 1);
	glTranslatef(0, -h, 0);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Visual::Escrita2D(void) {
	char msg[256];
	iniciaEscrita2D();
	
	/////////////////////////////////////////////////////////
	//Escrever Resolucao
	/////////////////////////////////////////////////////////
	{
	char strVideo[256];
	sprintf(strVideo,"Video: %dx%d",this->telaLargura,this->telaAltura);
	EscreveString(10,22,(void *)font,strVideo);
	}
	////////////////////////////////////////////////////////
	//Escrever FPS
	/////////////////////////////////////////////////////////
	{
	char strFPS[256];
	gameFPS = retornaFPS(gameFPS);
	sprintf(strFPS,"FPS:%.0f",gameFPS);
	EscreveString(10,34,(void *)font,strFPS);
	}
	////////////////////////////////////////////////////////
	//Escrever Console
	/////////////////////////////////////////////////////////
	this->desenhaConsole();
}

void Visual::desenhaConsole()
{
	Console *c = jogo->getConsole();
	unsigned int i;
	for (i = 1; i <= c->getTamanho(); i++)
		EscreveString(10.0, 46.0 + 12.0 * i, (void *)font, c->getLinha(i).c_str());
}


void Visual::cylinder(float r, float h, int segs)
{
    GLUquadricObj *obj = gluNewQuadric();
    gluCylinder( obj, r, r, h, segs, 1 );
    // top and bottom
    gluDisk( obj, 0, r, segs, 1 );
    glPushMatrix();
	glTranslatef ( 0, 0, h);
	gluDisk( obj, 0, r, segs, 1 );
    glPopMatrix();
    gluDeleteQuadric( obj );
}

/******** Metodos de configuracao de visualizacao ************/

void Visual::defineCamera(void)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60,1.33,3.0f,500.0f);

	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
		
	gluLookAt(camera->origem.x,camera->origem.y,camera->origem.z,
		  camera->alvo.x,camera->alvo.y,camera->alvo.z,
		  0,0,1);

//	glRotatef(-50,1,0,0);
//	glTranslatef(0,160,-100);
		
}

void Visual::reconfiguraCamera(void) {
	/*
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,1.33,3.0f,300.0f);
*/
	
	this->camera->origem.x=0.0;
	this->camera->origem.y=-200.0;
	this->camera->origem.z=90.0;

	this->camera->alvo.x=0.0;
	this->camera->alvo.y=0.0;
	this->camera->alvo.z=0.0;
	
/*        gluLookAt(camera.origem.x,camera.origem.y,camera.origem.z,
		  camera.alvo.x,camera.alvo.y,camera.alvo.z,
    		  0,0,1);				
*/
}

void Visual::RedimensionaTela(int x, int y)
{
	glViewport(0,0,x,y);
}

/**************** Metodos de desenho ***************************/

void Visual::inicio()
{
	float g_LightPosition[4] = {0, 1, 0, 1};
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	defineCamera();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glLightfv( GL_LIGHT0, GL_POSITION, g_LightPosition );
	glEnable(  GL_LIGHT0   );	
	glNormal3f(1, 0, 1);
}

void Visual::desenhaNoBuffer()
{
	DesenhaMesa();
	DesenhaDisco();
	DesenhaJogador(0);
	DesenhaJogador(1);
	DesenhaPlacar();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	Escrita2D();
}

void Visual::Desenha(void) {
	inicio();
	desenhaNoBuffer();
	fim();
}	

void Visual::fim()
{
	SDL_GL_SwapBuffers();
}

void Visual::DesenhaDisco(void)
{
	glPushMatrix();
	//glColor3f(1.0f,0.0f,0.0f);
	glTranslatef(jogo->getPartida()->getDisco()->getPos().x,
		jogo->getPartida()->getDisco()->getPos().y, 2);
	//cylinder(jogo->getPartida().getDisco().getRaio(),1.5,12);
	DesenhaMesh(&puck);
	glPopMatrix();
}

void Visual::DesenhaPlacar()
{
	int gols0 = jogo->getPartida()->getJog(0)->getPontuacao();
	int gols1 = jogo->getPartida()->getJog(1)->getPontuacao();
	//glColor3f(0.0f,0.0f,0.0f);
	
	glBindTexture(GL_TEXTURE_2D,display[gols0]);

	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3f(-17.0f,-36.0f,84.0f);
		glTexCoord2d(1,0); glVertex3f(-10.0f,-36.0f,84.0f);
		glTexCoord2d(1,1); glVertex3f(-10.0f,-39.0f,90.0f);
		glTexCoord2d(0,1); glVertex3f(-17.0f,-39.0f,90.0f);
		
		glTexCoord2d(1,1); glVertex3f(10.0f,39.0f,90.0f);
		glTexCoord2d(0,1); glVertex3f(17.0f,39.0f,90.0f);
		glTexCoord2d(0,0); glVertex3f(17.0f,36.0f,84.0f);
		glTexCoord2d(1,0); glVertex3f(10.0f,36.0f,84.0f);
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D,display[gols1]);
	
	glBegin(GL_QUADS);
	        glTexCoord2d(0,0); glVertex3f(10.0f,-36.0f,84.0f);
       	 	glTexCoord2d(1,0); glVertex3f(17.0f,-36.0f,84.0f);
	        glTexCoord2d(1,1); glVertex3f(17.0f,-39.0f,90.0f);
        	glTexCoord2d(0,1); glVertex3f(10.0f,-39.0f,90.0f);
	        
		glTexCoord2d(1,1); glVertex3f(-17.0f,39.0f,90.0f);
       	 	glTexCoord2d(0,1); glVertex3f(-10.0f,39.0f,90.0f);
	        glTexCoord2d(0,0); glVertex3f(-10.0f,36.0f,84.0f);
        	glTexCoord2d(1,0); glVertex3f(-17.0f,36.0f,84.0f);
	glEnd();					
}

// j eh o numero do jogador
void Visual::DesenhaJogador(int j)
{
	glPushMatrix();
	glTranslatef(
			jogo->getPartida()->getJog(j)->getPos().x,
			jogo->getPartida()->getJog(j)->getPos().y,
			0.5f);
//	if (j==0) 	glColor3f(0.3f,0.3f,1.0f);
//	else 		glColor3f(1.0f,0.3f,1.0f);
//
//	cylinder(jogo->getPartida().getJog(j).getRaio(),2.0,16);
//	cylinder(2,6,12);
	DesenhaMesh(&mallet);
	glPopMatrix();
}
void Visual::DesenhaMesh(obj_type_ptr mesh)
{
	int l_index;
	
   	glBindTexture(GL_TEXTURE_2D, mesh->id_texture);
	
	glBegin(GL_TRIANGLES);
	for (l_index=0;l_index<mesh->polygons_qty;l_index++)
	{
        //----------------- FIRST VERTEX -----------------
	// Texture coordinates of the first vertex
	 glTexCoord2f( mesh->mapcoord[ (unsigned short)mesh->polygon[l_index].a ].u,
		       mesh->mapcoord[ (unsigned short)mesh->polygon[l_index].a ].v);
	// Coordinates of the first vertex
        glVertex3f( mesh->vertex[ (unsigned short)mesh->polygon[l_index].a ].x,
                    mesh->vertex[ (unsigned short)mesh->polygon[l_index].a ].y,
                    mesh->vertex[ (unsigned short)mesh->polygon[l_index].a ].z);

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( mesh->mapcoord[ (unsigned short)mesh->polygon[l_index].b ].u,
		      mesh->mapcoord[ (unsigned short)mesh->polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( mesh->vertex[ (unsigned short)mesh->polygon[l_index].b ].x,
                    mesh->vertex[ (unsigned short)mesh->polygon[l_index].b ].y,
                    mesh->vertex[ (unsigned short)mesh->polygon[l_index].b ].z);
        
        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( mesh->mapcoord[ (unsigned short)mesh->polygon[l_index].c ].u,
                      mesh->mapcoord[ (unsigned short)mesh->polygon[l_index].c ].v);
				
        // Coordinates of the Third vertex
        glVertex3f( mesh->vertex[ (unsigned short)mesh->polygon[l_index].c ].x,
                    mesh->vertex[ (unsigned short)mesh->polygon[l_index].c ].y,
                    mesh->vertex[ (unsigned short)mesh->polygon[l_index].c ].z);
	}
    	glEnd();

}

void Visual::DesenhaMesa(void) {
	glBindTexture(GL_TEXTURE_2D,logomesa);
	//glColor3f(0.0f,0.0f,0.0f);
	glBegin(GL_QUADS);
		glTexCoord2d(0,0); glVertex3f(-25.0f,-25.0f,1.2f);
		glTexCoord2d(1,0); glVertex3f(25.0f,-25.0f,1.2f);
		glTexCoord2d(1,1); glVertex3f(25.0f,25.0f,1.2f);
		glTexCoord2d(0,1); glVertex3f(-25.0f,25.0f,1.2f);
	glEnd();
	DesenhaMesh(&mesa);
	glPushMatrix();
	glTranslatef(72.5,6.5,0);
	DesenhaMesh(&placar);
	glPopMatrix();
}

float Visual::retornaFPS(float ultimaFPS) {
	float	novaFPS;
	this->frame++;
	int tempo = glutGet(GLUT_ELAPSED_TIME);
	if (tempo - this->tempobase > 1000) {
		novaFPS = frame*1000/(tempo-this->tempobase);
		this->tempobase = tempo;
		this->frame = 0;
		return novaFPS;
	}
	else
		return ultimaFPS;
}
