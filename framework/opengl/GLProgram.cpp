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

GLProgram::GLProgram() {
}

GLProgram::~GLProgram() {
}

void GLProgram::loadVertexShader(const char* path){
    shaders.push_back(ShaderPtr(new Shader(GL_VERTEX_SHADER, path)));
}

void GLProgram::loadFragmentShader(const char* path){
    shaders.push_back(ShaderPtr(new Shader(GL_FRAGMENT_SHADER, path)));
}

void GLProgram::compileAndLink(){
    util::each(shaders, [](ShaderPtr shader) {
       shader->compile(); 
    });
}

void GLProgram::use(){
    
}