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

#include "Position.h"
#include "Volume.h"
#include "include/cef_app.h"

namespace Ogre {
    class SceneManager;
    class ManualObject;
}

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
public:
    World(Ogre::SceneManager* sceneManager);
    void batchCreateVoxels(std::vector<uint32>& voxels, int xwidth, int ywidth, int zwidth);
    void createVoxel(int type, int x, int y, int z);
    void clearVoxels();
};

typedef std::shared_ptr<World> WorldPtr;

#endif	/* WORLD_H */

