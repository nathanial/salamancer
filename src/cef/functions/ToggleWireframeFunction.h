/* 
 * File:   ToggleWireframeFunction.h
 * Author: nathan
 *
 * Created on September 28, 2014, 6:12 PM
 */

#ifndef TOGGLEWIREFRAMEFUNCTION_H
#define	TOGGLEWIREFRAMEFUNCTION_H

#include "include/cef_client.h"

namespace Ogre {
    class Camera;
}

namespace API {
    class ToggleWireframeFunction : public CefV8Handler {
    private:
        Ogre::Camera* mCamera;

    public:

        ToggleWireframeFunction(Ogre::Camera* camera);

        virtual bool Execute(const CefString& name,
                CefRefPtr<CefV8Value> object,
                const CefV8ValueList& arguments,
                CefRefPtr<CefV8Value>& retval,
                CefString& exception) OVERRIDE;

        void ToggleWireframe(bool enabled);

        IMPLEMENT_REFCOUNTING(ToggleWireframeFunction);
    };
    
}

#endif	/* TOGGLEWIREFRAMEFUNCTION_H */

