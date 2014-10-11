
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
    MeshLoader::loadMesh(this, manual, vf);
}


void World::clearVoxels() {
    this->sceneManager->clearScene();
    this->manuals.clear();
    this->volumes.clear();
    this->sceneManager->destroyAllManualObjects();
}

void World::batchCreateVoxels(int baseX, int baseY, int baseZ, std::vector<unsigned char>& voxels){
    std::unordered_map<Position, VolumePtr> dirtyVolumes;
    Position volumePosition(baseX, baseY, baseZ);
    for(int x = 0; x < Volume::XWIDTH; x++){
        for(int y = 0; y < Volume::YWIDTH; y++){
            for(int z = 0; z < Volume::ZWIDTH; z++){
                unsigned char type = voxels.at(x*Volume::YWIDTH*Volume::ZWIDTH + y*Volume::ZWIDTH + z);
                Position voxelPosition(x,y,z);
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
        MeshLoader::loadMesh(this, manual, vf);
    }
}

void World::createVoxels(int baseX, int baseY, int baseZ, std::string runLengthEncodedVoxels){
    std::cout << "World Create Voxels: " << baseX << " " << baseY << " " << baseZ << " " << runLengthEncodedVoxels << std::endl;
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

void World::defineVoxel(VoxelDefinition definition){
    definitions.push_back(definition);
   
    std::vector<std::tuple<std::string, std::string> > materialNames = {
        std::make_tuple(definition.name + "Top", definition.topImage),
        std::make_tuple(definition.name + "Side", definition.sideImage),
        std::make_tuple(definition.name + "Bottom", definition.bottomImage)
    };
    
    for(auto pair : materialNames){
        auto materialName = std::get<0>(pair);
        auto imageName = std::get<1>(pair);

        auto material = Ogre::MaterialManager::getSingleton().create(materialName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
        auto pass = material->getTechnique(0)->getPass(0);
        pass->setLightingEnabled(false);
        if(definition.transparent) {
            pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
            pass->setSceneBlendingOperation(Ogre::SceneBlendOperation::SBO_MAX);
        }
        Ogre::TextureUnitState *tex = pass->createTextureUnitState();
        tex->setTextureName(imageName);
        material ->load();
    }
}

VoxelDefinition World::lookupVoxelDefinition(int type){
    return definitions.at(type - 1);
}