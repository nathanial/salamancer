/* 
 * File:   App.cpp
 * Author: nathan
 * 
 * Created on July 29, 2014, 1:13 AM
 */

#include "App.h"
#include "API.h"
#include <iostream>

    
void App::OnContextCreated(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefV8Context> context) {
    std::cout << "On Context Created" << std::endl;
    CefRefPtr<CefV8Value> object = context->GetGlobal();

    CefRefPtr<CefV8Handler> handler = new API::CreateVoxelFunction();
    object->SetValue("createVoxel",
                       CefV8Value::CreateFunction("createVoxel", handler),
                       V8_PROPERTY_ATTRIBUTE_NONE);
}

