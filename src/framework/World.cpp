
#include "World.h"
#include "meshers/GreedyMesher.h"

#include <iostream>
#include <exception>

#include "framework/meshers/GreedyMesher.h"
#include "Ogre.h"
#include "OgreManualObject.h"
#include "MeshLoader.h"
#include "include/internal/cef_types.h"

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
}


void World::clearVoxels() {
    this->sceneManager->clearScene();
    this->manuals.clear();
    this->volumes.clear();
    this->sceneManager->destroyAllManualObjects();
}

void World::batchCreateVoxels(std::vector<uint32>& voxels, int xwidth, int ywidth, int zwidth){
    std::unordered_map<Position, VolumePtr> dirtyVolumes;
    for(int x = 0; x < xwidth; x++){
        for(int y = 0; y < ywidth; y++){
            for(int z = 0; z < zwidth; z++){
                uint32 type = voxels.at(x*xwidth*ywidth + y*ywidth + z);
                Position p(x,y,z);
                Position volumePosition = this->toVolumePosition(p);
                Position voxelPosition = this->toVoxelPosition(p);
                VolumePtr volume = this->findOrCreateVolume(volumePosition);
                dirtyVolumes.insert({volumePosition, volume});
                volume->setVoxel(voxelPosition, type);
            }
        }
    }

    for(auto& volPair : dirtyVolumes){
        GreedyMesher mesher;
        VerticesAndFaces vf = mesher.mesh(volPair.second);
        Ogre::ManualObject* manual = this->findOrCreateManualObject(volPair.first);
        MeshLoader::loadMesh(manual, vf);
    }
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
        Ogre::ManualObject *manual = sceneManager->createManualObject();
        this->manuals.insert({p, manual});
        Ogre::SceneNode* thisSceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        thisSceneNode->setPosition(p.x * Volume::XWIDTH,p.y * Volume::YWIDTH,p.z * Volume::ZWIDTH - 100);
        thisSceneNode->attachObject(manual);
        return manual;
    }
}
