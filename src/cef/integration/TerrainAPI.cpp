/* 
 * File:   TerrainAPI.cpp
 * Author: nathan
 * 
 * Created on August 4, 2014, 10:59 PM
 */

#include "TerrainAPI.h"
#include <iostream>
#include "noise/noise.h"
#include "framework/terrain/noiseutils.h"

using namespace API;

bool TerrainRenderFunction::Execute(
    const CefString& name, 
    CefRefPtr<CefV8Value> object, 
    const CefV8ValueList& arguments, 
    CefRefPtr<CefV8Value>& retval, 
    CefString& exception)
{
    if (name == "renderTerrain") {
        if(arguments.size() <= 0){
            exception = "Not enough arguments";
            return true;
        }
        if(!arguments[0]->IsObject()){
            exception = "First argument to renderTerrain must be an object.";
            return true;
        }
        CefRefPtr<CefV8Value> options = arguments[0];
        
        retval = renderTerrain();
        return true;
    }
    return false;
}

CefRefPtr<CefV8Value> TerrainRenderFunction::renderTerrain(){
    return CefV8Value::CreateString("http://indervilla.com/home/2013/01/Frog-After-Diner-HD.jpg");
}