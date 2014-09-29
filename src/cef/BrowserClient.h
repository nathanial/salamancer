/* 
 * File:   BrowserClient.h
 * Author: nathan
 *
 * Created on July 20, 2014, 1:49 AM
 */

#ifndef BROWSERCLIENT_H
#define	BROWSERCLIENT_H

#include "include/cef_client.h"
#include "RenderHandler.h"
#include "LifeSpanHandler.h"

class BrowserClient : public CefClient {
public: 
    BrowserClient(RenderHandler *renderHandler, LifeSpanHandler *lifespanHandler) : renderHandler(renderHandler), lifespanHandler(lifespanHandler) {
    }
    
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() {
        return renderHandler;
    }
    
    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() {
        return lifespanHandler;
    }

    
    CefRefPtr<CefRenderHandler> renderHandler;
    CefRefPtr<CefLifeSpanHandler> lifespanHandler;
    
    IMPLEMENT_REFCOUNTING(BrowserClient);
};

#endif	/* BROWSERCLIENT_H */

