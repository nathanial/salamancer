/* 
 * File:   ToggleWireframeFunction.h
 * Author: nathan
 *
 * Created on September 28, 2014, 6:12 PM
 */

#ifndef TOGGLEWIREFRAMEFUNCTION_H
#define	TOGGLEWIREFRAMEFUNCTION_H

#include "include/cef_client.h"
#include "cef/AppContext.h"

namespace API {
    class ToggleWireframeFunction : public CefV8Handler {
    private:
        API::AppContextPtr context;

    public:

        ToggleWireframeFunction(API::AppContextPtr context);

        virtual bool Execute(const CefString& name,
                CefRefPtr<CefV8Value> object,
                const CefV8ValueList& arguments,
                CefRefPtr<CefV8Value>& retval,
                CefString& exception) OVERRIDE;

        IMPLEMENT_REFCOUNTING(ToggleWireframeFunction);
    };
    
}

#endif	/* TOGGLEWIREFRAMEFUNCTION_H */

