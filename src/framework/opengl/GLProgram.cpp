/* 
 * File:   GLProgram.cpp
 * Author: nathan
 * 
 * Created on June 21, 2014, 8:00 PM
 */

#include "GLProgram.h"

#include "util.h"
#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <GL/glext.h>
#include "exceptions.h"

GLProgram::GLProgram() {
}

GLProgram::~GLProgram() {
    util::each(shaders, [&](ShaderPtr shader){
        shader->detach(this->programHandle);
    });
}

void GLProgram::loadVertexShader(const char* path){
    this->loadShader(GL_VERTEX_SHADER, path);
}

void GLProgram::loadFragmentShader(const char* path){
    this->loadShader(GL_FRAGMENT_SHADER, path);
}

void GLProgram::compileAndLink(){
    this->programHandle = glCreateProgram();
    util::each(shaders, [&](ShaderPtr shader) {
       shader->compile(); 
       shader->attach(this->programHandle);
       glLinkProgram(this->programHandle);
       util::checkLinkError(this->programHandle);
       util::checkOpenGLError();
    });
}

void GLProgram::loadShader(GLuint shaderType, const char* path) {
    auto shader = ShaderPtr(new Shader(shaderType, path));
    shaders.push_back(shader);
}


void GLProgram::use(){
    glUseProgram(this->programHandle);
    util::checkOpenGLError();
}

GLint GLProgram::getUniformLocation(const char* name){
    GLint location = glGetUniformLocation(this->programHandle, name);
    util::checkOpenGLError();
    if(location == -1){
        throw new OpenGLException();
    }

    return location;
}