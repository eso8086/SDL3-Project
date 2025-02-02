//
// Created by el on 2/1/25.
//
#define SDL_MAIN_USE_CALLBACKS 1

#include "vendor/glad./include/glad/glad.h"
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include <iostream>

#define WINDOW_TITLE "OpenGL"
#define WINDOW_W 800
#define WINDOW_H 600



struct AppContext{
    SDL_Window* window;
    SDL_GLContext main_context;
};

//startup
SDL_AppResult SDL_AppInit(void **appstate, int argc, char* argv[]){
    SDL_SetAppMetadata("My OpenGL App", "0.1", "com.example.opengl");


    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }


    SDL_GL_LoadLibrary(NULL);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL);
    if(!window){
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_GLContext maincontext = SDL_GL_CreateContext(window);
    if(!maincontext){
        SDL_Log("Couldn't create OpenGL context: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress);

    SDL_Log("Vendor: %s", glGetString(GL_VENDOR));
    SDL_Log("Renderer: %s", glGetString(GL_RENDERER));
    SDL_Log("Version: %s", glGetString(GL_VERSION));

    SDL_GL_SetSwapInterval(1);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);


    *appstate = new AppContext{
        window,
        maincontext,
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

    const double now = ((double)SDL_GetTicks()) / 1000.0;

    glViewport(0, 0, WINDOW_W, WINDOW_H);


    //RENDER



    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    SDL_GL_SwapWindow(app->window);

    return SDL_APP_CONTINUE;
}

//clean up
void SDL_AppQuit(void* appstate, SDL_AppResult result){
    //clean up if needed
    auto* app = (AppContext*)appstate;
    if(app){
        SDL_DestroyWindow(app->window);
        delete app;
    }
    SDL_Quit();
    SDL_Log("Application quit successfully");
}