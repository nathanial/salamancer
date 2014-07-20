/* 
 * File:   SalamancerHandler.cpp
 * Author: nathan
 * 
 * Created on July 19, 2014, 10:47 PM
 */

#include "SalamancerHandler.h"

#include <sstream>
#include <string>

#include <assert.h>

#include "include/cef_task.h"
#include "include/cef_app.h"
#include "include/cef_runnable.h"

namespace {
    SalamancerHandler * g_instance = NULL;
}

SalamancerHandler::SalamancerHandler() : is_closing(false){
    assert(!g_instance);
    g_instance = this;
}

SalamancerHandler::~SalamancerHandler(){
    g_instance = NULL;
}

SalamancerHandler* SalamancerHandler::GetInstance(){
    return g_instance;
}

void SalamancerHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser){
    assert(CefCurrentlyOn(TID_UI));
    
    browser_list.push_back(browser);
}

bool SalamancerHandler::DoClose(CefRefPtr<CefBrowser> browser){
    assert(CefCurrentlyOn(TID_UI));

    if(browser_list.size() == 1){
        is_closing = true;
    }
    
    return false;
}

void SalamancerHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser){
    assert(CefCurrentlyOn(TID_UI));
    
    BrowserList::iterator bit = browser_list.begin();
    for(; bit != browser_list.end(); ++bit){
        if((*bit)->IsSame(browser)){
            browser_list.erase(bit);
            break;
        }
    }
    
    if(browser_list.empty()){
        CefQuitMessageLoop();
    }
}

void SalamancerHandler::OnLoadError(CefRefPtr<CefBrowser> browser,
                                    CefRefPtr<CefFrame> frame,
                                    ErrorCode errorCode,
                                    const CefString& errorText,
                                    const CefString& failedUrl){
    assert(CefCurrentlyOn(TID_UI));
    
    if(errorCode == ERR_ABORTED){
        return;
    }
    
    std::stringstream ss;
    ss << "h1>oops</h1>";
    frame->LoadString(ss.str(), failedUrl);
}

void SalamancerHandler::CloseAllBrowsers(bool force_close){
    if(!CefCurrentlyOn(TID_UI)){
        CefPostTask(TID_UI, NewCefRunnableMethod(this, &SalamancerHandler::CloseAllBrowsers, force_close));
        return;
    }
    
    if(browser_list.empty()){
        return;
    }
    
    BrowserList::const_iterator it = browser_list.begin();
    for(; it != browser_list.end(); ++it){
        (*it)->GetHost()->CloseBrowser(force_close);
    }
}

void SalamancerHandler::OnTitleChange(CefRefPtr<CefBrowser> browser, const CefString& title){
    
}