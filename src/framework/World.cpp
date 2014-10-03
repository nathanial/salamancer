
#include "World.h"

#include <iostream>
#include <exception>

World::World(Ogre::SceneManager* sceneManager) : sceneManager(sceneManager) {}

void World::createVoxel(int type, int x, int y, int z) {
    VolumePtr volume = this->findOrCreateVolume(Position(x,y,z));
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
    Position volumePosition = this->toVolumePosition(p);
    auto item = this->volumes.find(p);
    if(item != this->volumes.end()){
        VolumePtr vol = item->second;
        return vol;
    } else {
        throw std::runtime_error("Need to create volume");
    }
}

Position World::toVolumePosition(Position voxelPosition){
    return Position(voxelPosition.x / Volume::XWIDTH, 
                    voxelPosition.y / Volume::YWIDTH, 
                    voxelPosition.z / Volume::ZWIDTH);
}