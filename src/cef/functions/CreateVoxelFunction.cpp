#include "cef/functions/CreateVoxelFunction.h"

API::CreateVoxelFunction::CreateVoxelFunction() {
    
}

bool API::CreateVoxelFunction::Execute(const CefString& name, CefRefPtr<CefV8Value> object, const CefV8ValueList& arguments, CefRefPtr<CefV8Value>& retval, CefString& exception) {

    if (name == "createVoxel") {
        if (arguments.size() < 4) {
            exception = "Insufficient Arguments";
            return false;
        }
        for (int i = 0; i < 4; i++) {
            if (!arguments[i]->IsInt()) {
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

void API::CreateVoxelFunction::CreateVoxel(int type, int x, int y, int z) {

}