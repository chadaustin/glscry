/* main.cpp */

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <GL/gl.h>
#include <SDL.h>
#include <assert.h>
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 600;
const int INDEX_COUNT = 10000;

struct Vertex{
    GLfloat v[3];
//    GLubyte c[4];
//    GLfloat t[2];

    static void checkSize() {
        //assert(sizeof(Vertex) == sizeof(GLfloat) * 5 + sizeof(GLubyte) * 4);
        assert(sizeof(Vertex) == sizeof(GLfloat) * 3);
    }
};

void test ( )
{
    Vertex data[8192];
    GLushort indices[INDEX_COUNT];

    for ( int i=0; i < 8192; ++i )
    {
        data[i].v[0] = 0.0f;
        data[i].v[1] = 0.0f;
        data[i].v[2] = 0.0f;
#if 0
        data[i].v[0] = 0.001f*(float)(i/2);
        data[i].v[1] = 0.001f*(float)(i%2);
        data[i].v[2] = 0.0f;
        data[i].c[0] = 0xff;
        data[i].c[1] = 0x00;
        data[i].c[2] = 0xff;
        data[i].c[3] = 0xff;
        data[i].t[0] = 0.0f;
        data[i].t[1] = 0.0f;
#endif
    }

    //glDisable ( GL_LIGHTING );
    //glDisable ( GL_BLEND );
    //glDisable ( GL_TEXTURE_2D );
    //glDisable ( GL_TEXTURE_1D );
    //glDisable ( GL_DEPTH_TEST );
    //glDisable ( GL_STENCIL_TEST );

    //glClearColor ( 0, 0, 0.3f, 0);
    //glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glViewport ( 0, 0, WIDTH, HEIGHT );

    glEnableClientState ( GL_VERTEX_ARRAY );
//    glEnableClientState ( GL_COLOR_ARRAY );
//    glEnableClientState ( GL_TEXTURE_COORD_ARRAY );
    glVertexPointer ( 3, GL_FLOAT, sizeof(Vertex), data[0].v );
//    glColorPointer ( 4, GL_UNSIGNED_BYTE, sizeof(Vertex), data[0].c );
//    glTexCoordPointer ( 2, GL_FLOAT, sizeof(Vertex), data[0].t );

    for ( int count=2; count<256; count+=2 )
    {
        /* ok */
        for ( int j=0; j < 10000; ++j )
            indices[j]=j%count;
        long t_start=SDL_GetTicks();
		
        int loop=0;
        for (; loop<1000; ++loop)
            glDrawElements(GL_TRIANGLES, INDEX_COUNT, GL_UNSIGNED_SHORT, &indices);
        glFinish ();
		
        long t_delta=SDL_GetTicks() - t_start;
        float rate = ((float)(loop*INDEX_COUNT))*1000.0f/t_delta;
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
    SDL_SetVideoMode ( WIDTH, HEIGHT, 32, SDL_OPENGL );

    test ( );
/*
    SDL_Event ev;
    bool quit=false;

    do
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
