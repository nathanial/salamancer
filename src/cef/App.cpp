/* 
 * File:   App.cpp
 * Author: nathan
 * 
 * Created on July 29, 2014, 1:13 AM
 */

#include "App.h"
#include "include/cef_client.h"
#include "functions/ToggleWireframeHandler.h"
#include <iostream>

void App::OnWebKitInitialized() {
    // Create the renderer-side router for query handling.
    CefMessageRouterConfig config;
    messageRouter = CefMessageRouterRendererSide::Create(config);
}

void App::OnContextCreated(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) {
    messageRouter->OnContextCreated(browser, frame, context);
}

void App:: OnContextReleased(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) {
    messageRouter->OnContextReleased(browser, frame, context);
}

void App::SetCamera(Ogre::Camera* camera){
    this->context->SetCamera(camera);
}

