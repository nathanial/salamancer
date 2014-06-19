#include "util.h"
#include <string>
#include "exceptions.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>

using namespace std;

#define MAX_COMPILE_LOG_LEN 1000


string util::readFile(const char* path){
    ifstream t(path);
    if(!t.is_open()){
        throw FileNotFoundException(path);
    }
    string str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());
    return str;
}

void util::clearOpenGLErrors(){
    GLenum error = glGetError();
    while(error != GL_NO_ERROR){
        error = glGetError();
    }
}

void util::checkOpenGLError(){
    GLenum error;
    error = glGetError();
    if(error != GL_NO_ERROR){
        cout << gluErrorString(error) << endl;
        throw OpenGLException();
    }
}

void util::checkCompileError(GLuint shader){
    GLint compiled = GL_FALSE;
    GLchar log[MAX_COMPILE_LOG_LEN] = {0};
    GLsizei logLen = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if(!compiled){
        glGetShaderInfoLog(shader, MAX_COMPILE_LOG_LEN, &logLen, log);
        cout << log << endl;
        throw OpenGLException();
    }
}

void util::checkLinkError(GLuint program){
    GLint isLinked = 0;
    GLchar log[MAX_COMPILE_LOG_LEN] = {0};
    GLsizei logLen = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    checkOpenGLError();
    if(isLinked == GL_FALSE){
        glGetProgramInfoLog(program, MAX_COMPILE_LOG_LEN, &logLen, log);
        cout << "Link Error:" << log << endl;
        throw OpenGLException();
    }
}

GLuint util::compileShader(GLenum shaderType, const char* path){
    string shaderSource = readFile(path);
    const char *source = shaderSource.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    util::checkCompileError(shader);
    util::checkOpenGLError();
    return shader;
}