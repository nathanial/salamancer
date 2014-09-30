/* 
 * File:   ClientHandler.h
 * Author: nathan
 *
 * Created on September 28, 2014, 10:27 PM
 */

#ifndef CLIENTHANDLER_H
#define	CLIENTHANDLER_H

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"
#include "include/cef_render_process_handler.h"

#include "cef/functions/ToggleWireframeHandler.h"

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

class ClientHandler : public CefClient, public CefLifeSpanHandler, public CefRenderHandler, public Ogre::FrameListener{
private:
    
    CefRefPtr<API::ToggleWireframeHandler> _toggleWireframeHandler;
    CefRefPtr<CefMessageRouterBrowserSide> _messageRouter;

    Ogre::TexturePtr renderTexture;
    OIS::Mouse* mouse;
    Ogre::RenderWindow *window;
    CefRefPtr<CefBrowser> browser;
    Ogre::Timer *keyTimer;

    bool hasKeyBeenPressed = false;
    bool repeatStarted = false;

    CefKeyEvent keyEvent;
        
public:
    
    ClientHandler(Ogre::TexturePtr texture, Ogre::RenderWindow *window, OIS::Mouse* mouse, Ogre::Camera* camera)
    : renderTexture(texture), window(window), mouse(mouse), keyTimer(new Ogre::Timer()) {
        _toggleWireframeHandler = new API::ToggleWireframeHandler(camera);
    }

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {
        return this;
    }

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
        return this;
    }
    
    virtual bool OnProcessMessageReceived(
            CefRefPtr<CefBrowser> browser,
            CefProcessId source_process,
            CefRefPtr<CefProcessMessage> message) OVERRIDE;
    
    
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    bool frameStarted(const Ogre::FrameEvent &evt) OVERRIDE;
    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) OVERRIDE;
    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) OVERRIDE;
    void OnCursorChange(CefRefPtr<CefBrowser> browser, CefCursorHandle cursor) OVERRIDE;

    void SetBrowser(CefRefPtr<CefBrowser> browser);

    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);
    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    
    IMPLEMENT_REFCOUNTING(ClientHandler);
};

#endif	/* CLIENTHANDLER_H */

