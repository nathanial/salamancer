/* 
 * File:   Element.cpp
 * Author: nathan
 * 
 * Created on June 21, 2014, 11:16 PM
 */

#include "Element.h"
#include "exceptions.h"
#include <GL/glew.h>

void Element::load(){
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    glGenBuffers(1, &this->buffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->buffer);
    glBufferData(GL_ARRAY_BUFFER, 1024 * 1024, NULL, GL_STATIC_DRAW);
    
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->dataSize(), this->dataPtr());
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
}

void Element::render(){
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount());
}