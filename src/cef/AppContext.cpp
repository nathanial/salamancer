#include "AppContext.h"

using namespace API;

Ogre::Camera* AppContext::GetCamera(){
    return this->camera;
}

void AppContext::SetCamera(Ogre::Camera* camera){
    this->camera = camera;
}