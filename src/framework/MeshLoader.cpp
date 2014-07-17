/* 
 * File:   MeshLoader.cpp
 * Author: nathan
 * 
 * Created on July 11, 2014, 12:53 AM
 */

#include "MeshLoader.h"
#include "framework/Volume.h"
#include "framework/meshers/Mesher.h"
#include "framework/World.h"
#include <functional>

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>
#include <string>

using namespace Ogre;

void MeshLoader::loadMesh(std::string name, VerticesAndFaces verticesAndFaces){
//    PerlinTerrainGenerator gen;
//    VolumePtr volume = gen.generate(Position(1,World::YCHUNKS -1,1));
//    auto verticesAndFaces = Mesher::mesh(volume);
    Vertices voxVertices = std::get<0>(verticesAndFaces);
    Faces voxFaces = std::get<1>(verticesAndFaces);
    
    /// Create the mesh via the MeshManager
    Ogre::MeshPtr msh = MeshManager::getSingleton().createManual(name, "General");
 
    /// Create one submesh
    SubMesh* sub = msh->createSubMesh();
 
    const float sqrt13 = 0.577350269f; /* sqrt(1/3) */
 
    /// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
    size_t nVertices = voxVertices.size();
    size_t vbufCount = 3*2*nVertices;
    float vertices[vbufCount]; 
    for(int i = 0; i < nVertices; i++){
        int cursor = i*3*2;
        Vertex vertex = voxVertices.at(i);
        
        //position
        vertices[cursor++] = vertex[0];
        vertices[cursor++] = vertex[1];
        vertices[cursor++] = vertex[2];
        
        //normal
        vertices[cursor++] = sqrt13 * (vertex[0] < 0 ? -1 : 1);
        vertices[cursor++] = sqrt13 * (vertex[1] < 0 ? -1 : 1);
        vertices[cursor++] = sqrt13 * (vertex[2] < 0 ? -1 : 1);
    }
 
    RenderSystem* rs = Root::getSingleton().getRenderSystem();
    RGBA colours[nVertices];
    RGBA *pColour = colours;
    // Use render system to convert colour value since colour packing varies
    rs->convertColourValue(ColourValue(1.0,0.0,0.0), pColour++); //0 colour
    rs->convertColourValue(ColourValue(1.0,1.0,0.0), pColour++); //1 colour
    rs->convertColourValue(ColourValue(0.0,1.0,0.0), pColour++); //2 colour
    rs->convertColourValue(ColourValue(0.0,0.0,0.0), pColour++); //3 colour
    rs->convertColourValue(ColourValue(1.0,0.0,1.0), pColour++); //4 colour
    rs->convertColourValue(ColourValue(1.0,1.0,1.0), pColour++); //5 colour
    rs->convertColourValue(ColourValue(0.0,1.0,1.0), pColour++); //6 colour
    rs->convertColourValue(ColourValue(0.0,0.0,1.0), pColour++); //7 colour
 
    /// Define 12 triangles (two triangles per cube face)
    /// The values in this table refer to vertices in the above table
    size_t ibufCount = voxFaces.size() * 3;
    unsigned short faces[ibufCount];
    
    for(int i = 0; i < voxFaces.size(); i++){
        int cursor = i * 3;
        Face face = voxFaces[i];
        faces[cursor++] = face[0];
        faces[cursor++] = face[1];
        faces[cursor++] = face[2];
    }
 
    /// Create vertex data structure for 8 vertices shared between submeshes
    msh->sharedVertexData = new VertexData();
    msh->sharedVertexData->vertexCount = nVertices;
 
    /// Create declaration (memory format) of vertex data
    VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
    size_t offset = 0;
    // 1st buffer
    decl->addElement(0, offset, VET_FLOAT3, VES_POSITION);
    offset += VertexElement::getTypeSize(VET_FLOAT3);
    decl->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
    offset += VertexElement::getTypeSize(VET_FLOAT3);
    /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
    /// and bytes per vertex (offset)
    HardwareVertexBufferSharedPtr vbuf = 
        HardwareBufferManager::getSingleton().createVertexBuffer(
        offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);
 
    /// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
    VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
    bind->setBinding(0, vbuf);
 
    // 2nd buffer
    offset = 0;
    decl->addElement(1, offset, VET_COLOUR, VES_DIFFUSE);
    offset += VertexElement::getTypeSize(VET_COLOUR);
    /// Allocate vertex buffer of the requested number of vertices (vertexCount) 
    /// and bytes per vertex (offset)
    vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(
        offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);
 
    /// Set vertex buffer binding so buffer 1 is bound to our colour buffer
    bind->setBinding(1, vbuf);
 
    /// Allocate index buffer of the requested number of vertices (ibufCount) 
    HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().
        createIndexBuffer(
        HardwareIndexBuffer::IT_16BIT, 
        ibufCount, 
        HardwareBuffer::HBU_STATIC_WRITE_ONLY);
 
    /// Upload the index data to the card
    ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);
 
    /// Set parameters of the submesh
    sub->useSharedVertices = true;
    sub->indexData->indexBuffer = ibuf;
    sub->indexData->indexCount = ibufCount;
    sub->indexData->indexStart = 0;
 
    /// Set bounding information (for culling)
    msh->_setBounds(AxisAlignedBox(-100,-100,-100,100,100,100));
    msh->_setBoundingSphereRadius(Math::Sqrt(3*100*100));
 
    /// Notify -Mesh object that it has been loaded
    msh->load();
}

void MeshLoader::loadMesh(ManualObject *manual, VerticesAndFaces vf){
    const float sqrt13 = 0.577350269f; /* sqrt(1/3) */
    manual->begin("ColorTest", RenderOperation::OT_TRIANGLE_LIST);
    Vertices vertices = std::get<0>(vf);
    
    float colors[][3] = {
        {1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0},
        {1.0, 1.0, 1.0},
        {0.5, 0.5, 0.5}
    };
    
    for(int i = 0; i < vertices.size(); i++){
        Vertex vertex = vertices[i];
        float *color = colors[i % 5];
        manual->colour(color[0], color[1], color[2]);
        manual->position(vertex[0], vertex[1], vertex[2]);
    }
    Faces faces = std::get<1>(vf);
    for(int i = 0; i < faces.size(); i++){
        Face face = faces[i];
        manual->quad(face[0], face[1], face[2], face[3]);
    }
    
    manual->end();
}