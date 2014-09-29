
#include "cef/functions/ToggleWireframeFunction.h"

API::ToggleWireframeFunction::ToggleWireframeFunction(Ogre::Camera* camera) : mCamera(camera) {}

bool API::ToggleWireframeFunction::Execute(
        const CefString& name,
        CefRefPtr<CefV8Value> object, 
        const CefV8ValueList& arguments, 
        CefRefPtr<CefV8Value>& retval, 
        CefString& exception) {
    
    if (name == "toggleWireframe") {
        if (arguments.size() < 1) {
            exception = "Insufficient Arguments";
            return false;
        }
        if (!arguments[0]->IsBool()) {
            exception = "First argument must be a boolean";
            return false;
        }

        bool enabled = arguments[0]->GetBoolValue();

        this->ToggleWireframe(enabled);
        return true;
    }
    
}

void ToggleWireframeFunction::ToggleWireframe(bool enabled){
    
}