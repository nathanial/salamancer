/* 
 * File:   TerrainAPI.h
 * Author: nathan
 *
 * Created on August 4, 2014, 10:59 PM
 */

#ifndef TERRAINAPI_H
#define	TERRAINAPI_H

#include "include/cef_v8.h"
#include "include/cef_client.h"

namespace API {
    class TerrainRenderFunction : public CefV8Handler {
    public:
        TerrainRenderFunction() {}
        
        virtual bool Execute(const CefString& name,
                             CefRefPtr<CefV8Value> object,
                             const CefV8ValueList& arguments,
                             CefRefPtr<CefV8Value>& retval,
                             CefString& exception) OVERRIDE; 
        
        IMPLEMENT_REFCOUNTING(TerrainRenderFunction);
        
    private:
        CefRefPtr<CefV8Value> renderTerrain();
    };
};

#endif	/* TERRAINAPI_H */

