
#include "World.h"
#include "meshers/GreedyMesher.h"

#include <iostream>
#include <exception>
#include <vector>

#include "framework/meshers/GreedyMesher.h"
#include "Ogre.h"
#include "OgreManualObject.h"
#include "MeshLoader.h"
#include "include/internal/cef_types.h"
#include "OgrePass.h"

std::vector<std::string> split(const std::string src, char delim) {
    std::vector<std::string> elements;
    std::stringstream ss(src);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elements.push_back(item);
    }
    return elements;
}

World::World(Ogre::SceneManager* sceneManager) : sceneManager(sceneManager) {}

void World::createVoxel(int type, int x, int y, int z) {
    Position p(x, y, z);
    Position volumePosition = this->toVolumePosition(p);
    Position voxelPosition = this->toVoxelPosition(p);
    VolumePtr volume = this->findOrCreateVolume(volumePosition);
    volume->setVoxel(type, voxelPosition.x, voxelPosition.y, voxelPosition.z);
    GreedyMesher mesher;
    VerticesAndFaces vf = mesher.mesh(volume);
    Ogre::ManualObject* manual = this->findOrCreateManualObject(volumePosition);
    MeshLoader::loadMesh(this, manual, vf);
}


void World::clearVoxels() {
    this->definitions.clear();
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
                VolumePtr volume = this->findOrCreateVolume(volumePosition);
                dirtyVolumes.insert({volumePosition, volume});
                volume->setVoxel(type, x,y,z);
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
    
    Position volumePosition(baseX, baseY, baseZ);
    VolumePtr volume = this->findOrCreateVolume(volumePosition);
    std::vector<Run> runs = this->parseRuns(runLengthEncodedVoxels);
    int cursor = 0;
    for(auto run : runs){
        for(int i = 0; i < run.length; i++){
            int x = cursor % Volume::XWIDTH;
            int y = cursor / (Volume::XWIDTH * Volume::ZWIDTH);
            int z = (cursor / Volume::XWIDTH) % Volume::ZWIDTH;
            
            assert(x < Volume::XWIDTH);
            assert(y < Volume::YWIDTH);
            assert(z < Volume::ZWIDTH);
            volume->setVoxel(run.type, x, y, z);
            cursor++;
        }
    }
    
    GreedyMesher mesher;
    auto vf = mesher.mesh(volume);
    auto manual = this->findOrCreateManualObject(Position(baseX, baseY, baseZ));
    MeshLoader::loadMesh(this, manual, vf);
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
   
    
    std::vector<std::string> textures = { definition.topImage, definition.sideImage, definition.sideImage, definition.sideImage, definition.sideImage, definition.bottomImage };

    Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().createManual("TextureArrayTex",
            Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
            Ogre::TEX_TYPE_3D,
            256, 256, 6,
            0,
            Ogre::PF_A8R8G8B8,
            Ogre::TU_STATIC_WRITE_ONLY);


    Ogre::HardwarePixelBufferSharedPtr buffer = tex->getBuffer(0,0);
    buffer->lock(Ogre::HardwareBuffer::HBL_NORMAL);
    const Ogre::PixelBox &pb = buffer->getCurrentLock();
    Ogre::uint32 *pbptr = static_cast<Ogre::uint32*> (pb.data);
    for (size_t z = pb.front; z < pb.back; z++) {
        for (size_t y = pb.top; y < pb.bottom; y++) {
            for (size_t x = pb.left; x < pb.right; x++) {
                if (z == pb.front || z == (pb.back - 1) || y == pb.top || y == (pb.bottom - 1) ||
                        x == pb.left || x == (pb.right - 1)) {
                    // On border, must be zero
                    pbptr[x] = 0;
                }
                else {
                    //Ogre::TexturePtr texture = Ogre::TextureManager::getSingleton().load(textures[i], Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                    Ogre::PixelUtil::packColour(1.0f, 0.5f, 0.1f, 1.0f, Ogre::PF_A8R8G8B8, &pbptr[x]);
                }
            }
            pbptr += pb.rowPitch;
        }
        pbptr += pb.getSliceSkip();
    }
    buffer->unlock();
    
    auto material = Ogre::MaterialManager::getSingleton().create(definition.name, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);
    Ogre::Pass *pass = material->getTechnique(0)->getPass(0);
    pass->setLightingEnabled(false);
    if(definition.transparent) {
        pass->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
        pass->setSceneBlendingOperation(Ogre::SceneBlendOperation::SBO_MAX);
    }
    Ogre::TextureUnitState *texUnit = pass->createTextureUnitState();
    texUnit->setTextureName("TextureArrayTex");
}

VoxelDefinition World::lookupVoxelDefinition(int type){
    return definitions.at(type - 1);
}

std::vector<Run> World::parseRuns(std::string runLengthEncodedVoxels) {
    auto runTexts = split(runLengthEncodedVoxels, ',');
    std::vector<Run> runs;
    for(auto runText : runTexts){
        auto runElements = split(runText, ':');
        Run run;
        run.length = std::stoi(runElements[0]);
        run.type = std::stoi(runElements[1]);
        runs.push_back(run);
    }
    return runs;
}