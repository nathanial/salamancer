/* 
 * File:   RenderHandler.cpp
 * Author: nathan
 * 
 * Created on July 20, 2014, 1:42 AM
 * 
 * 
 */

#include <iostream>
#include "RenderHandler.h"

bool RenderHandler::frameStarted(const Ogre::FrameEvent &evt){
    if(Ogre::Root::getSingletonPtr()->getAutoCreatedWindow()->isClosed()){
        return false;
    }
    
    //renderNode->yaw(Ogre::Radian(evt.timeSinceLastFrame)*Ogre::Math::PI*2.*(1./10.));
    
    std::cout << "Do Work" << std::endl;
    CefDoMessageLoopWork();
    
    return true;
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect){
    rect = CefRect(0, 0, renderTexture->getWidth(), renderTexture->getHeight());
    return true;
}

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height){
    std::cout << "PAINT" << std::endl;
    Ogre::HardwarePixelBufferSharedPtr texBuf = renderTexture->getBuffer();
    texBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    memcpy(texBuf->getCurrentLock().data, buffer, width*height*4);
    texBuf->unlock();
}


