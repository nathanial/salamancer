/* 
 * File:   API.h
 * Author: nathan
 *
 * Created on July 28, 2014, 11:53 PM
 */

#ifndef API_H
#define	API_H

#include "include/cef_client.h"

namespace API {
    class CreateVoxelFunction : public CefV8Handler {
    public:
        CreateVoxelFunction() {}

        virtual bool Execute(const CefString& name,
                             CefRefPtr<CefV8Value> object,
                             const CefV8ValueList& arguments,
                             CefRefPtr<CefV8Value>& retval,
                             CefString& exception) OVERRIDE {
          if (name == "createVoxel") {
            // Return my string value.
            retval = CefV8Value::CreateString("Make a Voxel");
            return true;
          }

          // Function does not exist.
          return false;
        }

        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(CreateVoxelFunction);
    };
    
    
}

#endif	/* API_H */

