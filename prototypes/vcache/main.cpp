/* main.cpp */

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <GL/gl.h>
#include <SDL.h>
#include <stdio.h>

struct Vertex{
    float x,y,z;
    long c;
    float u,v;
};

void test ( )
{
    Vertex data[8192];
    unsigned short indices[10000];
    int err;

    for ( int i=0; i < 8192; ++i )
    {
        data[i].x = 0.001f*(float)(i/2);
        data[i].y = 0.001f*(float)(i%2);
        data[i].z = 0.0f;
        data[i].c = 0xffff00ff;
        data[i].u = 0.0f;
        data[i].v = 0.0f;
    }

    glDisable ( GL_LIGHTING );
    glDisable ( GL_BLEND );
    glDisable ( GL_TEXTURE_2D );
    glDisable ( GL_TEXTURE_1D );
    glDisable ( GL_DEPTH_TEST );
    glDisable ( GL_STENCIL_TEST );

    glClearColor ( 0, 0, 0.3f, 0);
    err=glGetError ();
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    err=glGetError ();
    glViewport ( 0, 0, 800, 600 );
    err=glGetError ();

    glEnableClientState ( GL_VERTEX_ARRAY );
    err=glGetError ();
    glEnableClientState ( GL_COLOR_ARRAY );
    err=glGetError ();
    glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
    err=glGetError ();
    glColorPointer ( 4, GL_UNSIGNED_BYTE, sizeof(Vertex), &data[0].c );
    err=glGetError ();
    glVertexPointer ( 3, GL_FLOAT, sizeof(Vertex), &data[0].x );
    err=glGetError ();
    glTexCoordPointer ( 2, GL_FLOAT, sizeof(Vertex), &data[0].u );
    err=glGetError ();

    for ( int count=2; count<256; count+=2 )
    {
        /* ok */
        for ( int j=0; j < 10000; ++j )
            indices[j]=j%count;
        long t_start=SDL_GetTicks();
		
        int loop=0;
        for (; loop<1000; ++loop )
            glDrawElements ( GL_TRIANGLE_STRIP, 10000, GL_UNSIGNED_SHORT, &indices );
        glFlush ();
		
        long t_delta=SDL_GetTicks() - t_start;
        float rate = ((float)(loop*10000))*1000.0f/t_delta;
        printf ("%3d : %f vertices/s\n", count, rate );
    }

		
}

int main ( int argc, char ** argv )
{
    SDL_Init ( SDL_INIT_EVERYTHING );
    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );	
    SDL_SetVideoMode ( 800, 600, 32, SDL_OPENGL );

    SDL_Event ev;
    bool quit=false;

    test ( );
/*	do
  {
  if ( SDL_PollEvent ( &ev ) )
  {
  if ( ev.type == SDL_KEYDOWN )
  if ( ev.key.keysym.sym == SDLK_q )
  quit = true;
			
  }

  } while ( !quit );
*/
    SDL_Quit ( );
	
    return 0;
}


#if defined(WIN32) && !defined(_CONSOLE)

    #include <windows.h>

    #ifdef __CYGWIN__
    extern "C" __declspec(dllimport) int __argc;
    extern "C" __declspec(dllimport) char* __argv[];
    #endif

    int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
        return main(__argc, __argv);
    }

#endif
