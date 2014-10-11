/* 
 * File:   World.h
 * Author: nathan
 *
 * Created on July 10, 2014, 11:23 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>

#include "Position.h"
#include "Volume.h"
#include "include/cef_app.h"

namespace Ogre {
    class SceneManager;
    class ManualObject;
}

struct VoxelDefinition {
    std::string name;
    std::string topImage;
    std::string bottomImage;
    std::string sideImage;
    bool transparent;
};

struct Run {
    int type;
    int length;
};

typedef std::vector<VoxelDefinition> VoxelDefinitions;

class World {
private:
    Ogre::SceneManager *sceneManager;
    
    std::unordered_map<Position, VolumePtr> volumes;
    std::unordered_map<Position, Ogre::ManualObject*> manuals;
    
    VolumePtr findOrCreateVolume(Position p);
    Position toVolumePosition(Position p);
    Position toVoxelPosition(Position p);
    VolumePtr createVolume(Position volumePosition);
    Ogre::ManualObject* findOrCreateManualObject(Position volumePosition);

    VoxelDefinitions definitions;
public:
    
    World(Ogre::SceneManager* sceneManager);
    void batchCreateVoxels(int baseX, int baseY, int baseZ, std::vector<unsigned char>& voxels);
    void createVoxel(int type, int x, int y, int z);
    void createVoxels(int x, int y, int z, std::string runLengthEncodedVoxels);
    void clearVoxels();
    void defineVoxel(VoxelDefinition definition);
    VoxelDefinition lookupVoxelDefinition(int type);
    std::vector<Run> parseRuns(std::string runLengthEncodedVoxels);
};

typedef std::shared_ptr<World> WorldPtr;

#endif	/* WORLD_H */

