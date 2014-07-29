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
#include "include/cef_render_process_handler.h"

#include <OgreEntity.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreMeshManager.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include <OgreTimer.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

namespace OIS {
    class Mouse;
}

class RenderHandler : public Ogre::FrameListener, public CefRenderHandler {
    public:
        Ogre::TexturePtr renderTexture;
        OIS::Mouse* mouse;
        Ogre::RenderWindow *window;
        CefRefPtr<CefBrowser> browser;
        Ogre::Timer *keyTimer;
        
        bool hasKeyBeenPressed = false;
        bool repeatStarted = false;

        CefKeyEvent keyEvent;
        
        RenderHandler(Ogre::TexturePtr texture, Ogre::RenderWindow *window, OIS::Mouse* mouse)
        : renderTexture(texture), window(window), mouse(mouse), keyTimer(new Ogre::Timer())
        {
        }
        
        bool frameStarted(const Ogre::FrameEvent &evt) OVERRIDE;
        bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) OVERRIDE;
        void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) OVERRIDE;
        void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor) OVERRIDE;
        
        void SetBrowser(CefRefPtr<CefBrowser> browser){
            this->browser = browser;
        }
        
        bool keyPressed( const OIS::KeyEvent &arg );
        bool keyReleased( const OIS::KeyEvent &arg );
        bool mouseMoved( const OIS::MouseEvent &arg );
        bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id);
        bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id);
        
        IMPLEMENT_REFCOUNTING(RenderHandler);
};

#endif	/* RENDERHANDLER_H */