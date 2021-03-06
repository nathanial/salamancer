/* 
 * File:   AppContext.h
 * Author: nathan
 *
 * Created on October 2, 2014, 7:55 PM
 */

#ifndef APPCONTEXT_H
#define	APPCONTEXT_H

#include <memory>

#include "framework/World.h"

namespace Ogre {
    class Camera;
}

class AppContext {
public:
    Ogre::Camera *camera;
    WorldPtr world;
};

typedef std::shared_ptr<AppContext> AppContextPtr;

#endif	/* APPCONTEXT_H */

