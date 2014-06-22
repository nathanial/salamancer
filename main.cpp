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

using namespace std;

static SDL_Window* window;
static SDL_Renderer* renderer;
static bool running = true;

static int windowWidth = 600;
static int windowHeight = 600;



static GLProgram program;
static Cube cube;

static GLint transformLocation;


void render(){
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    double currentTime = ((double)SDL_GetTicks()) / 1000;
    
    const GLfloat color[] = { 1.0f, 1.0f,
                              1.0f, 1.0f };
    
    float rotation = (int)(SDL_GetTicks() / 10) % 360;
    
    float aspect = (float)windowWidth / (float)windowHeight;
    vmath::mat4 transform(vmath::mat4::identity());
    
    auto perspective = vmath::perspective(45.0f, aspect, 0.1f, 100.0f);
    
    transform = transform * perspective;
    transform = transform * vmath::lookat(
            vmath::vec3(4.0f,3.0f,-3.0f), 
            vmath::vec3(0.0f,0.0f,0.0f), 
            vmath::vec3(0.0f,1.0f,0.0f)
            );
    transform = transform * vmath::rotate(rotation, 0.0f, 1.0f, 0.0f);
    
    glClearBufferfv(GL_COLOR, 0, color);
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);

    cube.render();
    
    util::checkOpenGLError();
    
    
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
                        windowWidth = event.window.data1;
                        windowHeight = event.window.data2;
                        glViewport(0,0,event.window.data1, event.window.data2);
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

    window = SDL_CreateWindow("GodKing", 0, 0, 600, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    
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
}

void runEventLoop(){
    while(running){
        handleEvents();
        update();
        render();
    }    
}

int main(int argc, char* args[]){
    initSDL();
    initGlew();
    
    
    program.loadVertexShader("shaders/vertex.shader");
    program.loadFragmentShader("shaders/fragment.shader");
    program.compileAndLink();
    program.use();
    
    transformLocation = program.getUniformLocation("Transform");
    
    cube.load();
    
    runEventLoop();
    SDL_Quit();
    return 0;
}
