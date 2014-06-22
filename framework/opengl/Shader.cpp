/* 
 * File:   Shader.cpp
 * Author: nathan
 * 
 * Created on June 21, 2014, 8:11 PM
 */

#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#include "util.h"
#include "GLProgram.h"

Shader::Shader(GLuint shaderType, const char *path) : shaderType(shaderType), path(path) {

}

Shader::~Shader() {
    if(this->compiled){
        std::cout << "Shader Terminated" << std::endl;
        glDeleteShader(this->shaderHandle);
    }
}

void Shader::compile(){
    std::string shaderSource = util::readFile(this->path.c_str());
    const char *src = shaderSource.c_str();
    this->shaderHandle = glCreateShader(this->shaderType);
    glShaderSource(this->shaderHandle, 1, &src, NULL);
    util::checkOpenGLError();
    
    glCompileShader(this->shaderHandle);
    util::checkCompileError(this->shaderHandle);
    util::checkOpenGLError();
    this->compiled = true;
}

void Shader::attach(GLuint program){
    glAttachShader(program, this->shaderHandle);
    util::checkOpenGLError();
}

void Shader::detach(GLuint program){
    glDetachShader(program, this->shaderHandle);
    util::checkOpenGLError();
}