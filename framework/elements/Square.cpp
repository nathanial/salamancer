/* 
 * File:   Square.cpp
 * Author: nathan
 * 
 * Created on June 21, 2014, 11:18 PM
 */

#include "Square.h"

static float square[] = {
    -1, -1, -1, 1,
    -1, 1, -1, 1.0,
    1, 1, -1, 1.0,

    -1, -1, -1, 1.0,
    1, -1, -1, 1.0,
    1, 1, -1, 1.0
};


Square::Square() {
}

Square::~Square() {
}

size_t Square::dataSize() {
    return sizeof(square);
}

void* Square::dataPtr(){
    return square;
}

int Square::vertexCount(){
    return 6;
}