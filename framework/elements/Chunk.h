/* 
 * File:   Chunk.h
 * Author: nathan
 *
 * Created on June 23, 2014, 1:57 AM
 */

#ifndef CHUNK_H
#define	CHUNK_H

#include "util.h"
#include "framework/Volume.h"
#include "framework/Mesher.h"

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

    Volume volume;
    Position position;
    Mesher::Vertices vertices;
    Mesher::Faces faces;
    
    GLuint vao;
    GLuint verticesBuffer;
    GLuint facesBuffer;
    GLuint colorBuffer;
    
    void generateFacesBuffer();
    void generateVerticesBuffer();
    void generateColorsBuffer();
};

#endif	/* CHUNK_H */

