/* 
 * File:   Chunk.h
 * Author: nathan
 *
 * Created on June 23, 2014, 1:57 AM
 */

#ifndef CHUNK_H
#define	CHUNK_H

#include <memory.h>

#include "util.h"
#include "framework/Position.h"
#include "framework/Volume.h"
#include "framework/Mesher.h"

class Chunk {
public:
    Chunk();
    ~Chunk();
    
    void load();
    void render();
    
    void setPosition(Position position);
    Position getPosition();
    
    VolumePtr volume;

private:
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

