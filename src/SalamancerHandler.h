/* 
 * File:   SalamancerHandler.h
 * Author: nathan
 *
 * Created on July 19, 2014, 10:47 PM
 */

#ifndef SALAMANCERHANDLER_H
#define	SALAMANCERHANDLER_H

#include "include/cef_client.h"
#include <list>

class SalamancerHandler : public CefClient, 
                          public CefDisplayHandler,
                          public CefLifeSpanHandler,
                          public CefLoadHandler {
    
    public:

        SalamancerHandler();
        ~SalamancerHandler();
        
        static SalamancerHandler* GetInstance();
        
        virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE {
            return this;
        }
        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
            return this;
        }
        virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
            return this;
        }
        
        virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
                                   const CefString& title) OVERRIDE; 
        
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
        virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
        
        virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                                 CefRefPtr<CefFrame> frame,
                                 ErrorCode errorCode,
                                 const CefString& errorText,
                                 const CefString& failedUrl
                                 ) OVERRIDE;
        
        void CloseAllBrowsers(bool force_close);
        
        bool IsClosing() const { return is_closing; }
        
    private:
        
        typedef std::list<CefRefPtr<CefBrowser> > BrowserList;
        BrowserList browser_list;
        
        bool is_closing;
        
        IMPLEMENT_REFCOUNTING(SalamancerHandler);
};

#endif	/* SALAMANCERHANDLER_H */

