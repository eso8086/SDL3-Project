//
// Created by el on 2/1/25.
//
#define SDL_MAIN_USE_CALLBACKS 1

#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include "SDL3/SDL_opengl.h"
#include <iostream>


#define WINDOW_TITLE "OpenGL"
#define WINDOW_W 800
#define WINDOW_H 600



struct AppContext{
    SDL_Window* window;
    SDL_Renderer* renderer;
};

//startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]){
    SDL_SetAppMetadata("My OpenGL App", "0.1", "com.example.opengl");


    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL);
    if(!window){
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if(!renderer){
        SDL_Log("Couldn't create renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    *appstate = new AppContext{
        window,
        renderer
    };

    SDL_Log("Application started successfully");

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
    auto* app = (AppContext*) appstate;

    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const auto red = (float) (0.5 + 0.5 * SDL_sin(now));
    const auto green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const auto blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));

    glClearColor(red, green, blue, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);


    SDL_GL_SwapWindow(app->window);

    return SDL_APP_CONTINUE;
}

//clean up
void SDL_AppQuit(void* appstate, SDL_AppResult result){
    //clean up if needed
    auto* app = (AppContext*)appstate;
    if(app){
        SDL_DestroyRenderer(app->renderer);
        SDL_DestroyWindow(app->window);
        delete app;
    }
    SDL_Quit();
    SDL_Log("Application quit successfully");
}