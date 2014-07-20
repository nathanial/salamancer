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
    
    CefDoMessageLoopWork();
    
    return true;
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect){
    rect = CefRect(0, 0, renderTexture->getWidth(), renderTexture->getHeight());
    return true;
}

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height){
    Ogre::HardwarePixelBufferSharedPtr texBuf = renderTexture->getBuffer();
    texBuf->lock(Ogre::HardwareBuffer::HBL_DISCARD);
    memcpy(texBuf->getCurrentLock().data, buffer, width*height*4);
    texBuf->unlock();
}


