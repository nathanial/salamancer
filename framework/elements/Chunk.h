/* 
 * File:   Chunk.h
 * Author: nathan
 *
 * Created on June 23, 2014, 1:57 AM
 */

#ifndef CHUNK_H
#define	CHUNK_H

#include "util.h"

class Position {
public:
    float x;
    float y;
    float z;
    
    Position(float x = 0, float y = 0, float z = 0) : x(x), y(y),  z(z) {}
    
private:
};

class Chunk {
public:
    Chunk();
    ~Chunk();
    void load();
    void render();
    
    void setPosition(Position position);
    Position getPosition();
private:
    DISALLOW_COPY_AND_ASSIGN(Chunk);
    
    const int XWIDTH = 16;
    const int YWIDTH = 16;
    const int ZWIDTH = 16;
    
    Position position;
    
    GLuint vao;
    GLuint cubesBuffer;
    GLuint colorBuffer;
    
    void generateCubesBuffer();
    void generateColorsBuffer();
};

#endif	/* CHUNK_H */

