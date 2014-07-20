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

class BrowserClient : public CefClient {
public: 
    BrowserClient(RenderHandler *renderHandler) : renderHandler(renderHandler) {
    }
    
    virtual CefRefPtr<CefRenderHandler> GetRenderHandler() {
        return renderHandler;
    }
    
    CefRefPtr<CefRenderHandler> renderHandler;
    
    IMPLEMENT_REFCOUNTING(BrowserClient);
};

#endif	/* BROWSERCLIENT_H */

