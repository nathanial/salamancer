#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "exceptions.h"
#include "util.h"
#include "vmath.h"
#include "framework/opengl/GLProgram.h"
#include "framework/elements/Element.h"
#include "framework/elements/Square.h"
#include "framework/elements/Cube.h"
#include "framework/elements/Chunk.h"

using namespace std;

static SDL_Window* window;
static SDL_Renderer* renderer;
static bool running = true;

static int windowWidth = 1920;
static int windowHeight = 1080;



static GLProgram program;
static Chunk chunk;

static GLint transformLocation;

float absF(float x){
    if(x < 0){
        return -1 * x;
    } else {
        return x;
    }
}

vmath::mat4 createTransform(double currentTime, float x, float y, float z){
    float aspect = (float)windowWidth / (float)windowHeight;
    vmath::mat4 transform(vmath::mat4::identity());
    transform = vmath::mat4::identity();
    transform *= vmath::perspective(1, aspect, 0.1f, 1000.0f);
    transform *= vmath::translate(x, y, z);
    transform *= vmath::rotate((float)sin(currentTime) * 360, 1.0f, 0.0f, 0.0f);
//    transform *= vmath::translate(0.0f, 0.0f, (float)sin(currentTime) * 10);
    return transform;
}

void render(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double currentTime = ((double)SDL_GetTicks()) / 1000;
    
    const GLfloat color[] = { 1.0f, 1.0f,
                              1.0f, 1.0f };
    
    float z = -100.0f;
    
    auto renderChunk = [&](float x, float y){
        vmath::mat4 transform = createTransform(currentTime, x, y, z);
        glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);
        chunk.render();
    };
    
    glClearBufferfv(GL_COLOR, 0, color);

    renderChunk(40, 10.0f);
    renderChunk(0, 10.0f);
    renderChunk(-40, 10.0f);
    
    SDL_GL_SwapWindow(window);
}

void update(){
    
}

void handleEvents(){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_WINDOWEVENT:
                switch(event.window.event){
                    case SDL_WINDOWEVENT_RESIZED:
                        windowWidth = event.window.data1 / 2.0;
                        windowHeight = event.window.data2 / 2.0;
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

    window = SDL_CreateWindow("GodKing", 200, 200, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
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
    initSDL();
    initGlew();
    initGL();
    
    
    program.loadVertexShader("/home/nathan/Projects/godking/shaders/vertex.shader");
    program.loadFragmentShader("/home/nathan/Projects/godking/shaders/fragment.shader");
    program.compileAndLink();
    program.use();
    
    transformLocation = program.getUniformLocation("Transform");
    
    chunk.load();
    
    runEventLoop();
    SDL_Quit();
    return 0;
}
