/* 
 * File:   ToggleWireframeFunction.h
 * Author: nathan
 *
 * Created on September 28, 2014, 6:12 PM
 */

#ifndef TOGGLEWIREFRAMEHANDLER_H
#define	TOGGLEWIREFRAMEHANDLER_H

#include "include/cef_client.h"
#include "cef/AppContext.h"
#include "include/wrapper/cef_message_router.h"

namespace Ogre {
    class Camera;
}

namespace API {
    class ToggleWireframeHandler : public CefMessageRouterBrowserSide::Handler {
    private:
        Ogre::Camera *camera;

    public:

        ToggleWireframeHandler(Ogre::Camera *camera);

        virtual bool OnQuery(CefRefPtr<CefBrowser> browser,
                CefRefPtr<CefFrame> frame,
                int64 query_id,
                const CefString& request,
                bool persistent,
                CefRefPtr<Callback> callback) OVERRIDE;

        IMPLEMENT_REFCOUNTING(ToggleWireframeHandler);
    };
    
}

#endif	/* TOGGLEWIREFRAMEFUNCTION_H */

