//
// Created by el on 2/1/25.
//
#define SDL_MAIN_USE_CALLBACKS 1
#include "SDL3/SDL.h"
#include <SDL3/SDL_main.h>

#include <iostream>

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;


//startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]){

    SDL_SetAppMetadata("My OpenGL App", "0.1", "com.example.opengl");

    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if(!SDL_CreateWindowAndRenderer("OpenGL", 800, 600, 0, &window, &renderer)){
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;
}

//events
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event *event){
    if(event->type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

//frame
SDL_AppResult SDL_AppIterate(void* appstate){
    const double now = ((double) SDL_GetTicks()) / 1000.0;

    const auto red = (float) (0.5 + 0.5 * SDL_sin(now));
    const auto green = (float) (0.5 + 0.5 * SDL_sin(SDL_PI_D * 2 / 3));
    const auto blue = (float) (0.5 + 0.5 * SDL_sin(SDL_PI_D * 4 / 3));

    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);


    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;
}

//clean up
void SDL_AppQuit(void* appstate, SDL_AppResult result){
    //clean up if needed
}