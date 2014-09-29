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

void App::OnContextCreated(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefV8Context> context) {
    
}

void App::SetCamera(Ogre::Camera* camera){
    this->context->SetCamera(camera);
}

