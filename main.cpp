//
// Created by el on 2/1/25.
//
#define SDL_MAIN_USE_CALLBACKS 1

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "SDL3/SDL.h"
#include "SDL3/SDL_main.h"
#include <iostream>

#define WINDOW_TITLE "OpenGL"
#define WINDOW_W 800
#define WINDOW_H 600



struct {
    SDL_Window* window;
    SDL_GLContext gl_context;
} app;

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

    app.window = SDL_CreateWindow(WINDOW_TITLE, WINDOW_W, WINDOW_H, SDL_WINDOW_OPENGL);
    if(!app.window){
        SDL_Log("Couldn't create window: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetWindowPosition(app.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    app.gl_context = SDL_GL_CreateContext(app.window);
    if(!app.gl_context){
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

//RENDER
SDL_AppResult SDL_AppIterate(void* appstate){
    const double now = ((double)SDL_GetTicks()) / 1000.0;

    glViewport(0, 0, WINDOW_W, WINDOW_H);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(app.window);

    return SDL_APP_CONTINUE;
}

//clean up
void SDL_AppQuit(void* appstate, SDL_AppResult result){
    if(result == SDL_APP_SUCCESS){
        SDL_Log("Application quit successfully");
    }
    else{
        SDL_Log("Application quit unsuccessfully");
    }

    SDL_DestroyWindow(app.window);
    SDL_Quit();
}
