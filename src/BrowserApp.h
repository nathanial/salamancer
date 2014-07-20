/* 
 * File:   BrowserApp.h
 * Author: nathan
 *
 * Created on July 19, 2014, 10:42 PM
 */

#ifndef BROWSERAPP_H
#define	BROWSERAPP_H

#include "include/cef_app.h"

class BrowserApp: public CefApp, public CefBrowserProcessHandler {
    public:
        virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE {
            return this;
        }
        
        virtual void OnContextInitialized() OVERRIDE;
        
    private:
        IMPLEMENT_REFCOUNTING(BrowserApp);
};

#endif	/* BROWSERAPP_H */

