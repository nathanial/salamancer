#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "exceptions.h"
#include "util.h"

using namespace std;

#define MAX_COMPILE_LOG_LEN 1000

static GLuint program;
static SDL_Window* window;
static SDL_Renderer* renderer;
static bool running = true;
static GLint colorLocation;

static GLuint vao;

static const char *vertexShaderPath = "shaders/vertex.shader";
static const char *fragmentShaderPath = "shaders/fragment.shader";
static const char *geometryShaderPath = "shaders/geometry.shader";


void init(void){
    glGenVertexArrays(1, &vao);
    util::checkOpenGLError();
    glBindVertexArray(vao);
    util::checkOpenGLError();
}

void compileShaders(void){
    GLuint vertexShader = util::compileShader(GL_VERTEX_SHADER, vertexShaderPath);
    GLuint fragmentShader = util::compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    GLuint geometryShader = util::compileShader(GL_GEOMETRY_SHADER, geometryShaderPath);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glAttachShader(program, geometryShader);
    glLinkProgram(program);
    
    colorLocation = glGetUniformLocation(program, "color");

    util::checkOpenGLError();
    util::checkLinkError(program);
    

    init();
    
}

void render(){
    double currentTime = ((double)SDL_GetTicks()) / 1000;
    
    const GLfloat color[] = { 1.0f, 1.0f,
                              1.0f, 1.0f };
    const GLfloat reddish[] = {(float)sin(currentTime),0,0,1};
    glClearBufferfv(GL_COLOR, 0, color);

    // Use the program object we created earlier for rendering
    glUseProgram(program);

    GLfloat position[] = { (float)sin(currentTime) * 0.5f,
                         (float)cos(currentTime) * 0.5f,
                         0.0f, 0.0f };

    // Update the value of input attribute 0
    glVertexAttrib4fv(0, position);
    glUniform4fv(colorLocation, 1, reddish);
    
    util::checkOpenGLError();

    glPointSize(5);
    // Draw one triangle
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    
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
            default:
                break; 
       }
    }
}

int main(int argc, char* args[]){
    
    SDL_Init(SDL_INIT_EVERYTHING);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    window = SDL_CreateWindow("GodKing", 0, 0, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    
    SDL_GLContext context = SDL_GL_CreateContext(window);
    
    if(context == NULL){
        cout << SDL_GetError() << endl;
        throw SDLInitFailed();
    }
    
    SDL_GL_MakeCurrent(window, context);
    
    glewExperimental = true;
    
    GLenum status = glewInit();
    if(status != GLEW_OK){
        cout << glewGetErrorString(status) << endl;
        throw CouldNotInitGlew();
    }
    
    util::clearOpenGLErrors();
    
    
    compileShaders();
    
    
    while(running){
        handleEvents();
        update();
        render();
    }
    
//    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}
