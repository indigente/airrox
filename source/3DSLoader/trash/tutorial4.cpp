/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 2: 3d engine - Start to draw using OpenGL!
 * 
 *
 * To compile this project you must include the following libraries:
 * opengl32.lib,glu32.lib,sdl.lib
 *
 */

/*
	port to SDL(www.libsdl.org) by Afrasinei Alexandru alex-toranaga@home.ro
*/
#include "main.h"        

			        
/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/


// Absolute rotation values (0-359 degrees) and rotation increments for each frame
double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.1;
double rotation_z=0, rotation_z_increment=0.2;
 
// Flag for rendering as lines or filled polygons
int filling=1; //0=OFF 1=ON

//Now the object is generic, the cube has annoyed us a little bit, or not?
obj_type object;


/**********************************************************
 *
 * SUBROUTINE init()
 *
 * Used to initialize OpenGL and to setup our world
 *
 *********************************************************/
void Init()
{
    InitializeOpenGL(SCREEN_WIDTH, SCREEN_HEIGHT);    
    
    if ( SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL) )	 
    {
        std::cout << "Failed enablaing key repeat :" << SDL_GetError() << std::endl;
        Quit(1);
    }  
    
    Load3DS (&object,"mesa.3ds");

    object.id_texture=LoadBitmap("mesatext.bmp"); // The Function LoadBitmap() return the current texture ID
    
    // If the last function returns -1 it means the file was not found so we exit from the program
    if (object.id_texture==-1)
   {
	   std::cout << "Image file: mesatext.bmp not found\n" << std::endl;
        exit (0);
    }
}


/**********************************************************
 *
 * SUBROUTINE display()
 *
 * This is our main rendering subroutine, called each frame
 * 
 *********************************************************/

void display() 
{
	int l_index;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity
    
    glTranslatef(0.0,0.0,-300); // We move the object forward (the model matrix is multiplied by the translation matrix)
 
    rotation_x = rotation_x + rotation_x_increment;
    rotation_y = rotation_y + rotation_y_increment;
    rotation_z = rotation_z + rotation_z_increment;

    if (rotation_x > 359) rotation_x = 0;
    if (rotation_y > 359) rotation_y = 0;
    if (rotation_z > 359) rotation_z = 0;

/*  glRotatef(rotation_x,1.0,0.0,0.0); // Rotations of the object (the model matrix is multiplied by the rotation matrices)
    glRotatef(rotation_y,0.0,1.0,0.0);
    glRotatef(rotation_z,0.0,0.0,1.0);*/

    glRotatef(-75,1,0,0); // posiciona a mesa na visao do jogo
    
	glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 
    glColor3f(0.7f,0.7f,0.7f);
    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<object.polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].a ].u,
                      object.mapcoord[ object.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object.vertex[ object.polygon[l_index].a ].x,
                    object.vertex[ object.polygon[l_index].a ].y,
                    object.vertex[ object.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].b ].u,
                     object.mapcoord[ object.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object.vertex[ object.polygon[l_index].b ].x,
                    object.vertex[ object.polygon[l_index].b ].y,
                    object.vertex[ object.polygon[l_index].b ].z);
        
        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( object.mapcoord[ object.polygon[l_index].c ].u,
                      object.mapcoord[ object.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object.vertex[ object.polygon[l_index].c ].x,
                    object.vertex[ object.polygon[l_index].c ].y,
                    object.vertex[ object.polygon[l_index].c ].z);
    }
    glEnd();

    glFlush(); // This force the execution of OpenGL commands
	SDL_GL_SwapBuffers();									
}


//---------HANDLE KEY PRESS EVENT---------
void HandleKeyPressEvent(SDL_keysym * keysym)
{
    switch(keysym -> sym)                                  
    {
        case SDLK_ESCAPE:                                 
            Quit(0);                                       
	
	case SDLK_UP:
            rotation_x_increment = rotation_x_increment +0.1;
        break;
        case SDLK_DOWN:
            rotation_x_increment = rotation_x_increment -0.1;
        break;
        case SDLK_LEFT:
            rotation_y_increment = rotation_y_increment +0.1;
        break;
        case SDLK_RIGHT:
            rotation_y_increment = rotation_y_increment -0.1;
        break;
    }
}

//---------HANDLE KEY RELEASE EVENT---------
void HandleKeyReleaseEvent(SDL_keysym * keysym)
{
    switch(keysym -> sym)                                 
    {
    
    	case ' ':
            rotation_x_increment=0;
            rotation_y_increment=0;
            rotation_z_increment=0;
        break;
	
        case 'r': case 'R':
            if (filling==0)
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
                filling=1;
            }   
            else 
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
                filling=0;
            }
        break;
                                           
    }
}

//-------------HANDLE MAIN LOOP---------
void MainLoop(void)
{
    bool done = false;                                     
    SDL_Event event;

    while(! done)                                          
    {
        while( SDL_PollEvent(& event) )                    
        {
            switch ( event.type )                          
            {
                case SDL_QUIT :                                        
                    done = true;                                        
                    break;

                case SDL_KEYDOWN :                                      
                    HandleKeyPressEvent( & event. key.keysym );         
                    break;
		
		case SDL_KEYUP :                                                  
                    HandleKeyReleaseEvent( & event. key.keysym );                
                    break;
		    
                case SDL_VIDEORESIZE :                                                 
                    MainWindow = SDL_SetVideoMode( event.resize.w, event.resize.h, SCREEN_DEPTH, VideoFlags );
                    SizeOpenGLScreen(event.resize.w, event.resize.h);   
    
                    if(MainWindow == NULL)                              
                    {
                        std::cout << " Failed resizing SDL window : " << SDL_GetError() << std::endl;   
                        Quit(0);
                    }
                    break;

                default:                                    
                    break;                                  
            } 
        } 
		display();								// Redraw the scene every frame
    } 
}
