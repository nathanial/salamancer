/* 
 * File:   BrowserApp.cpp
 * Author: nathan
 * 
 * Created on July 19, 2014, 10:42 PM
 */

#include "BrowserApp.h"

#include <assert.h>
#include <string>
#include "SalamancerHandler.h"
#include "include/cef_browser.h"
#include "include/cef_task.h"

void BrowserApp::OnContextInitialized() {
    assert(CefCurrentlyOn(TID_UI));
    
    CefWindowInfo window_info;
    
    CefRefPtr<SalamancerHandler> handler(new SalamancerHandler);
    
    CefBrowserSettings browser_settings;
    
    std::string url = "http://www.google.com";
    
    CefBrowserHost::CreateBrowser(window_info, handler.get(), url, browser_settings, NULL);
}

