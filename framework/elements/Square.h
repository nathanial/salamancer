/* 
 * File:   Square.h
 * Author: nathan
 *
 * Created on June 21, 2014, 11:18 PM
 */

#ifndef SQUARE_H
#define	SQUARE_H

#include "Element.h"
#include "util.h"

class Square : public Element {
public:
    Square();
    ~Square();
    virtual size_t dataSize();
    virtual void* dataPtr();
    virtual int vertexCount();
private:
    DISALLOW_COPY_AND_ASSIGN(Square);
};

#endif	/* SQUARE_H */

