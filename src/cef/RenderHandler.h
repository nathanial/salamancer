/* 
 * File:   RenderHandler.h
 * Author: nathan
 *
 * Created on July 20, 2014, 1:42 AM
 */

#ifndef RENDERHANDLER_H
#define	RENDERHANDLER_H

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"

#include <OGRE/OgreEntity.h>
#include <OGRE/OgreHardwarePixelBuffer.h>
#include <OGRE/OgreMeshManager.h>
#include <OGRE/OgreRenderWindow.h>
#include <OGRE/OgreRoot.h>


class RenderHandler : public Ogre::FrameListener, public CefRenderHandler {
    public:
        Ogre::TexturePtr renderTexture;
        
        RenderHandler(Ogre::TexturePtr texture)
        : renderTexture(texture)
        {
        }
        
        bool frameStarted(const Ogre::FrameEvent &evt);
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);
        void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height);
        
        IMPLEMENT_REFCOUNTING(RenderHandler);
};

#endif	/* RENDERHANDLER_H */

