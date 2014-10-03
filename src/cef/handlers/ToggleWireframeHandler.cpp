/* 
 * File:   ToggleWireframeHandler.cpp
 * Author: nathan
 * 
 * Created on October 2, 2014, 7:51 PM
 */

#include "ToggleWireframeHandler.h"

#include <iostream>
#include <OGRE/OgreCamera.h>

void ToggleWireframeHandler::Handle(CefRefPtr<CefProcessMessage> message){
    std::cout << "Toggle Wireframe Handler" << std::endl;
    
    auto arguments = message->GetArgumentList();
    
    auto camera = this->context->camera;
    auto enabled = arguments->GetBool(1);
    
    if(camera == nullptr){
        throw std::runtime_error("Camera is null");
    }
    
    if(enabled){
        camera->setPolygonMode(Ogre::PM_WIREFRAME);
    } else {
        camera->setPolygonMode(Ogre::PM_SOLID);
    }
}

std::string ToggleWireframeHandler::GetFunctionName() {
    return "toggleWireframe";
}