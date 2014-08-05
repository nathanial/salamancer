/* 
 * File:   TerrainAPI.cpp
 * Author: nathan
 * 
 * Created on August 4, 2014, 10:59 PM
 */

#include "TerrainAPI.h"
#include <iostream>

using namespace API;

bool TerrainRenderFunction::Execute(
    const CefString& name, 
    CefRefPtr<CefV8Value> object, 
    const CefV8ValueList& arguments, 
    CefRefPtr<CefV8Value>& retval, 
    CefString& exception)
{
    if (name == "renderTerrain") {
        std::cout << "Render Terrain" << std::endl;
        return true;
    }
    return false;
}