/* 
 * File:   AppContext.h
 * Author: nathan
 *
 * Created on September 28, 2014, 8:28 PM
 */

#ifndef APPCONTEXT_H
#define	APPCONTEXT_H

#include <memory>

namespace Ogre {
    class Camera;
}

namespace API {
    class AppContext {
    private:
        Ogre::Camera* camera;
    
    public:
        
        Ogre::Camera* GetCamera();
        void SetCamera(Ogre::Camera* camera);
    };
    
    typedef std::shared_ptr<AppContext> AppContextPtr;
}

#endif	/* APPCONTEXT_H */

