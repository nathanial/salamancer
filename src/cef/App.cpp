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
    createVoxelDescription.arguments = {AFA_INT, AFA_INT, AFA_INT, AFA_INT};
    
    AutoFunctionDescription clearVoxelsDescription;
    clearVoxelsDescription.name = "clearVoxels";
    clearVoxelsDescription.arguments = {};
    
    AutoFunctionDescription defineVoxelHandlerDescription;
    defineVoxelHandlerDescription.name = "defineVoxel";
    defineVoxelHandlerDescription.arguments = { AFA_STRING, AFA_STRING, AFA_STRING, AFA_STRING, AFA_BOOL };
    
    AutoFunctionDescription runLengthCreateVoxelsDescription;
    runLengthCreateVoxelsDescription.name = "createVoxels";
    runLengthCreateVoxelsDescription.arguments = { AFA_INT, AFA_INT, AFA_INT, AFA_STRING };
    
    this->CreateAutoFunction(browser, frame, context, toggleWireframeDescription);
    this->CreateAutoFunction(browser, frame, context, createVoxelDescription);
    this->CreateAutoFunction(browser, frame, context, clearVoxelsDescription);
    this->CreateAutoFunction(browser, frame, context, defineVoxelHandlerDescription);
    this->CreateAutoFunction(browser, frame, context, runLengthCreateVoxelsDescription);
}

void App:: OnContextReleased(CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        CefRefPtr<CefV8Context> context) {
}

void App::CreateAutoFunction(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context, AutoFunctionDescription description) {
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    CefRefPtr<CefV8Handler> handler = new AutoFunctionForwarder(browser, frame, description);
    // Create the "myfunc" function.
    CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction(description.name, handler);

    // Add the "myfunc" function to the "window" object.
    object->SetValue(description.name, func, V8_PROPERTY_ATTRIBUTE_NONE);
}

void App::OnRegisterCustomSchemes(CefRefPtr<CefSchemeRegistrar> registrar) {
//    if(!registrar->AddCustomScheme("batch", true, false, false)){
//        throw "Could not add custom scheme";
//    }
}