/* 
 * File:   World.h
 * Author: nathan
 *
 * Created on July 10, 2014, 11:23 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include <memory>
#include <unordered_map>

#include "Position.h"
#include "Volume.h"

namespace Ogre {
    class SceneManager;
}

class World {
private:
    Ogre::SceneManager *sceneManager;
    std::unordered_map<Position, VolumePtr> volumes;
    VolumePtr findOrCreateVolume(Position p);
    Position toVolumePosition(Position p);
public:
    World(Ogre::SceneManager* sceneManager);
    void createVoxel(int type, int x, int y, int z);
};

typedef std::shared_ptr<World> WorldPtr;

#endif	/* WORLD_H */

