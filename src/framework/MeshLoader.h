/* 
 * File:   MeshLoader.h
 * Author: nathan
 *
 * Created on July 11, 2014, 12:53 AM
 */

#ifndef MESHLOADER_H
#define	MESHLOADER_H

#include "meshers/GreedyMesher.h"

namespace Ogre{
    class ManualObject;
}

namespace MeshLoader {    
    void loadMesh(Ogre::ManualObject *manual, VerticesAndFaces quads);
};

#endif	/* MESHLOADER_H */

