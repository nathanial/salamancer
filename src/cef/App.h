/* 
 * File:   App.h
 * Author: nathan
 *
 * Created on July 29, 2014, 1:13 AM
 */

#ifndef APP_H
#define	APP_H

#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"

namespace Ogre {
    class Camera;
}

class App : public CefApp, public CefRenderProcessHandler  {
    public:
        
    Ogre::Camera* mCamera;
        
        
    virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE {
        return this;
    }
    
    virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
                              CefRefPtr<CefFrame> frame,
                              CefRefPtr<CefV8Context> context) OVERRIDE;
    
    IMPLEMENT_REFCOUNTING(App);
};

#endif	/* APP_H */

