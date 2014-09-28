
#include "World.h"
#include "meshers/GreedyMesher.h"

#include <iostream>
#include <exception>

#include "framework/meshers/GreedyMesher.h"
#include "Ogre.h"
#include "OgreManualObject.h"
#include "MeshLoader.h"

World::World(Ogre::SceneManager* sceneManager) : sceneManager(sceneManager) {}

void World::createVoxel(int type, int x, int y, int z) {
    Position p(x, y, z);
    Position volumePosition = this->toVolumePosition(p);
    Position voxelPosition = this->toVoxelPosition(p);
    VolumePtr volume = this->findOrCreateVolume(volumePosition);
    volume->setVoxel(voxelPosition,type);
    GreedyMesher mesher;
    VerticesAndFaces vf = mesher.mesh(volume);
    Ogre::ManualObject* manual = this->findOrCreateManualObject(volumePosition);
    MeshLoader::loadMesh(manual, vf);
    
//    for(int x = 0; x < World::XCHUNKS; x++){
//        for(int y = 0; y < World::YCHUNKS; y++){
//            for(int z = 0; z < World::ZCHUNKS; z++){
//                VolumePtr volume = gen.generate(Position(x, y, z));
//                GreedyMesher mesher;
//                VerticesAndFaces vf = mesher.mesh(volume);
//
//                ManualObject* manual = mSceneMgr->createManualObject("cc"+std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z));
//                MeshLoader::loadMesh(manual, vf);
//
//                SceneNode* thisSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
//                thisSceneNode->setPosition(x * Volume::XWIDTH,y * Volume::YWIDTH,z * Volume::ZWIDTH - 100);
//                thisSceneNode->attachObject(manual);
//            }
//        }
//    }

}

VolumePtr World::findOrCreateVolume(Position p){
    auto item = this->volumes.find(p);
    if(item != this->volumes.end()){
        VolumePtr vol = item->second;
        return vol;
    } else {
        return this->createVolume(p);
    }
}

Position World::toVolumePosition(Position p){
    return Position(p.x / Volume::XWIDTH, 
                    p.y / Volume::YWIDTH, 
                    p.z / Volume::ZWIDTH);
}

Position World::toVoxelPosition(Position p){
    return Position(p.x % Volume::XWIDTH, 
                    p.y % Volume::YWIDTH,
                    p.z % Volume::ZWIDTH);
}

VolumePtr World::createVolume(Position volumePosition){
    VolumePtr volume(new Volume());
    this->volumes.insert({volumePosition, volume});
    return volume;
}

Ogre::ManualObject* World::findOrCreateManualObject(Position p){
    auto item = this->manuals.find(p);
    if(item != this->manuals.end()) {
        return item->second;
    } else {
        Ogre::ManualObject *manual = sceneManager->createManualObject("cc" + std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z));
        this->manuals.insert({p, manual});
        Ogre::SceneNode* thisSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        thisSceneNode->setPosition(p.x * Volume::XWIDTH,p.y * Volume::YWIDTH,p.z * Volume::ZWIDTH - 100);
        thisSceneNode->attachObject(manual);
        return manual;
    }
}