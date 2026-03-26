#include <SDL2/SDL.h>
#include <cstdio>
#include "Boid.h"
#include <cstdlib>
#include <ctime>

#define WIN_W 640
#define WIN_H 480
#define BOID_COUNT 100

using std::printf;

int main( int argc, char** argv )
{
    srand( time( NULL ) );
    if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        printf( "Could not initialize SDL2.\nI'm blind!\n\nError: %s", SDL_GetError() );
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow( "Boids", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN );
    SDL_Renderer* renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

    // boid flock
    CBoid* flock = ( CBoid* ) malloc( BOID_COUNT * sizeof(CBoid) );  

    // initialize all boids
    for(int i = 0; i < BOID_COUNT; i++)
    {
        int x = rand() % WIN_W;
        int y = rand() % WIN_H;
        flock[i] = CBoid( x, y, 0, flock, BOID_COUNT ); // evil anti-placement new cult classic hack (don't tell the purists)
    }

    SDL_Event e;
    bool running = true;

    long lastFrameTime = SDL_GetTicks64();

    while( running )
    {
        long currtime = SDL_GetTicks64();
        if( SDL_PollEvent( &e ) )
        {
            switch( e.type )
            {
                case SDL_QUIT:
                {
                    running = false;
                }
            }
        }

        long deltaTime = currtime - lastFrameTime;

        SDL_SetRenderDrawColor( renderer, 0x20, 0x20, 0x20, 0xff );
        SDL_RenderClear( renderer );

        SDL_SetRenderDrawColor( renderer, 0x50, 0xff, 0x50, 0xff );
        for(int i = 0; i < BOID_COUNT; i++)
        {
            flock[i].update( deltaTime / 1000.0f );
            Vector pos = flock[i].getPosition();
            int px = (int)pos.x;
            int py = (int)pos.y;
            SDL_Rect rect = { px, py, 4, 4 };
            SDL_RenderFillRect(renderer, &rect);
        }



        SDL_RenderPresent( renderer );
        lastFrameTime = currtime;
    }

    free(flock);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}