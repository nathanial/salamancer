/* 
 * File:   API.h
 * Author: nathan
 *
 * Created on July 28, 2014, 11:53 PM
 */

#ifndef API_H
#define	API_H

#include "include/cef_client.h"

#include <iostream>

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
                if(arguments.size() < 4){
                    exception = "Insufficient Arguments";
                    return false;
                }
                for(int i = 0 ; i < 4; i++){
                    if(!arguments[i]->IsInt()){
                        exception = "Arguments must be integers";
                        return false;
                    }
                }
                int x = arguments[0]->GetIntValue();
                int y = arguments[1]->GetIntValue();
                int z = arguments[2]->GetIntValue();
                int type = arguments[3]->GetIntValue();

                this->CreateVoxel(type, x, y, z);
                return true;
          }
          return false;
        }
        
        void CreateVoxel(int type, int x, int y, int z){
            
        }

        // Provide the reference counting implementation for this class.
        IMPLEMENT_REFCOUNTING(CreateVoxelFunction);
    };
    
    
    class ToggleWireframeFunction : public CefV8Handler {
    public:
        
        ToggleWireframeFunction() {}
        
        virtual bool Execute(const CefString& name,
                             CefRefPtr<CefV8Value> object, 
                             const CefV8ValueList& arguments, 
                             CefRefPtr<CefV8Value>& retval, 
                             CefString& exception) OVERRIDE {
            if (name == "toggleWireframe"){
                if(arguments.size() < 1){
                    exception = "Insufficient Arguments";
                    return false;
                }
                if(!arguments[0]->IsBool()){
                    exception = "First argument must be a boolean";
                    return false;
                }
                
                bool enabled = arguments[0]->GetBoolValue();
                
                this->ToggleWireframe(enabled);
                return true;
            }
        }
        
        void ToggleWireframe(bool enabled){
            std::cout << "Toggle Thy Wireframe" << std::endl;
        }
        
        IMPLEMENT_REFCOUNTING(ToggleWireframeFunction);
    };
    
    
}

#endif	/* API_H */

