#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "exceptions.h"
#include "util.h"
#include "vmath.h"
#include "framework/World.h"

using namespace std;

static SDL_Window* window;
static SDL_Renderer* renderer;
static bool running = true;


static World world;

float absF(float x){
    if(x < 0){
        return -1 * x;
    } else {
        return x;
    }
}

void render(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    const GLfloat color[] = { 1.0f, 1.0f,
                              1.0f, 1.0f };
    
    
    glClearBufferfv(GL_COLOR, 0, color);
    
    world.render();
    
    SDL_GL_SwapWindow(window);
}

void update(){
    
}

void handleEvents(){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_s:
                        world.camera.move(0, 10, 0);
                        break;
                    case SDLK_w:
                        world.camera.move(0, -10, 0);
                        break;
                    case SDLK_a:
                        world.camera.move(10, 0, 0);
                        break;
                    case SDLK_d:
                        world.camera.move(-10, 0, 0);
                        break;
                    case SDLK_q:
                        world.camera.move(0,0,-10);
                        break;
                    case SDLK_e:
                        world.camera.move(0,0,10);
                        break;
                    case SDLK_UP:
                        world.camera.rotate(1.0f, 0.0f, 0.0f);
                        break;
                    case SDLK_DOWN:
                        world.camera.rotate(-1.0f, 0.0f, 0.0f);
                        break;
                    case SDLK_LEFT:
                        world.camera.rotate(0.0f, 1.0, 0.0f);
                        break;
                    case SDLK_RIGHT:
                        world.camera.rotate(0.0f, -1.0, 0.0f);
                        break;
                    
                    case SDLK_PAGEDOWN:
                        world.camera.rotate(0,0,-1.0f);
                        break;
                    case SDLK_PAGEUP:
                        world.camera.rotate(0,0,1.0f);
                        break;
                }
                break;
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                switch(event.window.event){
                    case SDL_WINDOWEVENT_RESIZED:
                        world.camera.windowWidth = event.window.data1 / 2.0;
                        world.camera.windowHeight = event.window.data2 / 2.0;
                        glViewport(0,0,event.window.data1 / 2.0, event.window.data2 / 2.0);
                        break;
                }
                break;
       }
    }
}

void initSDL(){
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    window = SDL_CreateWindow("GodKing", 200, 200, world.camera.windowWidth, world.camera.windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    SDL_GLContext context = SDL_GL_CreateContext(window);
    
    if(context == NULL){
        cout << SDL_GetError() << endl;
        throw SDLInitFailed();
    }
    
    SDL_GL_MakeCurrent(window, context);
}

void initGlew(){
    glewExperimental = true;
    
    GLenum status = glewInit();
    if(status != GLEW_OK){
        cout << glewGetErrorString(status) << endl;
        throw CouldNotInitGlew();
    }
    
    util::clearOpenGLErrors();
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
//    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

void runEventLoop(){
    Uint32 frameCount = 0;
    Uint32 frameTime = 0;
    Uint32 ticks = SDL_GetTicks();
    
    auto fps = [&](){
        std::cout << 1000.0 / frameTime << ", ";
    };
    
    while(running){
        handleEvents();
        update();
        render();
        frameCount++;
        Uint32 newTicks = SDL_GetTicks();
        frameTime = newTicks - ticks;
        ticks = newTicks;
        fps();
    }    
}

void initGL(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}


int main(int argc, char* args[]){
    world.camera.windowWidth = 1080;
    world.camera.windowHeight = 1080;

    
    initSDL();
    initGlew();
    initGL();
    
    world.load();

    runEventLoop();
    SDL_Quit();
    return 0;
}
