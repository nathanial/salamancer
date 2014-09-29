/* 
 * File:   CreateVoxelFunction.h
 * Author: nathan
 *
 * Created on September 28, 2014, 6:10 PM
 */

#ifndef CREATEVOXELFUNCTION_H
#define	CREATEVOXELFUNCTION_H

#include "include/cef_client.h"

namespace API {
    class CreateVoxelFunction : public CefV8Handler {
    public:
        CreateVoxelFunction();

        virtual bool Execute(const CefString& name,
                CefRefPtr<CefV8Value> object,
                const CefV8ValueList& arguments,
                CefRefPtr<CefV8Value>& retval,
                CefString& exception) OVERRIDE;
        void CreateVoxel(int type, int x, int y, int z);

        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(CreateVoxelFunction);
    };    
}

#endif	/* CREATEVOXELFUNCTION_H */

