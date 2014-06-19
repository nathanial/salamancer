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

static GLuint vao;

static const char *vertexShaderPath = "shaders/vertex.shader";
static const char *fragmentShaderPath = "shaders/fragment.shader";


void init(void){
    glGenVertexArrays(1, &vao);
    util::checkOpenGLError();
    glBindVertexArray(vao);
    util::checkOpenGLError();
}

void compileShaders(void){
    GLuint vertexShader;
    GLuint fragmentShader;
    
    string vertexSrc = util::readFile(vertexShaderPath);
    string fragmentSrc = util::readFile(fragmentShaderPath);
    
    const char *vertexShaderSource = vertexSrc.c_str();
    const char *fragmentShaderSource = fragmentSrc.c_str();
    
    util::checkOpenGLError();
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    util::checkOpenGLError();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    util::checkOpenGLError();
    glCompileShader(vertexShader);
    util::checkCompileError(vertexShader);
    util::checkOpenGLError();

            
    
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    util::checkOpenGLError();
    glCompileShader(fragmentShader);
    util::checkCompileError(fragmentShader);
    util::checkOpenGLError();
    
    program = glCreateProgram();
    util::checkOpenGLError();
    glAttachShader(program, vertexShader);
    util::checkOpenGLError();
    glAttachShader(program, fragmentShader);
    util::checkOpenGLError();
    glLinkProgram(program);
    util::checkOpenGLError();
    util::checkLinkError(program);

    init();
    
}

void render(){
    const GLfloat color[] = { 1.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, color);
    glUseProgram(program);
    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 0, 1);
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
