/* 
 * File:   World.h
 * Author: nathan
 *
 * Created on June 28, 2014, 10:27 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include "framework/opengl/GLProgram.h"
#include "framework/Position.h"
#include "framework/Rotation.h"
#include "framework/Camera.h"
#include "Chunk.h"
#include <vector>
#include "vmath.h"

#include <GL/glew.h>

class World {

public:
    World();
    ~World();
    
    static const int XCHUNKS = 20;
    static const int YCHUNKS = 5;
    static const int ZCHUNKS = 20;

    Camera camera;
    
    Chunk chunks [XCHUNKS][YCHUNKS][ZCHUNKS];
    
    
    void render();
    void load();
    
private:
    vmath::mat4 createTransform(
            Position chunkPosition,
            Rotation chunkRotation
            );
    
    GLint transformLocation;
    GLProgram program;
};

#endif	/* WORLD_H */

