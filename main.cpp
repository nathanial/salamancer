#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "exceptions.h"
#include "util.h"
#include "shapes.h"
#include "vmath.h"

using namespace std;

#define MAX_COMPILE_LOG_LEN 1000

static GLuint program;
static SDL_Window* window;
static SDL_Renderer* renderer;
static bool running = true;
static GLint colorLocation;
static GLint transformLocation;

static const char *vertexShaderPath = "shaders/vertex.shader";
static const char *fragmentShaderPath = "shaders/fragment.shader";
static const char *geometryShaderPath = "shaders/geometry.shader";

static int windowWidth = 600;
static int windowHeight = 600;


static GLuint buffer;

void init(void){
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glGenBuffers(1, &buffer);
    util::checkOpenGLError();
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    util::checkOpenGLError();
    glBufferData(GL_ARRAY_BUFFER, 1024 * 1024, NULL, GL_STATIC_DRAW);
    util::checkOpenGLError();
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(shapes::square), shapes::square);
    util::checkOpenGLError();
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    util::checkOpenGLError();
    glEnableVertexAttribArray(0);
    util::checkOpenGLError();
    
}

void compileShaders(void){
    GLuint vertexShader = util::compileShader(GL_VERTEX_SHADER, vertexShaderPath);
    GLuint fragmentShader = util::compileShader(GL_FRAGMENT_SHADER, fragmentShaderPath);
    GLuint geometryShader = util::compileShader(GL_GEOMETRY_SHADER, geometryShaderPath);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    //glAttachShader(program, geometryShader);
    glLinkProgram(program);
    
    colorLocation = glGetUniformLocation(program, "color");
    transformLocation = glGetUniformLocation(program, "Transform");

    util::checkOpenGLError();
    util::checkLinkError(program);
    
    glUseProgram(program);

    init();
    
}

void render(){
    double currentTime = ((double)SDL_GetTicks()) / 1000;
    
    const GLfloat color[] = { 1.0f, 1.0f,
                              1.0f, 1.0f };
    
    float redValue = (float)sin(currentTime);
    if(redValue < 0){
        redValue *= -1;
    }
    
    const GLfloat reddish[] = {redValue,0,0,1};
    
    float scaleValue = 50* (sin(currentTime / 10))  + 0.1;
    
    float aspect = (float)windowWidth / (float)windowHeight;
    vmath::mat4 transform(vmath::mat4::identity());
    
    transform = transform * vmath::perspective(45.0f, aspect, 0.1f, 100.0f);
    
    glClearBufferfv(GL_COLOR, 0, color);
    util::checkOpenGLError();
    
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, transform);
    
    util::checkOpenGLError();
    glUniform4fv(colorLocation, 1, reddish);
    util::checkOpenGLError();

    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    
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

int main(int argc, char* args[]){
    
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
