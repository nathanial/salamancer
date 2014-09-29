/* 
 * File:   LifeSpanHandler.h
 * Author: nathan
 *
 * Created on September 28, 2014, 9:34 PM
 */

#ifndef LIFESPANHANDLER_H
#define	LIFESPANHANDLER_H

#include "include/cef_app.h"
#include "include/cef_client.h"
#include "include/cef_render_handler.h"
#include "include/cef_life_span_handler.h"
#include "include/cef_render_process_handler.h"

class LifeSpanHandler : public CefLifeSpanHandler {

public:
    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
    
    IMPLEMENT_REFCOUNTING(LifeSpanHandler);
};

#endif	/* LIFESPANHANDLER_H */

