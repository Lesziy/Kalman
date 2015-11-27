#include "SimpleSDL.h"

SimpleSDL::SimpleSDL() 
{
    SDL_Surface* hello = NULL;
    SDL_Surface* screen = NULL;

    //Start SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    // Unrecoverable error, exit here.
    printf("SDL_Init failed: %s\n", SDL_GetError());
}


    //Set up screen
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    //Load image
    hello = SDL_LoadBMP( "hello.bmp" );

    //Apply image to screen
    SDL_BlitSurface( hello, NULL, screen, NULL );

    //Update Screen
    SDL_Flip( screen );

    //Pause
    SDL_Delay( 2000 );

    //Free the loaded image
    SDL_FreeSurface( hello );

    //Quit SDL
    SDL_Quit();
}

SimpleSDL::~SimpleSDL()
{
}
