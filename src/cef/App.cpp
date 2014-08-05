/* 
 * File:   App.cpp
 * Author: nathan
 * 
 * Created on July 29, 2014, 1:13 AM
 */

#include "App.h"
#include "include/cef_v8.h"
#include <iostream>

#include "cef/integration/TerrainAPI.h"

    
void App::OnContextCreated(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           CefRefPtr<CefV8Context> context) {
    std::cout << "On Context Created" << std::endl;
    CefRefPtr<CefV8Value> object = context->GetGlobal();
    CefRefPtr<CefV8Value> native = CefV8Value::CreateObject(NULL);
    context->GetGlobal()->SetValue("Native",native, V8_PROPERTY_ATTRIBUTE_NONE);
    CefRefPtr<CefV8Handler> handler = new API::TerrainRenderFunction();
    native->SetValue("renderTerrain", CefV8Value::CreateFunction("renderTerrain", handler), V8_PROPERTY_ATTRIBUTE_NONE);
}

