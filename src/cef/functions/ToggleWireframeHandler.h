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

namespace API {
    class ToggleWireframeHandler : public CefMessageRouterBrowserSide::Handler {

    public:

        ToggleWireframeHandler();

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

