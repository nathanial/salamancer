/* 
 * File:   TerrainAPI.cpp
 * Author: nathan
 * 
 * Created on August 4, 2014, 10:59 PM
 */

#include "TerrainAPI.h"
#include <iostream>
#include "noise/noise.h"
#include "noiseutils.h"

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
    module::Perlin perlin;
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(perlin);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(256, 256);
    heightMapBuilder.SetBounds(2.0, 6.0, 1.0, 5.0);
    heightMapBuilder.Build();
    
    utils::RendererImage renderer;
    utils::Image image;
    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);
    renderer.Render();
    
    utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("/home/nathan/Projects/salamancer/dist/bin/terrain.bmp");
    writer.WriteDestFile();
    return CefV8Value::CreateString("../terrain.bmp");
}