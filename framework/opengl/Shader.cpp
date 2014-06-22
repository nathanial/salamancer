/* 
 * File:   Shader.cpp
 * Author: nathan
 * 
 * Created on June 21, 2014, 8:11 PM
 */

#include "Shader.h"
#include <iostream>

Shader::Shader(GLuint shaderType, const char *path) : shaderType(shaderType), path(path) {
    std::cout << "Shader Construct " << std::endl;
}

Shader::~Shader() {
    std::cout << "Shader Destruct " << std::endl;
}

void Shader::compile(){
    std::cout << "Shader Compile " << this->path << std::endl;
}