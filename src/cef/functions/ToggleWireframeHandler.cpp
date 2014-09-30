
#include <OGRE/OgreCamera.h>

#include "include/cef_app.h"
#include "include/cef_render_process_handler.h"
#include "cef/functions/ToggleWireframeHandler.h"

API::ToggleWireframeHandler::ToggleWireframeHandler(Ogre::Camera *camera) 
: camera(camera)
{
}

bool API::ToggleWireframeHandler::OnQuery(
        CefRefPtr<CefBrowser> browser,
        CefRefPtr<CefFrame> frame,
        int64 query_id,
        const CefString& request,
        bool persistent,
        CefRefPtr<Callback> callback)
{
    if(request.ToString() == "enableWireframe"){
        this->camera->setPolygonMode(Ogre::PM_WIREFRAME);
        return true;
    } else if (request.ToString() == "disableWireframe"){
        this->camera->setPolygonMode(Ogre::PM_SOLID);
        return true;
    } else {
        std::cout << "Didn't recognize: " << request.ToString() << std::endl;
        return false;
    }
//
//    if (name == "toggleWireframe") {
//        if (arguments.size() < 1) {
//            exception = "Insufficient Arguments";
//            return false;
//        }
//        if (!arguments[0]->IsBool()) {
//            exception = "First argument must be a boolean";
//            return false;
//        }
//
//        bool enabled = arguments[0]->GetBoolValue();
//
//        Ogre::Camera* camera = context->GetCamera();
//        if (camera != 0) {
//            if (enabled) {
//                camera->setPolygonMode(Ogre::PM_WIREFRAME);
//            } else {
//                camera->setPolygonMode(Ogre::PM_SOLID);
//            }
//            return true;
//        } else {
//            exception = "Camera not set";
//            return false;
//        }
//    }
}