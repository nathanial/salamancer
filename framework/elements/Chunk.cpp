/* 
 * File:   Chunk.cpp
 * Author: nathan
 *  
* Created on June 23, 2014, 1:57 AM
 */

#include "Chunk.h"
#include <iostream>

#include <GL/glew.h>
#include "framework/Mesher.h"
#include "framework/Volume.h"


static const int VERTICES_PER_CUBE = 12 * 3;
static const int CUBES = Volume::XWIDTH * Volume::YWIDTH * Volume::ZWIDTH;
static const float VERTEX = 1.0f;
static const float OFFSET = VERTEX * 2;
static const int FLOATS_IN_ARRAY = VERTICES_PER_CUBE * 4;
static const int FLOATS_IN_COLOR_ARRAY = VERTICES_PER_CUBE * 3;

static GLfloat cube_vertices[] = {
    -VERTEX,-VERTEX,-VERTEX, 1, // triangle 1 : begin
    -VERTEX,-VERTEX, VERTEX, 1,
    -VERTEX, VERTEX, VERTEX, 1, // triangle 1 : end
    VERTEX, VERTEX,-VERTEX, 1, // triangle 2 : begin
    -VERTEX,-VERTEX,-VERTEX, 1,
    -VERTEX, VERTEX,-VERTEX, 1, // triangle 2 : end
    VERTEX,-VERTEX, VERTEX, 1,
    -VERTEX,-VERTEX,-VERTEX, 1,
    VERTEX,-VERTEX,-VERTEX, 1,
    VERTEX, VERTEX,-VERTEX, 1,
    VERTEX,-VERTEX,-VERTEX, 1,
    -VERTEX,-VERTEX,-VERTEX, 1,
    -VERTEX,-VERTEX,-VERTEX, 1,
    -VERTEX, VERTEX, VERTEX, 1,
    -VERTEX, VERTEX,-VERTEX, 1,
    VERTEX,-VERTEX, VERTEX, 1,
    -VERTEX,-VERTEX, VERTEX, 1,
    -VERTEX,-VERTEX,-VERTEX, 1,
    -VERTEX, VERTEX, VERTEX, 1,
    -VERTEX,-VERTEX, VERTEX, 1,
    VERTEX,-VERTEX, VERTEX, 1,
    VERTEX, VERTEX, VERTEX, 1,
    VERTEX,-VERTEX,-VERTEX, 1,
    VERTEX, VERTEX,-VERTEX, 1,
    VERTEX,-VERTEX,-VERTEX, 1,
    VERTEX, VERTEX, VERTEX, 1,
    VERTEX,-VERTEX, VERTEX, 1,
    VERTEX, VERTEX, VERTEX, 1,
    VERTEX, VERTEX,-VERTEX, 1,
    -VERTEX, VERTEX,-VERTEX, 1,
    VERTEX, VERTEX, VERTEX, 1,
    -VERTEX, VERTEX,-VERTEX, 1,
    -VERTEX, VERTEX, VERTEX, 1,
    VERTEX, VERTEX, VERTEX, 1,
    -VERTEX, VERTEX, VERTEX, 1,
    VERTEX,-VERTEX, VERTEX, 1
};

static GLfloat cube_colors[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};

Chunk::Chunk() {
    for(int row = 0; row < Volume::XWIDTH; row++){
        for(int column = 0; column < Volume::YWIDTH; column++){
            for(int rank = 0; rank < Volume::ZWIDTH; rank++){
//                int choice = rand() % 100;
//                this->volume[row][column][rank] = choice > 50 ? 1 : 0;
                this->volume.voxels[row][column][rank] = 1;
            }
        }
    }
    
    int dims[3] = {Volume::XWIDTH, Volume::YWIDTH, Volume::ZWIDTH};
    Mesher::mesh(this->volume, dims);
    
}

Chunk::~Chunk() {
    
}

void Chunk::load(){
    
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    this->generateCubesBuffer();
    this->generateColorsBuffer();

}

void Chunk::render(){
    glBindVertexArray(this->vao);
    glDrawArrays(GL_TRIANGLES, 0, VERTICES_PER_CUBE * CUBES);
}
    
void Chunk::setPosition(Position position){
    this->position = position;
}

Position Chunk::getPosition(){
    return this->position;
}

void Chunk::generateCubesBuffer(){
    glGenBuffers(1, &this->cubesBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->cubesBuffer);
    
    GLfloat *cubeVertices = new GLfloat[FLOATS_IN_ARRAY * CUBES];
    
    int cubeIndex = 0;
    auto createCube = [&](int row, int column, int rank){
        for(int i = 0; i < VERTICES_PER_CUBE; i++){
            for(int j = 0; j < 4; j++){
                int index = (i * 4 + j) + (VERTICES_PER_CUBE * cubeIndex * 4);
                cubeVertices[index] = cube_vertices[index % FLOATS_IN_ARRAY];
                if(j == 0){
                    cubeVertices[index] += OFFSET * row;
                } else if(j == 1){
                    cubeVertices[index] += OFFSET * column;
                } else if(j == 2){
                    cubeVertices[index] += OFFSET * rank;
                }
            }                    
        }
        cubeIndex++;
    };
    
    for(int row = 0; row < Volume::XWIDTH; row++){
        for(int column = 0; column < Volume::YWIDTH; column++){
            for(int rank = 0; rank < Volume::ZWIDTH; rank++){
                if(this->volume.voxels[row][column][rank] != 0){
                    createCube(row, column, rank);
                }
            }
        }
    }
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * VERTICES_PER_CUBE * CUBES * 4, cubeVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    util::checkOpenGLError();
    
    delete [] cubeVertices;
}

void Chunk::generateColorsBuffer(){
    glGenBuffers(1, &this->colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    
    GLfloat *colorVertices = new GLfloat[FLOATS_IN_COLOR_ARRAY * CUBES];
    for(int i = 0; i < (VERTICES_PER_CUBE * CUBES); i++){
        for(int j = 0; j < 4; j++){
            colorVertices[i * 3 + j] = cube_colors[(i*3+j) % FLOATS_IN_COLOR_ARRAY];
        }
    }
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * VERTICES_PER_CUBE * CUBES * 3, colorVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    util::checkOpenGLError();
    
    delete [] colorVertices;
}

