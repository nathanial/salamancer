/* 
 * File:   App.cpp
 * Author: nathan
 * 
 * Created on July 29, 2014, 1:13 AM
 */

#include "App.h"
#include "include/cef_client.h"
#include <iostream>
#include "AutoFunctionForwarder.h"

void App::OnWebKitInitialized() {
}

void App::OnContextCreated(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) {
    
    AutoFunctionDescription toggleWireframeDescription;
    toggleWireframeDescription.name = "toggleWireframe";
    toggleWireframeDescription.arguments.push_back(AFA_BOOL);
    
    AutoFunctionDescription createVoxelDescription;
    createVoxelDescription.name = "createVoxel";

    this->CreateAutoFunction(browser, frame, context, toggleWireframeDescription);
    this->CreateAutoFunction(browser, frame, context, createVoxelDescription);
}

void App:: OnContextReleased(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) {
}

void App::SetCamera(Ogre::Camera* camera){
}

void App::CreateAutoFunction(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context, AutoFunctionDescription description) {
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    CefRefPtr<CefV8Handler> handler = new AutoFunctionForwarder(browser, frame, description);
    // Create the "myfunc" function.
    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction(description.name, handler);

    // Add the "myfunc" function to the "window" object.
    object->SetValue(description.name, func, V8_PROPERTY_ATTRIBUTE_NONE);
}