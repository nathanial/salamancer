/* 
 * File:   World.cpp
 * Author: nathan
 * 
 * Created on June 28, 2014, 10:27 PM
 */

#include "World.h"
#include "vmath.h"
#include "terrain/PerlinTerrainGenerator.h"
#include <GL/glew.h>


World::World() {
    PerlinTerrainGenerator gen;
    for(int i = 0; i < XCHUNKS; i++){
        for(int j = 0; j < YCHUNKS; j++){
            for(int k = 0; k < ZCHUNKS; k++){
                this->chunks[i][j][k].volume = gen.generate(Position(i,j,k));
            }
        }
    }
}


World::~World() {
}

void World::render() {
    for(int i = 0; i < XCHUNKS; i++){
        for(int j = 0 ; j < YCHUNKS; j++){
            for(int k = 0; k < ZCHUNKS; k++){
                Position pos(i,j,k);
                Rotation rot;
                
                vmath::mat4 transform = this->createTransform(pos, rot);
                glUniformMatrix4fv(this->transformLocation, 1, GL_FALSE, transform);
                this->chunks[i][j][k].render();
                util::checkOpenGLError();
            }
        }
    }
    
}

void World::load(){
    program.loadVertexShader("/home/nathan/Projects/godking/shaders/vertex.shader");
    program.loadFragmentShader("/home/nathan/Projects/godking/shaders/fragment.shader");
    program.compileAndLink();
    program.use();
    
    this->transformLocation = this->program.getUniformLocation("Transform");
    
    util::checkOpenGLError();

    for(int i = 0; i < XCHUNKS; i++){
        for(int j = 0; j < YCHUNKS; j++){
            for(int k = 0; k < ZCHUNKS; k++){
                this->chunks[i][j][k].load();
                util::checkOpenGLError();
            }
        }
    }
}

vmath::mat4 World::createTransform(Position chunkPosition, Rotation chunkRotation){
    vmath::mat4 transform(vmath::mat4::identity());
    transform *= camera.getMatrix();
    transform *= vmath::translate(chunkPosition.x * Volume::XWIDTH, 
                                  chunkPosition.y * Volume::YWIDTH, 
                                  chunkPosition.z * Volume::ZWIDTH);  
    return transform;
}

//vmath::mat4 createTransform(double currentTime, float x, float y, float z){
//    float aspect = (float)windowWidth / (float)windowHeight;
//    vmath::mat4 transform(vmath::mat4::identity());
//    transform = vmath::mat4::identity();
//    transform *= vmath::perspective(1, aspect, 0.1f, 10000.0f);
//    transform *= vmath::translate(x, y, z);
//    //transform *= vmath::rotate((float)currentTime * 100, 1.0f, 0.0f, 0.0f);
////    transform *= vmath::translate(0.0f, 0.0f, (float)sin(currentTime) * 10);
//    return transform;
//}
