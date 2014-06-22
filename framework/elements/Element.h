/* 
 * File:   Element.h
 * Author: nathan
 *
 * Created on June 21, 2014, 11:16 PM
 */

#ifndef ELEMENT_H
#define	ELEMENT_H

#include "util.h"

class Element {
public:
    void load();
    void render();
    virtual size_t dataSize() = 0;
    virtual void* dataPtr() = 0;
    virtual int vertexCount() = 0;
    virtual void* colorPtr();
    virtual size_t colorSize();
    
protected:
    GLuint vao;
    GLuint buffer;
    GLuint colorBuffer;
};

#endif	/* ELEMENT_H */

