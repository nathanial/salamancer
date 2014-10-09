/* 
 * File:   MeshLoader.cpp
 * Author: nathan
 * 
 * Created on July 11, 2014, 12:53 AM
 */

#include "MeshLoader.h"
#include "framework/Volume.h"
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


bool axisIsConstant(char axis, std::vector<Vertex> vertices){
    if(axis == 'x'){
        float value = vertices[0][0];
        for(int i = 0; i < vertices.size(); i++){
            if(value != vertices[i][0]){
                return false;
            }
        }
        return true;
    } else if(axis == 'y'){
        float value = vertices[0][1];
        for(int i = 0; i < vertices.size(); i++){
            if(value != vertices[i][1]){
                return false;
            }
        }
        return true;
    } else if(axis == 'z'){
        float value = vertices[0][2];
        for(int i = 0; i < vertices.size(); i++){
            if(value != vertices[i][2]){
                return false;
            }
        }
        return true;
    } else {
        throw "oops";
    }
}

char constantAxis(Vertex v1, Vertex v2, Vertex v3, Vertex v4){
    std::vector<Vertex> quad({v1,v2,v3,v4});
    if(axisIsConstant('x', quad)){
        return 'x';
    } else if(axisIsConstant('y', quad)){
        return 'y';
    } else if(axisIsConstant('z', quad)){
        return 'z';
    } else {
        throw "Could not find constant axis";
    }
}

float textureXScale(Vertex v1, Vertex v2, Vertex v3, Vertex v4){
    std::vector<Vertex> quad({v1,v2,v3,v4});
    if(axisIsConstant('x', quad)){
        return std::abs(v1[2]-v3[2]);
    } else if(axisIsConstant('y', quad)){
        return std::abs(v1[0] - v3[0]);
    } else if(axisIsConstant('z', quad)){
        return std::abs(v1[0] - v3[0]);
    } else {
        throw "No Constant Axis";
    }
}

float textureYScale(Vertex v1, Vertex v2, Vertex v3, Vertex v4){
    std::vector<Vertex> quad({v1,v2,v3,v4});
    if(axisIsConstant('x', quad)){
        return std::abs(v1[1]-v3[1]);
    } else if(axisIsConstant('y', quad)){
        return std::abs(v1[2]-v3[2]);
    } else if(axisIsConstant('z', quad)){
        return std::abs(v1[1]-v3[1]);
    } else {
        throw "No Constant Axis";
    }
}

void MeshLoader::loadMesh(ManualObject *manual, VerticesAndFaces vf){
    Vertices vertices = std::get<0>(vf);

    if (vertices.size() == 0) {
        return;
    }
    
    const float sqrt13 = 0.577350269f; /* sqrt(1/3) */
    manual->clear();
    
    Faces faces = std::get<1>(vf);
    bool alreadyLoaded[vertices.size()] = {false};
    
    for(int i = 0; i < faces.size(); i++){
        Face face = faces[i];
        
        Vertex v1 = vertices[face[0]];
        Vertex v2 = vertices[face[1]];
        Vertex v3 = vertices[face[2]];
        Vertex v4 = vertices[face[3]];
        
        auto computeNormal = [&](){
            Ogre::Vector3 ov1(v1[0], v1[1], v1[2]);
            Ogre::Vector3 ov2(v2[0], v2[1], v2[2]);
            Ogre::Vector3 ov3(v3[0], v3[1], v3[2]);
            Ogre::Vector3 ov4(v4[0], v4[1], v4[2]);
               
            Ogre::Vector3 dir0 = ov3 - ov1;
            Ogre::Vector3 dir1 = ov1 - ov2;
            Ogre::Vector3 normal = dir0.crossProduct(dir1).normalisedCopy();
            return normal;
        };
        
        Ogre::Vector3 normal = computeNormal();
        
        
        auto rightside = normal.x >= 1;
        auto leftside = normal.x <= -1;
        auto backside = normal.z <= -1;
        auto frontside = normal.z >= 1;
        
        float frontXScale = std::abs(v1[0] - v3[0]);
        float frontYScale = std::abs(v1[1] - v3[1]);
        float leftXScale = std::abs(v1[2]-v3[2]);
        float leftYScale = std::abs(v1[1]-v3[1]);
        
        manual->begin("Dirt", RenderOperation::OT_TRIANGLE_LIST);

        manual->position(v1[0], v1[1], v1[2]);
        if(leftside){           
            manual->textureCoord(0, leftYScale);
        } else if(frontside){
            manual->textureCoord(0, frontYScale);
        } else if(backside){
            manual->textureCoord(frontXScale,frontYScale);
        } else if(rightside){
            manual->textureCoord(leftXScale, leftYScale);
        } else {
            manual->textureCoord(0,0);
        }
        
        manual->position(v2[0], v2[1], v2[2]);
        if(leftside){
            manual->textureCoord(leftXScale, leftYScale);
        } else if(frontside) {
            manual->textureCoord(frontXScale, frontYScale);
        } else if(backside){
            manual->textureCoord(frontXScale,0);
        } else if(rightside){
            manual->textureCoord(leftXScale, 0);
        } else {
            manual->textureCoord(0,0);
        }
        
        manual->position(v3[0], v3[1], v3[2]);
        if(leftside){
            manual->textureCoord(leftXScale, 0);
        } else if(frontside){
            manual->textureCoord(frontXScale, 0);
        } else if(backside){
            manual->textureCoord(0, 0);
        } else if(rightside){
            manual->textureCoord(0, 0);
        }  else {
            manual->textureCoord(0,0);
        }

        manual->position(v4[0], v4[1], v4[2]);
        if(backside){
            manual->textureCoord(0, frontYScale);
        } else if(rightside){
            manual->textureCoord(0, leftYScale);
        } else {
            manual->textureCoord(0,0);
        }

        //manual->quad(face[0], face[1], face[2], face[3]);
        manual->quad(0,1,2,3);

        manual->end();
    }
    
}