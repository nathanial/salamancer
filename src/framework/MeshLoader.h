/* 
 * File:   MeshLoader.h
 * Author: nathan
 *
 * Created on July 11, 2014, 12:53 AM
 */

#ifndef MESHLOADER_H
#define	MESHLOADER_H

#include "meshers/Mesher.h"
#include "meshers/GreedyMesher.h"
#include <functional>
#include <string>

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

namespace MeshLoader {    
    void loadMesh(Ogre::ManualObject *manual, VerticesAndFaces quads);
};

#endif	/* MESHLOADER_H */

