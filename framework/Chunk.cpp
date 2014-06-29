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
#include "Camera.h"

static const int VERTICES_PER_CUBE = 12 * 3;
static const int CUBES = Volume::XWIDTH * Volume::YWIDTH * Volume::ZWIDTH;
static const float VERTEX = 1.0f;
static const float OFFSET = VERTEX * 2;
static const int FLOATS_IN_ARRAY = VERTICES_PER_CUBE * 4;
static const int FLOATS_IN_COLOR_ARRAY = VERTICES_PER_CUBE * 3;

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

Chunk::Chunk(){}
Chunk::~Chunk(){}

void Chunk::load(){
    int dims[3] = {Volume::XWIDTH, Volume::YWIDTH, Volume::ZWIDTH};
    auto meshResults = Mesher::mesh(this->volume, dims);
    Mesher::Vertices &vertices = std::get<0>(meshResults);
    Mesher::Faces &faces = std::get<1>(meshResults);
    this->vertices = vertices;
    this->faces = faces;
    
    glGenBuffers(1, &this->verticesBuffer);
    glGenBuffers(1, &this->facesBuffer);
    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);
    
    this->generateVerticesBuffer();
    this->generateFacesBuffer();
    this->generateColorsBuffer();
}

void Chunk::render(){
    glBindVertexArray(this->vao);
    glDrawElements(GL_TRIANGLES, this->faces.size() * 3, GL_UNSIGNED_INT, 0);
    util::checkOpenGLError();
}
    
void Chunk::setPosition(Position position){
    this->position = position;
}

Position Chunk::getPosition(){
    return this->position;
}

void Chunk::generateFacesBuffer(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->facesBuffer );

    GLuint *indices = new GLuint[this->faces.size() * 3];
    
    for(int i = 0; i < this->faces.size(); i++){
        for(int j = 0; j < 3; j++){
            indices[i*3+j] = (unsigned int)this->faces[i][j];
        }
    }
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * this->faces.size() * 3, indices, GL_STATIC_DRAW);
    
    util::checkOpenGLError();
    
    delete [] indices;
}

void Chunk::generateVerticesBuffer(){
    glBindBuffer(GL_ARRAY_BUFFER, this->verticesBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
        
    GLfloat *cubeVertices = new GLfloat[this->vertices.size() * 3];

    int i = 0;
    for(Mesher::Vertex v : vertices){
        cubeVertices[i++] = v[0];
        cubeVertices[i++] = v[1];
        cubeVertices[i++] = v[2];
    }

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * this->vertices.size() * 3, cubeVertices, GL_STATIC_DRAW);
    util::checkOpenGLError();

    delete [] cubeVertices;
}

void Chunk::generateColorsBuffer(){
    glGenBuffers(1, &this->colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);
    util::checkOpenGLError();
    
}
