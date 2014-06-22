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
    glBufferData(GL_ARRAY_BUFFER, this->dataSize(), this->dataPtr(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    
    util::checkOpenGLError();
    
 
    void* colorData = this->colorPtr();
    if(colorData != NULL){
        glGenBuffers(1, &this->colorBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, this->colorSize(), colorData, GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glEnableVertexAttribArray(1);
        util::checkOpenGLError();
    }
}

void Element::render(){
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount());
}

void* Element::colorPtr(){
    return NULL;
}

size_t Element::colorSize(){
    return 0;
}