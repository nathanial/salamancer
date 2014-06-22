/* 
 * File:   Cube.h
 * Author: nathan
 *
 * Created on June 22, 2014, 12:39 AM
 */

#ifndef CUBE_H
#define	CUBE_H

#include "Element.h"
#include "util.h"

class Cube : public Element {
public:
    Cube();
    ~Cube();
    virtual size_t dataSize();
    virtual void* dataPtr();
    virtual int vertexCount();
    virtual size_t colorSize();
    virtual void* colorPtr();
private:
    DISALLOW_COPY_AND_ASSIGN(Cube);
    
};

#endif	/* CUBE_H */

